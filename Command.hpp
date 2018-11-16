#ifndef IDJIT__COMMAND_HPP
#define IDJIT__COMMAND_HPP

#include <iostream>
#include "Arguments.hpp"

class Command {
  private:
    int _count;
  public:
    Command(Arguments args);
    void run(std::istream& is, std::ostream& os, std::ostream& es);
};

#endif /* IDJIT__COMMAND_HPP */

