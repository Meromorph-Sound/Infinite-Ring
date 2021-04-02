/*
 * Limiter.cpp
 *
 *  Created on: 20 Feb 2021
 *      Author: julianporter
 */

#include "Limiter.hpp"

namespace meromorph {
namespace ring {

void Limiter::limit(float32 *data,const uint32 n) {
	if(!active) return;

	switch(mode) {
	case Mode::SOFT:
		for(auto i=0;i<n;i++) data[i]=scale*tanh(data[i]/scale);
		break;
	case Mode::HARD:
		for(auto i=0;i<n;i++) data[i]=std::min(scale,std::max(-scale,data[i]));
		break;
	}
}

} /* namespace click */
} /* namespace meromorph */
