#include "gsVector3.h"

#include "gsMath.h"

namespace opengs
{

Vector3::Vector3()
  : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(const float x, const float y, const float z)
  : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3& v)
  : x(v.x), y(v.y), z(v.z)
{
}

Vector3::~Vector3()
{
}

#pragma region OPERATORS

Vector3
Vector3::operator+(const Vector3& v) const {
  return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3
Vector3::operator-(const Vector3& v) const {
  return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3
Vector3::operator*(const float s) const {
  return Vector3(x * s, y * s, z * s);
}

Vector3
Vector3::operator/(const float s) const {
  return Vector3(x / s, y / s, z / s);
}

Vector3&
Vector3::operator+=(const Vector3& v) {
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}

Vector3&
Vector3::operator-=(const Vector3& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return *this;
}

Vector3&
Vector3::operator*=(const float s) {
  x *= s;
  y *= s;
  z *= s;

  return *this;
}

Vector3&
Vector3::operator/=(const float s) {
  x /= s;
  y /= s;
  z /= s;

  return *this;
}

#pragma endregion

float
Vector3::dot(const Vector3& v) const {
  return (x * v.x) + (y * v.y) + (z * v.z);
}

Vector3
Vector3::cross(const Vector3& v) const {
  return Vector3((y * v.z) - (z * v.y),
                 (z * v.x) - (x * v.z),
                 (x * v.y) - (y * v.x));
}

float
Vector3::length() const {
  return Math::sqrt((x * x) + (y * y) + (z * z));
}

Vector3
Vector3::normalized() const {
  float l = length();
  
  return Math::almostEqual(l, 0.0f) ?
    Vector3(0.0f, 0.0f, 0.0f) :
    Vector3(x / l, y / l, z / l);
}

Vector3&
Vector3::normalize() {
  float l = length();

  if (Math::almostEqual(l, 0.0f)) {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }
  else {
    x /= l;
    y /= l;
    z /= l;
  }

  return *this;
}

#pragma region CONSTANTS

const Vector3 Vector3::Zero     = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One      = Vector3(1.0f, 1.0f, 1.0f);

const Vector3 Vector3::Up       = Vector3( 0.0f,  1.0f,  0.0f);
const Vector3 Vector3::Down     = Vector3( 0.0f, -1.0f,  0.0f);
const Vector3 Vector3::Left     = Vector3(-1.0f,  0.0f,  0.0f);
const Vector3 Vector3::Right    = Vector3( 1.0f,  0.0f,  0.0f);
const Vector3 Vector3::Forward  = Vector3( 0.0f,  0.0f,  1.0f);
const Vector3 Vector3::Backward = Vector3( 0.0f,  0.0f, -1.0f);

#pragma endregion

}