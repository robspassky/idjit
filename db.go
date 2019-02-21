// Copyright © 2019 Rob Cabacungan <robspassky@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

package main

import (
	"database/sql"
	"fmt"
	"log"
	"os"
	"path/filepath"
  "strconv"

	"github.com/google/uuid"
	_ "github.com/mattn/go-sqlite3"
)

type Task struct {
	Id       string
	Name     string
	Owner    sql.NullString
	Assignee string
	Eta     int
	Est     int
  Status  string
	Progress sql.NullInt64
	Priority sql.NullInt64
	Ordering sql.NullFloat64
}

var (
	keyDefaultUser = "defaultUser"
)

const (
	sqlConfigSet = `
  INSERT INTO config (key, value) VALUES (?, ?)
    ON CONFLICT(key) DO UPDATE SET value = ?;`

	sqlConfigGet = "SELECT value FROM config WHERE key = ?;"

	sqlInitialize = `
  CREATE TABLE tasks (
    id TEXT,
    name TEXT,
    owner TEXT,
    assignee TEXT,
    eta INT,
    est INT,
    progress INT,
    priority INT,
    ordering REAL,
    PRIMARY KEY (id)
  );
  CREATE INDEX task_assignee ON tasks (assignee, id);
  CREATE INDEX task_owner ON tasks (owner, id);
  CREATE TABLE deps (
    parent TEXT,
    child TEXT,
    PRIMARY KEY (parent, child)
  );
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
  );`

  sqlTaskFind = "SELECT id FROM tasks WHERE id LIKE ?;"

	sqlTaskAdd = "INSERT INTO tasks (id, name, assignee, eta, est) VALUES (?, ?, ?, ?, ?);"
  
	sqlTaskEta = "UPDATE tasks SET eta = ? WHERE id = ?;"

	sqlTaskUndepAll = "DELETE FROM deps WHERE parent = ?;"

	sqlTaskList = `
  SELECT 
    id,
    name,
    owner,
    assignee,
    eta,
    est,
    progress,
    priority,
    ordering
  FROM tasks WHERE assignee = ?`

	sqlUserFind = "SELECT * FROM users WHERE name = ?;"

	sqlUserCreate = "INSERT INTO USERS (id, name) VALUES (?, ?);"
)

const dbName = ".idjit.db"

var dbSave *sql.DB = nil

func dbExists(dir string) bool {
	s := fmt.Sprintf("%s/%s", dir, dbName)
	_, err := os.Stat(s)
	return err == nil
}

func dbInitialize(dir string) *sql.DB {
	if dbExists(dir) == true {
		log.Fatal("idjit already initialized")
	}
	db := open(dir)
	defer db.Close()
	if _, err := db.Exec(sqlInitialize); err != nil {
		log.Fatal(err)
	}
	return db
}

