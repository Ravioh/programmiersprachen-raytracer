#ifndef BUW_CYLINDER_HPP
#define BUW_CYLINDER_HPP

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"
#include "shape.h"
#include "ray.h"

class Cylinder : public Shape{
public:
	Cylinder();
	Cylinder(glm::vec3 const& centerbasedisk, float radius,
		glm::vec3 const& centertopdisk);
	Cylinder(std::string name, glm::vec3 const& centerbasedisk, float radius,
		glm::vec3 const& centertopdisk, std::string material);

	glm::vec3 const& get_centerbasedisk() const;
	glm::vec3 const& get_centertopdisk() const;
	float const& get_radius() const;

	double intersect(Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal)const;
	bool intersect_shadow(Ray const& ray) const override { return false; }


	std::ostream& print(std::ostream& os) const;

private:
	glm::vec3 centerbasedisk_;	// Center of base disk
	float radius_;
	glm::vec3 centertopdisk_; // Center of top disk
};

#endif // #ifndef BUW_CYLINDER_HPP