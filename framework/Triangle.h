#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

#include "shape.h"
#include <glm\glm.hpp>
#include <memory>
#include "material.h"
#include "renderer.hpp"
#include "plane.h"

#include <array>

class Triangle : public Shape
{
public:
  Triangle(std::shared_ptr<Material> const& material,
    std::array<glm::vec3, 3> const& vertices);
  Triangle(std::shared_ptr<Material> const& material,
    std::array<glm::vec3, 3> const& vertices,
    std::array<glm::vec3, 3> const& normals);
 double intersect(Ray const& ray) const;
  std::ostream& print(std::ostream& os) const override;
private:
  void init();
  std::array<glm::vec3, 3> vertices_;
  glm::vec3 u_, v_, n_;
  float uv_, uu_, vv_, denom_, denom_inv_;
};

#endif // BUW_TRIANGLE_HPP