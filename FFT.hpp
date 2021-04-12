/*
 * FFT.hpp
 *
 *  Created on: 1 Apr 2021
 *      Author: julianporter
 */

#ifndef FFT_HPP_
#define FFT_HPP_

#include "base.hpp"


namespace meromorph { namespace dsp {


class FFT {
public:
	static void fft(std::vector<cx32> &buffer);
	static void ifft(std::vector<cx32> &buffer);
};

}} /* namespace meromorph */

#endif /* FFT_HPP_ */
