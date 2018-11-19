#ifndef __SQLITEPP_HPP
#define __SQLITEPP_HPP

#include <map>
#include <string>
#include <exception>
#include <iostream>
#include "sqlite3.h"

using namespace std;

namespace sqlite {

  class stmt {
    private:
      string _sql;

    public:
      stmt(string sql) : _sql(sql) {}

      string sql() { return _sql; }
      virtual void process(map<string, string>& row) { }
      virtual ~stmt() {}
  };

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

      void execute(string sql) {
        stmt st{sql};
        execute(&st);
      }

      void execute(stmt* st) {
        char *errmsg = nullptr;
        int err = sqlite3_exec(_pdb, st->sql().c_str(), db::exec_callback, st, &errmsg);

        if (err != SQLITE_OK)
          throw sqlite_error(err);

        if (errmsg != nullptr)
          throw sqlite_error(errmsg);
      }

      static int exec_callback(void *context, int ncols, char **data, char **columns) {
        map<string, string> row;
        for (int i=0; i<ncols; i++)
          row.insert(make_pair<string, string>(columns[i], data[i]));

        try {
          auto pstmt = reinterpret_cast<stmt*>(context);
          pstmt->process(row);
        } catch (const exception& e) {
          return -1;
        }
        return 0;
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
