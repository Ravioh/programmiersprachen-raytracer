#ifndef BUW_CONE_HPP
#define BUW_CONE_HPP

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"
#include "shape.h"
#include "ray.h"

class Cone : public Shape{
public:
	Cone();
	Cone(glm::vec3 const& centertop, float radius, glm::vec3 const& centerbase);
	Cone(std::string name, glm::vec3 const& centertop, float radius,
		glm::vec3 const& centerbase, std::string material);

	glm::vec3 const& get_centertop() const;
	glm::vec3 const& get_centerbase() const;
	float const& get_radius() const;
	

	double intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;
	bool intersect_shadow(Ray const& ray) const override { return false; }

	std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 centertop_;
	glm::vec3 centerbase_; 
	float radius_;
	
};

#endif // #ifndef BUW_CONE_HPP

