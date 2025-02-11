#pragma once

#include "gsGraphicsConfig.h"
#include "gsVertex.h"

namespace opengs
{

class GRAPHICS_API Triangle
{
 public:
#pragma region CONSTRUCTORS

  Triangle();

  Triangle(const Vertex* v1, const Vertex* v2, const Vertex* v3);

  Triangle(const Triangle& t);

  ~Triangle();

#pragma endregion

  const Vertex*
  getVertex1();

  const Vertex*
  getVertex2();

  const Vertex*
  getVertex3();
  
  Vector3
  getNormal() const;

 protected:
  const Vertex* m_v1;
  const Vertex* m_v2;
  const Vertex* m_v3;
};

}