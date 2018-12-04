#ifndef IDJIT_JOB_COMMAND_H_
#define IDJIT_JOB_COMMAND_H_

#include <string>
#include <vector>
#include "command.h"

class JobCommand : public Command {
  private:
    std::string _name;

  public:
    JobCommand(const std::vector<std::string>& args);
    void run();
};

#endif /* IDJIT_JOB_COMMAND_H_ */
