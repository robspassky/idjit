import React, { Component } from 'react'
import Header from './Header.js'
import TaskTable from './TaskTable.js'
import './App.css'

function listTasks() {
  return fetch("api/tasks").then(response => response.json())
}

class App extends Component {
  constructor(props) {
    super(props)
    this.state = { tasks: [] }
    listTasks().then(tasks => {
      this.setState(state => {
        return { tasks }
      })
    })
  }

  render() {
    return (
      <div className="App">
        <Header/>
        <TaskTable tasks={this.state.tasks}/>
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

