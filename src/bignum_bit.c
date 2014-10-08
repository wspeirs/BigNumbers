#include <bignum_bit.h>

void BIGNUM_recalc_size(BIGNUM arg);

// left shift arg by amnt; like arg * 2^amt
void BIGNUM_lshift(BIGNUM arg, block_t amnt)
{
	int		i;
	block_t		blks = amnt / (sizeof(block_t)*8);
	uint		shift = amnt % (sizeof(block_t)*8);
	uint		inv_shift = sizeof(block_t)*8 - shift;
	
	
// 	char	*str;
	
	// no shift needed
	if(amnt == 0)
		return;

	// resize the number
	BIGNUM_resize(arg, arg->num_size + BITS_TO_BLOCKS(amnt) + 1);
	
	for(i = arg->num_size + blks; (unsigned)i >= blks + 1; --i)
	{
		if(shift == 0)
			arg->num[i-1] = arg->num[i - blks - 1];

		else
			arg->num[i] |= arg->num[i - blks - 1] >> inv_shift;
			arg->num[i - 1] = arg->num[i - blks - 1] << shift;
	}
	
	// zero out the rest of the number
	for(--i ; i >= 0; --i)
		arg->num[i] = 0;
	
	arg->num_size += blks+1;	// update the size
	
	BIGNUM_recalc_size(arg);
}

// right shift arg by amnt; like arg / 2^amt
void BIGNUM_rshift(BIGNUM arg, block_t amnt)
{
	block_t		i;
	block_t		blks = amnt / (sizeof(block_t)*8);
	uint		shift = amnt % (sizeof(block_t)*8);
	uint		inv_shift = sizeof(block_t)*8 - shift;
	
	// we've shifted off the end
	if(amnt >= sizeof(block_t) * 8 * arg->num_size)
	{
		BIGNUM_set_hex(arg, "0");
		return;
	}
	
	// no shift needed
	if(amnt == 0)
		return;
	
	for(i = 0; i < arg->num_size - blks - 1; ++i)
	{
		arg->num[i] = arg->num[i + blks] >> shift;
		arg->num[i] |= arg->num[i + blks + 1] << inv_shift;
	}
	
	arg->num[i] = arg->num[i + blks] >> shift;
	arg->num_size -= blks;	// adjust the size
}

int BIGNUM_setbit(BIGNUM arg, block_t bit)
{
	block_t		blk = bit / (sizeof(block_t) * 8);
	block_t		a = 0x1 << (bit % (sizeof(block_t) * 8));

	// not enough memory, so make more
	if(blk >= arg->alloc_size)
		BIGNUM_resize(arg, blk + 1);
	
	if(bit == 0)
		arg->num[0] |= 0x1;
	
	else
		arg->num[blk] |= a;
	
	BIGNUM_recalc_size(arg);
		
	return NO_ERROR;
}

int BIGNUM_clearbit(BIGNUM arg, block_t bit)
{
	block_t		blk = bit / (sizeof(block_t) * 8);
	block_t		a = 0x1 << (bit % (sizeof(block_t) * 8));

	if(blk >= arg->num_size)
		return NO_MEM;	// TODO: Change this to a real error later
	
	if(bit == 0)
		arg->num[0] &= 0xFFFFFFFE;
	
	else
		arg->num[blk] &= ~a;
	
	return NO_ERROR;
}

ulong BIGNUM_getbit_size(BIGNUM arg)
{
	block_t		mask = 0x1 << (sizeof(block_t) * 8 - 1);
	ulong		size = BLOCKS_TO_BITS(arg->num_size);
	
	if(size == 0)
		return size;
	
	while((mask & arg->num[arg->num_size-1]) == 0)
	{
		mask >>= 1;
		--size;
	}
	
	return size;	
}
