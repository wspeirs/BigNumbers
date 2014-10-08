#ifndef BIGNUM_ARITH_UI_H
#define BIGNUM_ARITH_UI_H

#include <bignum.h>

/**
 * @fn int BIGNUM_add_ui(BIGNUM r, BIGNUM a, block_t b);
 * Adds an unsigned intiger to a BIGNUM: r = a + b.
 * It is assumed that b is always positive.
 * @param r The result of the addition.
 * @param a One of the numbers to add.
 * @param b The other number to add.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_add_ui(BIGNUM r, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_sub_ui(BIGNUM r, BIGNUM a, block_t b);
 * Subtracts an unsigned integer from a BIGNUM: r = a - b.
 * It is assumed that b is always positive.
 * @param r The result of the subtraction.
 * @param a One of the numbers to subtract.
 * @param b The other number to subtract.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_sub_ui(BIGNUM r, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_mul_ui(BIGNUM r, BIGNUM a, block_t b);
 * Multiplies an unsigned integer to a BIGNUM: r = a * b.
 * It is assumed that b is always positive.
 * @param r The result of the multiplication.
 * @param a One of the numbers to multiply.
 * @param b The other number to multiply.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_mul_ui(BIGNUM r, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_div_ui(BIGNUM q, BIGNUM r, BIGNUM a, block_t b);
 * Divides a BIGNUM by an unsigned integer: q = a / b where r is the remainder.
 * It is assumed that b is always positive.
 * @param q The quotient of the division.
 * @param r The remainder from the division.
 * @param a The dividend.
 * @param b The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_div_ui(BIGNUM q, BIGNUM r, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_div_ui_nr(BIGNUM q, BIGNUM a, block_t b);
 * Divides a BIGNUM by an unsigned integer: q = a / b.
 * It is assumed that b is always positive.
 * @param q The quotient of the division.
 * @param a The dividend.
 * @param b The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_div_ui_nr(BIGNUM q, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_mod_ui(BIGNUM r, BIGNUM a, block_t b);
 * Computes the remainder of a division of a BIGNUM by an unsigned integer: a / b, where r is the remainder.
 * @param r The remainder from the division.
 * @param a The dividend.
 * @param b The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_mod_ui(BIGNUM r, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_pow_ui(BIGNUM r, BIGNUM a, block_t b);
 * Computes r = c^b where b is assumed positive.
 * @param r The result of the exponentiation.
 * @param a The base.
 * @param b The exponent.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_pow_ui(BIGNUM r, BIGNUM a, block_t b);

/**
 * @fn int BIGNUM_pow_mod_ui(BIGNUM r, BIGNUM a, block_t b, BIGNUM m);
 * Computes r = c^b mod m, where b is assumed positive.
 * @param r The result of the exponentiation.
 * @param a The base.
 * @param b The exponent.
 * @param m The divisor.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_pow_mod_ui(BIGNUM r, BIGNUM a, block_t b, BIGNUM m);

#endif
