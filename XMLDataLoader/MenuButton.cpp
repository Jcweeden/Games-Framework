#include "MenuButton.h"


MenuButton::MenuButton()
    : GameObject()
{
  //defaultly begin at frame 0 of spritesheet, button will be drawn normally
  m_currentFrame = MOUSE_OUT;
}

void MenuButton::load(const LoaderParams *pParams)
{
  GameObject::load(pParams);

  //specifically set the callback function (this is not included in load() as is not standard)
  m_callbackID = pParams->getCallBackID();

  //defaultly begin at frame 0 of spritesheet, button will be drawn normally
  m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
  //base class draw method
  GameObject::draw(); 
}

void MenuButton::update()
{
  //get current mouse position
  Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

  //if mouse is on top of button
  if (pMousePos->getX() < (m_position.getX() + m_width) //less than right hand side of button (position + button width)
      && pMousePos->getX() > m_position.getX()
      && pMousePos->getY() < (m_position.getY() + m_height)
      && pMousePos->getY() > m_position.getY())
  {
    //if button is pressed
    if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
    {
      //update the texture to be drawn for the button to represent it is being clicked
      m_currentFrame = CLICKED;
      //call the specified function for when the button is pressed
      m_callback(); //call function

      m_bReleased = false;
    }
    //else if button is not pressed
    else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
    {
      //mouse is hovering over button
      m_bReleased = true;
      //update the texture to be drawn for the button to represent it is being HOVERED over
      m_currentFrame = MOUSE_OVER;
    }
  }
  else
  {
    //m_bReleased = true;
    m_currentFrame = MOUSE_OUT;
  }
}


void MenuButton::clean()
{
  GameObject::clean();
}
