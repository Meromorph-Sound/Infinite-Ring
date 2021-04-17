/*
 * Clicker.hpp
 *
 *  Created on: 31 Jan 2021
 *      Author: julianporter
 */

#ifndef RING_HPP_
#define RING_HPP_

#include "RackExtension.hpp"
#include "ChannelProcessor.hpp"



namespace meromorph {
namespace ring {





enum Tags : uint32 {
	PHASE=1,
	OFFSET=2,
	ANGLE=3,
	LIMITER_ONOFF = 4,
	LIMITER_HARD_SOFT = 5,
	LIMITER = 6,
	INPUT_GAIN = 7,
	OUTPUT_GAIN = 8
	};







class InfiniteRing : public RackExtension {
private:
	ChannelProcessor left;
	ChannelProcessor right;
	State state = State::On;

	std::vector<float32> lBuffer;
	std::vector<float32> rBuffer;




protected:

	virtual void processApplicationMessage(const TJBox_PropertyDiff &diff);
	virtual void process();
	virtual void reset();
public:
	InfiniteRing();
	virtual ~InfiniteRing() = default;
	InfiniteRing(const InfiniteRing &other) = default;
	InfiniteRing& operator=(const InfiniteRing &other) = default;



};

} /* namespace click */
} /* namespace meromorph */

#endif /* RING_HPP_ */