func dbUserFind(name string) bool {
	db := findopen()
	rows, err := db.Query(sqlUserFind, name)
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

func dbUserCreate(name string) {
	db := findopen()
	id := mkuuid()
	_, err := db.Exec(sqlUserCreate, id, name)
	if err != nil {
		log.Fatal(err)
	}
}

func dbConfigSet(key, value string) {
	db := findopen()
	if _, err := db.Exec(sqlConfigSet, key, value, value); err != nil {
		log.Fatal(err)
	}
}

func dbConfigGet(key string, def string) string {
	db := findopen()
	row := db.QueryRow(sqlConfigGet, key)
	var value string
	if err := row.Scan(&value); err != nil {
    return def
	}
	return value
}

func dbGetDefaultUser() string {
	name := dbConfigGet(keyDefaultUser, "")
  if name == "" {
    log.Fatal("must set user first")
  }
  return name
}

func dbTaskAdd(name string, est int) {
	db := findopen()
	id := mkuuid()
	username := dbGetDefaultUser()
  log.Println(sqlTaskAdd)
	_, err := db.Exec(sqlTaskAdd, id, name, username, est, est)
	if err != nil {
		log.Fatal(err)
	}
}

func dbTaskList() []Task {
	db := findopen()
	name := dbGetDefaultUser()
	rows, err := db.Query(sqlTaskList, name)
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	tasks := make([]Task, 0)
	for rows.Next() {
		var t Task
		if err := rows.Scan(
			&t.Id,
			&t.Name,
			&t.Owner,
			&t.Assignee,
			&t.Eta,
			&t.Est,
			&t.Progress,
			&t.Priority,
			&t.Ordering,
		); err != nil {
			log.Fatal(err)
		}
    if t.Eta == t.Est {
      t.Status = "READY"
    } else if t.Eta == 0 {
      t.Status = "DONE"
    } else {
      t.Status = "WORK"
    }
		tasks = append(tasks, t)
	}
	return tasks
}

func dbTaskDep(parent string, children []string) {
  sqlStmt := "INSERT INTO deps VALUES";
  for i := range children {
    if i > 0 {
      sqlStmt += ","
    }
    sqlStmt += fmt.Sprintf(" (?, ?)")
  }
  sqlStmt += ";"
  args := make([]interface{}, len(children)*2)
  for i, child := range children {
    args[i*2] = parent
    args[(i*2)+1] = child
  }
  db := findopen()
  if _, err := db.Exec(sqlStmt, args...); err != nil {
    log.Fatal(err)
  }
}

func dbTaskEta(idpart string, etastr string) {
  eta, err := strconv.Atoi(etastr)
  if err != nil {
    abort("ETA must be a number", err)
  }
  db := findopen()
  id := onetask(idpart)
  if _, err := db.Exec(sqlTaskEta, eta, id); err != nil {
    abort("failed to run eta update sql", err)
  }
}

func dbTaskFind(id string) []string {
  wildcard := fmt.Sprintf("%%%s%%", id)
  db := findopen()
  retval := make([]string, 0)
  if rows, err := db.Query(sqlTaskFind, wildcard); err == nil {
    for rows.Next() {
      var val string
      if err := rows.Scan(&val); err != nil {
        abort("failed to read task id from sql result", err)
      }
      retval = append(retval, val)
    }
  }
  return retval
}

func dbTaskUndep(parent string, children []string) {
  sqlStmt := "DELETE FROM deps WHERE parent = ? AND child IN ("
  for i := range children {
    if i > 0 {
      sqlStmt += ", "
    }
    sqlStmt += "?"
  }
  sqlStmt += ");"
  args := make([]interface{}, len(children)+1)
  args[0] = parent
  for i, child := range children {
    args[i+1] = child
  }
  db := findopen()
  if _, err := db.Exec(sqlStmt, args...); err != nil {
    log.Fatal(err)
  }
}

func dbTaskUndepAll(parent string) {
  db := findopen()
  if _, err := db.Exec(sqlTaskUndepAll, parent); err != nil {
    log.Fatal(err)
  }
}

// internal functions

func findopen() *sql.DB {
	if dbSave != nil {
		return dbSave
	}
	d, err := os.Getwd()
	if err != nil {
		log.Fatal(err)
	}
	for d != "." {
		if dbExists(d) {
			return open(d)
		}
		d = filepath.Dir(d)
	}
	log.Fatal("cannot find an initialized idjit instance")
	return nil
}

func open(dir string) *sql.DB {
	if dbSave != nil {
		return dbSave
	}
	var err error = nil
	f := fmt.Sprintf("%s/%s", dir, dbName)
	dbSave, err = sql.Open("sqlite3", f)
	if err != nil {
		log.Fatal(err)
	}
	return dbSave
}

func mkuuid() string {
	return uuid.New().String()
}

func onetask(s string) string {
  ids := dbTaskFind(s)
  if len(ids) == 0 {
    log.Fatalf("no task for '%s' found", s)
  }
  if len(ids) > 1 {
    log.Printf("given task id '%s' is ambiguous:\n", s)
    for _, id := range ids {
      log.Printf("  %s\n", id)
    }
    log.Fatalf("please try again")
  }
  return ids[0]
}

