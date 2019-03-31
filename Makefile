CC = g++
LFLAGS = -O3 
CFLAGS = `pkg-config --cflags --libs opencv` -std=c++11 -Wall
OBJS = main.o
PROGS = OpenCVCalculator
all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o OpenCVCalculator $(CFLAGS)
# 	./OpenCVCalculator
train: train.o
	$(CC) train.o -o train $(CFLAGS)

calculator.o: main.cpp
	 $(CC) main.cpp -o main.o $(CFLAGS)

train.o: train.cpp
	$(CC) train.cpp -o train.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(PROGS) train.o