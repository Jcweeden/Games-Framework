#include "PauseState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "MainMenuState.h"



const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
  for (size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->update();
  }

  //Check and dequeue the state if it is invalid and ready to delete
  TheGame::Instance()->getStateMachine()->checkForStatesToRemove();
}

void PauseState::render()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw();
  }
}

bool PauseState::onEnter()
{

  StateParser stateParser;
  stateParser.parseState("///Users/Joshua/Documents/GameDev/Emacs/GamesFramework/XMLDataLoader/data/GameStateObjects.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_pauseToMenu);
  m_callbacks.push_back(s_resumePlay);
      
  setCallbacks(m_callbacks);
  
  
  std::cout << "PauseState.cpp: entering PauseState\n";
  return true;
}


bool PauseState::onExit()
{
  for (size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->clean();
  }

  m_gameObjects.clear();

  TheTextureManager::Instance()->clearFromTextureMap("resumeButton");
  TheTextureManager::Instance()->clearFromTextureMap("mainButton");

  //reset mouse button clicks to false
  TheInputHandler::Instance()->reset();

  std::cout << "PauseState.cpp: exiting PauseState\n";
  return true;
}

void PauseState::s_resumePlay()
{
  TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::s_pauseToMenu()
{
  TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
  for (size_t i = 0 ; i < m_gameObjects.size(); i++)
  {
    if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
    {
      MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
      pButton->setCallback(callbacks[pButton->getCallbackID()]);
    }
  }
}
