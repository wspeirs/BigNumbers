#include <x86_64-linux-gnu/gmp.h>
#include <bignum.h>

#include <stdio.h>
#include <time.h>
#include <sys/times.h>

void AdditionTest(char *num1, char *num2);
void ComparisonTests(char *num1, char *num2);
void SubtractionTest(char *num1, char *num2);
void MultiplicationTest(char *num1, char *num2);
void PowTest(char *num1, uint_32 i);
void DivisionTest(char *num1, char *num2);
void ModTest(char *num1, char *num2);
void ModularArithTest(char *num1, char *num2, char *mod);
void GCDTest(char *num1, char *num2);
void PowMod(char *num1, char *num2, char *num3);

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	//
	// Comparison Tests
	//
/*	printf("*** CMP TESTS ***\n");
	ComparisonTests("111111111112111111111112111111111112", "-111111111111111111111111111111111111111111111111");
*/	
	
	//
	// Addition Tests
	//
/*	AdditionTest("00000000", "00000000");	// single "digit"
	AdditionTest("78788888", "88887879");
	AdditionTest("11111111", "EEEEEEEF");
	
	AdditionTest("1111111111111111", "EEEEEEEFEEEEEEEF");	// multi "digit"
	AdditionTest("11111111", "EEEEEEEFEEEEEEEF");
	AdditionTest("1111111111111111", "EEEEEEEF");
	
	AdditionTest("-11111111", "EEEEEEEF");
	AdditionTest("11111111", "-EEEEEEEF");
	
	AdditionTest("1FD4", "-76B51AE8");	// both negative

	return 0;
*/	
	//
	// Subtraction Tests
	//
/*	printf("*** SUB TESTS ***\n");
	SubtractionTest("00000000", "-00000000");	// single "digit"
	SubtractionTest("-78788888", "88887879");
	SubtractionTest("11111111", "EEEEEEEF");
	
	SubtractionTest("1111111111111111", "EEEEEEEFEEEEEEEF");	// multi "digit"
	SubtractionTest("-11111111", "-EEEEEEEFEEEEEEEF");
	SubtractionTest("1111111111111111", "EEEEEEEF");
	
	SubtractionTest("-1111111111111111", "EEEEEEEF");
	SubtractionTest("1111111111111111", "-EEEEEEEF");
	
	SubtractionTest("-1111111111111111", "-EEEEEEEFEEEEEEEF");	// both negative
	
	return 0;
*/	
	//
	// Multiplication Tests
	//
/*	printf("*** MUL TESTS ***\n");
	MultiplicationTest("AAABABABAA", "EEEEEEEF");	// single "digit"
	MultiplicationTest("-78788888", "88887879");
	MultiplicationTest("11111111", "EEEEEEEF");
	
	MultiplicationTest("-1111111111111111", "EEEEEEEFEEEEEEEF");	// multi "digit"
	MultiplicationTest("1111111111111111", "-EEEEEEEFEEEEEEEF");	// both negative
	
	MultiplicationTest("-11111111", "EEEEEEEFEEEEEEEF");
	MultiplicationTest("-1111111111111111", "EEEEEEEF");
	
	MultiplicationTest("-1111111111111111AAABABABAABABABABABABABABABABABABABABABABA", "-EEEEEEEFEEEEEEEF");	// both negative

	return 0;
*/	

	//
	// Pow (sqr) Tests
	//
	printf("*** POW TESTS ***\n");
	
	int i;
	
	for(i=0; i <= 10; ++i)
		PowTest("-11111111", i);	// single "digit"

	PowTest("FFFFFFFF", 0xFFF);
	
	//
	// Division Tests
	//
