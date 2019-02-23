export const taskList = () => dispatch => {
  fetch("api/tasks")
    .then(response => response.json())
    .then(tasks => dispatch({ type: 'TASK_LIST', payload: tasks }))
}
