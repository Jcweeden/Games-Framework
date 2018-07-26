#ifndef _MenuButton_
#define _MenuButton_

#include "GameObject.h"

class MenuButton: public GameObject {
public:

  //loaderParams for GameObject, 
  //and callback contains the function to be called upon clicking the button 
  MenuButton(const LoaderParams* pParams, void (*callback)());

  virtual void draw();
  virtual void update();
  virtual void clean();

private:

  enum button_state
  {
    //used within RenderManager to multiple the width/height of the image being drawn so
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

#endif
