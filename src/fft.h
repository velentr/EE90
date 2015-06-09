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
 *      06 Jun 2015     Brian Kubisiak      Added method for FFT comparison.
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


/*
 * is_fft_match
 *
 * Description: Determines if the given frequency spectrum data is an
 *              approximate match for the previously recorded data. The data
 *              that this will be compared to is stored in ROM at compile time.
 *              This function will first take the (integer) log2 of the
 *              magnitude of the input data in order to normalize it. Then, the
 *              difference between this data and the comparison values is
 *              calculated, squared, and accumualted to get a measure of the
 *              error. This is compared to a set threshold: above the threshold,
 *              0 is returns; below the threshold, 1 is returned.
 *
 * Arguments:   data -- The data to compare to the previously-recorded data to
 *                      determine whether or not there is a match.
 *
 * Returns:     Returns 0 if the input data is dissimilar to the comparison
 *              data. Returns 1 if the input data matches the comparison data,
 *              within some error.
 *
 * Notes:       This function is very slow and probably won't give very good
 *              results. Ideally, some more sophisticated analysis on a more
 *              powerful chip should be used.
 */
unsigned char is_fft_match(complex *data);


#endif /* end of include guard: _FFT_H_ */
