#include <bignum_arith_ui.h>

#include <bignum_bit.h>

// this isn't included in any header file because we don't want the user calling it
void BIGNUM_recalc_size(BIGNUM arg);

int BIGNUM_add_ui(BIGNUM r, BIGNUM a, block_t b)
{
	block_t		c = 0;
	uint		i;
	
	if(a->sign == -1)	// we have b - a, no savings here, prob a waste of time in fact :-(
	{
		BIGNUM	tmp_b;
		
		BIGNUM_new(&tmp_b, sizeof(block_t)*8);
		tmp_b->num[0] = b;
		
		return BIGNUM_sub(r, tmp_b, a);
	}
	
	BIGNUM_cpy(r, a);	// copy it over
	
	BIGNUM_resize(r, a->num_size+1);	// make sure we have enough room
	r->num_size++;
	
	r->num[0] += b;	// add in the number
	c = (r->num[0] < b ? 1 : 0);
	
	for(i=1; c; ++i)
	{
		r->num[i] += c;
		
		if(r->num[i] == 0)
			break;
	}
	
	BIGNUM_recalc_size(r);
	
	return NO_ERROR;
}

int BIGNUM_sub_ui(BIGNUM r, BIGNUM a, block_t b)
{
	block_t		barrow = 0, old_r;
	uint		i;
	
	if(a->sign == -1)	// we have -a - b, no savings here, prob a waste of time in fact :-(
	{
		BIGNUM	tmp_b;
		
		BIGNUM_new(&tmp_b, sizeof(block_t)*8);
		tmp_b->num[0] = b;
		tmp_b->sign = -1;
		
		return BIGNUM_add(r, a, tmp_b);
	}
	
	BIGNUM_cpy(r, a);	// copy it over
	
	BIGNUM_resize(r, a->num_size);	// make sure we have enough room
	
	old_r = r->num[0];	// save the old number
	
	r->num[0] -= b;	// subtract the number
	
	barrow = (r->num[0] > old_r ? 1 : 0);
	
	for(i=1; barrow; ++i)
	{
		old_r = r->num[i];
		
		r->num[i] -= barrow;
		
		if(r->num[i] < old_r)
			break;
	}
	
	BIGNUM_recalc_size(r);

	return NO_ERROR;	
}

int BIGNUM_mul_ui(BIGNUM r, BIGNUM a, block_t b)
{
	double_block_t	uv = 0;
	uint		i;
	
	BIGNUM_cpy(r, a);	// copy it over
	BIGNUM_resize(r, a->num_size+1);
	
	for(i=0; i < r->num_size; ++i)
	{
		uv = r->num[i] * (double_block_t)b + (uv >> (sizeof(block_t)*8));
		r->num[i] = uv & 0xFFFFFFFF;
	}
	
	r->num[i] = uv >> (sizeof(block_t)*8);
	
	r->num_size++;
	
	BIGNUM_recalc_size(r);
	
	return NO_ERROR;
}

int BIGNUM_div_ui(BIGNUM q, BIGNUM r, BIGNUM a, block_t b)
{
// 	int		i;
	BIGNUM		tmp, tmp_a;
	double_block_t	c;
// 	char		*str;
	
// 	printf("%s / %x\n", BIGNUM_get_hex(a, &str), b);
	
	// check if a < b, then just return the a as the remainder
	if(BIGNUM_cmp_ui(a, b) < 0)
	{
		BIGNUM_cpy(r, a);
		q->num[0] = q->num_size = 0;
		
		return NO_ERROR;
	}
	
	// setup q
	BIGNUM_resize(q, a->num_size);	// make q large enough
	q->num_size = a->num_size;
	memset(q->num, 0, BLOCKS_TO_BYTES(q->num_size));	// zero out q
	
	if(a->num_size == 1)
	{
		BIGNUM_resize(r, 1);
		
		q->num[0] = a->num[0] / b;
		r->num[0] = a->num[0] % b;
		
		BIGNUM_recalc_size(q);
		BIGNUM_recalc_size(r);
		
		return NO_ERROR;
	}
	
	// setup tmp
	BIGNUM_new(&tmp, BIGNUM_getbit_size(a));
	
	// copy over a
	BIGNUM_new_cpy(&tmp_a, a);
	
	while(BIGNUM_cmp_ui(tmp_a, b) >= 0 && tmp_a->num_size > 1)
	{
		c = (((double_block_t)tmp_a->num[tmp_a->num_size-1]<<(sizeof(block_t)*8)) + tmp_a->num[tmp_a->num_size-2]) / (double_block_t)b;	// do the division
		
// 		printf("C: %016llx\n", c);
		
		q->num[tmp_a->num_size-1] += c >> (sizeof(block_t)*8);
		q->num[tmp_a->num_size-2] += c & 0xFFFFFFFF;
		
// 		printf("q[%d]: %08x\n", tmp_a->num_size-1, q->num[tmp_a->num_size-1]);
// 		printf("q[%d]: %08x\n", tmp_a->num_size-2, q->num[tmp_a->num_size-2]);
		
		c *= (double_block_t)b;
		
// 		printf("C: %016llx\n", c);
		
		tmp->num_size = 2;
		tmp->num[1] = c >> (sizeof(block_t)*8);
		tmp->num[0] = c & 0xFFFFFFFF;
		
// 		printf("TMP_A SIZE: %d\n", tmp_a->num_size);
		
		BIGNUM_lshift(tmp, (sizeof(block_t)*8) * (tmp_a->num_size - 2));	// shift up
		
// 		printf("TMP_A: %s\n", BIGNUM_get_hex(tmp_a, &str));
// 		printf("  TMP: %s\n", BIGNUM_get_hex(tmp, &str));
		
		BIGNUM_sub(tmp_a, tmp_a, tmp);	// perform the subtraction
		
// 		printf("TMP_A: %s\n", BIGNUM_get_hex(tmp_a, &str));
	}
	
	// we're done, set the remainder
	if(BIGNUM_cmp_ui(tmp_a, b) < 0)
	{
		BIGNUM_cpy(r, tmp_a);
		BIGNUM_recalc_size(q);
	}
	
	// one more division to perform
	else
	{
		return NOT_IMPLEMENTED;
	}
	
	return NO_ERROR;
}

