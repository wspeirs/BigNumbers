#ifndef BIGNUM_NUM_THEORY_H
#define BIGNUM_NUM_THEORY_H

#include <bignum.h>

/**
 * @fn int BIGNUM_gcd(BIGNUM r, BIGNUM a, BIGNUM b);
 * Computes the gcd (Greatest Common Divisor) of a & b.
 * @param r The gcd of a & b.
 * @param a A BIGNUM to use in the gcd computation.
 * @param b A BIGNUM to use in the gcd computation.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_gcd(BIGNUM r, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_lcm(BIGNUM r, BIGNUM a, BIGNUM b);
 * Computes the lcm (Least Common Multiple) of a & b.
 * @param r The lcm of a & b.
 * @param a A BIGNUM to use in the lcm computation.
 * @param b A BIGNUM to use in the lcm computation.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_lcm(BIGNUM r, BIGNUM a, BIGNUM b);

#endif
