#ifndef IDJIT_ARGUMENTS_H_
#define IDJIT_ARGUMENTS_H_

#include <map>
#include <string>
#include <vector>

// Command-line parser, takes args from main(), expecting something like:
//   $ program -option1=value1 command -option2 arg1 arg2 -option3=true
// Options are processed anywhere and must have '=' unless they are a simple boolean flag.
class Arguments {
 public:
  Arguments(int argc, char **argv);

  const std::vector<std::string>& args() const { return args_; }
  std::string command() const { return command_; }
  bool has(const char *name);
  // const std::string& option(const char *name);

 private:
  void handle_option(const char *option);

  std::string command_;
  std::vector<std::string> args_;
  std::map<std::string, std::string> options_;
};

#endif  // IDJIT_ARGUMENTS_H_

