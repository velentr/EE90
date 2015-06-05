/*
 * test-fft.c
 *
 * This file contains code to run a simple test of the FFT. It will create a
 * couple of simple data sets, run the FFT on the sets, then print out the
 * magnitude response for each set. This magnitude response can then be examined
 * visually to verify the FFT.
 *
 * Revision History:
 *      04 Jun 2015     Brian Kubisiak      Initial revision.
 */

#include <stdlib.h>
#include <stdio.h>

#include "data.h"
#include "fft.h"


/*
 * main
 *
 * Description: This function creates an array of data with a known FFT, then
 *              calls the FFT function on the data. The magnitude of the data is
 *              then printed to stdout for checking the validity.
 *
 * Returns:     Returns 0 on successful completion, or -1 if an error occurs.
 *
 * Notes:       Right now, this just tests a single dataset. This should be
 *              changed eventually. It is difficult to find good test sets since
 *              the resulting frequency data is not in the correct order.
 */
int main(void)
{
    complex *testdata;
    int i;

    /* Allocate a zeroed-out buffer, checking the allocation for failure. */
    testdata = (complex *)calloc(SAMPLE_SIZE, sizeof(complex));
    if (testdata == NULL) {
        perror("calloc");
        return -1;
    }

    /* Set only a single data point to be nonzero. This is essentially taking
     * the FFT of a delta function. */
    testdata[0].real = 127;

    /* Take the FFT of the data. */
    fft(testdata);

    /* Print out the magnitude of the result. */
    for (i = 0; i < SAMPLE_SIZE; i++)
    {
        int mag = testdata[i].real * testdata[i].real
                + testdata[i].imag * testdata[i].imag;

        printf("%d\n", mag);
    }

    free(testdata);

    return 0;
}
