import { createStore, applyMiddleware } from 'redux'
import thunk from 'redux-thunk'
import rootReducer from './reducers/rootReducer'

export default function configureStore() {
  let initialState = {
    result: {}
  }
  return createStore(
    rootReducer,
    initialState,
    applyMiddleware(thunk)
  )
}

