#include <iostream>
#include <stdexcept>
#include "Arguments.hpp"
#include "InitCommand.hpp"

int main(int argc, char **argv) {

  try {

    Arguments a{argc, argv};

    if (a.command() == "init") {

      InitCommand ic{a.args()};

      ic.run();

    } else {

      throw std::invalid_argument("unknown command");

    }

    return 0;

  } catch (const std::exception& e) {

    std::cerr << "idjit failed with: " << e.what() << std::endl;

    return -1;

  }

}

