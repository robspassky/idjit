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
	"fmt"
	"log"
  "strconv"

	"github.com/spf13/cobra"
)

var (
	cmdInit = &cobra.Command{
		Use:   "init",
		Run:   runInit,
		Args:  cobra.MaximumNArgs(1),
		Short: "Initialize a new idjit instance",
		Long: `Initialize a new idjit instance by creating a new idjit database 
in the given directory (current directory if none provided).`,
	}

	cmdTask = &cobra.Command{
		Use:   "task",
		Run:   runTaskAdd,
		Short: "Create a new task",
		Long: `Create a new task assigned to the current user and owned by the current team.
For example:

idjit task 'Add "task" command'
idjit task`,
	}

	cmdUser = &cobra.Command{
		Use:   "user",
		Run:   runUser,
		Args:  cobra.ExactArgs(1),
		Short: "Create/set the current user",
		Long: `Creates and/or sets a user to use as default for other commands.

idjit user robc     # make 'robc' current user, error if it doesn't exist
idjit user robc -n  # create if does not exist`,
	}

  cmdServe = &cobra.Command{
    Use: "serve",
    Run: runServe,
    Args: cobra.MaximumNArgs(1),
    Short: "Start server (foreground) with optional port",
    Long: `Start web server.
idjit serve 8888     # start server on port 8888`,
  }

  cmdTaskEta = &cobra.Command{
    Use: "eta",
    Run: runTaskEta,
    Args: cobra.ExactArgs(2),
    Short: "Update the ETA of a task",
    Long: "Update the ETA of a task",
  }

  cmdTaskDep = &cobra.Command{
    Use: "dep",
    Run: runTaskDep,
    Args: cobra.MinimumNArgs(2),
    Short: "Add a dependency between tasks",
    Long: `Add a dependency between tasks.
idjit task dep aaa 111 222 333`,
  }

  cmdTaskUndep = &cobra.Command{
    Use: "undep taskid",
    Run: runTaskUndep,
    Args: cobra.MinimumNArgs(1),
    Short: "Remove a dependency between tasks",
    Long: `Remove a dependency between tasks.
idjit task undep aaa -a            # remove all dependencies
idjit task undep aaa 111 222 333   # remove 3 dependencies`,
  }
)

var flgUserCreate bool
var flgTaskUndepAll bool

func init() {
	cmdRoot.AddCommand(cmdInit)
	cmdRoot.AddCommand(cmdServe)
	cmdRoot.AddCommand(cmdTask)
	cmdTask.AddCommand(cmdTaskDep)
	cmdTask.AddCommand(cmdTaskEta)
	cmdTask.AddCommand(cmdTaskUndep)
	cmdRoot.AddCommand(cmdUser)
	cmdUser.Flags().BoolVarP(&flgUserCreate, "new", "n", false, "Create new user if it does not exist")
  cmdTaskUndep.Flags().BoolVarP(&flgTaskUndepAll, "all", "a", false, "Remove all dependencies")
}

func runInit(cmd *cobra.Command, args []string) {
	dir := "."
	if len(args) > 0 {
		dir = args[0]
	}
	if dbExists(dir) {
		log.Fatalf("idjit already initialized in %s", dir)
	}
	dbInitialize(dir)
}

// TODO: extract dir from flags
func runServe(cmd *cobra.Command, args []string) {
  var dir = "."
  if len(args) > 0 {
    if port, err := strconv.Atoi(args[0]); err == nil {
      startServer(port, dir)
      return
    }
    abort("invalid server port provided", nil)
  }
  startServer(8080, dir)
}

func runTaskAdd(cmd *cobra.Command, args []string) {
	if len(args) == 0 {
		tasks := dbTaskList()
		fmt.Printf("                 Id                                 Name               Status    ETA\n")
		fmt.Printf("------------------------------------  ------------------------------  -------  ------\n")
		for _, t := range tasks {
			fmt.Printf("%s  %30s  %7s  %d\n", t.Id, t.Name, t.Status, t.Eta)
		}
		return
	}
	name := args[0]
  var est = 1
  if len(args) > 1 {
    x, err := strconv.Atoi(args[1])
    if err != nil {
      log.Fatal(err)
    }
    est = x
  }
	dbTaskAdd(name, est)
}

func runTaskDep(cmd *cobra.Command, args []string) {
  dbTaskDep(args[0], args[1:])
}

func runTaskEta(cmd *cobra.Command, args []string) {
  dbTaskEta(args[0], args[1])
}

func runTaskUndep(cmd *cobra.Command, args []string) {
  if len(args) > 1 {
    dbTaskUndep(args[0], args[1:])
  } else {
    dbTaskUndepAll(args[0])
  }
}

func runUser(cmd *cobra.Command, args []string) {
	name := args[0]
	if !dbUserFind(name) {
		if flgUserCreate == false {
			log.Fatalf("user %s not found\n", name)
		}
		dbUserCreate(name)
	}
	dbConfigSet(keyDefaultUser, name)
}
