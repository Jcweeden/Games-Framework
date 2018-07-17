#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) :
    GameObject(pParams)
{
  m_velocity.setX(2);
  m_velocity.setY(0.001);
}

void Enemy::draw()
{
  GameObject::draw();
}

void Enemy::update()
{
  m_currentFrame = int(((SDL_GetTicks() /100) % 4));

  if(m_position.getX() < 100)
  {
    m_velocity.setX(2);
  }
  else if (m_position.getX() > 400)
  {
    m_velocity.setX(-2);
  }

  GameObject::update();
}

void Enemy::clean(){}
