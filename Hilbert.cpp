/*
 * Convolver.cpp
 *
 *  Created on: 31 Mar 2021
 *      Author: julianporter
 */

#include "Hilbert.hpp"
#include <algorithm>
#include <functional>

namespace meromorph { namespace dsp {



void Hilbert::makeHilbertKernel() {
	for(auto i=0;i<=nStages;i++) {
		cx32 value = (0==(i&1)) ? cx::Zero : cx32(2.0/(Pi * i));
		hilbert[nStages+i] = value;
		hilbert[nStages-i] = -value;
	}
	FFT::fft(hilbert);
}



Hilbert::Hilbert(const uint32 N_) : N(N_), nStages((N-1)/2), hilbert(2*N), buffer(2*N), tmp(2*N) {
	sqr2=cx32(sqrt(2.f));
	makeHilbertKernel();
}


void Hilbert::reset() {
	std::fill(buffer.begin(),buffer.end(),0.f);
}

void Hilbert::apply(const std::vector<cx32> &in,std::vector<cx32> &out) {
	std::copy(buffer.begin()+N,buffer.end(),buffer.begin());
	std::copy(in.begin(),in.end(),buffer.begin()+N);

	std::copy(buffer.begin(),buffer.end(),tmp.begin());
	//std::copy(std::begin(buffer),std::end(buffer),std::begin(out));

	FFT::fft(tmp);
	std::transform(tmp.begin(),tmp.end(),hilbert.begin(),tmp.begin(), std::multiplies<cx32>());
	//tmp=tmp * hilbert;
	FFT::ifft(tmp);

	std::copy(tmp.begin()+N,tmp.end(),tmp.begin());
	for(auto i=0;i<N;i++) out[i]= in[i] + cx::I * tmp[i] / sqr2;
}


}}
