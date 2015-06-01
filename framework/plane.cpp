#include "plane.h"
#include <ostream>
#include <algorithm>
#include <cmath>


Plane::Plane() {
	name_ = "";
	normal_ = glm::vec3();
	d_ = 0.0;					//distance to origin
	material_ = Material();
}
Plane::Plane(std::string name, glm::vec3 normal, double d, Material material) : name_( name ), normal_( normal ), d_( d ), material_( material ) {}
Plane::~Plane() {}


double Plane::intersect(Ray ray) {

	if (glm::dot(normal_, ray.direction) != 0) {

		//Checking if the Plane and the Ray are parallel
		return (d_ - glm::dot(normal_, ray.origin)) / glm::dot(normal_, ray.direction);
	} else {

		//If parallel = no Intersection. If ray lies on plane = endless Intersections. 
		return -1;
	}
}
//Usage of Dot product to determine

bool Plane::isInPlane(glm::vec3 point) {
	return (normal_.x * point.x + normal_.y * point.y + normal_.z * point.z) == d_;
}


std::string Plane::getName() {
	return name_;
}
Material Plane::getMaterial() const {
	return material_;
}
glm::vec3 Plane::getNormalAt(glm::vec3 point) const {
	return normal_;
}
double Plane::getD() {
	return d_;
}


void Plane::setName(std::string name) {
	name_ = name;
}
void Plane::setD(double d) {
	d_ = d;
}
void Plane::setMaterial(Material material) {
	material_ = material;
}