CC=g++
LFLAGS=
CFLAGS=-c -Wall -std=c++11 -O2
OBJS=lexer.o
EXE=lexer

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

lexer.o: lexer.cpp  lexer.h token.h
	$(CC) lexer.cpp -o lexer.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)