/*
 * Convolver.cpp
 *
 *  Created on: 31 Mar 2021
 *      Author: julianporter
 */

#include "Convolver.hpp"

namespace meromorph {

void Hilbert::makeHilbertKernel() {
	for(auto i=0;i<hilbertN;i++) {
		cx32 value = (0==(i&1)) ? cx::Zero : cx32(2.0/(Pi * i));
		hilbert[i+hilbertN] = value;
		hilbert[i-hilbertN] = -value;

	}
	FFT::fft(hilbert);
}



Hilbert::Hilbert(const uint32 N_) :
		N(N_), hilbertN((N/2)-1),
		hilbert(cx::Zero,2*N), buffer(cx::Zero,2*N), tmp(cx::Zero,2*N) {
	makeHilbertKernel();
}



void Hilbert::reset() {
	buffer = CxZero;
}

void Hilbert::apply(std::valarray<cx32> &real) {
	buffer = buffer.shift(N);
	for(auto i=0;i<N;i++) buffer[N+i]=real[i];
	tmp=buffer;
	FFT::fft(tmp);
	tmp=tmp * hilbert;
	FFT::ifft(tmp);

	tmp.shift(N);
	tmp *= cx::I;
	real += tmp;
}

}
