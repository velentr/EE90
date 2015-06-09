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
#include <math.h>

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
    testdata[0].real = 97;
    testdata[1].real = 46;
    testdata[2].real = 0;
    testdata[3].real = 0;
    testdata[4].real = 0;
    testdata[5].real = 0;
    testdata[6].real = 44;
    testdata[7].real = 49;
    testdata[8].real = 13;
    testdata[9].real = 0;
    testdata[10].real = 20;
    testdata[11].real = 36;
    testdata[12].real = 23;
    testdata[13].real = 3;
    testdata[14].real = 0;
    testdata[15].real = 0;
    testdata[16].real = 5;
    testdata[17].real = 36;
    testdata[18].real = 8;
    testdata[19].real = 0;
    testdata[20].real = 0;
    testdata[21].real = 33;
    testdata[22].real = 58;
    testdata[23].real = 3;
    testdata[24].real = 0;
    testdata[25].real = 0;
    testdata[26].real = 3;
    testdata[27].real = 61;
    testdata[28].real = 67;
    testdata[29].real = 26;
    testdata[30].real = 0;
    testdata[31].real = 0;
    testdata[32].real = 0;
    testdata[33].real = 0;
    testdata[34].real = 26;
    testdata[35].real = 28;
    testdata[36].real = 15;
    testdata[37].real = 0;
    testdata[38].real = 0;
    testdata[39].real = 5;
    testdata[40].real = 18;
    testdata[41].real = 0;
    testdata[42].real = 0;
    testdata[43].real = 0;
    testdata[44].real = 3;
    testdata[45].real = 31;
    testdata[46].real = 8;
    testdata[47].real = 0;
    testdata[48].real = 0;
    testdata[49].real = 3;
    testdata[50].real = 56;
    testdata[51].real = 49;
    testdata[52].real = 0;
    testdata[53].real = 0;
    testdata[54].real = 0;
    testdata[55].real = 5;
    testdata[56].real = 51;
    testdata[57].real = 28;
    testdata[58].real = 8;
    testdata[59].real = 0;
    testdata[60].real = 0;
    testdata[61].real = 0;
    testdata[62].real = 3;
    testdata[63].real = 28;

    /* Take the FFT of the data. */
    fft(testdata);

    /* Print out the magnitude of the result. */
    for (i = 0; i < SAMPLE_SIZE; i++)
    {
        int mag = testdata[i].real * testdata[i].real
                + testdata[i].imag * testdata[i].imag;

        printf("%d\n", (char)log10(mag));
    }

    free(testdata);

    return 0;
}
