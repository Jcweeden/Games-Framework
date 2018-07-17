#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GameObject.h"
#include "CollisionManager.h"


const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){
  //if ESC is pressed pause the game
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
  {
    TheGame::Instance()->getStateMachine()->pushState(new PauseState());
  }
  
  for (size_t i = 0; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->update();
  }

 if (TheCollManager::Instance()->
      isCollidingRectRect(dynamic_cast<GameObject*>(m_gameObjects[0]), dynamic_cast<GameObject*>(m_gameObjects[1]), 100))  {
    TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
  }

  //Check and dequeue the state if it is invalid and ready to delete
  TheGame::Instance()->getStateMachine()->checkForStatesToRemove();
}

void PlayState::render(){
  for (size_t i = 0; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->draw();
  }
}

bool PlayState::onEnter(){


  //PLAYER
  TheTextureManager::Instance()->load("assets/character.png", "character", TheGame::Instance()->getRenderer());
  // x,y w, h
  GameObject* player = new Player(new LoaderParams(300, 100, 42, 55, "character"));

  m_gameObjects.push_back(player);


  //ENEMY
  TheTextureManager::Instance()->load("assets/enemy.png", "enemy", TheGame::Instance()->getRenderer());

  GameObject* enemy = new Enemy(new LoaderParams(100,100,42,55, "enemy"));

  m_gameObjects.push_back(enemy);
  
  std::cout << "PlayState.cpp: entering PlayState\n";
  return true;
}

bool PlayState::onExit(){
  for (size_t i; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->clean();
  }

  m_gameObjects.clear();

  TheTextureManager::Instance()->clearFromTextureMap("character");
  TheTextureManager::Instance()->clearFromTextureMap("enemy");
  
  std::cout << "PlayState.cpp: exiting PlayState\n";
  return true;
}
