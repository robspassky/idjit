#ifndef IDJIT__DB_HPP
#define IDJIT__DB_HPP

#include <string>
#include <sqlite3.h>

class Db {
  private:
    sqlite3* _db = nullptr;

  public:
    Db(std::string path, bool create_flag);
    void initialize();
};

#endif /* IDJIT__DB_HPP */
