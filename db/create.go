package db

import (
  "log"
)

func Create(dir string) {
  if initialized(dir) == true {
    log.Fatal("idjit already initialized")
  }
  db := open(dir)
  //defer db.Close()
  sqlStmt := `
  CREATE TABLE tasks (
    id TEXT,
    name TEXT,
    owner TEXT,
    assignee TEXT,
    days INT,
    progress INT,
    status TEXT,
    priority INT,
    ordering REAL,
    PRIMARY KEY (id)
  );
  CREATE INDEX task_assignee ON tasks (assignee, id);
  CREATE INDEX task_owner ON tasks (owner, id);
  CREATE TABLE users (
    id TEXT,
    name TEXT,
    PRIMARY KEY (id),
    UNIQUE (name)
  );
  CREATE TABLE config (
    key TEXT,
    value TEXT,
    PRIMARY KEY (key)
  );
  `
  if _, err := db.Exec(sqlStmt); err != nil {
    log.Fatal(err)
  }
}

