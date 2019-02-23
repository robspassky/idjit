export default (state = {}, action) => {
  switch (action.type) {
    case 'TASK_LIST':
      return {
        result: action.payload
      }
    default:
      return state
  }
}

