#pragma once

#include "gsGraphicsConfig.h"
#include "gsVector3.h"

namespace opengs
{

class GRAPHICS_API Color
{
 public:
#pragma region CONSTRUCTORS

  Color();

  Color(const float r, const float g, const float b);

  Color(const float r, const float g, const float b, const float a);

  Color(const Color& v);

  ~Color();

#pragma endregion

#pragma region OPERATORS

  Color&
  operator=(const Color& v);

  Color
  operator+(const Color& v) const;

  Color
  operator-(const Color& v) const;

  Color
  operator*(const Color& v) const;

  Color
  operator/(const Color& v) const;

  Color
  operator*(const float s) const;

  Color
  operator/(const float s) const;

  Color&
  operator+=(const Color& v);

  Color&
  operator-=(const Color& v);

  Color&
  operator*=(const Color& v);

  Color&
  operator/=(const Color& v);

  Color&
  operator*=(const float s);

  Color&
  operator/=(const float s);

  bool
  operator==(const Color& v) const;

  bool
  operator!=(const Color& v) const;

  float&
  operator[](const int i);

  const float&
  operator[](const int i) const;

#pragma endregion
 
 public:
  union {
    struct {
      float r;
      float g;
      float b;
      float a;
    };

    float channels[4];
  };

  static const Color WHITE;
  static const Color BLACK;

  static const Color RED;
  static const Color GREEN;
  static const Color BLUE;

  static const Color YELLOW;
  static const Color CYAN;
  static const Color MAGENTA;

  static const Color ORANGE;
  static const Color PURPLE;
  static const Color PINK;
  static const Color BROWN;
  static const Color GRAY;
  static const Color LIGHT_GRAY;

  static const Color CLEAR;
};

}