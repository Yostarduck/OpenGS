#pragma once

#include "gsGraphicsConfig.h"
#include "gsVector3.h"

namespace opengs
{

class GRAPHICS_API Vertex
{
 public:
#pragma region CONSTRUCTORS

  Vertex();
  
  Vertex(const float x, const float y, const float z, const float u, const float v);

  Vertex(const float x, const float y, const float z);

  Vertex(const Vertex& v);

  ~Vertex();

#pragma endregion

#pragma region OPERATORS

  Vertex&
  operator=(const Vertex& v);

  bool
  operator==(const Vertex& v) const;

  bool
  operator!=(const Vertex& v) const;

  Vertex
  operator+(const Vertex& v) const;

  Vertex
  operator-(const Vertex& v) const;

  Vertex
  operator*(const float s) const;

  Vertex
  operator/(const float s) const;

  Vertex&
  operator+=(const Vertex& v);

  Vertex&
  operator-=(const Vertex& v);

  Vertex&
  operator*=(const float s);

  Vertex&
  operator/=(const float s);

#pragma endregion
 
 public:
  union {
    struct {
      float x;
      float y;
      float z;
    };

    float position[3];
    
    Vector3 vector;
  };
  
  float u;
  float v;
};

}