CXX = clang++

CXXFLAGS = -O3 -std=c++17

all: test

sources := $(wildcard test_*.cpp)
test_objects := test.o $(sources:.cpp=.o)
objects := $(sources:test_%.cpp=../%.o)

test: $(test_objects) $(objects)
	$(CXX) -o test $^

# use test_*.o intead of *.o as test.o takes too damn long to recompile
clean:
	$(RM) -f test test_*.o
