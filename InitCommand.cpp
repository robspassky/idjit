#include "InitCommand.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;

pair<bool, std::string> InitCommand::run() {
  string path = _dir + "/.idjit.db";
  if (access(path.c_str(), F_OK) != -1) {
    return make_pair(false, "file already exists");
  }

  int sqlerr = sqlite3_open(path.c_str(), &_db);
  if (sqlerr != SQLITE_OK)
    return make_pair(false, sqlite3_errstr(errno));

  char *errmsg = populate();
  if (errmsg != NULL) {
    std::string err{errmsg};
    sqlite3_free(errmsg);
    std::cout << "ERROR: " << err << std::endl;
    return make_pair(false, err);
  }

  std::cout << "OK" << std::endl;
  return make_pair(true, "");
}

char* InitCommand::populate() {
  std::string sql = R"(
CREATE TABLE jobs (
  id CHAR(36) NOT NULL PRIMARY_KEY,
  name VARCHAR(30) NOT NULL,
  criteria VARCHAR(1024) NOT NULL,
  owner VARCHAR(30) NOT NULL,
  importance CHAR(3) NOT NULL,
  assignee VARCHAR(30) NOT NULL,
  state CHAR(3) NOT NULL,
  status CHAR(3) NOT NULL,
  points INTEGER NOT NULL,
  deadline INTEGER NOT NULL,
);

CREATE TABLE tags (
  job_id CHAR(36) NOT NULL,
  tag VARCHAR(30) NOT NULL,
  PRIMARY_KEY(job_id, tag),
  KEY (tag)
);

CREATE TABLE dependencies (
  job_id CHAR(36) NOT NULL,
  dependent_job CHAR(36) NOT NULL,
  PRIMARY_KEY(job_id, dependent_job),
  KEY(dependent_job)
);

CREATE TABLE history (
  job_id CHAR(36) NOT NULL PRIMARY_KEY,
  timestamp INTEGER NOT NULL,
  author VARCHAR(30) NOT NULL,
  name VARCHAR(30) NOT NULL,
  criteria VARCHAR(1024) NOT NULL,
  owner VARCHAR(30) NOT NULL,
  importance CHAR(3) NOT NULL,
  assignee VARCHAR(30) NOT NULL,
  state CHAR(3) NOT NULL,
  status CHAR(3) NOT NULL,
  points INTEGER NOT NULL,
  deadline INTEGER NOT NULL,
  job_id CHAR(36) NOT NULL,
  state CHAR(3) NOT NULL,
  assignee CHAR(30) NOT NULL,
  status CHAR(30) NOT NULL,
  PRIMARY_KEY(job_id, timestamp, author)
);
)";

  char *errmsg = nullptr;
  sqlite3_exec(_db, sql.c_str(), NULL, NULL, &errmsg);
  return errmsg;
};
