#include "Enemy.h"

Enemy::Enemy() :
    GameObject()
{
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

void Enemy::load(const LoaderParams *pParams)
{
  GameObject::load(pParams);
  m_velocity.setX(2);
}
