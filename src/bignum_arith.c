#include <bignum_arith.h>

#include <bignum_cmp.h>
#include <bignum_bit.h>

// this isn't included in any header file because we don't want the user calling it
void BIGNUM_recalc_size(BIGNUM arg);

// r can *NOT* be the same as b
// Signs are *NOT* considered
static int BIGNUM_INTERNAL_ADD(BIGNUM r, BIGNUM a, BIGNUM b)
{
	block_t	carry = 0, *ptr = NULL;
	uint	i;
	uint	minBlocks = MIN(a->num_size, b->num_size);

	BIGNUM_resize(r, MAX(a->num_size, b->num_size) + 1);	// make r big enough
	
	for(i=0; i < minBlocks; ++i)
	{
		r->num[i] = a->num[i] + b->num[i] + carry;	// do the addition
		
// 		PRINTF("%08X + %08X + %d = %08X\n", a->num[i], b->num[i], carry, r->num[i]);
		
		carry = (r->num[i] < b->num[i] ? 1 : 0);	// set the carry bit if needed
	}
	
// 	PRINTF("CARRY: %d\n", carry);
	
	// figure out if we need to find the longer one and continue
	if(a->num_size > b->num_size)
	{
		ptr = &a->num[i];
		minBlocks = a->num_size;
	}
	
	else if(a->num_size < b->num_size)
	{
		ptr = &b->num[i];
		minBlocks = b->num_size;
	}
	
	// continue the "addition" if needed
	for( ; i < minBlocks; ++i)
	{
// 		PRINTF("%08X + %d = %08X\n", *ptr, carry, r->num[i]);
		
		r->num[i] = *(ptr++) + carry;
		carry = (r->num[i] == 0x0 ? 1 : 0);
	}
	
	r->num[i] = carry;	// in case we have a carry on the last one
	r->num_size = i+1;	// set the number's size
	
	return NO_ERROR;
}

int BIGNUM_add(BIGNUM r, BIGNUM a, BIGNUM b)
{
	// check for 1 number that is zero
	if(BIGNUM_cmp_ui(a, 0) == 0)
	{
		BIGNUM_cpy(r, b);
		return NO_ERROR;	
	}
	
	if(BIGNUM_cmp_ui(b, 0) == 0)
	{
		BIGNUM_cpy(r, a);
		return NO_ERROR;
	}
	
	// both positive or both negative
	if(a->sign == b->sign)
	{
		if(r == b)
			BIGNUM_INTERNAL_ADD(r, b, a);
		
		else
			BIGNUM_INTERNAL_ADD(r, a, b);
		
		r->sign = b->sign;	// set the sign
	}
	
	// a is negative
	else if(a->sign == -1)
	{
		a->sign = 1;
		BIGNUM_sub(r, b, a);
		if(r != a)
			a->sign = -1;
	}
	
	// b is negative
	else
	{
		b->sign = 1;
		BIGNUM_sub(r, a, b);
		if(r != b)
			b->sign = -1;
	}
	
	return NO_ERROR;
}

// preforms a - b without consideration of sign
static int BIGNUM_INTERNAL_SUB(BIGNUM r, BIGNUM a, BIGNUM b)
{
	block_t	barrow = 0, nextBarrow = 0, *ptr;
	uint	i;
	uint	minBlocks = MIN(a->num_size, b->num_size);

	BIGNUM_resize(r, MAX(a->num_size, b->num_size) + 1);	// make r big enough
	
	for(i=0; i < minBlocks; ++i)
	{
		nextBarrow = ( a->num[i] < (b->num[i] + barrow) ? 1 : 0 );	// calc the barrow
		
		r->num[i] = a->num[i] - b->num[i] - barrow;	// do the subtraction
		
// 		PRINTF("%08X - %08X + %d = %08X\n", a->num[i], b->num[i], barrow, r->num[i]);
		
		barrow = nextBarrow;	// update the barrow
	}
	
// 	PRINTF("BARROW: %d\n", barrow);
	
	// figure out if we need to find the longer one and continue
	if(a->num_size > b->num_size)
	{
		ptr = &a->num[i];
		minBlocks = a->num_size;
	}
	
	else if(a->num_size < b->num_size)
	{
		ptr = &b->num[i];
		minBlocks = b->num_size;
	}
	
	// continue the "addition" if needed
	for( ; i < minBlocks; ++i)
	{
// 		PRINTF("%08X + %d = %08X\n", *ptr, carry, r->num[i]);
		
		r->num[i] = *(ptr++) - barrow;
		barrow = (r->num[i] == 0xFFFFFFFF ? 1 : 0);
	}
	
// 	r->num[i] = barrow;	// in case we have a carry on the last one
	r->num_size = i+1;	// set the number's size
	
	return NO_ERROR;
}

