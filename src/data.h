/*
 * data.h
 *
 * Data types and constants for analyzing a frequency spectrum.
 *
 * This file describes the complex number data type, as well as functions for
 * adding and multiplying complex numbers. Constants for determining the number
 * of samples to use are also defined here.
 *
 * Revision History:
 *      16 Apr 2015     Brian Kubisiak      Initial revision.
 */

#ifndef _DATA_H_
#define _DATA_H_


#define SAMPLE_SIZE         1024    /* Number of samples in the buffer. */
#define LOG2_SAMPLE_SIZE    10      /* Base two logarithm of the sample size. */


/*
 * complex
 *
 * Description: Data type for holding a complex number. This data type uses
 *              Cartesian coordinates for holding the number, so it is optimized
 *              for addition rather than multiplication.
 *
 * Members:     real  The real part of the complex number.
 *              imag  The imaginary part of the complex number.
 */
typedef struct _complex {
    char real;
    char imag;
} complex;


/*
 * add
 *
 * Description: Adds together two complex numbers in the Cartesian plane.
 *
 * Arguments:   a  The first number to add.
 *              b  The second number to add.
 *
 * Returns:     Returns the complex number that is the sum of the two inputs.
 */
complex add(complex a, complex b);


/*
 * mul
 *
 * Description: Computes the product of two complex numbers in the Cartesian
 *              plane.
 *
 * Arguments:   a  First number to multiply.
 *              b  Second number to multiply.
 *
 * Returns:     Returns the complex number that is the product of the two
 *              inputs.
 *
 * Notes:       The number is stored in rectangular coordinates, so taking the
 *              product will be a bit slow.
 */
complex mul(complex a, complex b);



#endif /* end of include guard: _DATA_H_ */
