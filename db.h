#ifndef IDJIT__DB_HPP
#define IDJIT__DB_HPP

#include <string>
#include <vector>
#include <sqlite3.h>

class Db {
  private:
    sqlite3* _db = nullptr;

  public:
    Db(std::string path = ".idjit.db", bool create_flag = false);
    void initialize();
    void execute(std::string sql);
};

#endif /* IDJIT__DB_HPP */
