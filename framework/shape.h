#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.h"
#include "ray.h"
#include <memory>
#include <glm/glm.hpp>
#include <cmath>

using namespace std; 

class Shape {
public:
	Shape();
	Shape(std::string const& n, Material const& m);
	// : name_(n), material_(m) {}
	std::string const& getName() const { return name_; };
	virtual double intersect(Ray const& ray) const = 0;
	virtual bool intersect_shadow(Ray const& ray) const = 0;
	Material const& getMaterial() const { return material_; }
	virtual glm::vec3 getNormalAt(glm::vec3 const& point) const = 0;
    void translate(glm::vec3 const& t);
	void scale(glm::vec3 const& s);
	void rotate(float deg, glm::vec3 const& axis);



	glm::mat4 world_transform_;
	glm::mat4 world_transform_inv_;


	glm::mat3 world_transform_T_;
	glm::mat3 world_transform_inv_T_;



protected:
  std::string name_;
  Material material_;
  
  
  
};





#endif
