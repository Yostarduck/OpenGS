#include "gsTriangle.h"

namespace opengs
{

#pragma region CONSTRUCTORS

Triangle::Triangle()
  : m_v1(nullptr), m_v2(nullptr), m_v3(nullptr) {
}

Triangle::Triangle(const Vertex* v1, const Vertex* v2, const Vertex* v3)
  : m_v1(v1), m_v2(v2), m_v3(v3) {
}

Triangle::Triangle(const Triangle& t)
  : m_v1(t.m_v1), m_v2(t.m_v2), m_v3(t.m_v3) {
}

Triangle::~Triangle() {
}

#pragma endregion

const Vertex*
Triangle::getVertex1() {
  return m_v1;
}

const Vertex*
Triangle::getVertex2() {
  return m_v2;
}

const Vertex*
Triangle::getVertex3() {
  return m_v3;
}

Vector3
Triangle::getNormal() const {
  Vector3 v1 = Vector3(m_v2->x - m_v1->x, m_v2->y - m_v1->y, m_v2->z - m_v1->z);
  Vector3 v2 = Vector3(m_v3->x - m_v1->x, m_v3->y - m_v1->y, m_v3->z - m_v1->z);

  return v1.cross(v2).normalize();
}

}