#ifndef BIGNUM_CMP_H
#define BIGNUM_CMP_H

#include <bignum.h>

/**
 * @fn int BIGNUM_cmp(BIGNUM x, BIGNUM y)
 * 
 * Compares two BIGNUMs and returns the status of the comparison.
 * @param x The value to compare with y.
 * @param y The value to compare with x.
 * @return 0 if x == y, +1 if x > y, -1 if x < y
 */
int BIGNUM_cmp(BIGNUM x, BIGNUM y);

/**
 * @fn int BIGNUM_cmp_ui(BIGNUM x, block_t y)
 * 
 * Compares a BIGNUM and an unsigned int and returns the status of the comparison.
 * It is assumed that y is always positive.
 * @param x The value to compare with y.
 * @param y The value to compare with x.
 * @return 0 if x == y, +1 if x > y, -1 if x < y
 */
int BIGNUM_cmp_ui(BIGNUM x, block_t y);

/**
 * @fn int BIGNUM_cmp_abs(BIGNUM x, BIGNUM y)
 * 
 * Compares the absolute value of two BIGNUMs and returns the status of the comparison.
 * @param x The value to compare with y.
 * @param y The value to compare with x.
 * @return 0 if |x| == |y|, +1 if |x| > |y|, -1 if |x| < |y|
 */
int BIGNUM_cmp_abs(BIGNUM x, BIGNUM y);

/**
 * @fn int BIGNUM_cmp_abs_ui(BIGNUM x, block_t y)
 * 
 * Compares the absolute value of a BIGNUM and an unsigned int and returns the status of the comparison.
 * It is assumed that y is always positive.
 * @param x The value to compare with y.
 * @param y The value to compare with x.
 * @return 0 if |x| == |y|, +1 if |x| > |y|, -1 if |x| < |y|
 */
int BIGNUM_cmp_abs_ui(BIGNUM x, block_t y);

/**
 * @fn int BIGNUM_sign(BIGNUM x)
 * 
 * Returns the sign of a BIGNUM.
 * @param x The value with the sign to return.
 * @return 0 if x == 0, +1 if x > 0, -1 if x < 0
 */
int BIGNUM_sign(BIGNUM x);

/**
 * @fn int BIGNUM_is_even(BIGNUM x)
 * 
 * Checks to see if x is even.
 * @param x The value to check.
 * @return 0 if x is odd, +1 if x is even.
 */
int BIGNUM_is_even(BIGNUM x);

/**
 * @fn int BIGNUM_is_odd(BIGNUM x)
 * 
 * Checks to see if x is odd.
 * @param x The value to check.
 * @return 0 if x is even, +1 if x is odd.
 */
int BIGNUM_is_odd(BIGNUM x);

#endif
