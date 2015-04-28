/*
 * fft.h
 *
 * Perform Fast Fourier Transforms on data.
 *
 * This code is used for computing a low-footprint, high-speed FFT on an array
 * of data. Because of the limitations of the platform that I am working on,
 * several optimizations have to be made in order for the code to work.
 * Specifically, the limitations I have are:
 *
 *      8 kB of RAM
 *      No floating-point unit
 *      8 -> 16 bit multiplier
 *      8 bit adder (for speed)
 *
 * Some limitations are self-imposed in order to produce faster code. Each data
 * point is a complex number with 8 bits for the real part and 8 bits for the
 * imaginary.
 *
 * Revision History:
 *      16 Apr 2015     Brian Kubisiak      Initial revision.
 */


#ifndef _FFT_H_
#define _FFT_H_


#include "data.h"   /* Complex data type, size of array, etc. */


/*
 * fft
 *
 * Description: Computes the fast Fourier transform (FFT) of an array of input
 *              data. This implementation is in-place, so it will take O(1)
 *              space. Additionally, optimizations are performed assuming that
 *              the data to transform is purely real. The implementation assumes
 *              8-bit characters and 16-bit shorts. It attempts to avoid 16-bit
 *              additions/multiplications wherever possible in order to cut down
 *              on the number of clocks.
 *
 * Arguments:   data An array of complex numbers for performing the FFT. This
 *                   FFT assumes that the array contains 'SAMPLE_SIZE' values of
 *                   type 'complex'. Both of these are defined in 'data.h'.
 *
 * Limitations: Assumes that the input data is purely real. Because there is no
 *              FPU and fixed-point arithmetic is used, the resulting FFT will
 *              not be normalized to anything sensible.
 */
void fft(complex *data);


#endif /* end of include guard: _FFT_H_ */
