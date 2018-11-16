#ifndef IDJIT__ARGUMENTS_HPP
#define IDJIT__ARGUMENTS_HPP

#include <string>
#include <vector>

class Arguments {
  public:
    std::string command;
    std::vector<std::string> args;
    Arguments(int argc, char **argv);
};

#endif /* IDJIT__ARGUMENTS_HPP */

