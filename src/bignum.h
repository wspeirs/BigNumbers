#ifndef BIGNUM_H
#define BIGNUM_H

#include <config.h>

typedef uint_32 block_t;	///< The type used for the blocks
typedef uint_64 double_block_t;	///< The type used for sizeof(block_t)*2

#define BLOCKS_TO_BYTES(x)	( (x)*sizeof(block_t) )
#define BLOCKS_TO_BITS(x)	( (x)*(sizeof(block_t)*8) )
#define BITS_TO_BLOCKS(x)	( ((x)/(8*sizeof(block_t))) + ((x) % (8*sizeof(block_t)) == 0 ? 0 : 1) )
#define BYTES_TO_BLOCKS(x)	( ((x)/sizeof(block_t)) + ((x) % sizeof(block_t) == 0 ? 0 : 1) )

#define MIN(x,y)	((x) < (y) ? (x) : (y))
#define MAX(x,y)	((x) > (y) ? (x) : (y))

// the BIGNUM structure, holds a pointer to the number and the sign
struct BIGNUM_Struct
{
	block_t		*num;		///< Pointer to the memory for the number.
	uint		num_size;	///< The size in blocks of the number.
	uint		alloc_size;	///< The number of blocks allocated to the number.
	char		sign;		///< The sign of the intiger (1 = positive, -1 = negative).
};

typedef struct BIGNUM_Struct*	BIGNUM;

// include all the other files here, so you need only include bignum.h to use BIGNUM
#include <bignum_assign.h>
#include <bignum_arith.h>
#include <bignum_arith_ui.h>
#include <bignum_cmp.h>
#include <bignum_bit.h>
#include <bignum_mod_arith.h>
#include <bignum_num_theory.h>


#endif

