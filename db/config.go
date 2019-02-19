package db

import (
  "log"
)

func SetConfig(key, value string) {
  db := findopen()
  //defer db.Close()
  sqlStmt := `
  INSERT INTO config (key, value) VALUES (?, ?)
    ON CONFLICT(key) DO UPDATE SET value = ?;
  `
  _, err := db.Exec(sqlStmt, key, value, value)
  if err != nil {
    log.Fatal(err)
  }
}


