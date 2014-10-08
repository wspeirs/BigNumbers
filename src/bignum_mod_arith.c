#include <bignum_mod_arith.h>

int BIGNUM_add_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m)
{
	BIGNUM	tmp_a, tmp_b;
	int	ret;

	// check that m > 0
	if(BIGNUM_sign(m) <= 0)
		return DIVIDE_BY_ZERO;
	
	BIGNUM_new_cpy(&tmp_a, a);
	BIGNUM_new_cpy(&tmp_b, b);
	
	// check if |a| and/or |b| are larger than m, then do a division first
	if(BIGNUM_cmp_abs(a, m) >= 0)
	{
		if((ret = BIGNUM_mod(tmp_a, a, m)) < 0)
			return ret;
	}
	
	if(BIGNUM_cmp_abs(b, m) >= 0)
	{	
		if((ret = BIGNUM_mod(tmp_b, b, m)) < 0)
			return ret;
	}
	
	// now |a| and |b| are less than m, so just do the add and adjust
	if((ret = BIGNUM_add(r, tmp_a, tmp_b)) < 0)
		return ret;
		
	if(BIGNUM_sign(r) < 0)	// negative number, so need to add m
		return BIGNUM_add(r, r, m);
		
	if(BIGNUM_cmp(r, m) >= 0)	// r >= m, so subtract m
		return BIGNUM_sub(r, r, m);
		
	// if we got here, everything is OK, so just return ret
	return ret;
}

int BIGNUM_sub_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m)
{
	BIGNUM	tmp_a, tmp_b;
	int	ret;

	// check that m > 0
	if(BIGNUM_sign(m) <= 0)
		return DIVIDE_BY_ZERO;
	
	BIGNUM_new_cpy(&tmp_a, a);
	BIGNUM_new_cpy(&tmp_b, b);
	
	// check if |a| and/or |b| are larger than m, then do a division first
	if(BIGNUM_cmp_abs(a, m) >= 0)
	{
		if((ret = BIGNUM_mod(tmp_a, a, m)) < 0)
			return ret;
	}
	
	if(BIGNUM_cmp_abs(b, m) >= 0)
	{
		if((ret = BIGNUM_mod(tmp_b, b, m)) < 0)
			return ret;
	}
		
	// now |a| and |b| are less than m, so just do the sub and adjust
	if((ret = BIGNUM_sub(r, tmp_a, tmp_b)) < 0)
		return ret;
		
	if(BIGNUM_sign(r) < 0)	// negative number, so need to add m
		return BIGNUM_add(r, r, m);
		
	if(BIGNUM_cmp(r, m) >= 0)	// r >= m, so subtract m
		return BIGNUM_sub(r, r, m);
		
	// if we got here, everything is OK, so just return ret
	return ret;
}

int BIGNUM_mul_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m)
{
	int	ret;

	if((ret = BIGNUM_mul(r, a, b)) < 0)	// mul the numbers
		return ret;

	ret = BIGNUM_mod(r, r, m);	// get the remainder
	
	return ret;
}

int BIGNUM_sqr_mod(BIGNUM r, BIGNUM a, BIGNUM m)
{
	int	ret;

	if((ret = BIGNUM_sqr(r, a)) < 0)	// sqr the numbers
		return ret;

	ret = BIGNUM_mod(r, r, m);	// get the remainder
	
	return ret;
}

int BIGNUM_pow_mod(BIGNUM r, BIGNUM a, BIGNUM b, BIGNUM m)	// r = a^b mod m
{
	BIGNUM	tmp_r = r, tmp_b;
	BIGNUM	a_max;
	
	if(r == a || r == b || r == m)
		BIGNUM_new(&tmp_r, BIGNUM_getbit_size(m));	
	
	// check to see if b = 0
	if(BIGNUM_cmp_ui(b, 0) == 0)
	{
		BIGNUM_set_hex(r, "1");		// a^0 mod m = 1
		
		return NO_ERROR;
	}
	
	// check if b = 1
	if(BIGNUM_cmp_ui(b, 1) == 0)
	{
		BIGNUM_cpy(tmp_r, a);		// a^1 mod m = a mod m
		BIGNUM_mod(tmp_r, tmp_r, m);
		
		if(tmp_r != r)
			BIGNUM_cpy(r, tmp_r);
	
		return NO_ERROR;
	}
	
	BIGNUM_new_cpy(&tmp_b, b);	// make a copy of b
	
	// pre-compute a^0xFF...FF
	BIGNUM_new(&a_max, 1);
	BIGNUM_pow_mod_ui(a_max, a, 0xFFFFFFFF, m);
	
	BIGNUM_set_hex(tmp_r, "1");	// set r = 1
	
	char *str;
	
	while(BIGNUM_cmp_abs_ui(tmp_b, 0xFFFFFFFF) > 0)
	{
		BIGNUM_sub_ui(tmp_b, tmp_b, 0xFFFFFFFF);	// b = b - 0xFF..FF
		
		printf("B: %s\n", BIGNUM_get_hex(tmp_b, &str));
		
		BIGNUM_mul_mod(tmp_r, tmp_r, a_max, m);		// r = r * a_max mod m
	}
	
	if(BIGNUM_cmp_ui(tmp_b, 0) != 0)	// if we are not done
	{
		BIGNUM_pow_mod_ui(a_max, a, tmp_b->num[0], m);	// a_max = a^last_num
// 		printf("A MAX: %s\n", BIGNUM_get_hex(a_max, &str));
		BIGNUM_mul_mod(tmp_r, tmp_r, a_max, m);	// r = r * a_max mod m
	}
	
	if(r != tmp_r)
		BIGNUM_cpy(r, tmp_r);
	
	return NO_ERROR;
}
