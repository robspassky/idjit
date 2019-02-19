package db

import (
  "log"
)

func FindUser(name string) bool {
  db := findopen()
  //defer db.Close()
  sqlStmt := "SELECT * FROM users WHERE name = ?;"
  rows, err := db.Query(sqlStmt, name)
  if err != nil {
    log.Fatal(err)
  }
  defer rows.Close()
  count := 0
  for rows.Next() == true {
    count += 1
  }
  if count > 1 {
    log.Fatal("found duplicate users")
  }
  return count == 1
}

func CreateUser(name string) {
  db := findopen()
  //defer db.Close()
  sqlStmt := "INSERT INTO USERS (id, name) VALUES (?, ?);"
  id := mkuuid()
  _, err := db.Exec(sqlStmt, id, name)
  if err != nil {
    log.Fatal(err)
  }
}

func SetDefaultUser(name string) {
  SetConfig("defaultUser", name)
}

func GetDefaultUser() string {
  return GetConfig("defaultUser")
}

