#ifndef BIGNUM_MOD_ARITH_H
#define BIGNUM_MOD_ARITH_H

#include <bignum.h>

/**
 * @fn int BIGNUM_add_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);
 * Adds two integers mod a third: r = a + b mod m, where r can be a or b.
 * @param r The result of the addition.
 * @param a One of the numbers to add.
 * @param b The other number to add.
 * @param m The modulus.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_add_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);

/**
 * @fn int BIGNUM_sub_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);
 * Subtracts two integers mod a third: r = a - b mod m, where r can be a or b.
 * @param r The result of the subtraction.
 * @param a One of the numbers to subtract.
 * @param b The other number to subtract.
 * @param m The modulus.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_sub_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);

/**
 * @fn int BIGNUM_mul_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);
 * Multiplies two integers mod a third: r = a * b mod m, where r can be a or b.
 * @param r The result of the multiplication.
 * @param a One of the numbers to multiply.
 * @param b The other number to multiply.
 * @param m The modulus.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_mul_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);

/**
 * @fn int BIGNUM_sqr_mod(BIGNUM r, BIGNUM a, BIGNUM m);
 * Computes a^2 mod m and is much faster than multiplying a by itself.
 * @param r The result of the square.
 * @param a The base.
 * @param m The modulus.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_sqr_mod(BIGNUM r, BIGNUM a, BIGNUM m);

/**
 * @fn int BIGNUM_pow_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);
 * Computes r = c^b mod m.
 * @param r The result of the exponentiation.
 * @param a The base.
 * @param b The exponent.
 * @param m The modulus.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_pow_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m);


#endif
