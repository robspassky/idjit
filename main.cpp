#include <iostream>
#include <stdexcept>
#include "Arguments.hpp"
#include "InitCommand.hpp"

void execute_command(const std::vector<std::string>& args) {
  if (args.size() == 0)
    throw std::invalid_argument("no arguments provided");

  if (args[0] == "init") {
    switch (args.size()) {
      case 2: 
        {
          InitCommand ic{args[1]};
          ic.run();
          break;
        }
      case 1:
        {
          InitCommand ic;
          ic.run();
          break;
        }
      default:
        throw std::invalid_argument("too many arguments passed to 'init'");
    }
  } else {
    throw std::invalid_argument("unknown command");
  }
}

int main(int argc, char **argv) {

  try {
    Arguments a{argc, argv};
    auto args = a.args();
    execute_command(args);
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "idjit failed with: " << e.what() << std::endl;
    return -1;
  }
}

