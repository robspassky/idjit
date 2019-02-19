package db

import (
  "database/sql"
  "log"
)


type Task struct {
  Id string
  Name string
  Owner sql.NullString
  Assignee string
  Days sql.NullInt64
  Progress sql.NullInt64
  Status sql.NullString
  Priority sql.NullInt64
  Ordering sql.NullFloat64
}

func ListTasks() []Task {
  db := findopen()
  sqlStmt := `
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
  FROM tasks WHERE assignee = ?
  `
  username := GetDefaultUser()
  if username == "" {
    log.Fatal("set default user first")
  }
  rows, err := db.Query(sqlStmt, username)
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

func AddTask(name string) {
  db := findopen()
  //defer db.Close()
  sqlStmt := "INSERT INTO tasks (id, name, assignee) VALUES (?, ?, ?);"
  id := mkuuid()
  username := GetDefaultUser()
  _, err := db.Exec(sqlStmt, id, name, username)
  if err != nil {
    log.Fatal(err)
  }
}

