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

uint32 ChannelProcessor::read(float32 *l) {
		if(!inputConnected()) return 0;
		auto ref = JBox_LoadMOMPropertyByTag(input, IN_BUFFER);
		auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(length>0) JBox_GetDSPBufferData(ref, 0, length, l);
		return static_cast<int32>(length);
	}

void ChannelProcessor::write(uint32 N,float32 *l) {
	if(N>0) {
		auto ref = JBox_LoadMOMPropertyByTag(output, OUT_BUFFER);
		JBox_SetDSPBufferData(ref, 0, N, l);
	}
}

void ChannelProcessor::reset() {
	hilbert.reset();
	runningPhase=cx::One;
}

void ChannelProcessor::process() {
	auto n=read(buffer.data());
	if(n>0) {
		for(auto i=0;i<BUFFER_SIZE;i++) cxbuffer[i]=cx32(buffer[i]);
		hilbert.apply(cxbuffer,cxout);

		// put in the phase bit here

		for(auto i=0;i<BUFFER_SIZE;i++) {
			runningPhase *= phase;
			auto p = std::imag(runningPhase);
			cx32 z = cxout[i]*p;
			cx32 o = angle / (cx::One - z);
			buffer[i]=std::real(o)-offset;
		}
		limiter.limit(buffer);
		write(BUFFER_SIZE,buffer.data());
	}
}

void ChannelProcessor::bypass() {
	auto n=read(buffer.data());
	if(n>0) write(BUFFER_SIZE,buffer.data());
}










} /* namespace ring */
} /* namespace meromorph */
