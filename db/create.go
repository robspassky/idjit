package db

import (
  "log"
)

func Create(name string) {
  db := open(name)
  defer db.Close()
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
    ordering REAL
  );
  CREATE TABLE users (
    id TEXT,
    name TEXT
  );
  `
  if _, err := db.Exec(sqlStmt); err != nil {
    log.Fatal(err)
  }
}