int BIGNUM_sub(BIGNUM r, BIGNUM a, BIGNUM b)
{
	// check for 1 number that is zero
	if(BIGNUM_cmp_ui(a, 0) == 0)
	{
		BIGNUM_cpy(r, b);
		r->sign = -1 * b->sign;
		return NO_ERROR;	
	}
	
	if(BIGNUM_cmp_ui(b, 0) == 0)
	{
		BIGNUM_cpy(r, a);
		return NO_ERROR;
	}
	
	// signs different, so we add
	if(a->sign != b->sign)
	{
		if(r == b)
			BIGNUM_INTERNAL_ADD(r, b, a);
		else
			BIGNUM_INTERNAL_ADD(r, a, b);
		r->sign = a->sign;
	}
	
	// same sign
	else
	{
		switch(BIGNUM_cmp_abs(a, b))
		{
		case 0:		// a = b, so r = 0
			BIGNUM_set_hex(r, "0");
			break;
			
		case 1:		// a > b, so do a normal subtraction
			BIGNUM_INTERNAL_SUB(r, a, b);
			r->sign = a->sign;
			break;
			
		case -1:	// a < b, so switch the numbers, do the subtraction, then set the sign as negative
			BIGNUM_INTERNAL_SUB(r, b, a);
			r->sign = -1 * a->sign;
			break;
		}
	}
	
	return NO_ERROR;
}

int BIGNUM_mul(BIGNUM r, BIGNUM a, BIGNUM b)
{
	block_t		*w;
	block_t		c;
	double_block_t	uv = 0;
	uint		i,j;
	
	BIGNUM_recalc_size(a);	// resize the numbers just in case
	BIGNUM_recalc_size(b);
	
// 	char	*str;
	
// 	printf("A: %s * B: %s\n\n", BIGNUM_get_hex(a, &str), BIGNUM_get_hex(b, &str));
	
	w = (block_t*)MALLOC(BLOCKS_TO_BYTES(a->num_size + b->num_size)); // the max size the new number could be
	
	memset(w, 0, BLOCKS_TO_BYTES(a->num_size + b->num_size));	// zero out the number
	
// 	printf("A SIZE: %d\tB SIZE: %d\n", a->num_size, b->num_size);
	
	double_block_t	tmp_a, tmp_b;
	
	for(i = 0; i < a->num_size; ++i)
	{
		c = 0;
		
		for(j = 0; j < b->num_size; ++j)
		{
			tmp_a = a->num[i];
			tmp_b = b->num[j];
			
// 			printf("W: %08x\tB: %08X\tA: %08X\tC: %08x\n", w[i+j], b->num[j], a->num[i], c);
// 			printf("RES: %016llx\n", tmp_b * tmp_a);
			
// 			uv = w[i+j] + (b->num[j] * (double_block_t)a->num[i]) + c;
			uv = w[i+j] + (tmp_b * tmp_a) + c;
			
// 			printf(" uv: %016llX\tc: %08X\tw[%d+%d]: %08X\n\n", uv, c, i, j, w[i+j]);
// 			printf("%d %d: %08x + (%08x * %08x)%016llx + %08x\n", i, j, w[i+j], b->num[j], a->num[i], (b->num[j] * (double_block_t)a->num[i]), c);
			
			w[i+j] = uv & 0xFFFFFFFF;
			c = uv >> (sizeof(block_t)*8);

		}
		
		w[i+b->num_size] = uv >> (sizeof(block_t)*8);
		
/*		printf("W: ");
		for(j=a->num_size + b->num_size-1; j >= 0; --j)
			printf("%08X ", w[j]);
		printf("\n");*/
	}
	
	FREE(r->num);	// free the memory that was there
	r->num = w;	// switch the pointers
	r->num_size = r->alloc_size = a->num_size + b->num_size;	// set the number's size
	r->sign = r->num_size == 0 ? 1 : a->sign * b->sign;	// set the sign
	
	BIGNUM_recalc_size(r);
	
	return NO_ERROR;
}

