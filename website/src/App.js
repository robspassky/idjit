import React, { Component } from 'react'
import { connect } from 'react-redux'
import Header from './Header.js'
import TaskTable from './TaskTable.js'
import './App.css'

import { taskList } from './actions/taskList'

class App extends Component {
  componentDidMount() {
    this.props.taskList()
  }

  render() {
    return (
      <div className="App">
        <Header/>
        <TaskTable/>
        <pre>
        {
          JSON.stringify(this.props)
        }
        </pre>
      </div>
    )
  }

  taskListAction = (event) => {
    console.log('foo')
    this.props.taskList()
  }

}

const mapStateToProps = state => ({
  ...state
})

const mapDispatchToProps = dispatch => ({
  taskList: () => dispatch(taskList())
})

export default connect(mapStateToProps, mapDispatchToProps)(App)

