#include "GameStateMachine.h"
#include "InputHandler.h"

//add a state without removing the previous state
//calls the onEnter() function of the newly added state
void GameStateMachine::pushState(GameState* pState)
{
  m_gameStates.push_back(pState);
  m_gameStates.back()->onEnter();
}


void GameStateMachine::popState()
{
  if(!m_gameStates.empty())//if a state on the stack
  {
    if(m_gameStates.back()->onExit()) //call onExit() for the state
    {
      delete m_gameStates.back(); //and delete it
      m_gameStates.pop_back();
    }
  }
}

//checks if there are any other states in the array
//if there are, check that they are not the same as the current state
//if different, remove the current state, add our new pState, and call onEnter()
void GameStateMachine::changeState(GameState *pState)
{
  if (!m_gameStates.empty())
  {
    if (m_gameStates.back()->getStateID() == pState->getStateID())
    {
      return; //states are the same - do nothing
    }

    if (!m_gameStates.back()->getToBeDeleted())
    {
      m_gameStates.back()->setToBeDeleted(true); //mark state as invalid and ready to delete
    }
  }

  //push back our new state
  m_gameStates.push_back(pState);

  //init state
  m_gameStates.back()->onEnter();
}


void GameStateMachine::update()
{
  if (!m_gameStates.empty())
  {
    m_gameStates.back()->update();
  }
}

void GameStateMachine::render()
{
  if (!m_gameStates.empty())
  {
    m_gameStates.back()->render();
  }
}

void GameStateMachine::checkForStatesToRemove(){
    if(!m_gameStates.empty()){
        //if the current state has been marked for deletion
        if(m_gameStates[0]->getToBeDeleted() && m_gameStates[0]->onExit()){
            //delete and dequeue the state
            delete m_gameStates[0];
            m_gameStates.erase(m_gameStates.begin());

            //and reset the current input to prevent button presses being held over from one state to the next
            TheInputHandler::Instance()->reset();
        }
    }
}