int BIGNUM_sqr(BIGNUM r, BIGNUM a)
{
	block_t		*w;
	block_t		c;
	double_block_t	uv = 0;
	uint		i,j;
	
	BIGNUM_recalc_size(a);	// resize the number just in case
	
	w = (block_t*)MALLOC(BLOCKS_TO_BYTES(2 * a->num_size)); // the max size the new number could be
	
	memset(w, 0, BLOCKS_TO_BYTES(2 * a->num_size));	// zero out the number
	
	for(i = 0; i < a->num_size-1; ++i)
	{
		c = 0;
		
		for(j = i+1; j < a->num_size; ++j)
		{
			uv = (double_block_t)w[i+j] + (double_block_t)a->num[i] * (double_block_t)a->num[j] + (double_block_t)c;
			
//  			printf("uv: %016llX\tc: %08X\tw[%d+%d]: %08X\n", uv, c, i, j, w[i+j]);
			
			w[i+j] = uv & 0xFFFFFFFF;
			c = uv >> (sizeof(block_t)*8);
		}
		
		w[i+j] = c;
/*		printf("W: ");
		for(j=a->num_size + b->num_size-1; j >= 0; --j)
		printf("%08X ", w[j]);
		printf("\n");*/
	}
	
	c = 0;
	
	for(i = 0; i < 2 * a->num_size; ++i)
	{
		uv = 2 * (double_block_t)w[i] + c;
		w[i] = uv & 0xFFFFFFFF;
		c = uv >> (sizeof(block_t)*8);
// 		printf("C: %d\n", c);
	}
	
	w[2 * a->num_size - 1] += c;
// 	printf("INDEX: %d\n", 2 * a->num_size - 1);
	c = 0;
	
	for(i = 0; i < a->num_size; ++i)
	{
		uv = (double_block_t)w[2*i] + (double_block_t)a->num[i] * (double_block_t)a->num[i] + (double_block_t)c;
		w[2*i] = uv & 0xFFFFFFFF;
		c = uv >> (sizeof(block_t)*8);
		
		uv = (double_block_t)w[2*i + 1] + c;
		w[2*i+1] = uv & 0xFFFFFFFF;
		c = uv >> (sizeof(block_t)*8);
// 		printf("*C: %d\n", c);
	}
	
// 	printf("C: %d\n", c);
// 	printf("INDEX: %d\n", 2*i-1);
	w[2*i-1] += c;	
	
	FREE(r->num);	// free the memory that was there
	r->num = w;	// switch the pointers
	r->num_size = r->alloc_size = 2 * a->num_size;		// set the number's size
	r->sign = r->num_size == 0 ? 1 : a->sign * a->sign;	// set the sign
	
	return NO_ERROR;
}

