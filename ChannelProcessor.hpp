/*
 * ChannelProcessor.hpp
 *
 *  Created on: 4 Apr 2021
 *      Author: julianporter
 */

#ifndef CHANNELPROCESSOR_HPP_
#define CHANNELPROCESSOR_HPP_

#include "base.hpp"
#include "Limiter.hpp"
#include "Hilbert.hpp"


namespace meromorph {
namespace ring {

class ChannelProcessor {
	protected:
		static const uint32 IN_BUFFER = kJBox_AudioInputBuffer;
		static const uint32 OUT_BUFFER = kJBox_AudioOutputBuffer;

		static const uint32 IN_CONN = kJBox_AudioInputConnected;
		static const uint32 OUT_CONN = kJBox_AudioOutputConnected;

		TJBox_ObjectRef input;
		TJBox_ObjectRef output;

		bool inConnected = false;
		bool outConnected = false;


		bool inputConnected() const;
		bool outputConnected() const;

		uint32 read(float32 *l);
		void write(uint32 N,float32 *l);

		bool initialised = false;

		cx32 phase = cx::One;
			float32 offset = 0;
			cx32 angle = cx::One;
			Limiter limiter;


		std::vector<float32> buffer;
		std::vector<cx32> cxbuffer;
		std::vector<cx32> cxout;
		dsp::Hilbert hilbert;

		cx32 runningPhase = cx::One;


	public:
		const static uint32 BUFFER_SIZE = 64;

		ChannelProcessor(const char *nameIn,const char *nameOut);
		virtual ~ChannelProcessor() = default;

		void reset();

		void process();
		void bypass();
		void off() {};

		void setPhase(const cx32 p) { phase=p; }
		void setAngle(const cx32 a) { angle=a; }
		void setOffset(const float32 o) { offset=o; }
		void setLimiterOnOff(const bool b) { limiter.setActive(b); }
		void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
		void setLimit(const float32 l) { limiter.setActive(l); }



	};




} /* namespace ring */
} /* namespace meromorph */

#endif /* CHANNELPROCESSOR_HPP_ */
