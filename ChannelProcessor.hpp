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

enum ProcessingMode {
	REAL,
	SEMI_COMPLEX,
	COMPLEX
};

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

		uint32 read();
		void write();
		bool isSilent();

		bool initialised = false;

		cx32 phase = cx::One;
		cx32 angle = cx::One;
		Limiter limiter;
		float32 inputGain = 1.f;
		float32 outputGain = 1.f;


		std::vector<float32> buffer;
		std::vector<cx32> cxbuffer;
		std::vector<cx32> cxout;
		dsp::Hilbert hilbert;

		cx32 runningPhase = cx::One;

		ProcessingMode mode = REAL;


		void processReal();
		void processSemiComplex();
		void processComplex();



	public:
		const static uint32 BUFFER_SIZE = 64;

		ChannelProcessor(const char *nameIn,const char *nameOut);
		virtual ~ChannelProcessor() = default;

		void reset();

		bool process();
		bool bypass();
		bool off() { return false; };

		void setInputGain(const float32 a) { inputGain=a; }
		void setOutputGain(const float32 a) { outputGain=a; }
		void setPhase(const float32 p) { phase=std::polar(1.f,p); }
		void setProcessingMode(const ProcessingMode m) { mode=m; }
		void setLimiterOnOff(const bool b) { limiter.setActive(b); }
		void setLimiterMode(const Limiter::Mode m) { limiter.setMode(m); }
		void setLimit(const float32 l) { limiter.setActive(l); }



	};




} /* namespace ring */
} /* namespace meromorph */

#endif /* CHANNELPROCESSOR_HPP_ */
