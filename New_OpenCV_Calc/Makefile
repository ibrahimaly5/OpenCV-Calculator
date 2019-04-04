CC = g++
LFLAGS = 
CFLAGS = `pkg-config --cflags --libs opencv` -std=c++11 -Wall -O2 -c
OBJS = util.o main.o
PROGS = OpenCVCalculator

OpenCVCalculator: $(OBJS)
	$(CC) $(OBJS) -o OpenCVCalculator
main.o: main.cpp util.h
	$(CC) main.cpp -o main.o $(CFLAGS)
util.o: util.h util.cpp
	$(CC) util.cpp -o util.o $(CFLAGS)
