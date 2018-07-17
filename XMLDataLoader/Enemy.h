#ifndef _Enemy_
#define _Enemy_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

#include <iostream>


class Enemy : public GameObject
{
public:
  Enemy(/*const LoaderParams* pParams*/);
  
  void draw();
  void update();
  void clean();

  void load(const LoaderParams *pParams);

};


//Creator implementation that allows for creation of objects in the GameObjectFactory
class EnemyCreator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new Enemy();
  }
};

#endif
