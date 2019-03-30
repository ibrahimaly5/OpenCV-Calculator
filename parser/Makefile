CC=g++
LFLAGS=
CFLAGS=-c -Wall -std=c++11 -O2
OBJS=parser.o lexer.o
EXE=parser

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)
# lexer: lexer.o
# 	$(CC) lexer.o -o lexer $(LFLAGS)
parser.o: parser.cpp  parser.h lexer.h token.h
	$(CC) parser.cpp -o parser.o $(CFLAGS)
lexer.o: lexer.cpp  lexer.h token.h
	$(CC) lexer.cpp -o lexer.o $(CFLAGS)
clean:
	@rm -f $(OBJS) $(EXE)