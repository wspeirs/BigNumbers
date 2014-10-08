#ifndef BIGNUM_BIT_H
#define BIGNUM_BIT_H

#include <bignum.h>

/**
 * @fn void BIGNUM_lshift(BIGNUM arg, block_t amnt)
 * Bit shift the BIGNUM to the left by amnt.
 * @param arg The BIGNUM to bit shift.
 * @param amt The amount (in bits) to shift.
 */
void BIGNUM_lshift(BIGNUM arg, block_t amnt);

/**
 * @fn void BIGNUM_rshift(BIGNUM arg, block_t amnt)
 * Bit shift the BIGNUM to the right by amnt.
 * @param arg The BIGNUM to bit shift.
 * @param amt The amount (in bits) to shift.
 */
void BIGNUM_rshift(BIGNUM arg, block_t amnt);


/**
 * @fn int BIGNUM_setbit(BIGNUM arg, block_t bit)
 * Sets a bit in the _BI. Indexed by 0.
 * @param arg The BIGNUM to bit set.
 * @param amt The bit to set.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_setbit(BIGNUM arg, block_t bit);

/**
 * @fn int BIGNUM_clearbit(BIGNUM arg, block_t bit)
 * Clears a bit in the _BI. Indexed by 0.
 * @param arg The BIGNUM to bit clear.
 * @param amt The bit to clear.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_clearbit(BIGNUM arg, block_t bit);

/**
 * @fn ulong BIGNUM_getbit_size(BIGNUM arg);
 * Returns the size of the BIGNUM in bits.
 * @param arg The _BI's size in bits to get
 * @return The size of the BIGNUM in bits.
 */
ulong BIGNUM_getbit_size(BIGNUM arg);

#endif
