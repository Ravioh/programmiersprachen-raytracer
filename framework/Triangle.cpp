#include "Triangle.h"
#include <memory>
#include "material.h"
#include <array>
#include <glm\glm.hpp>

Triangle::Triangle(std::shared_ptr<Material> const& material, std::array<glm::vec3, 3> const& vertices)
: Shape(material)
, vertices_(vertices)
, u_(vertices[1] - vertices[0])
, v_(vertices[2] - vertices[0])
, n_()
, denom_()
, denom_inv_()
, uu_()
, uv_()
, vv_()
{
  n_ = glm::cross(u_, v_);
  glm::normalize(n_);
  init();
}


Triangle::Triangle(std::shared_ptr<Material> const& material,
  std::array<glm::vec3, 3> const& vertices,
  std::array<glm::vec3, 3> const& normals)
: Shape(material)
, vertices_(vertices)
, u_(vertices[1] - vertices[0])
, v_(vertices[2] - vertices[0])
, n_()
, denom_()
, denom_inv_()
, uu_()
, uv_()
, vv_()
{
  n_ += normals[0];
  n_ += normals[1];
  n_ += normals[2];
  n_ /= 3.0f;

  if (glm::dot(n_, n_) == 0) {
    n_ = glm::cross(u_, v_);
  } else {
    n_ = glm::normalize(n_);
  }
  init();
}

void
Triangle::init()
{
  uv_ = glm::dot(u_,v_);
  uu_ = glm::dot(u_,u_);
  vv_ = glm::dot(v_,v_);
  denom_ = uv_*uv_ - uu_*vv_;
  denom_inv_ = 1.0f / denom_;
}



std::ostream&
Triangle::print(std::ostream& os) const
{
  os << "triangle";
  return os;
}
