#ifndef IDJIT__COMMAND_HPP
#define IDJIT__COMMAND_HPP

#include "arguments.h"
#include <memory>

class Command {
  public:
    static std::unique_ptr<Command> create(const Arguments& args);
    virtual void run() = 0;
    virtual ~Command() {}
};

#endif /* IDJIT__COMMAND_HPP */

