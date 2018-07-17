#ifndef _PlayState_
#define _PlayState_

#include "GameState.h"
#include <iostream>
#include <vector>
class GameObject;
class GameObject;


class PlayState : public GameState
{
public:
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const { return s_playID; };
  
private:
  static const std::string s_playID;

  std::vector <GameObject*> m_gameObjects;
};

#endif
