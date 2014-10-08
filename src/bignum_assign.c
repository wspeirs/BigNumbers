#include <bignum_assign.h>

int BIGNUM_new(BIGNUM *arg, uint numbits)
{
	*arg = (BIGNUM)MALLOC(sizeof(struct BIGNUM_Struct));	// make the struct
	
	(*arg)->num_size = 0;	// always have a zero length number to start with
	
	if(numbits == 0)
		(*arg)->alloc_size = INIT_SIZE;

	else
		(*arg)->alloc_size = BITS_TO_BLOCKS(numbits);	// conver to blocks

// 	PRINTF("NEW: %d bytes\n", BLOCKS_TO_BYTES((*arg)->alloc_size));
	
	(*arg)->num = (block_t*)MALLOC(BLOCKS_TO_BYTES((*arg)->alloc_size));	// make the memory
	memset((*arg)->num, 0, BLOCKS_TO_BYTES((*arg)->alloc_size));		// zero it out
	(*arg)->sign = 1;		// set the sign to positive
	
	return NO_ERROR;
}

int BIGNUM_delete(BIGNUM arg)
{
	FREE(arg->num);	// free the memory
	arg->num_size = arg->alloc_size = arg->sign = 0;
	FREE(arg);	// free the struct
	
	return NO_ERROR;
}

int BIGNUM_resize(BIGNUM arg, uint num_blocks)
{
// 	printf("REQUESTED: %d\tHAS:%d\n", num_blocks, arg->alloc_size);
	
	// we need more memory
	if(arg->alloc_size < num_blocks)
	{
// 		PRINTF("CREATED: %d bytes\n", BLOCKS_TO_BYTES(num_blocks));
		
		block_t	*tmp = (block_t*)MALLOC(BLOCKS_TO_BYTES(num_blocks));	// make the memory
		memset(tmp, 0, BLOCKS_TO_BYTES(num_blocks));			// zero out the memory
		memcpy(tmp, arg->num, BLOCKS_TO_BYTES(arg->num_size));		// copy over the old number
		FREE(arg->num);	// delete the number
		arg->num = tmp;	// switch the number
		arg->alloc_size = num_blocks;	// set the new number size
	}
	
	return NO_ERROR;
}

// Recalculates the size of the number based on how many leading "digits" are zero
void BIGNUM_recalc_size(BIGNUM arg)
{
	int	i;
	
	for(i = arg->num_size-1; i >= 0; --i)
		if(arg->num[i] != 0x0)
			break;
	
	arg->num_size = i+1;
	
	if(arg->num_size == 0)
		arg->sign = 0;
}

int BIGNUM_set_hex(BIGNUM arg, char *hex)
{
	int	len;
	int	i = 0;
	char	format[5];
	int	blocks;
	
	if(*hex == '-')	// we have a neg number
	{
		arg->sign = -1;
		++hex;
	}
	
	else	// positive number
		arg->sign = 1;
	
	if(*hex == '0' && *(hex+1) == 'x')	// 0x prefix
		hex += 2;	// just move the pointer
	
	len = strlen(hex);	// get the length without any prefix stuff
	
	blocks = (len/8) + (len % 8 == 0 ? 0 : 1);	// 2 chars = 1 byte, so slightly different than BYTES_TO_BLOCKS
	
	BIGNUM_resize(arg, blocks);	// make sure we have enough memory
	arg->num_size = blocks;		// set the length
	
	memset(arg->num, 0, BLOCKS_TO_BYTES(arg->alloc_size));	// zero out the number
	
	if(len%8 != 0)
	{
		sprintf(format, "%%0%dX", len%8);	// make the format string
		
		// get however much of the first piece
		sscanf(hex, format, &arg->num[arg->num_size-1]);
		
		hex += (len%8);	// advance the pointer the right amount
		i = arg->num_size - 2;	// advance i
	}
	
	else
		i = arg->num_size - 1;
	
	for(; i >= 0; --i)
	{
		sscanf(hex, "%08X", &arg->num[i]);
		
		hex += 8;	// move the pointer (could be dangerous)
	}
	
	BIGNUM_recalc_size(arg);	// make sure the size is correct
	
	return NO_ERROR;
}

char *BIGNUM_get_hex(BIGNUM arg, char **str)
{
	uint	i;
	uint	byte_size;
	char	*pStr;
	
	BIGNUM_recalc_size(arg);	// take care of any leading zeros
	
	byte_size = BLOCKS_TO_BYTES(arg->num_size) * 2;
	
	// make memory for the string
	*str = (char*)MALLOC(byte_size+2);	// 1 for the null and 1 for the sign
	pStr = *str;
	
	if(arg->sign == -1)
		*pStr++ = '-';	// set the sign
	
	// print out the first one without the leading zeros
	if(arg->num_size != 0)
		pStr += sprintf(pStr, "%x", arg->num[arg->num_size - 1]);
	else
		pStr += sprintf(pStr, "0");	
	
	for(i = 1; i < arg->num_size; ++i)
		pStr += sprintf(pStr, "%08x", arg->num[arg->num_size - i - 1]);
	
	*pStr = '\0';	// set the null character
	
	return *str;
}

int BIGNUM_cpy(BIGNUM dest, BIGNUM src)
{
	uint	amnt;
	
	if(src == dest)	// if they are the same, we don't need to do anything (MAYBE RETURN AN ERROR HERE)
		return NO_ERROR;
	
	BIGNUM_recalc_size(src);	// recalc the size of the source
	
	FREE(dest->num);		// free the memory
	
	if(src->num_size != 0)
		amnt = BLOCKS_TO_BYTES(src->num_size);
	
	else
		amnt = BLOCKS_TO_BYTES(src->alloc_size);
	
	dest->num = (block_t*)MALLOC(amnt);	// make the memory
	memcpy(dest->num, src->num, amnt);	// copy the memory
	
	// set sign and sizes
	dest->sign = src->sign;
	dest->num_size = src->num_size;
	dest->alloc_size = BYTES_TO_BLOCKS(amnt);
	
	return NO_ERROR;
}

int BIGNUM_new_cpy(BIGNUM *dest, BIGNUM src)
{
	// basically just create the struct for dest, then call BIGNUM_cpy
	*dest = (struct BIGNUM_Struct*)MALLOC(sizeof(struct BIGNUM_Struct));
	
	(*dest)->num = NULL;	// we'll call free in BIGNUM_cpy
	(*dest)->num_size = (*dest)->alloc_size = 0;	// memory will be made in the cpy call
	
	return BIGNUM_cpy(*dest, src);
}

