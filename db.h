#ifndef IDJIT_DB_H_
#define IDJIT_DB_H_

#include <sqlite3.h>

class Db {
  public:
    Db(const char *path, bool create_flag = false);
    void initialize();

  private:
    void execute(const char *sql);

    sqlite3 *db_ = nullptr;
};

#endif  /* IDJIT_DB_H_ */
