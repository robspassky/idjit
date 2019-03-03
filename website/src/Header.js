import React, { Component } from 'react'
import './Header.css'

class Header extends Component {
  onClickTasks = () => this.props.onClickHeader('tasks')

  onClickUsers = () => this.props.onClickHeader('users')

  render() {
    return (
      <header className="Header">
        <a href="#" onClick={this.onClickTasks}>Tasks</a>
        ||
        <a href="#" onClick={this.onClickUsers}>Users</a>
      </header>
    )
  }
}

export default Header

