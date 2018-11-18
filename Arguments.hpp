#ifndef IDJIT__ARGUMENTS_HPP
#define IDJIT__ARGUMENTS_HPP

#include <string>
#include <vector>
#include <map>

class Arguments {
  private:
    std::string _command;
    std::vector<std::string> _args;
    std::map<std::string, std::string> _options;
  public:
    Arguments(int argc, char** argv);
    std::string command() { return _command; }
    const std::vector<std::string>& args() { return _args; }
};

#endif /* IDJIT__ARGUMENTS_HPP */

