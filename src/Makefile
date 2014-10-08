GPP     = g++
GCC     = gcc
FLAGS   = -W -Wall -g
LIBS    = -lgmp
INCLUDE = -I.
EXEC    = test

all:	*.h \
	main.o \
	bignum_arith_ui.o \
	bignum_assign.o \
	bignum_cmp.o \
	bignum_arith.o \
	bignum_bit.o \
	bignum_mod_arith.o \
	bignum_num_theory.o
	$(GPP) $(INCLUDE) $(FLAGS) *.o -o $(EXEC) $(LIBS)

calc:	*.h \
	calc.o \
	bignum_arith_ui.o \
	bignum_assign.o \
	bignum_cmp.o \
	bignum_arith.o \
	bignum_bit.o \
	bignum_mod_arith.o \
	bignum_num_theory.o
	$(GPP) $(INCLUDE) $(FLAGS) *.o -o calc $(LIBS)

calc.o: calc.c /usr/include/gmp.h *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) calc.c

main.o: main.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) main.c

bignum_num_theory.o: bignum_num_theory.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_num_theory.c

bignum_mod_arith.o: bignum_mod_arith.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_mod_arith.c

bignum_bit.o: bignum_bit.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_bit.c
	
bignum_arith_ui.o: bignum_arith_ui.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_arith_ui.c

bignum_assign.o: bignum_assign.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_assign.c

bignum_cmp.o: bignum_cmp.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_cmp.c

bignum_arith.o: bignum_arith.c *.h
	$(GCC) -c $(INCLUDE) $(FLAGS) bignum_arith.c

clean:
	rm *~ *.o $(EXEC) calc