int BIGNUM_div(BIGNUM q, BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM	tmp_b, tmp_r = r, tmp_q = q;
	int	amt, bbits = BIGNUM_getbit_size(b);
	int	sign = a->sign * b->sign;
	
	char *str;
	
	// if a = b, then q = 1 and r = 0
	if(a == b)
	{
		BIGNUM_set_hex(q, "1");
		BIGNUM_set_hex(r, "0");
		return NO_ERROR;
	}
	
	// check to see if q = a or b
	if(q == a || q == b)
		BIGNUM_new(&tmp_q, 0);
	
	// check to see if r = a or b
	if(r == a || r == b)
		BIGNUM_new(&tmp_r, BIGNUM_getbit_size(a));
		
	BIGNUM_cpy(tmp_r, a);	// copy a over into tmp_r
	tmp_r->sign = 1;	// set to a positive sign
	
	BIGNUM_new_cpy(&tmp_b, b);	// copy over b into it's tmp
	tmp_b->sign = 1;		// set to a positive sign

	BIGNUM_resize(tmp_q, a->num_size - b->num_size + 1);	// make q large enough
	tmp_q->num_size = a->num_size - b->num_size + 1;
	
// 	int	i = 0;
	
	while(BIGNUM_cmp_abs(tmp_r, b) >= 0)
	{
// 		printf("B: %s\n", BIGNUM_get_hex(b, &str));
		BIGNUM_cpy(tmp_b, b);
		tmp_b->sign = 1;	// set to a positive sign
		
// 		printf("BEFORE: %s\n", BIGNUM_get_hex(tmp_b, &str));
// 		printf("B: %s\n", BIGNUM_get_hex(b, &str));
		
		amt = BIGNUM_getbit_size(tmp_r) - bbits;
		
		BIGNUM_lshift(tmp_b, amt);
		
		
		if(BIGNUM_cmp(tmp_r, tmp_b) < 0)
		{
			--amt;
			
// 			printf("BEFORE: %s\n", BIGNUM_get_hex(tmp_b, &str));

			BIGNUM_rshift(tmp_b, 1);
			
// 			printf("AFTER: %s\n", BIGNUM_get_hex(tmp_b, &str));
		}
		 
// 		printf("tmp_r: %s\n", BIGNUM_get_hex(tmp_r, &str));
// 		printf("tmp_b: %s\n", BIGNUM_get_hex(tmp_b, &str));
		
		BIGNUM_sub(tmp_r, tmp_r, tmp_b);
		
// 		printf("tmp_r: %s\n\n", BIGNUM_get_hex(tmp_r, &str));
		
		BIGNUM_setbit(tmp_q, amt);
		
// 		printf("q: %s\n\n", BIGNUM_get_hex(tmp_q, &str));
	}
	
	BIGNUM_recalc_size(tmp_q);
	tmp_q->sign = sign;
	
	tmp_r->sign = a->sign;
	
	if(tmp_r != r)
		BIGNUM_cpy(r, tmp_r);
	
	if(tmp_q != q)
		BIGNUM_cpy(q, tmp_q);
	
	return NO_ERROR;
}

/*
// my straight forward attempt
int BIGNUM_div(BIGNUM q, BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM		tmpbignum;
	double_block_t	tmp;
	block_t		tmp_q;
	int		i;
	char		*str;
	
	printf("A: %s\n", BIGNUM_get_hex(a, &str));
	printf("B: %s\n\n", BIGNUM_get_hex(b, &str));
	
	BIGNUM_cpy(r, a);	// set r = a
	BIGNUM_new(&tmpbignum, 0);	// make a tmp BI 
	
	BIGNUM_resize(q, a->num_size - b->num_size + 1);	// make q large enough
	q->num_size = a->num_size - b->num_size + 1;

	
	for(i=0; BIGNUM_cmp(r, b) > 0; ++i)
	{
		if(r->num[r->num_size-1] < b->num[b->num_size-1])	// need to do 2 at once
		{
			tmp = r->num[r->num_size-1];
			tmp <<= 32;
			tmp += r->num[r->num_size-2];
			
			printf("IN HERE\n");
		}
		
		else
			tmp = r->num[r->num_size-1];
		
		q->num[q->num_size-1-i] = tmp / b->num[b->num_size-1];
		
		printf("TMP_Q: %08x\n", q->num[q->num_size-1-i]);
		
		BIGNUM_mul_ui(tmpbignum, b, q->num[q->num_size-1-i]);
		
//		BIGNUM_lshift(tmpbignum, BIGNUM_getbit_size(r) - BIGNUM_getbit_size(b) - (i * 32));
		
		printf("T: %s\n\n", BIGNUM_get_hex(tmpbignum, &str));

		BIGNUM_lshift(tmpbignum, (r->num_size - tmpbignum->num_size) * 32);
		
		printf("TMP_Q: %08x\n", q->num[q->num_size-1-i]);
		printf("R: %s\n", BIGNUM_get_hex(r, &str));
		printf("T: %s\n", BIGNUM_get_hex(tmpbignum, &str));
		
		BIGNUM_sub(r, r, tmpbignum);
		
		printf("R: %s\n\n", BIGNUM_get_hex(r, &str));
		
	}
	
	return NO_ERROR;
}
*/

