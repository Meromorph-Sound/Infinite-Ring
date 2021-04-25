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
#include "TriggerState.hpp"


namespace meromorph {
namespace ring {

enum ProcessingMode : uint32 {
	REAL = 0,
	SEMI_COMPLEX = 1,
	COMPLEX = 2
};

class ChannelProcessor {
	protected:
		static const uint32 IN_BUFFER = kJBox_AudioInputBuffer;
		static const uint32 OUT_BUFFER = kJBox_AudioOutputBuffer;
		static const uint32 IN_CONN = kJBox_AudioInputConnected;
		static const uint32 OUT_CONN = kJBox_AudioOutputConnected;
		static const float32 constexpr EPSILON = 1.0e-5;
		static const float32 constexpr HARD_LIMIT = 1.f - EPSILON;

	private:
		TJBox_ObjectRef input;
		TJBox_ObjectRef output;
		std::vector<float32> buffer;
		std::vector<cx32> cxbuffer;
		std::vector<cx32> cxout;

		Limiter limiter;
		TriggerState trigger;
		dsp::Hilbert hilbert;

		cx32 phase = cx::One;
		float32 inputGain = 1.f;
		float32 outputGain = 1.f;
		ProcessingMode mode = REAL;
		cx32 runningPhase = cx::One;
		float32 rms = 0;
		uint32 chunkCount = 0;

		bool inConnected = false;
		bool outConnected = false;

		bool inputConnected() const;
		bool outputConnected() const;

		uint32 read();
		void write();
		bool isSilent();

		bool processReal();
		bool processSemiComplex();
		bool processComplex();



	public:
		const static uint32 BUFFER_SIZE = 64;

		ChannelProcessor(const char *nameIn,const char *nameOut);
		virtual ~ChannelProcessor() = default;

		void reset();

		TriggerState::Action process();
		TriggerState::Action bypass();
		TriggerState::Action off() { return TriggerState::NIL; };

		void setInputGain(const float32 a) { inputGain=a; }
		void setOutputGain(const float32 a) { outputGain=a; }
		void setPhase(const float32 p) { phase=std::polar(1.f,p); }
		void setProcessingMode(const ProcessingMode m) { mode=m; }
		void setLimiterOnOff(const bool b) { limiter.setActive(b); }
		void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
		void setLimit(const float32 l) { limiter.setActive(l); }
		void setSampleRate(const float32 rate) { trigger.setDelay(rate,BUFFER_SIZE); }

		void testConnections();
		float32 getRMS() const { return rms; }



	};




} /* namespace ring */
} /* namespace meromorph */

#endif /* CHANNELPROCESSOR_HPP_ */
