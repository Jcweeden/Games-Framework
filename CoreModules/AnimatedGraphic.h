#ifndef _AnimatedGraphic_
#define _AnimatedGraphic_

#include "GameObject.h"
#include "SDL2/SDL.h"

class AnimatedGraphic : public GameObject {

public:

AnimatedGraphic(const LoaderParams* pParams, int animSpeed, int frameNum)
    :GameObject(pParams), m_animSpeed(animSpeed), m_numFrames(frameNum)
  {}

  void Update()
  {
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
  }

private:
  int m_animSpeed;
  int m_numFrames;
  
};

#endif
