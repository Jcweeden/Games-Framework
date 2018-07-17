#ifndef _MainMenuState_
#define _MainMenuState_

#include "MenuState.h"
#include "GameState.h"
#include "StateParser.h"
#include <iostream>
#include <vector>
#include "GameObject.h";

class MainMenuState: public MenuState{
public:
 virtual void update();
 virtual void render();

 virtual bool onEnter();
 virtual bool onExit();

 virtual std::string getStateID() const { return s_menuID; };

private:

 virtual void setCallbacks(const std::vector<Callback>& callbacks);
 
 //callback functions for menu items
 static void s_menuToPlay();
 static void s_exitFromMenu();
 
 static const std::string s_menuID;
 
 std::vector<GameObject*> m_gameObjects;

};

#endif
