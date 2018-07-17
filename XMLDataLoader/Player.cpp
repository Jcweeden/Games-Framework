#include "Player.h"

Player::Player() :
    GameObject()
{
  
}

void Player::draw()
{
  GameObject::draw();
}

void Player::update()
{
  m_velocity.setX(0);
  m_velocity.setY(0);

  handleInput();

  m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
  
  GameObject::update();
}

void Player::clean(){}

void Player::handleInput()
{
  //CONTROLLER INPUT
  if(TheInputHandler::Instance()->joysticksInitialised())
  {
    //JOYSTICKINPUT
    if (TheInputHandler::Instance()->xValue(0,1) > 0 ||
        TheInputHandler::Instance()->xValue(0,1) < 0)
    {
      m_velocity.setX(1 * TheInputHandler::Instance()->xValue(0,1));
    }

    if (TheInputHandler::Instance()->yValue(0,1) > 0 ||
        TheInputHandler::Instance()->yValue(0,1) < 0)
    {
      m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,1));
    }

    if (TheInputHandler::Instance()->xValue(0,2) > 0 ||
        TheInputHandler::Instance()->xValue(0,2) < 0)
    {
      m_velocity.setX(1 * TheInputHandler::Instance()->xValue(0,2));
    }

    if (TheInputHandler::Instance()->yValue(0,2) > 0 ||
        TheInputHandler::Instance()->yValue(0,2) < 0)
    {
      m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,2));
    }

    //BUTTON INPUT
    //Y BUTTON
    if(TheInputHandler::Instance()->getButtonState(0,3))
    {
      m_velocity.setX(1);
    }
  }
  
  //MOUSE INPUT
  /*if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
  {
    //std::cout << "Player: mouse left button pressed\n";
    m_velocity.setX(1);
  }
  */
  
  //MOUSE POSITION
  Vector2D* mousePos = TheInputHandler::Instance()->getMousePosition();

  m_velocity = (*mousePos - m_position) /50;


  //KEYBOARD INPUT
  /*if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    m_velocity.setX(2);
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    m_velocity.setX(-2);
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
  {
    m_velocity.setY(-2);
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
  {
    m_velocity.setY(2);
  }
  */
}

void Player::load(const LoaderParams *pParams) {
  GameObject::load(pParams);
}
