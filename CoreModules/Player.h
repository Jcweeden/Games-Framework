#ifndef _Player_
#define _Player_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameObject.h"
#include "InputHandler.h"
#include <iostream>

class Player : public GameObject
{
public:
  Player(const LoaderParams* pParams);
  
  void draw();
  void update();
  void clean();

private:
  void handleInput();

};

#endif
