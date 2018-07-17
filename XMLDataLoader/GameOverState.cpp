#include "GameOverState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "MainMenuState.h"


const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
  for (size_t i = 0; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->update();
  }

  //Check and dequeue the state if it is invalid and ready to delete
  TheGame::Instance()->getStateMachine()->checkForStatesToRemove();
}

void GameOverState::render()
{
  for (size_t i = 0; i < m_gameObjects.size(); i++)
  { 
    m_gameObjects[i]->draw();
  }
}


bool GameOverState::onEnter()
{  
  StateParser stateParser;
  stateParser.parseState("///Users/Joshua/Documents/GameDev/Emacs/GamesFramework/XMLDataLoader/data/GameStateObjects.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_gameOverToMain);
  m_callbacks.push_back(s_restartPlay);

  setCallbacks(m_callbacks);

  
  std::cout << "GameOverState.cpp: entering PauseState\n";
  return true;
}

bool GameOverState::onExit()
{
  for (size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->clean();
  }

  m_gameObjects.clear();

  TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
  TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
  TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
  
  
  //reset mouse button clicks to false
  TheInputHandler::Instance()->reset();

  std::cout << "GameOverState.cpp: exiting PauseState\n";
  return true;
}

void GameOverState::s_gameOverToMain()
{
  TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
  TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}



void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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
