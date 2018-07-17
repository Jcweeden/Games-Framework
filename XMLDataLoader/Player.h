#ifndef _Player_
#define _Player_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

#include <iostream>

class Player : public GameObject
{
public:
  Player(/*const LoaderParams* pParams*/);
  
  void draw();
  void update();
  void clean();

  void load(const LoaderParams *pParams);


private:
  void handleInput();

};

//Creator implementation that allows for creation of objects in the GameObjectFactory
class PlayerCreator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new Player();
  }
};

#endif
