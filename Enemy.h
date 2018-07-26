#ifndef _Enemy_
#define _Enemy_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RenderManager.h"
#include "GameObject.h"
#include <iostream>


class Enemy : public GameObject
{
public:
  Enemy(const LoaderParams* pParams);
  
  void draw();
  void update();
  void clean();

};

#endif
