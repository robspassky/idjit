import React, { Component } from 'react'
import Table from '@material-ui/core/Table'
import TableBody from '@material-ui/core/TableBody'
import TableCell from '@material-ui/core/TableCell'
import TableHead from '@material-ui/core/TableHead'
import TableRow from '@material-ui/core/TableRow'
import './TaskTable.css'

class TaskTable extends Component {
  render() {
    return (
      <div>
        <Table className="TaskTable">
          <TableHead>
            <TableRow>
              <TableCell>Id</TableCell>
              <TableCell>Name</TableCell>
              <TableCell>Assignee</TableCell>
              <TableCell>Days Remaining</TableCell>
              <TableCell>Status</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {this.props.tasks.map(task => (
              <TableRow key={task.Id}>
                <TableCell>{task.Id}</TableCell>
                <TableCell>{task.Name}</TableCell>
                <TableCell>{task.Assignee}</TableCell>
                <TableCell>{task.Est}</TableCell>
                <TableCell>{task.Status}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </div>
    )
  }
}

export default TaskTable

