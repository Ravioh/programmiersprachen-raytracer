#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <iosfwd>

#include "color.hpp"
#include <glm/glm.hpp>
#include <cmath>
#include "shape.h"

class Sphere : public Shape {
public:
	Sphere();
	Sphere(std::string const& name, glm::vec3 const& center, double radius, Material const& material);
	~Sphere();

	double intersect(Ray const& ray);
	bool intersect_shadow(Ray const& ray) const override { return false; }
	glm::vec3 const& getNormalAt(glm::vec3 point) const;

	glm::vec3 const& getCenter() const;
	double getRadius();

	void setCenter(glm::vec3 const& center);
	void setRadius(double radius);
private:
	glm::vec3 center_;
	double radius_;
};

#endif // BUW_SPHERE_HPP
