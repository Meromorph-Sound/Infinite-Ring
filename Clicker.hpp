/*
 * Clicker.hpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#ifndef CLICKER_HPP_
#define CLICKER_HPP_

#include "RackExtension.hpp"
#include "Limiter.hpp"



namespace meromorph {
namespace ring {





enum Tags : uint32 {
	PHASE=1,
	OFFSET=2,
	ANGLE=3,
	LIMITER = 4,
	LIMITER_ONOFF = 5,
	LIMITER_HARD_SOFT = 6,
	GAIN = 7
	};



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


	TriggerState() = default;
	virtual ~TriggerState() = default;

	void set() { triggered=true; }
	void clear() { triggered=false; }
	bool isTriggered() const { return triggered; }
	void setDelay(const float32 sampleRate,const float32 BUFFER_SIZE);
	Action step();
	void reset();
};

class InfiniteRing : public RackExtension {
private:
	TJBox_ObjectRef left;
	TJBox_ObjectRef right;
	TJBox_ObjectRef externalTrigger;

	std::vector<float32> lBuffer;
	std::vector<float32> rBuffer;


	TriggerMode mode = MANUAL;
	TriggerState tState;
	bool initialised = false;

	float32 sampleRate = 48000;
	bool clicking = false;
	uint32 clickOffset = 0;
	uint32 clickLength = 100;



	Limiter limiter;

	float32 amplitude = 1.0;
	bool shouldTrigger = false;

	float32 triggerIn = 0.0;


	void handleTriggerLED();

protected:



	virtual void setSampleRate(const float32 rate);
	virtual void processApplicationMessage(const TJBox_PropertyDiff &diff);
	virtual void process();
	virtual void reset() {}
public:
	InfiniteRing();
	virtual ~InfiniteRing() = default;
	InfiniteRing(const InfiniteRing &other) = default;
	InfiniteRing& operator=(const InfiniteRing &other) = default;



};

} /* namespace click */
} /* namespace meromorph */

#endif /* CLICKER_HPP_ */
