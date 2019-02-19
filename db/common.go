package db

import (
  "database/sql"
  "fmt"
  "github.com/google/uuid"
  _ "github.com/mattn/go-sqlite3"
  "os"
  "path/filepath"
  "log"
)

const dbname = ".idjit.db"
var dbsave *sql.DB = nil

func initialized(dir string) bool {
  f := fmt.Sprintf("%s/%s", dir, dbname)
  _, err := os.Stat(f)
  return err == nil
}

func findopen() *sql.DB {
  if dbsave != nil {
    return dbsave
  }
  d, err := os.Getwd()
  if err != nil {
    log.Fatal(err)
  }
  for d != "." {
    if initialized(d) {
      return open(d)
    }
    d = filepath.Dir(d)
  }
  log.Fatal("cannot find an initialized idjit instance")
  return nil
}

func open(dir string) *sql.DB {
  if dbsave != nil {
    return dbsave
  }
  var err error = nil
  f := fmt.Sprintf("%s/%s", dir, dbname)
  dbsave, err = sql.Open("sqlite3", f)
  if err != nil {
    log.Fatal(err)
  }
  return dbsave
}

func mkuuid() string {
  return uuid.New().String()
}

func Close() {
  if dbsave != nil {
    dbsave.Close()
  }
}

