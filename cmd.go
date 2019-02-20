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
		Run:   runTask,
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
)

var flgUserCreate bool

func init() {
	cmdRoot.AddCommand(cmdInit)
	cmdRoot.AddCommand(cmdTask)
	cmdRoot.AddCommand(cmdUser)
	cmdUser.Flags().BoolVarP(&flgUserCreate, "new", "n", false, "Create new user if it does not exist")
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

func runTask(cmd *cobra.Command, args []string) {
	if len(args) == 0 {
		tasks := dbTaskList()
		fmt.Printf("                 Id                                 Name\n")
		fmt.Printf("------------------------------------  ------------------------------\n")
		for _, t := range tasks {
			fmt.Printf("%s  %-30s\n", t.Id, t.Name)
		}
		return
	}
	name := args[0]
	dbTaskAdd(name)
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
