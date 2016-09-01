#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

#include <glm/vec3.hpp>
#include "shape.h"
#include <ray.h>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmath>
#include <optional_hit.h>


class Triangle : public Shape
{
public:
	Triangle(); 
	Triangle(Triangle const& triangle);
	Triangle(glm::vec3 const& left, glm::vec3 const& right, glm::vec3 const& top, std::string const& name, Material const& material);
	//get sides and top for construction
	glm::vec3 const& gettop() const;
	glm::vec3 const& getleft() const;
	glm::vec3 const& getright() const;
	
	float area() const; 
	float volume() const; 
	std::ostream& print(std::ostream& os) const; 
	double intersect(Ray const& r, float & d);
	bool intersect_shadow(Ray const& ray) const override { return false; }

	void translate(glm::vec3 const& direction);
	void scale(glm::vec3 const& scale);
	void rotate(float angle, glm::vec3 const& axis);

private:

	glm::vec3 top_;
	glm::vec3 left_;
	glm::vec3 right_;
	
};

#endif // BUW_TRIANGLE_HPP