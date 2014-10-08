#include <bignum_num_theory.h>

void BIGNUM_recalc_size(BIGNUM arg);

int BIGNUM_gcd(BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM	g, tmp_a, tmp_b;
	
	if(BIGNUM_cmp_abs(a, b) < 0)	// a < b, switch the numbers and call it again
		return BIGNUM_gcd(r, b, a);
	
	// check to see if one of the numbers is zero
	if(BIGNUM_cmp_ui(a, 0) == 0)
	{
		BIGNUM_cpy(r, b);
		r->sign = 1;
		return NO_ERROR;
	}
	
	if(BIGNUM_cmp_ui(b, 0) == 0)
	{
		BIGNUM_cpy(r, a);
		r->sign = 1;
		return NO_ERROR;
	}
		
	BIGNUM_new(&g, 1);
	g->num[0] = 1;
	g->num_size = 1;
	
	BIGNUM_new_cpy(&tmp_a, a);
	BIGNUM_new_cpy(&tmp_b, b);
	
	tmp_a->sign = tmp_b->sign = 1;	// we always want 
	
// 	char	*str;
		
	// while both are even
	while(BIGNUM_is_even(tmp_a) && BIGNUM_is_even(tmp_b))
	{
		// could speed this up by scanning for the first 1, and shifting that amnt
		BIGNUM_rshift(tmp_a, 1);	// a = a / 2
		BIGNUM_rshift(tmp_b, 1);	// b = b / 2
		
		BIGNUM_lshift(g, 1);		// g = g * 2
		
// 		printf("A: %s\n", BIGNUM_get_hex(tmp_a, &str));
// 		printf("B: %s\n", BIGNUM_get_hex(tmp_b, &str));
// 		printf("G: %s\n", BIGNUM_get_hex(g, &str));
		
// 		return;
	}
	
	// while a != 0
	while(BIGNUM_cmp_ui(tmp_a, 0) != 0)
	{
		while(BIGNUM_is_even(tmp_a))
			BIGNUM_rshift(tmp_a, 1);	// a = a / 2
		
		while(BIGNUM_is_even(tmp_b))
			BIGNUM_rshift(tmp_b, 1);	// b = b / 2
		
		if(BIGNUM_cmp(tmp_a, tmp_b) >= 0)
		{
			BIGNUM_sub(tmp_a, tmp_a, tmp_b);
			tmp_a->sign = 1;	// |a - b|
			BIGNUM_rshift(tmp_a, 1);
		}
		
		else
		{
			BIGNUM_sub(tmp_b, tmp_a, tmp_b);
			tmp_b->sign = 1;	// |a - b|
			BIGNUM_rshift(tmp_b, 1);
		}
	}
	
	
	
	return BIGNUM_mul(r, g, tmp_b);
}

int BIGNUM_lcm(BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM	tmp;
	int	ret;
	
	BIGNUM_new(&tmp, 0);	// make a new BIGNUM
	
	if((ret = BIGNUM_mul(tmp, a, b)) < 0)	// multiply the numbers.
		return ret;
	
	tmp->sign = 1;	// make sure it's positive, |ab|
	
	if((ret = BIGNUM_gcd(r, a, b)) < 0)	// compute the GCD
		return ret;
	
	BIGNUM_recalc_size(r);
	
	if((ret = BIGNUM_div_nr(r, tmp, r)) < 0)	// divide: |ab| / gcd(a,b)
		return ret;
	
	BIGNUM_delete(tmp);
	
	return ret;
}
