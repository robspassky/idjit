#ifndef IDJIT__JOBCOMMAND_HPP
#define IDJIT__JOBCOMMAND_HPP

#include <string>
#include <vector>
#include "Command.hpp"

class JobCommand : public Command {
  private:
    std::string _name;

  public:
    JobCommand(const std::vector<std::string>& args);
    void run();
};

#endif /* IDJIT__JOBCOMMAND_HPP */