/*	printf("*** DIV TESTS ***\n");
	DivisionTest("87654321", "11111111");	// works (1 long for each)
	DivisionTest("2233445511111111", "FFFFFFFF8765432187654321");	// works (a < b)
 	DivisionTest("FFFFFFFF8765432187654321", "2233445511111111");	
	DivisionTest("FFFAAAAAAAFFF8765432187654321", "2233445511111111");
	
	DivisionTest("-7", "3");
	DivisionTest("7", "-3");
	DivisionTest("-7", "-3");
 	
	DivisionTest("8765432187654321", "812345678");
	DivisionTest("641FDBA07654321", "812345678");
	
	DivisionTest("-641FDBA07654321", "812345678");
	DivisionTest("641FDBA07654321", "-812345678");
	DivisionTest("-641FDBA07654321", "-812345678");
	
	return 0;
*/	
	//
	// MOD test
	//
/*	ModTest("12345678", "11223344");
	ModTest("-12345678", "11223344");
	ModTest("12345678", "-11223344");
	ModTest("11223344", "12345678");
	ModTest("1122334411223344112233441122334411223344", "12345678");
	
	
	return 0;
*/
	
	//
	// Modular arith tests
	//	
/*	ModularArithTest("87654321", "12345678", "11223344");
	ModularArithTest("87654321876543218765432187654321", "567812345678", "112233446655");
	ModularArithTest("87654321", "-12345678", "11223344");
	ModularArithTest("-87654321876543218765432187654321", "567812345678", "112233446655");
	ModularArithTest("-87654321876543218765432187654321", "-567812345678", "112233446655");
	
	return 0;
*/
	
	//
	// GCD Tests
	//
/*	GCDTest("87654321", "12345678");
	GCDTest("8765432187654321", "FF12345678");
	
	GCDTest("-8765432187654321", "FF12345678");
	GCDTest("8765432187654321", "-FF12345678");
	GCDTest("-FF12345678", "-8765432187654321");
	
	return 0;
*/
	
	//
	// Pow Mod
	//
/*	PowMod("12345678", "87654321", "11223344");
	PowMod("1234567812345678", "87654321", "11223344");
	PowMod("12345678", "8765432187654321", "11223344");
*/
	return 0;
}


