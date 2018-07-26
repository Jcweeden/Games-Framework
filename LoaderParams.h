#ifndef _LoaderParams_
#define _LoaderParams_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>

/**
  LoaderParams contains all the parameter values for a GameObject. Holding
  all values inside a single class is easier to manage and adjust when put
  to use in different projects, as different objects will require different 
  parameters. 

  I'm not sure I like this approach.
**/
class LoaderParams
{
public:
LoaderParams(int x, int y, int width, int height, std::string textureID) 
: m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
{

} 

  int getX() const {return m_x; }
  int getY() const {return m_y; }
  int getWidth() const {return m_width;}
  int getHeight() const {return m_height;}
  std::string getTextureID() const{return m_textureID;}

  
private:
  //all values are member of the GameObject class

  int m_x;
  int m_y;

  int m_width;
  int m_height;
      
  std::string m_textureID;
};

#endif
