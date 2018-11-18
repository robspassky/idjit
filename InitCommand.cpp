#include "InitCommand.hpp"
#include "Db.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;

InitCommand::InitCommand(const std::vector<std::string>& args) {
  switch (args.size()) {
    case 1:
      _path = args[0] + "/.idjit.db";
      break;
    case 0:
      _path = "./.idjit.db";
      break;
    default:
      throw std::invalid_argument("too many arguments passed to 'init'");
  }
}

void InitCommand::run() {
  Db db(_path, true);
  db.initialize();
}

