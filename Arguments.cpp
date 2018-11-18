#include "Arguments.hpp"
#include <stdexcept>

Arguments::Arguments(int argc, char **argv) {
  if (argc < 2)
    throw std::invalid_argument("no command specified");

  _command = argv[1];

  if (argc > 2)
    _args.assign(argv+2, argv+argc);
}

