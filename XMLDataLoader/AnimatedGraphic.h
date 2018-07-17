#ifndef _AnimatedGraphic_
#define _AnimatedGraphic_

#include "GameObject.h"
#include "SDL2/SDL.h"
#include "GameObjectFactory.h"


class AnimatedGraphic : public GameObject {

public:

AnimatedGraphic(/*const LoaderParams* pParams, int animSpeed, int frameNum*/)
    :GameObject(), m_animSpeed(2), m_numFrames(2)
  {}

  void Update()
  {
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
  }

  void load(const LoaderParams *pParams)
  {
    GameObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
  }
  
private:
  int m_animSpeed;
  int m_numFrames;
  
};

//Creator implementation that allows for creation of objects in the GameObjectFactory
class AnimatedGraphicCreator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new AnimatedGraphic();
  }
};

#endif
