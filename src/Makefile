GPP   = /usr/bin/g++
GCC   = /usr/bin/gcc
FLAGS = -W -Wall -pedantic -g -O3 -Weffc++ -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual
LIBS  =
EXEC  = BigNumbers

all: main.o Integer.o 
	$(GPP) $(FLAGS) *.o -o $(EXEC) $(LIBS) 

main.o: main.cxx Integer.h
	$(GPP) -c $(FLAGS) main.cxx

Integer.o: Integer.cxx Integer.h
	$(GPP) -c $(FLAGS) Integer.cxx

clean:
	rm *~ *.o $(EXEC)
