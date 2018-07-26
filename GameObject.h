#ifndef _GameObject_
#define _GameObject_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Game.h"
#include "LoaderParams.h"
#include <string>

class GameObject {

public:
  GameObject(const LoaderParams* pParams);

  virtual void draw();
  virtual void update();
  
  virtual void clean();

  Vector2D& getPosition() { return m_position; }
  int getWidth() { return m_width; }
  int getHeight() { return m_height; }
  
protected:
  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;
  
  int m_width;
  int m_height;

  //if the gameObj has an animated sprite, these integers indicate the index of the current sprite in the sprite sheet
  int m_currentRow;
  int m_currentFrame;

  //stringID that will return the texture associated with the gameObject in RenderManager
  std::string m_textureID;
};

#endif
