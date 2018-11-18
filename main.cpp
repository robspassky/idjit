#include <iostream>
#include <stdexcept>
#include "Arguments.hpp"
#include "InitCommand.hpp"

int main(int argc, char **argv) {

  try {

    Arguments arguments{argc, argv};

    auto pcmd = Command::create(arguments);

    pcmd->run();

    return 0;

  } catch (const std::exception& e) {

    std::cerr << "idjit failed with: " << e.what() << std::endl;

    return -1;

  }

}

