/*
 * fft.c
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fft.h"

#define ERROR_THRESHOLD 10

extern complex root[SAMPLE_SIZE];       /* Roots of unity for the FFT. */
extern unsigned char key[SAMPLE_SIZE];  /* Spectrum that will open the bowl. */

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
 *
 * Notes:       A lot of the notation below is made up. Basically, we do log2(N)
 *              passes over the data, where each pass will iterate over a
 *              cluster of butterflies (try googling 'FFT butterfly' if you
 *              don't know what this is). Each cluster of butterflies is
 *              separated by a certain stride value, so we can just continue to
 *              increment by this stride until the data is covered. Then, start
 *              the next pass.
 *
 *              If you don't understand how this works, try staring at FFT
 *              butterflies a bit longer and it will hopefully make sense. If
 *              that doesn't work, try eating ice cream because yum ice cream.
 */

void fft(complex *data)
{
    /*
     * The stride of each pass over the data is a measure of the distance
     * between the two data points combined together in a butterfly. It is
     * always a power of two.
     */
    unsigned int stride;
    unsigned int i, j, k;      /* Loop indices. */


    /* We start off with two separate clusters of butterflie nodes filling the
     * entire data set. */
    stride = SAMPLE_SIZE / 2;

    /* We need to perform log2(N) iterations over the data in order to fully
     * transform it. */
    for (i = 0; i < LOG2_SAMPLE_SIZE; i++)
    {
        /*
         * Keep striding through the data until we cover all of it. Note that we
         * only go to 'SAMPLE_SIZE / 2', since each butterfly covers 2 data
         * points.
         */
        for (j = 0; j < SAMPLE_SIZE; j += 2*stride)
        {
            /*
             * Iterate over every butterfly in the cluster. This will use one
             * data point in the cluster, and one in the next cluster. We then
             * stride over the next butterfly cluster to avoid redoing this
             * computation.
             */
            for (k = j; k < j + stride; k++)
            {
                /* Get the two data points that we are transforming. */
                complex a = data[k];
                complex b = data[k+stride];

                /* Since the roots are stored in bit-reversed order, we can just
                 * index into the array with the butterfly index. */
                complex w = root[j];

                /* The negative of the root is just 180 degrees around the unit
                 * circle. */
                complex neg_w = root[j + SAMPLE_SIZE / 2];

                /* Now transform them using a butterfly. */
                data[k]         = add(a, mul(b, w));
                data[k+stride]  = add(a, mul(b, neg_w));
            }
        }

        /* Reduce the stride for the next pass over the data. */
        stride /= 2;
    }
}


/*
 * is_fft_match
 *
 * Description: Determines if the given frequency spectrum data is an
 *              approximate match for the previously recorded data (the 'key').
 *              The key that this data will be compared to is stored in ROM at
 *              compile time. This function will first take the (integer) log2
 *              of the magnitude of the input data in order to normalize it.
 *              Then, the difference between this data and the key is
 *              calculated, squared, and accumulated to get a measure of the
 *              error. This is compared to a set threshold: above the threshold,
 *              0 is returns; below the threshold, 1 is returned.
 *
 * Arguments:   data -- The data to compare to the key to determine whether or
 *                      not there is a match.
 *
 * Returns:     Returns 0 if the input data is dissimilar to the key.
 *              Returns 1 if the input data matches the key, within some error.
 *
 * Notes:       This function is very slow and probably won't give very good
 *              results. Ideally, some more sophisticated analysis on a more
 *              powerful chip should be used.
 */
unsigned char is_fft_match(complex *data)
{
    double mag;
    unsigned int i;
    unsigned char cmpval;
    unsigned long err = 0;

    /* Transform each point of the input data. */
    for (i = 0; i < SAMPLE_SIZE; i++)
    {
        /* First, take the log of the magnitude of the data. This will fit in an
         * 8-bit char. */
        mag = data[i].real * data[i].real + data[i].imag * data[i].imag;
        cmpval = (char)log10(mag);

        /* Now calculate the absolute value of the error, and accumulate it. */
        err += abs(cmpval - key[i]);
    }

    /* Return true iff the error is below the error threshold. */
    return (err < ERROR_THRESHOLD);
}
