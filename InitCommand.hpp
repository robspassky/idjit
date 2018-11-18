#ifndef IDJIT__INITCOMMAND_HPP
#define IDJIT__INITCOMMAND_HPP

#include <string>
#include <vector>
#include "Command.hpp"

class InitCommand : public Command {
  private:
    std::string _path;

  public:
    InitCommand(const std::vector<std::string>& args);
    void run();
};

#endif /* IDJIT__INITCOMMAND_HPP */