void PowMod(char *num1, char *num2, char *num3)
{
	mpz_t	gmp_a, gmp_b, gmp_c, gmp_m;
	BIGNUM	bignum_a, bignum_b, bignum_c, bignum_m;
	char	*str;
	struct tms	start_t, end_t;

	//
	// GMP
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init_set_str(gmp_m, num3, 16);
	mpz_init(gmp_c);
	
	times(&start_t);
	mpz_powm(gmp_c, gmp_a, gmp_b, gmp_m);
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_c);
	PRINTF("GMP RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	mpz_clear(gmp_m);
	
	
	
	//
	// BIGNUM
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
	BIGNUM_new(&bignum_m, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	BIGNUM_set_hex(bignum_m, num3);
	
	times(&start_t);
	BIGNUM_pow_mod(bignum_c, bignum_a, bignum_b, bignum_m);
	times(&end_t);
	
	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_c, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
	BIGNUM_delete(bignum_m);

}

void GCDTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	BIGNUM	bignum_a, bignum_b, bignum_c;
	char	*str;
	struct tms	start_t, end_t;

	//
	// GMP DIV
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init(gmp_c);
	
	times(&start_t);
	mpz_gcd(gmp_c, gmp_a, gmp_b);
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_c);
	PRINTF("GMP RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	mpz_lcm(gmp_c, gmp_a, gmp_b);
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_c);
	PRINTF("GMP RESULT: %s (%ld)\n\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	
	
	
	//
	// BIGNUM DIV
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	times(&start_t);
	BIGNUM_gcd(bignum_c, bignum_a, bignum_b);
	times(&end_t);
	
	printf(" RESULT: %s (%ld)\n", BIGNUM_get_hex(bignum_c, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	BIGNUM_lcm(bignum_c, bignum_a, bignum_b);
	times(&end_t);
	
	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_c, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
}


void ModularArithTest(char *num1, char *num2, char *mod)
{
	mpz_t	gmp_a, gmp_b, gmp_r, gmp_m;
	BIGNUM	bignum_a, bignum_b, _r, bignum_m;
	char	*str;
	struct tms	start_t, end_t;

	//
	// GMP
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init_set_str(gmp_m, mod, 16);
	mpz_init(gmp_r);
	
	times(&start_t);
	mpz_add(gmp_r, gmp_a, gmp_b);	// add
	mpz_mod(gmp_r, gmp_r, gmp_m);	// mod
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_r);
	PRINTF("GMP ADD RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	mpz_sub(gmp_r, gmp_a, gmp_b);	// sub
	mpz_mod(gmp_r, gmp_r, gmp_m);	// mod
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_r);
	PRINTF("GMP SUB RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	mpz_mul(gmp_r, gmp_a, gmp_b);	// mul
	mpz_mod(gmp_r, gmp_r, gmp_m);	// mod
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_r);
	PRINTF("GMP MUL RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	mpz_mul(gmp_r, gmp_a, gmp_a);	// sqr
	mpz_mod(gmp_r, gmp_r, gmp_m);	// mod
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_r);
	PRINTF("GMP SQR RESULT: %s (%ld)\n\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	

	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_r);
	mpz_clear(gmp_m);
	
	
	
	//
	// BIGNUM
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_m, 0);
	BIGNUM_new(&_r, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	BIGNUM_set_hex(bignum_m, mod);
	
	times(&start_t);
	BIGNUM_add_mod(_r, bignum_a, bignum_b, bignum_m);
	times(&end_t);
	
	printf(" ADD RESULT: %s (%ld)\n", BIGNUM_get_hex(_r, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	BIGNUM_sub_mod(_r, bignum_a, bignum_b, bignum_m);
	times(&end_t);
	
	printf(" SUB RESULT: %s (%ld)\n", BIGNUM_get_hex(_r, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	BIGNUM_mul_mod(_r, bignum_a, bignum_b, bignum_m);
	times(&end_t);
	
	printf(" MUL RESULT: %s (%ld)\n", BIGNUM_get_hex(_r, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	times(&start_t);
	BIGNUM_sqr_mod(_r, bignum_a, bignum_m);
	times(&end_t);
	
	printf(" SQR RESULT: %s (%ld)\n\n", BIGNUM_get_hex(_r, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_m);
	BIGNUM_delete(_r);
}

void ModTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	BIGNUM	bignum_a, bignum_b, bignum_c;
	char	*str;
	struct tms	start_t, end_t;

	//
	// GMP DIV
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init(gmp_c);
	
	times(&start_t);
	mpz_mod(gmp_c, gmp_a, gmp_b);
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_c);
	PRINTF("GMP RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	
	
	
	//
	// BIGNUM DIV
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	times(&start_t);
	BIGNUM_mod(bignum_c, bignum_a, bignum_b);
	times(&end_t);
	
	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_c, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
}


void DivisionTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c, gmp_d;
	BIGNUM	bignum_a, bignum_b, bignum_c, _d;
	char	*str;
	struct tms	start_t, end_t;

	PRINTF("%s / %s\n", num1, num2);
	
	//
	// GMP DIV
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init(gmp_c);
	mpz_init(gmp_d);
	
	times(&start_t);
	mpz_tdiv_qr(gmp_d, gmp_c, gmp_a, gmp_b);
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_d);
	PRINTF("GMP RESULT Q: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	str = mpz_get_str(NULL, 16, gmp_c);
	PRINTF("GMP RESULT R: %s\n\n", str);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	mpz_clear(gmp_d);
	
	
	
	//
	// BIGNUM DIV
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
	BIGNUM_new(&_d, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	times(&start_t);
	BIGNUM_div(_d, bignum_c, bignum_a, bignum_b);
	times(&end_t);
	
	printf(" RESULT Q: %s (%ld)\n", BIGNUM_get_hex(_d, &str), end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	printf(" RESULT R: %s\n\n\n", BIGNUM_get_hex(bignum_c, &str));
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
	BIGNUM_delete(_d);
}


void PowTest(char *num1, uint_32 i)
{
	mpz_t	gmp_a, gmp_c;
	BIGNUM	bignum_a, bignum_c;
	char	*str = NULL;
	struct tms	start_t, end_t;

	//
	// GMP POW
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init(gmp_c);
	
	times(&start_t);
	mpz_pow_ui(gmp_c, gmp_a, i);
	times(&end_t);
	
	str = mpz_get_str(NULL, 16, gmp_c);
	
	//PRINTF("GMP RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	PRINTF("GMP TIME: %ld\n", end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_c);
	
	str = NULL;

	//
	// BIGNUM POW
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_c, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	
	times(&start_t);
	BIGNUM_pow_ui(bignum_c, bignum_a, i);
	times(&end_t);

	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_c, &str), end_t.tms_utime - start_t.tms_utime);
	printf(" TIME: %ld\n\n", end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_c);
}

void MultiplicationTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	BIGNUM	bignum_a, bignum_b, bignum_c;
	char	*str;
	clock_t	start, end;

	//
	// GMP MUL
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init(gmp_c);
	
	start = clock();
	mpz_mul(gmp_c, gmp_a, gmp_b);
	end = clock();
	
	str = mpz_get_str(NULL, 16, gmp_c);
	
	PRINTF("GMP RESULT: %s (%ld)\n", str, end - start);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	
	
	//
	// BIGNUM MUL
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	start = clock();
	BIGNUM_mul(bignum_c, bignum_a, bignum_b);
	end = clock();
	
	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_c, &str), end - start);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
}

void SubtractionTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	BIGNUM	bignum_a, bignum_b, bignum_c;
	char	*str;
	clock_t	start, end;

	//
	// GMP SUB
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init(gmp_c);
	
	start = clock();
	mpz_sub(gmp_c, gmp_a, gmp_b);
	end = clock();
	
	str = mpz_get_str(NULL, 16, gmp_c);
	
	PRINTF("GMP RESULT: %s (%ld)\n", str, end - start);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	
	
	//
	// BIGNUM SUB
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	start = clock();
	BIGNUM_sub(bignum_a, bignum_a, bignum_b);
	end = clock();
	
	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_a, &str), end - start);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
}


void AdditionTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	BIGNUM	bignum_a, bignum_b, bignum_c;
	char	*str;
	clock_t	start, end;

	//
	// GMP ADD
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	mpz_init(gmp_c);
	
	start = clock();
	mpz_add(gmp_c, gmp_a, gmp_b);
	end = clock();
	
	str = mpz_get_str(NULL, 16, gmp_c);
	
	PRINTF("GMP RESULT: %s (%ld)\n", str, end - start);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	mpz_clear(gmp_c);
	
	
	//
	// BIGNUM ADD
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
	BIGNUM_new(&bignum_c, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	start = clock();
	BIGNUM_add(bignum_b, bignum_a, bignum_b);
	end = clock();
	
	printf(" RESULT: %s (%ld)\n\n", BIGNUM_get_hex(bignum_b, &str), end - start);
	FREE(str);
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
	BIGNUM_delete(bignum_c);
}

void ComparisonTests(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b;
	BIGNUM	bignum_a, bignum_b;

	//
	// GMP CMP
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	
	printf("GMP RESULT: %d\n", mpz_cmp(gmp_a, gmp_b));
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	
	
	//
	// BIGNUM ADD
	//
	BIGNUM_new(&bignum_a, 0);
	BIGNUM_new(&bignum_b, 0);
		
	BIGNUM_set_hex(bignum_a, num1);
	BIGNUM_set_hex(bignum_b, num2);
	
	printf(" RESULT: %d\n\n", BIGNUM_cmp(bignum_a, bignum_b));
	
	BIGNUM_delete(bignum_a);
	BIGNUM_delete(bignum_b);
}
