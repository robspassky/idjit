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
	"github.com/google/uuid"
	_ "github.com/mattn/go-sqlite3"
	"log"
	"os"
	"path/filepath"
)

type Task struct {
	Id       string
	Name     string
	Owner    sql.NullString
	Assignee string
	Days     sql.NullInt64
	Progress sql.NullInt64
	Status   sql.NullString
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
  );`

	sqlTaskAdd = "INSERT INTO tasks (id, name, assignee) VALUES (?, ?, ?);"

	sqlTaskList = `
  SELECT 
    id,
    name,
    owner,
    assignee,
    days,
    progress,
    status,
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

func dbConfigGet(key string) string {
	db := findopen()
	row := db.QueryRow(sqlConfigGet, key)
	var value string
	if err := row.Scan(&value); err != nil {
		log.Fatal(err)
	}
	return value
}

func dbTaskAdd(name string) {
	db := findopen()
	id := mkuuid()
	username := dbConfigGet(keyDefaultUser)
	_, err := db.Exec(sqlTaskAdd, id, name, username)
	if err != nil {
		log.Fatal(err)
	}
}

func dbTaskList() []Task {
	db := findopen()
	name := dbConfigGet(keyDefaultUser)
	if name == "" {
		log.Fatal("must set default user first")
	}
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
			&t.Days,
			&t.Progress,
			&t.Status,
			&t.Priority,
			&t.Ordering,
		); err != nil {
			log.Fatal(err)
		}
		tasks = append(tasks, t)
	}
	return tasks
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
