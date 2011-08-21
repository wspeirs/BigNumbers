#include <tests.h>
#include <Integer.h>

void ComparisonTests(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b;
	Integer	a(num1), b(num2);

	//
	// GMP CMP
	//
	mpz_init_set_str(gmp_a, num1, 16);
	mpz_init_set_str(gmp_b, num2, 16);
	
	printf("GMP RESULT: %d\n", mpz_cmp(gmp_a, gmp_b));
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_b);
	
	
	//
	// Integer ADD
	//
	printf("INT RESULT: %d\n\n", a.cmp(b));
}


void AdditionTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	Integer	a(num1), b(num2), c;
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
	// Integer ADD
	//
	start = clock();
	b = a + b;
	end = clock();
	
	printf("INT RESULT: %s (%ld)\n\n", b.toString(), end - start);
}

void SubtractionTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	Integer	a(num1), b(num2), c;
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
	// Integer SUB
	//
	start = clock();
	a = a - b;
	end = clock();
	
	printf("INT RESULT: %s (%ld)\n\n", a.toString(), end - start);
}

/*
void MultiplicationTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	Integer	a(num1), b(num2), c;
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
	// Integer MUL
	//
	start = clock();
	c = a * b;
	end = clock();
	
	printf("INT RESULT: %s (%ld)\n\n", c.toString(), end - start);
}

void DivisionTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c, gmp_d;
	Integer	a(num1), b(num2), c, d;
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
	// Integer DIV
	//
	times(&start_t);
	a.div_qr(b, d, c);
	times(&end_t);
	
	printf("INT RESULT Q: %s (%ld)\n", d.toString(), end_t.tms_utime - start_t.tms_utime);
	printf("INT RESULT R: %s\n\n\n", c.toString());
}

void GCDTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	Integer	a(num1), b(num2), c;
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
	// Integer DIV
	//
	times(&start_t);
	c = a.gcd(b);
	times(&end_t);
	
	printf("INT RESULT: %s (%ld)\n", c.toString(), end_t.tms_utime - start_t.tms_utime);
	
	times(&start_t);
	c = a.lcm(b);
	times(&end_t);
	
	printf("INT RESULT: %s (%ld)\n\n", c.toString(), end_t.tms_utime - start_t.tms_utime);
}

void PowTest(char *num1, uint_32 i)
{
	mpz_t	gmp_a, gmp_c;
	Integer	a(num1), c;
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
	
	PRINTF("GMP RESULT: %s (%ld)\n", str, end_t.tms_utime - start_t.tms_utime);
	PRINTF("GMP TIME: %ld\n", end_t.tms_utime - start_t.tms_utime);
	FREE(str);
	
	mpz_clear(gmp_a);
	mpz_clear(gmp_c);
	
	str = NULL;

	//
	// Integer POW
	//
	times(&start_t);
	c = a ^ i;
	times(&end_t);

	printf("INT RESULT: %s (%ld)\n\n", c.toString(), end_t.tms_utime - start_t.tms_utime);
	printf("INT TIME: %ld\n\n", end_t.tms_utime - start_t.tms_utime);
}

void ModTest(char *num1, char *num2)
{
	mpz_t	gmp_a, gmp_b, gmp_c;
	Integer	a(num1), b(num2), c;
	char	*str;
	struct tms	start_t, end_t;

	//
	// GMP MOD
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
	// Integer MOD
	//
	times(&start_t);
	c = a % b;
	times(&end_t);
	
	printf("INT RESULT: %s (%ld)\n\n", c.toString(), end_t.tms_utime - start_t.tms_utime);
}

void ModularArithTest(char *num1, char *num2, char *mod)
{
	mpz_t	gmp_a, gmp_b, gmp_r, gmp_m;
	Integer	a(num1), b(num2), r, m(mod);
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
	// Integer
	//
	times(&start_t);
	r = a.add_mod(b, m);
	times(&end_t);
	
	printf("INT ADD RESULT: %s (%ld)\n", r.toString(), end_t.tms_utime - start_t.tms_utime);
	
	times(&start_t);
	r = a.sub_mod(b, m);
	times(&end_t);
	
	printf("INT SUB RESULT: %s (%ld)\n", r.toString(), end_t.tms_utime - start_t.tms_utime);
	
	times(&start_t);
	r = a.mul_mod(b, m);
	times(&end_t);
	
	printf("INT MUL RESULT: %s (%ld)\n", r.toString(), end_t.tms_utime - start_t.tms_utime);
	
	times(&start_t);
	r = a.sqr_mod(m);
	times(&end_t);
	
	printf("INT SQR RESULT: %s (%ld)\n\n", r.toString(), end_t.tms_utime - start_t.tms_utime);
}

void PowMod(char *num1, char *num2, char *num3)
{
	mpz_t	gmp_a, gmp_b, gmp_c, gmp_m;
	Integer	a(num1), b(num2), c, m(num3);
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
	// Integer
	//
	times(&start_t);
	c = a.pow_mod(b, m);
	times(&end_t);
	
	printf("INT RESULT: %s (%ld)\n\n", c.toString(), end_t.tms_utime - start_t.tms_utime);
}

*/


