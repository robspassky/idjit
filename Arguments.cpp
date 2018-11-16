#include "Arguments.hpp"
#include <stdexcept>

Arguments::Arguments(int argc, char **argv) {
  if (argc < 2) {
    throw std::invalid_argument("Usage: idjit command arguments");
  }
  command = argv[1];
  for (int i=2; i<argc; i++) {
    args.push_back(argv[i]);
  }
}

