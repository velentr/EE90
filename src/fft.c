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
 */

#include <stdio.h>
#include "fft.h"

extern complex root[SAMPLE_SIZE];


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
