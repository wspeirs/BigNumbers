#include <gmp.h>
#include <bignum.h>

#include <stdio.h>
#include <time.h>
#include <sys/times.h>

// Useage: calc operation num1 [num2]
//	a = add
//	s = subtract
//	m = multiply
//	d = divide
//	q = square
//	o = mod
//	n = division no remainder
//	l = lcd
int main(int argc, char **argv)
{
	mpz_t	gmp_a, gmp_b, gmp_c, gmp_d;
	BIGNUM	bignum_a, bignum_b, bignum_c, bignum_d;
	char	*str;

// 	printf("ARGC: %d\n", argc);
	
	if(argc < 3)
		return -1;

	// setup
	mpz_init_set_str(gmp_a, argv[2], 16);
	mpz_init(gmp_c);
	mpz_init(gmp_d);
	
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
	BIGNUM_new(&bignum_d, 0);
		
	BIGNUM_set_hex(bignum_a, argv[2]);
	
	if(argc > 3)
	{
		mpz_init_set_str(gmp_b, argv[3], 16);
		BIGNUM_set_hex(bignum_b, argv[3]);
	}

	switch(argv[1][0])
	{
		case 'a':	// add
			mpz_add(gmp_c, gmp_a, gmp_b);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));
			
			BIGNUM_add(bignum_c, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));
			
			BIGNUM_add(bignum_a, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));
			
			BIGNUM_set_hex(bignum_a, argv[2]);
			BIGNUM_set_hex(bignum_b, argv[3]);
			BIGNUM_add(bignum_b, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_b, &str));
			break;
			
		case 's':	// sub
			mpz_sub(gmp_c, gmp_a, gmp_b);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));
			
			BIGNUM_sub(bignum_c, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));
			
			BIGNUM_sub(bignum_a, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));
			
			BIGNUM_set_hex(bignum_a, argv[2]);
			BIGNUM_set_hex(bignum_b, argv[3]);
			BIGNUM_sub(bignum_b, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_b, &str));
			break;
			
		case 'm':	// mul
			mpz_mul(gmp_c, gmp_a, gmp_b);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));
		
			BIGNUM_mul(bignum_c, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));
		
			BIGNUM_mul(bignum_a, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));
		
			BIGNUM_set_hex(bignum_a, argv[2]);
			BIGNUM_set_hex(bignum_b, argv[3]);
			BIGNUM_mul(bignum_b, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_b, &str));
			break;
		
		case 'q':	// square
			mpz_mul(gmp_c, gmp_a, gmp_a);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));
	
			BIGNUM_sqr(bignum_c, bignum_a);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));
	
			BIGNUM_sqr(bignum_a, bignum_a);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));
			break;
			
		case 'o':	// mod
			mpz_mod(gmp_c, gmp_a, gmp_b);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));
	
			BIGNUM_mod(bignum_c, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));
	
			BIGNUM_mod(bignum_a, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));
	
			BIGNUM_set_hex(bignum_a, argv[2]);
			BIGNUM_set_hex(bignum_b, argv[3]);
			BIGNUM_mod(bignum_b, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_b, &str));
			break;
		
		case 'n':	// divide no remainder
			mpz_tdiv_q(gmp_c, gmp_a, gmp_b);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));

			BIGNUM_div_nr(bignum_c, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));

			BIGNUM_div_nr(bignum_a, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));

			BIGNUM_set_hex(bignum_a, argv[2]);
			BIGNUM_set_hex(bignum_b, argv[3]);
			BIGNUM_div_nr(bignum_b, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_b, &str));
			break;

		case 'g':	// GCD
			mpz_gcd(gmp_c, gmp_a, gmp_b);
			printf("%s\n", mpz_get_str(NULL, 16, gmp_c));

			BIGNUM_gcd(bignum_c, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_c, &str));

			BIGNUM_gcd(bignum_a, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_a, &str));

			BIGNUM_set_hex(bignum_a, argv[2]);
			BIGNUM_set_hex(bignum_b, argv[3]);
			BIGNUM_gcd(bignum_b, bignum_a, bignum_b);
			printf("%s\n", BIGNUM_get_hex(bignum_b, &str));
			break;
			
		default:
			printf("UNKNOWN\n");
			break;	
	}
	
	return 0;
}
