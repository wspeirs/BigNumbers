#include <gmp.h>
#include <Integer.h>

#include <stdio.h>
#include <time.h>
#include <sys/times.h>

void ComparisonTests(char *num1, char *num2);
void AdditionTest(char *num1, char *num2);
void SubtractionTest(char *num1, char *num2);
/*
void MultiplicationTest(char *num1, char *num2);
void PowTest(char *num1, uint_32 i);
void DivisionTest(char *num1, char *num2);
void ModTest(char *num1, char *num2);
void ModularArithTest(char *num1, char *num2, char *mod);
void GCDTest(char *num1, char *num2);
void PowMod(char *num1, char *num2, char *num3);
*/

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	//
	// Comparison Tests
	//
	printf("*** CMP TESTS ***\n");
	ComparisonTests("111111111112111111111112111111111112", "-111111111111111111111111111111111111111111111111");
	
	//
	// Addition Tests
	//
	AdditionTest("00000000", "00000000");	// single "digit"
	AdditionTest("78788888", "88887879");
	AdditionTest("11111111", "EEEEEEEF");
	
	AdditionTest("1111111111111111", "EEEEEEEFEEEEEEEF");	// multi "digit"
	AdditionTest("11111111", "EEEEEEEFEEEEEEEF");
	AdditionTest("1111111111111111", "EEEEEEEF");
	
	AdditionTest("-11111111", "EEEEEEEF");
	AdditionTest("11111111", "-EEEEEEEF");
	
	AdditionTest("1FD4", "-76B51AE8");	// both negative

	//
	// Subtraction Tests
	//
	printf("*** SUB TESTS ***\n");
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
/*	printf("*** POW TESTS ***\n");
	
	int i;
	
	for(i=0; i <= 10; ++i)
		PowTest("-11111111", i);	// single "digit"

	PowTest("FFFFFFFF", 0xFFF);
*/	
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



