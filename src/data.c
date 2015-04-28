/*
 * data.c
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

#include "data.h"



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
complex add(complex a, complex b)
{
    complex res;

    /* Real part of result is sum of real parts of inputs. */
    res.real = a.real + b.real;
    /* Imaginary part of result is sum of imaginary parts of inputs. */
    res.imag = a.imag + b.imag;

    return res;
}


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
complex mul(complex a, complex b)
{
    complex res;

    /* (a + jb)(c + jd) = ac + jad + jbc + j^2 cd = (ac - cd) + j(ad + bc) */

    /* Real part of result comes from product of real parts minus product of
     * imaginary parts. */
    res.real = (a.real * b.real) - (a.imag * b.imag);
    /* Imaginary part is sum of cross products of inputs. */
    res.imag = (a.real * b.imag) + (a.imag * b.real);

    return res;
}


