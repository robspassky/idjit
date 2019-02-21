package main

import (
  "encoding/json"
  "fmt"
  "log"
  "net/http"
)

func startServer(port int, docrootdir string) {
  http.HandleFunc("/api/tasks", hndTaskList)
  http.Handle("/", http.FileServer(http.Dir(docrootdir + "/.idjit-web")))
  log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", port), nil))
}

func hndTaskList(w http.ResponseWriter, r *http.Request) {
  tasks := dbTaskListAll()
  b, err := json.Marshal(tasks)
  if err != nil {
    abort("failed to json encode tasks", err)
  }
  w.Header().Add("Content-Type", "application/json")
  w.Write(b)
}
