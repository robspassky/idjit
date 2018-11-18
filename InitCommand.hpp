#ifndef IDJIT__INITCOMMAND_HPP
#define IDJIT__INITCOMMAND_HPP

#include <string>

class InitCommand {
  private:
    std::string _path;

  public:
    InitCommand(const std::string& dirname = ".") { _path = dirname + "/.idjit.db"; }
    std::pair<bool, std::string> run();
};

#endif /* IDJIT__INITCOMMAND_HPP */
