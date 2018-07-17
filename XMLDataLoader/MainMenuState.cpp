#include "MainMenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter()
{
  //parse the state
  StateParser stateParser;
  stateParser.parseState("///Users/Joshua/Documents/GameDev/Emacs/GamesFramework/XMLDataLoader/data/GameStateObjects.xml", s_menuID, &m_gameObjects, &m_textureIDList);

  m_callbacks.push_back(0); //pushback 0, callbackID starts from 1
  m_callbacks.push_back(s_menuToPlay);
  m_callbacks.push_back(s_exitFromMenu);

  //set callbacks for menu items
  setCallbacks(m_callbacks);

  return true;
}

bool MainMenuState::onExit()
{
  // clear the texture manager
  for (int i = 0; i < m_textureIDList.size(); i++)
  {
    TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
  }
  return true;
}


void MainMenuState::setCallbacks(const std::vector<Callback>&callbacks)
{
  //iterate through GO's
  for (int i = 0; i < m_gameObjects.size(); i++)
  {
    //if they are of type MenuButton then assign the button its callback function based on the ID passed in from file
    if(dynamic_cast<MenuButton*>(m_gameObjects[i])) //if gameobject is of type MenuButton
    {
      MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]); //then cast to MenuButton
      pButton->setCallback(callbacks[pButton->getCallbackID()]); //use obj's callbackID as index into callbacks vector and assign the correct function
    }
  }
}

void MainMenuState::update()
{
  for(int i = 0; i < m_gameObjects.size(); i++)
  {
    if(m_gameObjects[i] != 0)
    {
      m_gameObjects[i]->update();
    }
  }
  
  // std::cout << "MainMenuState.update(): m_gameObjects.size(): " << m_gameObjects.size() << "\n";
  //  MenuState::update();
}

void MainMenuState::render()
{
  for(int i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw();
  }
  
  //std::cout << "MainMenuState.render(): m_gameObjects.size(): " << m_gameObjects.size() << "\n";
  // MenuState::render();
}

void MainMenuState::s_menuToPlay(){
  TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu(){
  TheGame::Instance()->quit();
}