/*
#define MIN(x,y) ( (x) > (y) ? (y) : (x) )

int BIGNUM_div(BIGNUM q, BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM		ad, bd, tmpbignum;
	block_t		d = 1;
	int		i, j;
	block_t		qh;
	double_block_t	tmp;
	block_t		qb[3];
	
	char		*str;
	
	BIGNUM_new_cpy(&ad, a);
	BIGNUM_new_cpy(&bd, b);
	
	// calculate the scaling factor d
	while(d * b->num[b->num_size-1] >= 0x7FFFFFFF)
		d <<= 1;	
	
	printf("D: %d\n", d);
	printf("A: %s\n", BIGNUM_get_hex(a, &str));
	printf("B: %s\n\n", BIGNUM_get_hex(b, &str));
	
	// multiply by the scaling factor d
	if(d != 1)
	{
		BIGNUM_mul_ui(ad, a, d);
		BIGNUM_mul_ui(bd, b, d);
	}
	
	printf("AD: %s\n", BIGNUM_get_hex(ad, &str));
	printf("BD: %s\n\n", BIGNUM_get_hex(bd, &str));
	
	// copy a over to r
	BIGNUM_cpy(r, a);
	
	BIGNUM_new(&tmpbignum, 0);
	
	for(i = a->num_size-1, j = (a->num_size - b->num_size)-1; i >= b->num_size; --i, --j)
	{
		tmp = r->num[i];
		tmp <<= 32;
		tmp += r->num[i-1];
		
		printf("TMP: %llx\n", tmp);
		printf("bd: %x\n", bd->num[bd->num_size-1]);
		
		tmp /= (double_block_t)bd->num[bd->num_size-1];
		
		while(tmp > 0xFFFFFFFF)
			tmp >>= 4;
		
		printf("TMP: %0llx\n", tmp);
		
		qh = MIN(tmp, 0xFFFFFFFE);
		
		printf("qh: %x\n\n", qh);
		
		tmp = bd->num[bd->num_size-1] * (double_block_t)qh;
		
		printf("TMP: %llx\n\n", tmp);
		
		qb[2] = tmp >> 32;
		qb[1] = tmp & 0xFFFFFFFF;
		
		tmp = bd->num[bd->num_size-2] * (double_block_t)qh;
		
		printf("TMP: %llx\n\n", tmp);
		printf("qb[1]: %x\n", qb[1]);
		
		qb[1] += tmp >> 32;
		
		printf("qb[1]: %x\n", qb[1]);
		
		
		if(qb[1] < (tmp >> 32))
			++qb[2];
		
		qb[0] = tmp & 0xFFFFFFFF;
		
		
		printf("%x > %x\n", qb[2], r->num[i]);
		printf("%x > %x\n", qb[1], r->num[i-1]);
		printf("%x > %x\n", qb[0], r->num[i-2]);
		printf("\n");
		
		while( qb[2] > r->num[i] || 
		      (qb[2] == r->num[i] && qb[1] > r->num[i-1]) ||
		      (qb[2] == r->num[i] && qb[1] == r->num[i-1] && qb[0] > r->num[i-2]))
		{
			--qh;
			printf("qh: %x\n", qh);
			
			tmp = bd->num[bd->num_size-1] * (double_block_t)qh;
		
			qb[2] = tmp >> 32;
			qb[1] = tmp & 0xFFFFFFFF;
		
			tmp = bd->num[bd->num_size-2] * (double_block_t)qh;
		
			qb[1] += tmp >> 32;
			qb[0] = tmp & 0xFFFFFFFF;
		}
		
		BIGNUM_mul_ui(tmpbignum, b, qh);
		
		printf("     R: %s\n", BIGNUM_get_hex(r, &str));
		printf("TMPBIGNUM: %s\n", BIGNUM_get_hex(tmpbignum, &str));
		
		if(BIGNUM_cmp(r, tmpbignum) < 0)
			--qh;
		
		printf("qh: %x\n", qh);
		
		BIGNUM_sub(r, r, tmpbignum);
			
		
		return NO_ERROR;
	}
	
	return NO_ERROR;
}*/

