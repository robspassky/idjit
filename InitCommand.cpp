#include "InitCommand.hpp"
#include "Db.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;

void InitCommand::run() {
  Db db(_path, true);
  db.initialize();
}

