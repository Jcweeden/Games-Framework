#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"


const std::string MenuState::s_menuID = "MENU";

//update all objects in the state
void MenuState::update(){
  for (size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->update();
  }

  //Check and dequeue the state if it is invalid and ready to delete
  TheGame::Instance()->getStateMachine()->checkForStatesToRemove();
}

//render all objects in the state
void MenuState::render(){
  for (size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw();
  }
}

//load all objects in the state
bool MenuState::onEnter(){
  std::cout << "MenuState.cpp: entering Menu State\n";

  //load image
  if(!TheTextureManager::Instance()->load("assets/play.png", "playbutton", TheGame::Instance()->getRenderer()))
  {
    std::cout << "MenuState.cpp: failed to load image\n";
    return false;
  }

  if(!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
  {
    std::cout << "MenuState.cpp: failed to load image\n";
    return false;
  }

  GameObject* button1 = new MenuButton(new LoaderParams(200,100,200,100,"playbutton"), s_menuToPlay);
  GameObject* button2 = new MenuButton(new LoaderParams(200,300,200,100,"exitbutton"), s_exitFromMenu);

  m_gameObjects.push_back(button1);
  m_gameObjects.push_back(button2);   

  std::cout << "MenuState.cpp: entering MenuState\n";
  return true;
}

bool MenuState::onExit(){

  for(size_t i = 0; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->clean();
  }
  m_gameObjects.clear();

  TheTextureManager::Instance()->clearFromTextureMap("playbutton");
  TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
  
  std::cout << "MenuState.cpp: exiting Menu State\n";
  return true;
}

void MenuState::s_menuToPlay()
{
  std::cout << "Play button clicked\n";
  TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
  std::cout << "Exit button clicked\n";
  TheGame::Instance()->quit();
}
