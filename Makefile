CC = g++
LFLAGS =
CFLAGS = `pkg-config --cflags --libs opencv`
OBJS = main.o
PROGS = OpenCVCalculator
all: $(OBJS)
	$(CC) $(OBJS) -o OpenCVCalculator $(CFLAGS)
	./OpenCVCalculator
calculator.o: main.cpp
	 $(CC) main.cpp -o main.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(PROGS)