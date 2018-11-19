#ifndef __SQLITEPP_HPP
#define __SQLITEPP_HPP

#include <string>
#include <exception>
#include "sqlite3.h"


using namespace std;

namespace sqlite {

  class sqlite_error : public exception {
    private:
      string _message;

    public:
      sqlite_error(int sqlite_errnum) { 
        _message = "sqlite3 error: ";
        _message += sqlite3_errstr(sqlite_errnum);
      }
      sqlite_error(char *errmsg, bool free = true) { 
        _message = errmsg; 
        if (free)
          sqlite3_free(errmsg);
      }
      const char *what() const noexcept { return _message.c_str(); }
  };

  class db {

    private:
      sqlite3* _pdb = nullptr;

    public:
      db(sqlite3 **ppdb) {
        _pdb = *ppdb;
        *ppdb = nullptr;
      }

      db(const db& other) = delete;
      db& operator=(const db& other) = delete;

      db(db&& other) {
        _pdb = other._pdb;
        other._pdb = nullptr;
      }

      db& operator=(db&& other) {
        _pdb = other._pdb;
        other._pdb = nullptr;
        return *this;
      }

      virtual ~db() {
        (void) sqlite3_close_v2(_pdb);
      }

  };

  db create(string path) {
    sqlite3 *pdb = nullptr;

    int err = sqlite3_open_v2(path.c_str(), &pdb, SQLITE_OPEN_READONLY, NULL);
    if (err == SQLITE_OK)
      throw sqlite_error((char *)"database already exists", false);
    pdb = nullptr;

    err = sqlite3_open_v2(path.c_str(), &pdb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (err != SQLITE_OK)
      throw sqlite_error(err);

    return db(&pdb);
  }

  db open(string path) {
    sqlite3 *pdb = nullptr;
    int err = sqlite3_open_v2(path.c_str(), &pdb, SQLITE_OPEN_READWRITE, NULL);
    if (err != SQLITE_OK)
      throw sqlite_error(err);

    return db(&pdb);
  }

}

#endif /* __SQLITEPP_HPP */
