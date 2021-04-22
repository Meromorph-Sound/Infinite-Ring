/*
 * TriggerState.hpp
 *
 *  Created on: 22 Apr 2021
 *      Author: julianporter
 */

#ifndef TRIGGERSTATE_HPP_
#define TRIGGERSTATE_HPP_

#include "base.hpp"

namespace meromorph {

struct TriggerState {
	static const float32 TriggerPeriod;
	enum Action : uint32 {
		SET = 1,
		RESET = 2,
		NIL = 3
	};
	uint32 triggerDelay = 1;
	int32 triggeredCount = 0;
	bool triggered = false;

	uint32 tag;


	TriggerState(const uint32 tag_=0) : tag(tag_) {};
	virtual ~TriggerState() = default;

	void set() { triggered=true; }
	void clear() { triggered=false; }
	bool isTriggered() const { return triggered; }
	void setDelay(const float32 sampleRate,const float32 BUFFER_SIZE);
	uint32 Tag() const { return tag; }
	Action step();
	void reset();
};

} /* namespace meromorph */

#endif /* TRIGGERSTATE_HPP_ */
