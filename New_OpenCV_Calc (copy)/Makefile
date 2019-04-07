
main:
	g++ main.cpp util.cpp lexer.cpp parser.cpp -o OpenCVCalculator `pkg-config --libs --cflags opencv` -std=c++11
train:
	g++ train.cpp util.cpp -o train `pkg-config --libs --cflags opencv` -std=c++11

clean:
	@rm -f train OpenCVCalculator