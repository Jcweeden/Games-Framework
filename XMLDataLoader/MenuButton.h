#ifndef _MenuButton_
#define _MenuButton_

#include "GameObject.h"
#include "GameObjectFactory.h"

class MenuButton: public GameObject {
public:

  MenuButton();

  virtual void draw();
  virtual void update();
  virtual void clean();

  virtual void load(const LoaderParams *pParams);

  //set the function that will be called upon clicking the button
  void setCallback(void(*callback)()) { m_callback = callback; }

  //each function is assigned a number in the XML file that references the method it will when call clicked
  //these values are stored in m_callbacks in MenuState.h
  int getCallbackID() { return m_callbackID; }

private:

  enum  button_state
  {
    //used within TextureManager to multiple the width/height of the image being drawn so
    //different images from the spritesheet are used to represent different button states
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
  };


  //function pointer - holds the function that will be called upon clicking the button
  void (*m_callback) ();

  //false if the mouse is clicked on top of the button
  //prevent multiple calls to the button
  bool m_bReleased;

};

//Creator implementation that allows for creation of objects in the GameObjectFactory
class MenuButtonCreator : public BaseCreator
{
  GameObject* CreateGameObject() const
  {
    return new MenuButton();
  }
};

#endif
