#ifndef _GameState_
#define _GameState_

#include <string>
#include <vector>

//template class for all gameStates to derive from
class GameState
{
public:

  GameState();
  
  virtual void update() = 0;
  virtual void render() = 0;

  //called when a state is created
  virtual bool onEnter() = 0;
  //called when a state is exited
  virtual bool onExit() = 0;

  //each state has an ID that is used to ensure that states of the same kind do not repeat on the stack 
  virtual std::string getStateID() const = 0;

  bool getToBeDeleted() const { return toBeDeleted; }
  void setToBeDeleted(bool isValid) { toBeDeleted = isValid; }

protected:
  //list of textures for the State, fill from XML upon onEnter(), and cleared on onExit()
  std::vector<std::string> m_textureIDList;

private:
  //true when state is called to be removed from stack and deleted in GameStateMachine checkForStatesToRemove()
  bool toBeDeleted;
};

#endif
