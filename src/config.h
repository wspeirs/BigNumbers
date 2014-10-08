/**
 * @file config.h
 * @brief Configuration file built using configure... <b>DO NOT EDIT</b>
 * 
 * Contains all the typedef stuff with #defs for kernel/user and 32/64-bit stuff
 */

#ifndef _CONFIGURE_H
#define _CONFIGURE_H

// *** NOTE: We only do macros for those functions that need it ***

//
// This is all the user-land stuff that is needed
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MALLOC(x)		malloc((x))
#define FREE(x)			free((x))
#define PRINTF(x, args ...)	printf(x, ##args)

typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;


//
// Common #defines
//
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//
// Common type defs
//
typedef unsigned char	uchar;
typedef uchar*		_CTX;
typedef unsigned char	uint_8;
typedef unsigned short	uint_16;
typedef unsigned long	uint_32;
typedef unsigned long long	uint_64;



enum {
	NO_ERROR	= 0,
	BAD_ERROR	= -1,
	NOT_IMPLEMENTED	= -2,
	NULL_POINTER	= -3,
	NO_MEM		= -4,
	BAD_ALGO	= -5,
	WRONG_BLK_SIZE	= -6,
	WRONG_KEY_SIZE	= -7,
	WRONG_IV_SIZE	= -8,
	IV_NOT_NEEDED	= -9,
	WEAK_KEY	= -10,
	MALLOC_FAIL	= -11,
	DIVIDE_BY_ZERO	= -12
};




#endif

