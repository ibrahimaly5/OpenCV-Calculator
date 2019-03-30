CC = g++
LFLAGS = -O3 -std=c++11
CFLAGS = `pkg-config --cflags --libs opencv`
OBJS = main.o
PROGS = OpenCVCalculator
all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o OpenCVCalculator $(CFLAGS)
# 	./OpenCVCalculator
calculator.o: main.cpp
	 $(CC) main.cpp -o main.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(PROGS)