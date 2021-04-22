/*
 * Convolver.hpp
 *
 *  Created on: 31 Mar 2021
 *      Author: julianporter
 */

#ifndef HILBERT_HPP_
#define HILBERT_HPP_


#include "FFT.hpp"


namespace meromorph { namespace dsp {



class Hilbert {
private:
	uint32 N;

	uint32 nStages;
	cx32 sqr2;
public:
	std::vector<cx32> hilbert;
	std::vector<cx32> buffer;
	std::vector<cx32> tmp;

	void makeHilbertKernel();


	Hilbert(const uint32 N_);
	virtual ~Hilbert() = default;

	void reset();
	void apply(const std::vector<cx32> &,std::vector<cx32> &);
	uint32 delay() const { return nStages; }
};

}}

#endif /* HILBERT_HPP_ */
