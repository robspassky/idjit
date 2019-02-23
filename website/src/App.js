import React, { Component } from 'react'
import Button from '@material-ui/Core/Button'
import { connect } from 'react-redux'
import logo from './logo.svg'
import Table from '@material-ui/core/Table'
import './App.css'

import { taskList } from './actions/taskList'

class App extends Component {
  componentDidMount() {
    this.props.taskList()
  }

  render() {
    return (
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <p>
            donot  edit <code>src/App.js</code> and save to reload.
          </p>
          <a
            className="App-link"
            href="https://reactjs.org"
            target="_blank"
            rel="noopener noreferrer"
          >
            Learn React
          </a>
        </header>
        <button onClick={this.taskListAction}>Test Action</button>
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

