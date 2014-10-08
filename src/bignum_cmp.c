#include <bignum_cmp.h>

// this isn't included in any header file because we don't want the user calling it
// but there are functions, like the compare functions where it should be called
void BIGNUM_recalc_size(BIGNUM arg);

int BIGNUM_cmp(BIGNUM x, BIGNUM y)
{
	if(x->sign == y->sign)	// same sign
		return x->sign == 1 ? BIGNUM_cmp_abs(x, y) : -1 * BIGNUM_cmp_abs(x, y);
	
	return x->sign;		// signs are different, so just return x's sign
}

int BIGNUM_cmp_ui(BIGNUM x, block_t y)
{
	if(x->sign == 1)
		return BIGNUM_cmp_abs_ui(x, y);
	
	return x->sign;
}

int BIGNUM_cmp_abs(BIGNUM x, BIGNUM y)
{
	int	i;
	
	// start by recalculating the number size for each number
	BIGNUM_recalc_size(x);
	BIGNUM_recalc_size(y);

	if(x->num_size > y->num_size)
		return 1;	// x is larger
	
	else if(x->num_size < y->num_size)
		return -1;	// y is larger
	
	else	// same size numbers
	{
		for(i = x->num_size-1; i >= 0; --i)
			if(x->num[i] != y->num[i])
				return x->num[i] > y->num[i] ? 1 : -1;
	}
	
	return 0;	// they are equal
}

int BIGNUM_cmp_abs_ui(BIGNUM x, block_t y)
{
	BIGNUM_recalc_size(x);

	if(x->num_size > 1)
		return 1;	// x is larger
	
	if(x->num[0] == y)
		return 0;	// same number
	
	return x->num[0] > y ? 1 : -1;
}

int BIGNUM_sign(BIGNUM x)
{
	BIGNUM_recalc_size(x);	// recalc the number's size

	return x->num_size == 0 ? 0 : x->sign;
}

int BIGNUM_is_even(BIGNUM x)
{
	if(x->num_size == 0)
		return 0;

	return (x->num[0] & 0x1) == 1 ? 0 : 1;
}

int BIGNUM_is_odd(BIGNUM x)
{
	if(x->num_size == 0)
		return 0;

	return x->num[0] & 0x1;
}