int BIGNUM_div_ui_nr(BIGNUM q, BIGNUM a, block_t b)
{
	BIGNUM	r;
	
	//
	// No savings here... just makes it easier for the programmer
	//
	
	BIGNUM_new(&r, 0);		// create a remainder
	
	BIGNUM_div_ui(q, r, a, b);	// do the division
	
	BIGNUM_delete(r);	// delete the remainder
	
	return NO_ERROR;
}

int BIGNUM_mod_ui(BIGNUM r, BIGNUM a, block_t b)
{
	BIGNUM	q;
	
	//
	// No savings here... just makes it easier for the programmer
	//
	
	BIGNUM_new(&q, 0);		// create a quotient
	
	BIGNUM_div_ui(q, r, a, b);	// do the division
	
	BIGNUM_delete(q);	// delete the quotient
	
	return NO_ERROR;
}


int BIGNUM_pow_ui(BIGNUM r, BIGNUM a, block_t b)
{
	//
	// We go through and compute either a square or a multiplication
	//
	BIGNUM	res = r;
	block_t	t = 0x80000000;

	//
	// Deal with "base cases"
	//
	if(b == 0)	// x^0 = 1
		return BIGNUM_set_hex(r, "1");
	
// 	if(b == 1)	// x^1 = x
// 		return BIGNUM_mod(r, a, m);
	
	// they are the same, so we need a new number
	if(r == a)
		BIGNUM_new_cpy(&res, a);
	else
		BIGNUM_cpy(res, a);
	
	
	// move the bit until we find one that is set
	while((b & t) == 0)
		t >>= 1;
	
	while(1)
	{
		t >>= 1;
		
		if(t == 0)
			break;
		
		BIGNUM_sqr(res, res);	// square
		
		if(b & t)
			BIGNUM_mul(res, res, a);	// multiply
	}
	
	if(res != r)
		BIGNUM_cpy(r, res);	// copy over res
	
	return NO_ERROR;
}

int BIGNUM_pow_mod_ui(BIGNUM r, BIGNUM a, block_t b, BIGNUM m)
{
	//
	// Same algo as above, we just do it mod m
	//
	BIGNUM	res = r;
	block_t	t = 0x80000000;

	//
	// Deal with "base cases"
	//
	if(b == 0)	// x^0 = 1
		return BIGNUM_set_hex(r, "1");
	
	if(b == 1)	// x^1 = x
		return BIGNUM_mod(r, a, m);
	
	// they are the same, so we need a new number
	if(r == a || r == m)
		BIGNUM_new_cpy(&res, a);
	else
		BIGNUM_cpy(res, a);
	
	// move the bit until we find one that is set
	while((b & t) == 0)
		t >>= 1;
	
	while(1)
	{
		t >>= 1;
		
		if(t == 0)
			break;
		
		BIGNUM_sqr_mod(res, res, m);	// square
		
		if(b & t)
			BIGNUM_mul_mod(res, res, a, m);	// multiply
	}
	
	if(res != r)
		BIGNUM_cpy(r, res);	// copy over res
	
	return NO_ERROR;
}

