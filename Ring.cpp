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
		lBuffer(BUFFER_SIZE), rBuffer(BUFFER_SIZE), lTrigger(Tags::LEFT_INDICATOR),
		rTrigger(Tags::RIGHT_INDICATOR) {
	trace("Clicker is here");
}

void InfiniteRing::reset() {
	left.reset();
	right.reset();
}

void InfiniteRing::setSampleRate(const float32 rate) {
	lTrigger.setDelay(rate,BUFFER_SIZE);
	rTrigger.setDelay(rate,BUFFER_SIZE);
	trace("Sample rate is ^0",rate);
}


void InfiniteRing::handleTrigger(TriggerState &trigger,const bool triggered) {
	if(triggered) trigger.set();

	switch(trigger.step()) {
	case TriggerState::SET:
		set(1,trigger.Tag());
		break;
	case TriggerState::RESET:
		set(0,trigger.Tag());
		break;
	default:
		break;
	}

	trigger.clear();
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
		auto raw = toFloat(diff.fCurrentValue);
		auto p = phaseArgument(diff,0,90,9001)*0.1f;
		trace("Setting phase to ^0 degrees (raw is ^1)",p*180.f/Pi,raw);
		left.setPhase(p);
		right.setPhase(p);
		break;
	}
	case Tags::MODE: {
		auto i = toInt(diff.fCurrentValue);
		auto m = static_cast<ProcessingMode>(i);
		trace("Mode is ^0 (^1)",i,m);
		left.setProcessingMode(m);
		right.setProcessingMode(m);
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
		auto r = toFloat(diff.fCurrentValue);
		auto l = scaledFloat(diff.fCurrentValue,-12.f,0.f);
		auto p = pow(10.f,l*0.1f);
		trace("Limiter scale is ^0 <=> ^1",r,l);
		left.setLimit(p);
		right.setLimit(p);
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
	bool lA=false;
	bool rA=false;
	switch(state) {
	case State::On:
		lA=left.process();
		rA=right.process();
		break;
	case State::Bypassed:
		lA=left.bypass();
		rA=right.bypass();
		break;
	default:
		break;
	}

	handleTrigger(lTrigger,lA);
	handleTrigger(rTrigger,rA);

}




} /* namespace click */
} /* namespace meromorph */
