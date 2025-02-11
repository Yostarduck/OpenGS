#include "gsVertex.h"

namespace opengs
{

#pragma region CONSTRUCTORS

Vertex::Vertex()
  : x(0.0f), y(0.0f), z(0.0f), u(0.0f), v(0.0f) {
}

Vertex::Vertex(const float x, const float y, const float z, const float u, const float v)
  : x(x), y(y), z(z), u(u), v(v) {
}

Vertex::Vertex(const float x, const float y, const float z)
  : x(x), y(y), z(z), u(0.0f), v(0.0f) {
}

Vertex::Vertex(const Vertex& v)
  : x(v.x), y(v.y), z(v.z), u(v.u), v(v.v) {
}

Vertex::~Vertex() {
}

#pragma region OPERATORS

Vertex&
Vertex::operator=(const Vertex& v) {
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  this->u = v.u;
  this->v = v.v;

  return *this;
}

bool
Vertex::operator==(const Vertex& v) const {
  return (this->x == v.x && this->y == v.y && this->z == v.z && this->u == v.u && this->v == v.v);
}

bool
Vertex::operator!=(const Vertex& v) const {
  return (this->x != v.x || this->y != v.y || this->z != v.z || this->u != v.u || this->v != v.v);
}

Vertex
Vertex::operator+(const Vertex& v) const {
  return Vertex(this->x + v.x, this->y + v.y, this->z + v.z, this->u + v.u, this->v + v.v);
}

Vertex
Vertex::operator-(const Vertex& v) const {
  return Vertex(this->x - v.x, this->y - v.y, this->z - v.z, this->u - v.u, this->v - v.v);
}

Vertex
Vertex::operator*(const float s) const {
  return Vertex(this->x * s, this->y * s, this->z * s, this->u * s, this->v * s);
}

Vertex
Vertex::operator/(const float s) const {
  return Vertex(this->x / s, this->y / s, this->z / s, this->u / s, this->v / s);
}

Vertex&
Vertex::operator+=(const Vertex& v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
  this->u += v.u;
  this->v += v.v;

  return *this;
}

Vertex&
Vertex::operator-=(const Vertex& v) {
  this->x -= v.x;
  this->y -= v.y;
  this->z -= v.z;
  this->u -= v.u;
  this->v -= v.v;

  return *this;
}

Vertex&
Vertex::operator*=(const float s) {
  this->x *= s;
  this->y *= s;
  this->z *= s;
  this->u *= s;
  this->v *= s;

  return *this;
}

Vertex&
Vertex::operator/=(const float s) {
  this->x /= s;
  this->y /= s;
  this->z /= s;
  this->u /= s;
  this->v /= s;

  return *this;
}

#pragma endregion

}