/*
int BIGNUM_div(BIGNUM q, BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM		tmp_b, tmp_a;
	int		i;
	block_t		c = 0, qb[3] = {0x0, 0x0, 0x0};
	double_block_t	uv;
	
	// check for division by zero
	if(BIGNUM_cmp_ui(b, 0) == 0)
		return DIVIDE_BY_ZERO;
	
	BIGNUM_resize(q, a->num_size - b->num_size + 1);	// make q large enough
	q->num_size = a->num_size - b->num_size + 1;
	memset(q->num, 0, BLOCKS_TO_BYTES(q->num_size));	// zero out q
	
	printf("A SIZE: %d\tB SIZE: %d\n", a->num_size, b->num_size);
	
	// check to see if a < b, if so return b as the remainder
	if(BIGNUM_cmp(a, b) < 0)
	{
		q->num_size = 0;	// make q = 0
		BIGNUM_cpy(r, a);	// set the remainder to a
		
		return NO_ERROR;
	}
	
	// check to see if they are both just 1 long
	if(a->num_size == 1 && a->num_size == b->num_size)
	{
		q->num[0] = a->num[0] / b->num[0];	// preform the division
		r->num[0] = a->num[0] % b->num[0];	// get the remainder
		
		q->num_size = 1;
		r->num_size = 1;
		
		BIGNUM_recalc_size(r);
		
		return NO_ERROR;
	}
	
	BIGNUM_new_cpy(&tmp_a, a);	// make a copy of a
	BIGNUM_new_cpy(&tmp_b, b);	// make a copy of b
	
	char	*str;	// DEBUG

	printf("%s / %s\n", BIGNUM_get_hex(tmp_a, &str), BIGNUM_get_hex(tmp_b, &str));

	// scale up b
	BIGNUM_lshift(tmp_b, BIGNUM_getbit_size(a) - BIGNUM_getbit_size(b)); 

	printf("TMP_A: %s\n", BIGNUM_get_hex(tmp_a, &str));
	printf("TMP_B: %s\n", BIGNUM_get_hex(tmp_b, &str));
	
	while(BIGNUM_cmp(tmp_a, tmp_b) >= 0)
	{
		q->num[a->num_size-b->num_size] += 7;
		BIGNUM_sub(tmp_a, tmp_a, tmp_b);
		
		printf("IN HERE\n");
	}

	printf("Q: %s\n", BIGNUM_get_hex(q, &str));
	printf("TMP_A: %s\n", BIGNUM_get_hex(tmp_a, &str));
	printf("TMP_B: %s\n", BIGNUM_get_hex(tmp_b, &str));
	
	for(i = tmp_a->num_size-1; i >= b->num_size; --i)
	{
		if(tmp_a->num[i] == b->num[b->num_size-1])
		{
			q->num[i-(b->num_size-1)-1] = 0xFFFFFFFF - 1;
			printf("IN IF\n");
		}
	
		else
		{
			q->num[i-(b->num_size-1)-1] = (((double_block_t)tmp_a->num[i] << 32) + (double_block_t)tmp_a->num[i-1]) / (double_block_t)b->num[b->num_size-1];
			printf("IN ELSE: %x %x / %x = %x\n", tmp_a->num[i], tmp_a->num[i-1], b->num[b->num_size-1], q->num[i-(b->num_size-1)-1]);
		}

		BIGNUM_recalc_size(q);
		
		printf("Q: %s\n", BIGNUM_get_hex(q, &str));
		printf("B: %s\n", BIGNUM_get_hex(b, &str));

		// compute the tmp to compare with a
		uv = b->num[b->num_size-2] * (double_block_t)q->num[i-(b->num_size-1)-1];
		qb[0] = uv & 0xFFFFFFFF;
		c = uv >> 32;
	
		printf("C: %x\n", c);

		uv = b->num[b->num_size-1] * (double_block_t)q->num[i-(b->num_size-1)-1] + c;
		qb[1] = uv & 0xFFFFFFFF;
		qb[2] = uv >> 32;

		printf("qb[2]: %x\n", qb[2]);
		printf("UV: %llx\n", uv);

		printf("Q\tX\n");
		printf("%x > %x\n", qb[2], tmp_a->num[i]);
		printf("%x > %x\n", qb[1], tmp_a->num[i-1]);
		printf("%x > %x\n", qb[0], tmp_a->num[i-2]);

		while(qb[2] >= tmp_a->num[i] && qb[1] >= tmp_a->num[i-1] && qb[0] > tmp_a->num[i-2])
		{
			q->num[i-(b->num_size-1)-1]--;
			
			uv = b->num[b->num_size-2] * (double_block_t)q->num[i-(b->num_size-1)-1];
			qb[0] = uv & 0xFFFFFFFF;
			c = uv >> 32;
		
			uv = b->num[b->num_size-1] * (double_block_t)q->num[i-(b->num_size-1)-1] + c;
			qb[1] = uv & 0xFFFFFFFF;
			qb[2] = uv >> 32;
			
			printf("IN WHILE\n");
		}

		printf("B: %s\n", BIGNUM_get_hex(b, &str));

		BIGNUM_cpy(tmp_b, b);

		printf("TMP_B: %s\n", BIGNUM_get_hex(tmp_b, &str));
		
		printf("SHIFT: %d - %d - 1 = %d\n", i, (b->num_size-1), i - (b->num_size-1) - 1);
		
		BIGNUM_lshift(tmp_b, 32 * (i - (b->num_size-1) - 1));
	
		//
		// THIS IS NOT WORKING... NEED TO FIX
		//

		printf("\n\nTMP_B: %s  *  ", BIGNUM_get_hex(tmp_b, &str));
		printf("q_NUM: %x  =  ", q->num[i-(b->num_size-1)-1]);
		
		BIGNUM_mul_ui(tmp_b, tmp_b, q->num[i-(b->num_size-1)-1]);

		printf("TMP_B: %s\n\n", BIGNUM_get_hex(tmp_b, &str));
		
		printf("TMP_A: %s\n", BIGNUM_get_hex(tmp_a, &str));

		BIGNUM_sub(tmp_a, tmp_a, tmp_b);

		printf("TMP_A: %s\n", BIGNUM_get_hex(tmp_a, &str));
		
		if(BIGNUM_cmp_ui(tmp_a, 0) < 0)
		{
			BIGNUM_cpy(tmp_b, b);
			BIGNUM_lshift(tmp_b, 32 * (i - (b->num_size-1) - 1));
			
			BIGNUM_add(tmp_a, tmp_a, tmp_b);
			q->num[i-(b->num_size-1)-1]--;
			
			printf("IN IF\n");
		}
	}
	
	BIGNUM_cpy(r, tmp_a);
	
	BIGNUM_recalc_size(q);
	BIGNUM_recalc_size(r);
	
	BIGNUM_delete(tmp_a);
	BIGNUM_delete(tmp_b);
	
	return NO_ERROR;
}
*/

