#include "GameOverState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"

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
  //LOAD IMAGES
  if(!TheRenderManager::Instance()->load("assets/gameover.png", "gameovertext", TheGame::Instance()->getRenderer()))
  {
    return false;
  }
  if (!TheRenderManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer()))
  {
    return false;
  }
  if (!TheRenderManager::Instance()->load("assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer()))
  {
    return false;
  }

  //CREATE GAMEOBJECTS
  GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200,100,190,30,"gameovertext"),2,2);
  GameObject* button1 = new MenuButton(new LoaderParams(200,200,200,80,"mainbutton"), s_gameOverToMain);
  GameObject* button2 = new MenuButton(new LoaderParams(200,300,200,80,"restartbutton"), s_restartPlay);

  //ADD TO VECTOR
  m_gameObjects.push_back(gameOverText);
  m_gameObjects.push_back(button1);
  m_gameObjects.push_back(button2);

  
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

  TheRenderManager::Instance()->clearFromTextureMap("resumebutton");
  TheRenderManager::Instance()->clearFromTextureMap("mainbutton");
  TheRenderManager::Instance()->clearFromTextureMap("gameovertext");
  
  
  //reset mouse button clicks to false
  TheInputHandler::Instance()->reset();

  std::cout << "GameOverState.cpp: exiting PauseState\n";
  return true;
}

void GameOverState::s_gameOverToMain()
{
  TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
  TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}


