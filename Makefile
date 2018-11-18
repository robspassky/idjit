CXX = clang++ 
CXXFLAGS = -O3 -std=c++17

LDFLAGS = 

LIBRARIES = -lsqlite3

default: idjit

all: idjit test

cleanall: clean cleantest

objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

idjit: $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBRARIES) -o idjit $^

clean:
	$(RM) -f idjit $(objects)

# Unit Tests
# (could be done with a tests/Makefile and a $(MAKE) -C here, but
# both Makefiles are small enough I think it still works like this

test_sources := $(wildcard tests/test_*.cpp)

test_objects := $(test_sources:%.cpp=%.o)

test_subjects := $(test_sources:tests/test_%.cpp=%.o)

test: tests/test $(test_objects)
	./tests/test

tests/test: tests/test.o $(test_objects) $(test_subjects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBRARIES) -o tests/test $^

cleantest:
	$(RM) -f $(test_objects)

