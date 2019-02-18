#include <iostream>
#include "arguments.h"
#include "commands.h"

void show_help() {
  std::cout << "usage: idjit [-h] <command> <args>" << std::endl;
  std::cout << std::endl;
  std::cout << "  init      start a new idjit database" << std::endl;
}

int main(int argc, const char *argv[]) {
  try {
    auto args = idjit::parse_commandline(argc, argv);
    auto opt = args.options.find("h");
    if (opt != args.options.end() && opt->second == "true") {
      show_help();
      return 0;
    }
    if (args.command == "init") {
      idjit::do_init(args.args);
    } else {
      std::cout << "No action taken." << std::endl;
      std::cout << args << std::endl;
    }
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "idjit: " << e.what() << std::endl;
    return -1;
  }
}

