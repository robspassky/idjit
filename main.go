// Copyright © 2019 Rob Cabacungan <robspassky@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package main

import (
	"fmt"
	"log"
	"os"

	homedir "github.com/mitchellh/go-homedir"
	"github.com/spf13/cobra"
	"github.com/spf13/viper"
)

func main() {
	log.Print("aab")
	if err := cmdRoot.Execute(); err != nil {
		log.Fatal(err)
	}
}

func abort(msg string, err error) {
  log.Fatal("%s - %s", msg, err)
}

var cmdRoot = &cobra.Command{
	Use:   "idjit",
	Short: "a stupid dependency tracker",
	Long: `idjit is a stupid dependency tracker. It is a fast, decentralized
version of JIRA. It allows users to make local updates to their
task statuses and then push their updates to a central location.`,
	//  Run: func(cmd *cobra.Command, args []string) { },
}

var cfgFile string

func init() {
	cobra.OnInitialize(initConfig)
	cmdRoot.PersistentFlags().StringVar(&cfgFile, "config", "", "config file (default is $HOME/.idjit)")
}

func initConfig() {
	if cfgFile != "" {
		viper.SetConfigFile(cfgFile)
	} else {
		home, err := homedir.Dir()
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		viper.AddConfigPath(home)
		viper.SetConfigName(".idjit")
	}
	viper.AutomaticEnv()
	if err := viper.ReadInConfig(); err == nil {
		fmt.Println("Using config file:", viper.ConfigFileUsed())
	}
}
