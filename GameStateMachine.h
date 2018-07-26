#ifndef _GameStateMachine_
#define _GameStateMachine_

#include "GameState.h"
#include <iostream>
#include <vector>

class GameStateMachine
{
public:
  //adds a new state to the stack and calls its onEnter method
  void pushState(GameState* pState);

  //sets the current state to be deleted and calls onEnter for the new state
  void changeState(GameState* pState);

  //removes the current state from the stack by calling its onExit method
  void popState();

  //calls update for the current state
  void update();

  //calls render for the current state
  void render();

  //called every frame by the currently active state
  //checks if the current state has been marked for deletion, and call onExit and deletes if so
  void checkForStatesToRemove();
  
private:
  //stack containing all gamestates, with the active state being the state on top of the stack
  std::vector<GameState*> m_gameStates;
};

#endif
