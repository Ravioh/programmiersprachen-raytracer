#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.h"
#include "ray.h"
#include <glm/glm.hpp>

class Shape {
public:
	Shape();

	virtual std::string getName() { return " "; };
	virtual double intersect(Ray ray) { return 0.0; }
	virtual Material getMaterial() const { return Material();  }
	virtual glm::vec3 getNormalAt(glm::vec3 point) const { return glm::vec3(); }

	void translate(glm::vec3 const& t);
	void scale(glm::vec3 const& s);
	void rotate(float deg, glm::vec3 const& axis);



/*protected:
  glm::vec3 world_normal(glm::vec3 const& n) const;

  Ray object_ray(Ray const& r) const;


  /*
  //Transforms go here
  glm::mat4 world_transform_;
  glm::mat4 world_transform_inv_;


  glm::mat3 world_transform_T_;
  glm::mat3 world_transform_inv_T_;
  */
};





#endif