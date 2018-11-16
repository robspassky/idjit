CXX = clang++

CXXFLAGS = -O3 -std=c++17

all: idjit Makefile

objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

idjit: $(objects)
	$(CXX) -o idjit $^

test:
	$(MAKE) -C tests

clean:
	$(RM) -f idjit *.o
