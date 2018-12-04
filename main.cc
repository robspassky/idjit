#include <iostream>
#include "arguments.h"

int main(int argc, const char *argv[]) {
  try {
    auto args = idjit::parse_commandline(argc, argv);
    std::cout << args << std::endl;
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "idjit: " << e.what() << std::endl;
    return -1;
  }
}

