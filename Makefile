# Makefile
OBJS = term_control.o Lexer.o error_handling.o ubcalc.o infix.o\
       Postfix_Evaluator.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG)
LFLAGS = -Wall $(DEBUG)

ubcalc: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ubcalc

# ubcal program
ubcalc.o : term_control.o Lexer.o infix.o error_handling.o ubcalc.cpp
	$(CC) -c $(CFLAGS) ubcalc.cpp

# uses Lexer, error_handling
infix.o : Lexer.o error_handling.o term_control.o infix.h infix.cpp\
          Postfix_Evaluator.o
	$(CC) -c $(CFLAGS) infix.cpp

# uses Lexer, error_handling, term_control                                      
Postfix_Evaluator.o: Lexer.o error_handling.o term_control.o\
                      Postfix_Evaluator.h Postfix_Evaluator.cpp
	$(CC) -c $(CFLAGS) Postfix_Evaluator.cpp    

# error handling routines make use of terminal control routines
error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# the Lexer is fairly independent
Lexer.o : Lexer.h Lexer.cpp
	$(CC) -c $(CFLAGS) Lexer.cpp

# this object file is at the "lowest level"
term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp

clean:
	rm -f *.o a.out ubcalc
