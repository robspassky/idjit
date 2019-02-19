package db

import (
  "log"
)

func SetConfig(key, value string) {
  db := findopen()
  sql := `
  INSERT INTO config (key, value) VALUES (?, ?)
    ON CONFLICT(key) DO UPDATE SET value = ?;
  `
  if _, err := db.Exec(sql, key, value, value); err != nil {
    log.Fatal(err)
  }
}

func GetConfig(key string) string {
  db := findopen()
  sql := "SELECT value FROM config WHERE key = ?"
  row := db.QueryRow(sql, key)
  var value string
  if err := row.Scan(&value); err != nil {
    log.Fatal(err)
  }
  return value
}
