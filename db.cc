#include "db.h"

#include <iostream>
#include <stdexcept>
#include <unistd.h>

const char *DEFAULT_DB_NAME = ".idjit.db";

Db::Db(const char *path, bool create) {
  if (*path == '\0')
    path = DEFAULT_DB_NAME;

  std::cerr << "path is " << path << std::endl;
  std::cerr << "access is " << access(path, F_OK) << std::endl;

  if (create && (access(path, F_OK) != -1))
    throw std::invalid_argument("already initialized");

  if (!create && access(path, F_OK) == -1)
    throw std::invalid_argument("not initialized");

  if (create) {
    int err = sqlite3_open_v2(path, &db_, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (err != SQLITE_OK)
      throw std::logic_error(sqlite3_errstr(err));
  } else {
    int err = sqlite3_open_v2(path, &db_, SQLITE_OPEN_READWRITE, NULL);
    if (err != SQLITE_OK)
      throw std::logic_error(sqlite3_errstr(err));
  }
}

void Db::initialize() {
  const char *sql = R"(
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

  execute(sql);
}

void Db::execute(const char *sql) {
  char *errmsg = nullptr;
  sqlite3_exec(db_, sql, NULL, NULL, &errmsg);
  if (errmsg != nullptr)
    throw std::invalid_argument(errmsg);
}

