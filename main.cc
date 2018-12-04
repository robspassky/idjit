#include <iostream>
#include <memory>
#include <stdexcept>

#include "arguments.h"
#include "command.h"

int main(int argc, char **argv) {
  try {
    Arguments arguments{argc, argv};
    std::unique_ptr<Command> pcmd = Command::create(arguments);
    pcmd->run();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "idjit failed - " << e.what() << std::endl;
    return -1;
  }
}

