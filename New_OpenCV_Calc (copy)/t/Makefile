CC=g++
LFLAGS=
CFLAGS=-c -Wall -std=c++11 -O2
OBJS= lexer.o parser.o evaluator.o 
EXE=evaluator

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

# main.o: main.cpp parser.h lexer.h
# 	$(CC) main.cpp -o main.o $(CFLAGS)

parser.o: parser.cpp  parser.h lexer.h 
	$(CC) parser.cpp -o parser.o $(CFLAGS)

evaluator.o: evaluator.cpp evaluator.h  parser.h lexer.h 
	$(CC) evaluator.cpp -o evaluator.o $(CFLAGS)

lexer.o: lexer.cpp  lexer.h
	$(CC) lexer.cpp -o lexer.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)