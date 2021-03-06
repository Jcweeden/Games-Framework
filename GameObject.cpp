#include "GameObject.h"

GameObject::GameObject(const LoaderParams* pParams) :
    m_position(pParams->getX(), pParams->getY()), m_velocity(0,0), m_acceleration(0,0)
{
  m_width =  pParams->getWidth();
  m_height =  pParams->getHeight();

  m_textureID = pParams->getTextureID();

  //set to one as will be multipled by width/height
  m_currentRow = 1;
  m_currentFrame = 1;
}

void GameObject::draw() {

  //flips the texture as the character moves right/left
  if(m_velocity.getX() > 0) {
    RenderManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
  }
  else
  {
    RenderManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
  }
}

void GameObject::update(){
  //apply physics
  m_velocity += m_acceleration;
  m_position += m_velocity;
};

void GameObject::clean(){

};
