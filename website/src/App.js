import React, { Component } from 'react'
import Header from './Header.js'
import TaskTable from './TaskTable.js'
import UserTable from './UserTable.js'
import './App.css'

function listTasks() {
  return fetch("api/tasks").then(response => response.json())
}

function listUsers() {
  return fetch("api/users").then(response => response.json())
}


class App extends Component {
  constructor(props) {
    super(props)
    this.state = { tasks: [], users: [], pageType: 'tasks' }
    listTasks().then(tasks => {
      this.setState(state => {
        state.tasks = tasks
        return state
      })
    })
    listUsers().then(users => {
      this.setState(state => {
        state.users = users
        return state
      })
    })
  }

  handleClickHeader(pageType) {
    this.setState(state => {
      state.pageType = pageType
      return state
    })
  }

  render() {
    return (
      <div className="App">
        <Header onClickHeader={this.handleClickHeader.bind(this)}/>
        {this.state.pageType == 'tasks' && <TaskTable tasks={this.state.tasks}/>}
        {this.state.pageType == 'users' && <UserTable users={this.state.users}/>}
        <pre>
        {
          JSON.stringify(this.state.tasks)
        }
        </pre>
      </div>
    )
  }

}

export default App

