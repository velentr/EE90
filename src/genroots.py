#!/usr/bin/env python2

import math         # Mathematical constants (e, pi)
import sys          # Command-line arguments
import datetime     # Generating revision dates


# Header string for including at the top of the generated .h file containing the
# roots of unity. Assumes that the output will go into a file called 'roots.h'.
header = '''
/*
 * roots.h
 *
 * Constants representing the roots of unity.
 *
 * This file contains an array of the nth roots of unity. The total number of
 * roots is determined by the constant 'SAMPLE_SIZE', which should be defined in
 * the 'data.h' header file (or at compile time in the Makefile).
 *
 * DO NOT MODIFY THIS FILE BY HAND. IT IS GENERATED AUTOMATICALLY BY THE
 * genroots.py PYTHON SCRIPT.
 *
 * Revision History:
 *      04 Jun 2015     Brian Kubisiak      Initial revision.
 *
 * Last Generated:
 *      %s
 */

#ifndef _ROOTS_H_
#define _ROOTS_H_


#include "data.h"
''' % datetime.date.today().strftime("%d %b %Y")

dataheader = '''
/*
 * root
 *
 * Description: This array contains the nth roots of unity for calculating the
 *              FFT. The roots in this array contain an 8-bit real part and an
 *              8-bit imaginary part. The roots are organized in a modified
 *              bit-reversed order in order to make the accesses easier.
 *
 * Notes:       Due to the ordering of the roots, if the ith root is at
 *              'root[j]', then its negative is at 'root[j + SAMPLE_SIZE/2]'.
 */
const complex root[SAMPLE_SIZE] = {'''

datafooter = '''};'''

footer = '''

#endif /* _ROOTS_H_ */
'''

def genroots(n):
    """ This function takes in a number n and generates the nth roots of unity.
    The resulting roots are returned in an array.

    args:
      n -- The number of roots to generate.

    returns:
      Returns an array containing the nth roots of unity.
    """

    # Start with an empty array of roots.
    roots = []

    # First root. We can exponentiate this to get the other roots.
    w = math.e ** (2j * math.pi / n)

    # Need to generate all n roots.
    for i in range(n):
        roots.append(w ** i)

    return roots

def bitreverse(roots):
    """ This function takes in the nth roots of unity and rearranges them in
    bit-reversed order. Specifically, the root at index 0bwxyz will be moved to
    index 0bzyxw, assuming that the root is in the first half of the array.

    If the root is in the second half of the array, then it is just the negative
    of a root in the first half. The roots in the second half of the array will
    be ordered the same as their negatives in the first half. This will make it
    easier to find negations of roots.

    args:
      n -- number of roots of unity
      roots -- array containing all the nth roots of unity

    returns:
      Returns a new array of roots containing the values in the bit-reversed
      order described above.
    """

    # Begin by copying the roots array.
    out = roots

    # Get the number of roots from the length of the array
    n = len(roots)

    # Loop over the first half of the values. Note that the second half will be
    # rearranged in the same pattern as the first half.
    for i in range(n / 2):
        # First, compute a string representation of the number with the given
        # width.
        b = '{:0{width}b}'.format(i, width = int(math.log(n/2, 2)))
        # Now, reverse the string and convert it into an integer.
        j = int(b[::-1], 2)

        # Swap the values at these indices in both halves of the array.
        out[i], out[j] = out[j], out[i]
        out[i + n/2], out[j + n/2] = out[j + n/2], out[i + n/2]

    return out

def printroots(roots):
    """ This function prints out all the roots of unity in a format that can be
    included as a C header file. The output will create an array 'root' that
    contains the nth roots of unity of type 'complex' with fields 'real' and
    'imag'. Note that this does not comply with the standard complex data type
    in C.

    args:
      roots -- the roots of unity to print.
    """

    # Print the file header and some documentation
    print header
    print dataheader

    for i in roots:
        print "    { .real = %s, .imag = %s }," % (int(round(i.real * 127)),
                                                   int(round(i.imag * 127)))

    # Close the array and print some closing documentation.
    print datafooter
    print footer

def main():
    try:
        n = int(sys.argv[1])
    except IndexError:
        print("usage: %s [n]" % sys.argv[0])
        sys.exit(0)

    printroots(bitreverse(genroots(n)))

if __name__ == "__main__":
    main()
