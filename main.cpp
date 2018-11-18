#include <iostream>
#include "InitCommand.hpp"

int main(int argc, char **argv) {

  InitCommand ic;

  auto result = ic.run();
  if (!result.first) {
    std::cerr << "Error: " << result.second << std::endl;
  }
  return 0;
}

