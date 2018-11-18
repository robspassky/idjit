#include "Arguments.hpp"
#include <stdexcept>

Arguments::Arguments(int argc, char **argv) {
  _args.assign(argv+1, argv+argc);
}

