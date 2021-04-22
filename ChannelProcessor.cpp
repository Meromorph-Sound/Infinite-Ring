/*
 * ChannelProcessor.cpp
 *
 *  Created on: 4 Apr 2021
 *      Author: julianporter
 */

#include "ChannelProcessor.hpp"

namespace meromorph {
namespace ring {

ChannelProcessor::ChannelProcessor(const char *nameIn,const char *nameOut) :
				buffer(BUFFER_SIZE), cxbuffer(BUFFER_SIZE),
				cxout(BUFFER_SIZE), hilbert(BUFFER_SIZE) {
	input=JBox_GetMotherboardObjectRef(nameIn);
	output=JBox_GetMotherboardObjectRef(nameOut);
}

bool ChannelProcessor::inputConnected() const {
	auto ref = JBox_LoadMOMPropertyByTag(input,IN_CONN);
	if (JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}

bool ChannelProcessor::outputConnected() const {
	auto ref = JBox_LoadMOMPropertyByTag(output,OUT_CONN);
	if (JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}

uint32 ChannelProcessor::read() {
	if(!inputConnected()) return 0;
	auto ref = JBox_LoadMOMPropertyByTag(input, IN_BUFFER);
	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) JBox_GetDSPBufferData(ref, 0, length, buffer.data());



	return static_cast<int32>(length);
}

void ChannelProcessor::write() {
	auto ref = JBox_LoadMOMPropertyByTag(output, OUT_BUFFER);
	JBox_SetDSPBufferData(ref, 0, BUFFER_SIZE, buffer.data());

}

bool ChannelProcessor::isSilent() {
	for(auto it=buffer.begin();it!=buffer.end();it++) if(*it != 0.f) return false;
	return true;
}

void ChannelProcessor::reset() {
	hilbert.reset();
	runningPhase=cx::One;
}

cx32 ChannelProcessor::limit(const cx32 z) {
	return HARD_LIMIT*tanh(z/HARD_LIMIT);
}
float32 ChannelProcessor::limit(const float32 z) {
	return HARD_LIMIT*tanh(z/HARD_LIMIT);
}

void ChannelProcessor::processReal() {
	for(auto i=0;i<BUFFER_SIZE;i++) {
		runningPhase *= phase;
		buffer[i]=buffer[i]*inputGain*std::imag(runningPhase);
	}
	didLimit=limiter.limit(buffer);
	for(auto i=0;i<BUFFER_SIZE;i++) {
		auto frac = 1.f / (1.f - buffer[i]);
		buffer[i] = (frac-1.f)*outputGain;
	}
}

void ChannelProcessor::processSemiComplex() {
	for(auto i=0;i<BUFFER_SIZE;i++) {
		runningPhase *= phase;
		cxbuffer[i]=buffer[i]*inputGain*runningPhase;
	}
	didLimit=limiter.limit(cxbuffer);
	for(auto i=0;i<BUFFER_SIZE;i++) {
		auto frac = 1.f / (1.f - cxbuffer[i]);
		buffer[i] = std::real((frac-1.f)*outputGain);
	}
}

void ChannelProcessor::processComplex() {
	auto iG=inputGain/2.f;
	for(auto i=0;i<BUFFER_SIZE;i++) cxbuffer[i]=cx32(buffer[i]);
	hilbert.apply(cxbuffer,cxout);
	for(auto i=0;i<BUFFER_SIZE;i++) {
		runningPhase *= phase;
		cxout[i]=cxout[i]*runningPhase*iG;
	}
	didLimit=limiter.limit(cxout);
	for(auto i=0;i<BUFFER_SIZE;i++) {
		auto frac = cx::One / (cx::One - cxout[i]);
		buffer[i]=std::real(frac - cx::One)*outputGain;
	}
}


bool ChannelProcessor::process() {
	auto n=read();
	if(n>0 && ! isSilent()) {

		switch(mode) {
		case ProcessingMode::REAL:
			processReal();
			break;
		case ProcessingMode::SEMI_COMPLEX:
			processSemiComplex();
			break;
		case ProcessingMode::COMPLEX:
			processComplex();
			break;
		default:
			break;
		}



		write();
		return didLimit ;
	}
	return false;
}

bool ChannelProcessor::bypass() {
	auto n=read();
	if(n>0) write();
	return false;
}










} /* namespace ring */
} /* namespace meromorph */
