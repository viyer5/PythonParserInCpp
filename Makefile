# Makefile
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11

programs: ubcalc

# uses Lexer to implement UBCalculator

# only uses Lexer to test the Lexer class
ubcalc : Lexer.o UBCalculator.o error_handling.o 
	$(CC) $(CFLAGS) UBCalculator.o Lexer.o error_handling.o UBCalcDriver.cpp  -o ubcalc 

# error handling routines make use of terminal control routines
error_handling.o : error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# the Lexer is fairly independent
Lexer.o : Lexer.h Lexer.cpp
	$(CC) -c $(CFLAGS) Lexer.cpp
UBCalculator.o : UBCalculator.cpp UBCalculator.h
	$(CC) -c $(CFLAGS) UBCalculator.cpp

clean:
	rm -f *.o a.out ubcalc 
