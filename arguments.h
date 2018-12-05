#ifndef IDJIT_ARGUMENTS_H_
#define IDJIT_ARGUMENTS_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace idjit {

struct Arguments {
  std::string command = "";
  std::vector<std::string> args = {};
  std::map<std::string, std::string> options = {};

  bool operator==(const Arguments& other) const {
    return 
      command == other.command &&
      args == other.args &&
      options == other.options;
  }

};

// Command-line parser, takes args from main(), expecting something like:
//   $ program -option1=value1 command -option2 arg1 arg2 -option3=true
// Options are processed anywhere and must have '=' unless they are a simple boolean flag.
const Arguments parse_commandline(int argc, const char *argv[]);

};  // namespace idjit

std::ostream& operator<<(std::ostream& os, const idjit::Arguments& args);

#endif  // IDJIT_ARGUMENTS_H_

