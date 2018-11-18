#ifndef IDJIT__INITCOMMAND_HPP
#define IDJIT__INITCOMMAND_HPP

#include <string>

class InitCommand {
  private:
    std::string _path;

  public:
    InitCommand(const std::string& dirname = ".") { _path = dirname + "/.idjit.db"; }
    void run();
};

#endif /* IDJIT__INITCOMMAND_HPP */
