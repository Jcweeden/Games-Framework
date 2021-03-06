#ifndef _Vector2D_
#define _Vector2D_

#include <iostream>
#include <math.h>



class Vector2D
{
public:

Vector2D(float x, float y): m_x(x), m_y(y) {}

Vector2D() : m_x(0), m_y(0)
  {}

  float getX() {return m_x;}
  float getY() {return m_y;}

  void setX(float x) {m_x = x;}
  void setY(float y) {m_y = y;}  
  
  //returns length of the vector
  float length() {return sqrt(m_x * m_x + m_y * m_y); }

 //addition of vectors
  Vector2D operator+(const Vector2D& v2) const
  {
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
  }

  friend Vector2D& operator+=(Vector2D& v1, const Vector2D v2)
  {
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;

    return v1;
  }
  
  //subtraction of vectors
  Vector2D operator-(const Vector2D& v2) {
    return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
  }

  friend Vector2D& operator-=(Vector2D v1, const Vector2D v2) {

    v1.m_x -= v2.m_x;
    v1.m_y -= v2.m_y;
    
    return v1;
  }
  
  //multiplication of vectors
  Vector2D operator*(float scalar) {
    return Vector2D(m_x * scalar, m_y * scalar);
  }

  Vector2D& operator*=(float scalar) {
    m_x *= scalar;
    m_y *= scalar;

    return *this;
  }

  //division of vectors

  Vector2D operator/(float scalar) {
    return Vector2D(m_x/scalar, m_y/scalar);
  }

  Vector2D& operator/=(float scalar) {
    m_x /= scalar;
    m_y /= scalar;

    return *this;
  }

  //normalise

  void normalise()
  {
    float l = length();
    if (l > 0) {
      (*this) *= 1 / l;
    }
  }
  
private:

  float m_x;
  float m_y;


};

#endif
