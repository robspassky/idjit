package db

import (
  _ "github.com/mattn/go-sqlite3"
  "database/sql"
  "log"
)

func open(name string) *sql.DB {
  db, err := sql.Open("sqlite3", name)
  if err != nil {
    log.Fatal(err)
  }
  return db
}

