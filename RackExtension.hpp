#pragma once

#include "base.hpp"
#include <vector>
#include <cmath>
#include <type_traits>


namespace meromorph {




class RackExtension {

	
private:


		TJBox_ObjectRef props;
		TJBox_ObjectRef noteState;

protected:
		static const uint32 BUFFER_SIZE;
		bool forwarding = false;
		std::vector<float32> buffer;



		void set(const float32 value,const Tag tag);
		virtual void setSampleRate(const float32) {};
			virtual void setMasterTune(const float32) {};
			virtual void reset() {};

			virtual void processSystemCall(const TJBox_PropertyDiff &diff);
			virtual void processApplicationMessage(const TJBox_PropertyDiff &diff) { };
			virtual void processMIDIEvent(const TJBox_PropertyDiff &diff);

			virtual void process() {}

public:

	explicit RackExtension();
	virtual ~RackExtension() = default;



//	~CFollower(); 
    
    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