int BIGNUM_div_nr(BIGNUM q, BIGNUM a, BIGNUM b)
{
	BIGNUM	r;
	int	ret;
		
	//
	// No savings here... just makes it easier for the programmer
	//
	
	BIGNUM_new(&r, 0);		// create a remainder
	
	if((ret = BIGNUM_div(q, r, a, b)) < 0)	// do the division
		return ret;
	
	BIGNUM_delete(r);	// delete the remainder
	
	return ret;
}

int BIGNUM_mod(BIGNUM r, BIGNUM a, BIGNUM b)
{
	BIGNUM	q, tmp_r = r;
	int	ret;
	
	BIGNUM_new(&q, 0);		// create a quotient
	
	// copy over r if it is the same as a or b
	if(r == a || r == b)
		BIGNUM_new_cpy(&tmp_r, r);
		
	if((ret = BIGNUM_div(q, tmp_r, a, b)) < 0)	// do the division
		return ret;
	
	BIGNUM_delete(q);	// delete the quotient
	
	
	// check to make sure that the remainder is not negative
	if(BIGNUM_sign(tmp_r) < 0)
	{
		int	sign = b->sign;
		b->sign = 1;
		BIGNUM_add(tmp_r, tmp_r, b);	// add on b if it is
		b->sign = sign;
	}
	
	if(tmp_r != r)
		BIGNUM_cpy(r, tmp_r);
	
	BIGNUM_recalc_size(r);
	
	return ret;
}

