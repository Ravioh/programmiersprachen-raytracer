#include "plane.h"
#include <ostream>
#include <cmath>
#include <algorithm>

Plane::Plane() {
	name_ = "";
	normal_ = glm::vec3();
	d_ = 0.0;      //Distance to origin
	material_ = Material();
}
Plane::Plane(std::string name, glm::vec3 normal, double d, Material material) : name_( name ), normal_( normal ), d_( d ), material_( material ) {}
Plane::~Plane() {}

//Check if something is on the plane: 
bool Plane::isInPlane(glm::vec3 point) {
	return (normal_.x * point.x + normal_.y * point.y + normal_.z * point.z) == d_;
}



double Plane::intersect(Ray ray) {


	if (glm::dot(normal_, ray.direction) != 0) {

		return (d_ - glm::dot(normal_, ray.origin)) / glm::dot(normal_, ray.direction);
	} else {

		return -1;
	}
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