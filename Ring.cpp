/*
 * Clicker.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#include "Ring.hpp"


namespace meromorph {
namespace ring {



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
		auto p = cx::purePhase(toFloat(diff.fCurrentValue));
		left.setPhase(p);
		right.setPhase(p);
		break;
	}
	case Tags::OFFSET: {
		auto o = toFloat(diff.fCurrentValue);
		left.setOffset(o);
		right.setOffset(o);
		break;
	}
	case Tags::ANGLE: {
		auto a = cx::purePhase(-toFloat(diff.fCurrentValue));
		left.setAngle(a);
		right.setAngle(a);
		break;
	}

	case Tags::GAIN: {
		amplitude = clampedFloat(diff.fCurrentValue);
		trace("Amplitude is ^0",amplitude);
		break;
	}

	case Tags::LIMITER: {
		auto l = scaledFloat(diff.fCurrentValue,-12.f,0.f);
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
