PROGRAM=dictionary
CXX       = g++
CXXFLAGS  = -O3 -std=c++17 -Wall

$(PROGRAM): dictionary.o
	$(CXX) -o $(PROGRAM) dictionary.o

.PHONY: clean

clean:
	-rm *.o *.opf *.html $(PROGRAM)
