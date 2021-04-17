/*
 * Clicker.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#include "Ring.hpp"


namespace meromorph {
namespace ring {

float32 phaseArgument(const TJBox_PropertyDiff &diff,float32 minFreq,float32 maxFreq,uint32 N) {
	auto def = intRangeToFloat(diff.fCurrentValue,N,minFreq,maxFreq);
	return cx::deg2rad(def);
}


InfiniteRing::InfiniteRing() : RackExtension(), left("/audio_inputs/Left","/audio_outputs/Left"),
		right("/audio_inputs/Right","/audio_outputs/Right"),
		lBuffer(BUFFER_SIZE), rBuffer(BUFFER_SIZE) {
	trace("Clicker is here");
}

void InfiniteRing::reset() {
	left.reset();
	right.reset();
}


void InfiniteRing::processApplicationMessage(const TJBox_PropertyDiff &diff) {
	Tag tag = diff.fPropertyTag;

	switch(tag) {
	case kJBox_CustomPropertiesOnOffBypass:
		trace("On/off/bypass status change");
		state = static_cast<State>(toFloat(diff.fCurrentValue));
		break;
	case Tags::PHASE: {
		trace("phase fired");
		auto p = phaseArgument(diff,-45,45,9001);
		trace("Setting phase to ^0 degrees",p);
		left.setPhase(p);
		right.setPhase(p);
		break;
	}
	case Tags::ANGLE: {
		auto p = phaseArgument(diff,0,180,1801);
		trace("Setting angle to ^0 degrees",p);
		left.setAngle(p);
		right.setAngle(p);
		break;
	}

	case Tags::INPUT_GAIN: {
		auto a = intRangeToFloat(diff.fCurrentValue,101,0.f,1.f);
		trace("Amplitude is ^0",a);
		left.setInputGain(a);
		right.setInputGain(a);
		break;
	}
	case Tags::OUTPUT_GAIN: {
		auto a = clampedFloat(diff.fCurrentValue);
		left.setOutputGain(a);
		right.setOutputGain(a);
		break;
	}

	case Tags::LIMITER: {
		auto l = intRangeToFloat(diff.fCurrentValue,101,-12.f,0.f);
		trace("Limit is ^0",l);
		left.setLimit(l);
		right.setLimit(l);
		break;
	}
	case Tags::LIMITER_ONOFF: {
		auto l=toBool(diff.fCurrentValue);
		left.setLimiterOnOff(l);
		right.setLimiterOnOff(l);
		break;
	}
	case Tags::LIMITER_HARD_SOFT: {
		auto l=toBool(diff.fCurrentValue) ? Limiter::HARD : Limiter::SOFT;
		left.setLimiterMode(l);
		right.setLimiterMode(l);
		break;
	}



	case kJBox_AudioInputConnected:
		trace("Audio input");
		trace(diff.fPropertyRef.fKey);
		break;
	}

}


void InfiniteRing::process() {
	switch(state) {
	case State::On:
		left.process();
		right.process();
		break;
	case State::Bypassed:
		left.bypass();
		right.bypass();
		break;
	default:
		break;
	}
}




} /* namespace click */
} /* namespace meromorph */
