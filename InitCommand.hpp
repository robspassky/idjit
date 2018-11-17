#ifndef IDJIT__INITCOMMAND_HPP
#define IDJIT__INITCOMMAND_HPP

#include <string>
#include <sqlite3.h>

class InitCommand {
  private:
    std::string _dir;
    sqlite3* _db;
    char* populate();

  public:
    InitCommand(const std::string& dirname = ".") : _dir(dirname), _db(nullptr) {}
    std::pair<bool, std::string> run();
};

#endif /* IDJIT__INITCOMMAND_HPP */
