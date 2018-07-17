#ifndef _PauseState_
#define _PauseState_

#include "GameState.h"
#include "MenuState.h"
#include <iostream>
#include <vector>
class GameObject;

class PauseState : public MenuState
{
public:

virtual void update();
virtual void render();

virtual bool onEnter();
virtual bool onExit();

virtual std::string getStateID() const { return s_pauseID;}

private:

virtual void setCallbacks(const std::vector<Callback>& callbacks);

static void s_pauseToMenu();
static void s_resumePlay();

static const std::string s_pauseID;

std::vector<GameObject*> m_gameObjects;
};

#endif
