CXX = clang++

CXXFLAGS = -O3 -std=c++17

default: idjit

all: idjit test

cleanall: clean cleantest

objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

idjit: $(objects)
	$(CXX) -o idjit $^

clean:
	$(RM) -f idjit $(objects)

# Unit Tests

test_sources := $(wildcard tests/test_*.cpp)
test_objects := $(test_sources:%.cpp=%.o)
subject_objects := $(test_sources:tests/test_%.cpp=%.o)

test: tests/test
	./tests/test

tests/test: tests/test.o $(test_objects) $(subject_objects)
	$(CXX) -o tests/test $^

cleantest:
	$(RM) -f $(test_objects)

