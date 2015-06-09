/*
 * key.c
 *
 * Power spectrum for the key to the dog bowl.
 *
 * Contains the magnitude of the power spectrum of the dog bark that will unlock
 * the dog bowl. This spectrum is compared to the recorded spectrum in order to
 * identify the dog that barked. If the spectra match, the dog bowl will open.
 *
 * Revision History:
 *      06 Jun 2015     Brian Kubisiak      Initial revision.
 */

#include "data.h"

/* Frequency spectrum that unlocks the dog bowl. */
unsigned char key[SAMPLE_SIZE] = {
    3,
    3,
    3,
    3,
    4,
    4,
    3,
    4,
    3,
    4,
    4,
    4,
    4,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    3,
    3,
    4,
    4,
    4,
    3,
    4,
    3,
    3,
    2,
    3,
    4,
    4,
    4,
    4,
    3,
    4,
    4,
    3,
    4,
    4,
    4,
    2,
    4,
    3,
    3,
    3,
    4,
    3,
    4,
    3,
    3,
    2,
    4,
    3,
    3,
    3,
    4,
    4,
    4,
    3,
};
