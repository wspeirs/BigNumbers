#ifndef BIGNUM_ASSIGN_H
#define BIGNUM_ASSIGN_H

#define INIT_SIZE	16	// that's enough for a 512-bit number

#include <bignum.h>

/**
 * @fn int BIGNUM_new(BIGNUM *arg, uint numbits);
 * Creates a new BIGNUM for use.
 * @param arg The BIGNUM to initilize.
 * @param numbits The number of bits to initilize the BIGNUM to.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_new(BIGNUM* arg, uint numbits);

/**
 * @fn int BIGNUM_resize(BIGNUM arg, uint num_blocks);
 * Resizes a BIGNUM to num_blocks number of blocks.
 * @param arg The BIGNUM to resize.
 * @param num_blocks The number of blocks to resize the BIGNUM to.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_resize(BIGNUM arg, uint num_blocks);

/**
 * @fn int BIGNUM_delete(BIGNUM arg);
 * Deletes a BIGNUM. After this call you cannot use the BIGNUM.
 * 
 * If this number is sensitive (like a key) you should call BIGNUM_set first to zero it out before deleting it.
 * @param arg The BIGNUM to delete.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_delete(BIGNUM arg);

/**
 * @fn int BIGNUM_set_hex(BIGNUM arg, char *hex);
 * Sets a BIGNUM from a string of hex characters.
 * @param arg The BIGNUM to set.
 * @param hex The string of hex characters representing a number.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_set_hex(BIGNUM arg, char *hex);

/**
 * @fn char *BIGNUM_get_hex(BIGNUM arg, char **str);
 * Returns a string of hex characters that represent the BIGNUM.
 * @param arg The BIGNUM to get.
 * @param str The string which contains the BIGNUM representation in hex. (MUST DELETE THIS MEMORY).
 * @return NULL on an error, or the string of hex characters representing the BIGNUM.
 */
char *BIGNUM_get_hex(BIGNUM arg, char **str);

/**
 * @fn int BIGNUM_cpy(BIGNUM dest, BIGNUM src);
 * Copies the number at src to the number at dest.
 * NOTE: Dest MUST already be setup with BIGNUM_new, otherwise use BIGNUM_new_cpy.
 * @param dest The destination number.
 * @param src The source number.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_cpy(BIGNUM dest, BIGNUM src);

/**
 * @fn int BIGNUM_new_cpy(BIGNUM *dest, BIGNUM src);
 * Copies the number at src to the number at dest.
 * NOTE: Dest MUST NOT already be setup with BIGNUM_new, otherwise use BIGNUM_cpy.
 * @param dest The destination number.
 * @param src The source number.
 * @return An error code which can be resolved via _GetErrStr().
 */
int BIGNUM_new_cpy(BIGNUM *dest, BIGNUM src);


#endif
