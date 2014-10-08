#ifndef BIGNUM_ARITH_H
#define BIGNUM_ARITH_H

#include <bignum.h>

/**
 * @fn int BIGNUM_add(BIGNUM r, BIGNUM a, BIGNUM b);
 * Adds two integers: r = a + b where r can be a or b.
 * @param r The result of the addition.
 * @param a One of the numbers to add.
 * @param b The other number to add.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_add(BIGNUM r, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_sub(BIGNUM r, BIGNUM a, BIGNUM b);
 * Subtracts two integers: r = a - b where r can be a or b.
 * @param r The result of the subtraction.
 * @param a One of the numbers to subtract.
 * @param b The other number to subtract.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_sub(BIGNUM r, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_mul(BIGNUM r, BIGNUM a, BIGNUM b);
 * Multiplies two integers: r = a * b where r can be a or b.
 * @param r The result of the multiplication.
 * @param a One of the numbers to multiply.
 * @param b The other number to multiply.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_mul(BIGNUM r, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_div(BIGNUM q, BIGNUM r, BIGNUM a, BIGNUM b);
 * Divides two integers: q = a / b where r is the remainder.
 * @param q The quotient of the division.
 * @param r The remainder from the division.
 * @param a The dividend.
 * @param b The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_div(BIGNUM d, BIGNUM r, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_div_nr(BIGNUM q, BIGNUM a, BIGNUM b);
 * Divides two integers: q = a / b.
 * @param q The quotient of the division.
 * @param a The dividend.
 * @param b The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_div_nr(BIGNUM d, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_mod(BIGNUM r, BIGNUM a, BIGNUM b);
 * Computes the remainder of a division of two integers: a / b, where r is the remainder.
 * @param r The remainder from the division.
 * @param a The dividend.
 * @param b The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_mod(BIGNUM r, BIGNUM a, BIGNUM b);

/**
 * @fn int BIGNUM_sqr(BIGNUM r, BIGNUM a);
 * Computes a^2 and is much faster than multiplying a by itself.
 * @param r The result of the square.
 * @param a The base.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_sqr(BIGNUM r, BIGNUM a);

/**
 * @fn int BIGNUM_pow_ui(BIGNUM r, BIGNUM a, uint_32 b);
 * Computes r = c^b.
 * @param r The result of the exponentiation.
 * @param a The base.
 * @param b The exponent.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_pow_ui(BIGNUM r, BIGNUM a, uint_32 b);


#endif
