#include "sphere.h"
#include <ostream>
#include <cmath>
#include <algorithm>

Sphere::Sphere()
  : Shape()
  , center_()
  , radius_()
  {}

Sphere::Sphere(std::string const& name, glm::vec3 const& center, double radius, Material const& material)
: Shape{ name, material },
center_{ center },
radius_{ radius }
  {}


glm::vec3 const& Sphere::getCenter() const {
	return center_;
}
double Sphere::getRadius()  {
	return radius_;
}

glm::vec3 Sphere::getNormalAt(glm::vec3 point) const {
	return glm::normalize(point - center_);
}


void Sphere::setCenter(glm::vec3 const& center) {
	center_ = center;
}
void Sphere::setRadius(double radius) {
	radius_ = radius;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // //

double Sphere::intersect(Ray const& ray) {

	// compute delta and handle cases
	float a = glm::dot(ray.direction, ray.direction); // a = d*d
	float b = 2.0f*glm::dot(ray.direction, ray.origin - center_); // b = 2d(o-C)
	float c = glm::dot(ray.origin - center_, ray.origin - center_) - pow(radius_, 2); // c = (o-C)^2-R^2

	//Calculate discriminant
	float delta = (b*b) - (4.0f*a*c);

	if (delta < 0) {

		// no intersection
		return -1;
	} else if (delta == 0) {

		// one intersection
		return (-1 * b) / (2 * a);
	} else {

		// two intersections
		double d1 = (-1 * b - sqrt(delta)) / (2 * a);
		double d2 = (-1 * b + sqrt(delta)) / (2 * a);
		return std::min(d1, d2);
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // //
