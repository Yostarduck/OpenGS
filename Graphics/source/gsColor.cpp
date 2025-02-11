#include "gsColor.h"

namespace opengs
{

#pragma region CONSTRUCTORS

Color::Color()
  : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {
}

Color::Color(const float r, const float g, const float b)
  : r(r), g(g), b(b), a(1.0f) {
}

Color::Color(const float r, const float g, const float b, const float a)
  : r(r), g(g), b(b), a(a) {
}

Color::Color(const Color& v)
  : r(v.r), g(v.g), b(v.b), a(v.a) {
}

Color::~Color() {
}

#pragma endregion

#pragma region OPERATORS

Color&
Color::operator=(const Color& v) {
  this->r = v.r;
  this->g = v.g;
  this->b = v.b;
  this->a = v.a;

  return *this;
}

Color
Color::operator+(const Color& v) const {
  return Color(this->r + v.r,
               this->g + v.g,
               this->b + v.b,
               this->a + v.a);
}

Color
Color::operator-(const Color& v) const {
  return Color(this->r - v.r,
               this->g - v.g,
               this->b - v.b,
               this->a - v.a);
}

Color
Color::operator*(const Color& v) const {
  return Color(this->r * v.r,
               this->g * v.g,
               this->b * v.b,
               this->a * v.a);
}

Color
Color::operator/(const Color& v) const {
  return Color(this->r / v.r,
               this->g / v.g,
               this->b / v.b,
               this->a / v.a);
}

Color
Color::operator*(const float s) const {
  return Color(this->r * s,
               this->g * s,
               this->b * s,
               this->a * s);
}

Color
Color::operator/(const float s) const {
  return Color(this->r / s,
               this->g / s,
               this->b / s,
               this->a / s);
}

Color&
Color::operator+=(const Color& v) {
  this->r += v.r;
  this->g += v.g;
  this->b += v.b;
  this->a += v.a;

  return *this;
}

Color&
Color::operator-=(const Color& v) {
  this->r -= v.r;
  this->g -= v.g;
  this->b -= v.b;
  this->a -= v.a;

  return *this;
}

Color&
Color::operator*=(const Color& v) {
  this->r *= v.r;
  this->g *= v.g;
  this->b *= v.b;
  this->a *= v.a;

  return *this;
}

Color&
Color::operator/=(const Color& v) {
  this->r /= v.r;
  this->g /= v.g;
  this->b /= v.b;
  this->a /= v.a;

  return *this;
}

Color&
Color::operator*=(const float s) {
  this->r *= s;
  this->g *= s;
  this->b *= s;
  this->a *= s;

  return *this;
}

Color&
Color::operator/=(const float s) {
  this->r /= s;
  this->g /= s;
  this->b /= s;
  this->a /= s;

  return *this;
}

bool
Color::operator==(const Color& v) const {
  return (this->r == v.r &&
          this->g == v.g &&
          this->b == v.b &&
          this->a == v.a);
}

bool
Color::operator!=(const Color& v) const {
  return (this->r != v.r ||
          this->g != v.g ||
          this->b != v.b ||
          this->a != v.a);
}

float&
Color::operator[](const int i) {
  return (&r)[i];
}

const float&
Color::operator[](const int i) const {
  return (&r)[i];
}

#pragma endregion

#pragma region CONSTANTS

const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);

const Color Color::RED    = Color(1.0f, 0.0f, 0.0f);
const Color Color::GREEN  = Color(0.0f, 1.0f, 0.0f);
const Color Color::BLUE   = Color(0.0f, 0.0f, 1.0f);

const Color Color::CYAN     = Color(0.0f, 1.0f, 1.0f);
const Color Color::MAGENTA  = Color(1.0f, 0.0f, 1.0f);
const Color Color::YELLOW   = Color(1.0f, 1.0f, 0.0f);

const Color Color::ORANGE     = Color(1.0f,   0.5f,   0.0f);
const Color Color::PURPLE     = Color(0.5f,   0.0f,   1.0f);
const Color Color::PINK       = Color(1.0f,   0.0f,   0.5f);
const Color Color::BROWN      = Color(0.5f,   0.25f,  0.0f);
const Color Color::GRAY       = Color(0.5f,   0.5f,   0.5f);
const Color Color::LIGHT_GRAY = Color(0.75f,  0.75f,  0.75f);

const Color Color::CLEAR = Color(0.0f, 0.0f, 0.0f, 0.0f);

#pragma endregion

}