#include "Db.hpp"
#include <stdexcept>
#include <unistd.h>

Db::Db(std::string path, bool create) {
  if (create && (access(path.c_str(), F_OK) != -1))
    throw std::invalid_argument("idjit already initialized");

  if (!create && access(path.c_str(), F_OK) == -1)
    throw std::invalid_argument("idjit not yet initialized");

  int err = sqlite3_open(path.c_str(), &_db);
  if (err != SQLITE_OK)
    throw std::invalid_argument(sqlite3_errstr(err));
}

void Db::initialize() {
  std::string sql = R"(
CREATE TABLE 'jobs' (
  'id'         TEXT,
  'name'       TEXT,
  'criteria'   TEXT,
  'owner'      TEXT,
  'importance' INTEGER,
  'assignee'   TEXT,
  'state'      INTEGER,
  'status'     INTEGER,
  'points'     INTEGER,
  'deadline'   INTEGER,
  CONSTRAINT 'pk' PRIMARY KEY ('id')
);

CREATE TABLE 'tags' (
  'job_id' TEXT,
  'tag'    TEXT,
  CONSTRAINT 'forward' UNIQUE ('job_id', 'tag'),
  CONSTRAINT 'reverse' UNIQUE ('tag', 'job_id')
);

CREATE TABLE deps (
  'job_id' TEXT,
  'dep_id' TEXT,
  CONSTRAINT forward UNIQUE ('job_id', 'dep_id'),
  CONSTRAINT reverse UNIQUE ('dep_id', 'job_id')
);

CREATE TABLE history (
  'id'         TEXT,
  'timestamp'  INTEGER,
  'author'     TEXT,
  'name'       TEXT,
  'criteria'   TEXT,
  'owner'      TEXT,
  'importance' INTEGER,
  'assignee'   TEXT,
  'state'      INTEGER,
  'status'     INTEGER,
  'points'     INTEGER,
  'deadline'   INTEGER,
  CONSTRAINT 'pk' PRIMARY KEY ('id', 'timestamp', 'author')
);
)";

  char *errmsg = nullptr;
  sqlite3_exec(_db, sql.c_str(), NULL, NULL, &errmsg);
  if (errmsg != nullptr) {
    std::string errstring(errmsg);
    sqlite3_free(errmsg);
    throw std::invalid_argument(errstring);
  }
}

