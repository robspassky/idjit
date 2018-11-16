#include <iostream>
#include "Arguments.hpp"
#include "Command.hpp"

int main(int argc, char **argv) {

  Arguments args{argc, argv};
  Command cmd{args};
  cmd.run(std::cin, std::cout, std::cerr);

  return 0;
}

