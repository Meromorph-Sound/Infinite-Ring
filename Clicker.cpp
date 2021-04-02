/*
 * Clicker.cpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#include "Clicker.hpp"


namespace meromorph {
namespace click {

void TriggerState::setDelay(const float32 sampleRate,const float32 BUFFER_SIZE) {
	auto chunkCount = sampleRate/(float32)BUFFER_SIZE;
		auto nChunks = chunkCount*TriggerState::TriggerPeriod;
		triggerDelay = (uint32)nChunks;
		trace("Trigger Delay is ^0",triggerDelay);
}


TriggerState::Action TriggerState::step() {
	if(triggered) {
			//trace("Starting trigger");
			triggeredCount=triggerDelay;
			return SET;
		}
		else if(triggeredCount==1) {
			//trace("Ending trigger");
			triggeredCount=0;
			return RESET;
		}
		else if(triggeredCount>1) {
			//if(0 == triggeredCount%10) trace("Decrementing trigger x 10");
			triggeredCount--;
		}
	return NIL;
}
void TriggerState::reset() {
	triggerDelay=1;
	triggeredCount=0;
	triggered=false;
}

const float32 TriggerState::TriggerPeriod = 0.1;

Clicker::Clicker() : RackExtension(), lBuffer(BUFFER_SIZE), rBuffer(BUFFER_SIZE) {
	trace("Clicker is here");
	tState.setDelay(sampleRate,BUFFER_SIZE);
	right=JBox_GetMotherboardObjectRef("/audio_outputs/audioOutRight");
	left=JBox_GetMotherboardObjectRef("/audio_outputs/audioOutLeft");
	externalTrigger=JBox_GetMotherboardObjectRef("/cv_inputs/externalTrigger");

}




void Clicker::processApplicationMessage(const TJBox_PropertyDiff &diff) {
	Tag tag = diff.fPropertyTag;

	switch(tag) {
	case Tags::SHAPE: {
		trace("Shape fired");
		click = Clicks::asShape(diff);
		break;
	}
	case Tags::PITCH: {
		carrier.setFrequency(Property::pitch(diff));
		break;
	}
	case Tags::LENGTH: {
		clickLength = 1+toInt(diff.fCurrentValue); //Property::length(diff);
		clicks.setScale(clickLength);
		trace("Click length is ^0",clickLength);
		break;
	}
	case Tags::PAN: {
		pan = Property::pan(diff);
		break;
	}
	case Tags::AMPLITUDE: {
		amplitude = clampedFloat(diff.fCurrentValue);
		trace("Amplitude is ^0",amplitude);
		break;
	}
	/*
	 * The output limiter settings
	 *
	 * LIMITER : the limit threshold
	 * LIMITER_ONOFF : is it sitched on
	 * LIMITER_HARDSOFT: hard or soft limit
	 *
	 */
	case Tags::LIMITER:
		limiter.setLimit(Property::limit(diff));
		break;
	case Tags::LIMITER_ONOFF:
		limiter.setActive(toBool(diff.fCurrentValue));
		break;
	case Tags::LIMITER_HARD_SOFT:
		limiter.setMode(Property::limitMode(diff));
		break;

	/*
	 * LFO settings
	 *
	 * LFO_FREQUENCY
	 * LFO_HOLD
	 * LFO_MODULATOR_ONOFF
	 *
	 */
	case Tags::LFO_FREQUENCY:
		pulse.setFrequency(Property::lfoFreq(diff));
		break;
	case Tags::LFO_HOLD:
		pulse.hold(toBool(diff.fCurrentValue));
		break;
	/*
	 * Trigger settings
	 * TRIGGER: manual mode
	 * TRIGGER_MODE : the mode selector
	 */
	case Tags::TRIGGER_MODE:
		trace("Trigger mode ^0",toFloat(diff.fCurrentValue));
		mode = Property::triggerMode(diff);
		if(mode==TriggerMode::EXT_CLOCK) edges.reset();
		break;
	case Tags::TRIGGER:
		if(mode==TriggerMode::MANUAL) {
			if(toBool(diff.fCurrentValue)) shouldTrigger=true;
		}
		break;
	case Tags::EXT_TRIGGER_THRESHOLD:
		edges.setThreshold(Property::triggerThreshold(diff));
		break;
	case Tags::EXT_TRIGGER_DEBOUNCE:
		edges.setDelay(Property::triggerDebounce(diff));
		break;
		/* CV settings */
	case kJBox_CVInputValue:
		triggerIn = toFloat(diff.fCurrentValue);
		break;
	}





}

void Clicker::handleTriggerLED() {
	switch(tState.step()) {
	case TriggerState::SET:
		set(1,Tags::TRIGGER_BACK);
		break;
	case TriggerState::RESET:
		set(0,Tags::TRIGGER_BACK);
		break;
	default:
		break;
	}
}

void Clicker::setSampleRate(const float32 rate) {
	sampleRate=rate;
	tState.setDelay(rate,BUFFER_SIZE);
	carrier.setSampleRate(rate);
	//pulse.setSampleRate(rate/(float32)BUFFER_SIZE);
	pulse.setSampleRate(rate);
	trace("Sample rate is ^0",rate);
}

void Clicker::process() {
	if(!initialised) {
		clicks.setScale(clickLength);
		initialised=true;
	}



	if(mode==TriggerMode::EXT_CLOCK) {
		if(edges(triggerIn)) shouldTrigger=true;
	}


	for(auto n=0;n<BUFFER_SIZE;n++) {

		auto p = pulse.next();
		if(mode==TriggerMode::INT_CLOCK) {
			shouldTrigger=p>0;
			//if(p>0) trace("Triggering internal");
		}

		if(shouldTrigger) {
			//trace("Triggering pulse, mode is ^0",mode);
			tState.set();
			shouldTrigger=false;
		}


		if(tState.isTriggered()) {
			clicking=true;
			clickOffset=0;
		}
		//if(clicking) trace("Clicking ON  Click offset is ^0",clickOffset);

		if(clicking && clickOffset>=clickLength) {
			clicking=false;
			clickOffset=0;
		}

		auto c = (clicking) ? clicks.at(click,clickOffset) : 0.f;
		auto f = carrier.next();
		auto sample=c*f*amplitude;
		lBuffer[n]=pan.toLeft(sample);
		rBuffer[n]=pan.toRight(sample);

		if(clicking) clickOffset++;
	}


	limiter.limit(lBuffer);
	limiter.limit(rBuffer);

	auto refL = JBox_LoadMOMPropertyByTag(left, kJBox_AudioOutputBuffer);
	JBox_SetDSPBufferData(refL, 0, lBuffer.size(), lBuffer.data());

	auto refR = JBox_LoadMOMPropertyByTag(right, kJBox_AudioOutputBuffer);
	JBox_SetDSPBufferData(refR, 0, rBuffer.size(), rBuffer.data());

	handleTriggerLED();
	tState.clear();


}




} /* namespace click */
} /* namespace meromorph */
