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
	runningAngle=cx::One;
}



void ChannelProcessor::process() {
	auto n=read();
	if(n>0 && ! isSilent()) {
		for(auto i=0;i<BUFFER_SIZE;i++) cxbuffer[i]=cx32(buffer[i]*inputGain);
		hilbert.apply(cxbuffer,cxout);

		// put in the phase bit here

		for(auto i=0;i<BUFFER_SIZE;i++) {
			runningPhase *= phase;
			runningAngle *= angle;
			auto p = std::imag(runningPhase);
			cx32 z = cxout[i]*p;
			cx32 o = runningAngle / (cx::One - z);
			buffer[i]=std::real(o)*outputGain;
		}
		limiter.limit(buffer);
		write();
	}
}

void ChannelProcessor::bypass() {
	auto n=read();
	if(n>0) write();
}










} /* namespace ring */
} /* namespace meromorph */
