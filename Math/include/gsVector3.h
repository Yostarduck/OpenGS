#pragma once

#include "gsMathConfig.h"

namespace opengs
{

class MATH_API Vector3
{
 public:
#pragma region CONSTRUCTORS

  Vector3();
  
  Vector3(const float x, const float y, const float z);

  Vector3(const Vector3& v);

  ~Vector3();

#pragma endregion

#pragma region OPERATORS

  Vector3
  operator+(const Vector3& v) const;

  Vector3
  operator-(const Vector3& v) const;

  Vector3
  operator*(const float s) const;

  Vector3
  operator/(const float s) const;

  Vector3&
  operator+=(const Vector3& v);

  Vector3&
  operator-=(const Vector3& v);

  Vector3&
  operator*=(const float s);

  Vector3&
  operator/=(const float s);

#pragma endregion

  float
  dot(const Vector3& v) const;

  Vector3
  cross(const Vector3& v) const;

  float
  length() const;
  
  Vector3
  normalized() const;

  Vector3&
  normalize();

 public:
  float x;
  float y;
  float z;
};

}