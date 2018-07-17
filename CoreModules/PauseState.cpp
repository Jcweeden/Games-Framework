#include "PauseState.h"
#include "MenuState.h"
#include "MenuButton.h"



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
  //load resume button
  if (!TheTextureManager::Instance()->load("assets/resume.png", "resumeButton", TheGame::Instance()->getRenderer()))
  {
    return false;
  }

  //load main menu button
  if (!TheTextureManager::Instance()->load("assets/main.png", "mainButton", TheGame::Instance()->getRenderer()))
  {
    return false;
  }

  GameObject* button1 = new MenuButton(new LoaderParams(200,100,200,80,"mainButton"), s_pauseToMenu);
  GameObject* button2 = new MenuButton(new LoaderParams(200,300,200,80,"resumeButton"), s_resumePlay);

  m_gameObjects.push_back(button1);
  m_gameObjects.push_back(button2);

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
  TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}
