#include "InitCommand.hpp"
#include "Db.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;

pair<bool, std::string> InitCommand::run() {
  try {
    Db db(_path, true);
    db.initialize();
  } catch (const std::exception& e) {
    return make_pair(false, e.what());
  }
  return make_pair(true, "");
}

