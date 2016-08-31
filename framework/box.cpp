#include "box.h"
#include <ostream>
#include <cmath>
#include <algorithm>
#include <optional_hit.h>
#include <material.h>

Box::Box()
  : Shape()
  , pmin_()
  , pmax_()
{
}
Box::Box(std::string const&	name, glm::vec3 const&	pmin, glm::vec3 const&	pmax, Material const& material)
: Shape{ name, material }
, pmin_{ pmin }
, pmax_{ pmax }
{}

double Box::intersect(Ray const& ray) const {


	float ts[] = { -1, -1, -1, -1, -1, -1};

	//Calculation for each side, front, back, bottom top, left and right

	//Ray goes in z direction on grid = start calculation for front and back
	if (ray.direction.z != 0) {




		ts[0] = (pmin_.z - ray.origin.z) / ray.direction.z;
		glm::vec3 p_front = ray.origin + ts[0] * ray.direction;
		if (!(p_front.x < pmax_.x && p_front.x > pmin_.x && p_front.y > pmin_.y && p_front.y < pmax_.y))
			ts[0] = -1;


		ts[1] = (pmax_.z - ray.origin.z) / ray.direction.z;
		glm::vec3 p_back = ray.origin + ts[1] * ray.direction;
		if (!(p_back.x < pmax_.x && p_back.x > pmin_.x && p_back.y > pmin_.y && p_back.y < pmax_.y))
			ts[1] = -1;
	}

	//Ray goes in y direction on grid = start calculation for top and bottom
	if (ray.direction.y != 0) {


		ts[2] = (pmax_.y - ray.origin.y) / ray.direction.y;
		glm::vec3 p_top = ray.origin + ts[2] * ray.direction;
		if (!(p_top.x < pmax_.x && p_top.x > pmin_.x && p_top.z < pmin_.z && p_top.z > pmax_.z))
			ts[2] = -1;


		ts[3] = (pmin_.y - ray.origin.y) / ray.direction.y;
		glm::vec3 p_bottom = ray.origin + ts[3] * ray.direction;
		if (!(p_bottom.x < pmax_.x && p_bottom.x > pmin_.x && p_bottom.z < pmin_.z && p_bottom.z > pmax_.z))
			ts[3] = -1;
	}

	//Ray goes in x direction on grid = start calculation for sides (left and right)
	if (ray.direction.x != 0) {


		ts[4] = (pmin_.x - ray.origin.x) / ray.direction.x;
		glm::vec3 p_left = ray.origin + ts[4] * ray.direction;
		if (!(p_left.y < pmax_.y && p_left.y > pmin_.y && p_left.z < pmin_.z && p_left.z > pmax_.z))
			ts[4] = -1;


		ts[5] = (pmax_.x - ray.origin.x) / ray.direction.x;
		glm::vec3 p_right = ray.origin + ts[5] * ray.direction;
		if (!(p_right.y < pmax_.y && p_right.y > pmin_.y && p_right.z < pmin_.z && p_right.z > pmax_.z))
			ts[5] = -1;
	}
	double final_t = -1;
	for (int i = 0; i < 6; ++i) {
		if (ts[i] > 0 && (ts[i] < final_t || final_t == -1))
			final_t = ts[i];
	}

	return final_t;
}


glm::vec3 Box::getNormalAt(glm::vec3 const& point) const {
	if (point.x == pmin_.x)
		return glm::vec3(-1, 0, 0);
	else if (point.x == pmax_.x)
		return glm::vec3(1, 0, 0);
	else if (point.y == pmin_.y)
		return glm::vec3(0, -1, 0);
	else if (point.y == pmax_.y)
		return glm::vec3(0, 1, 0);
	else if (point.z == pmin_.z)
		return glm::vec3(0, 0, 1);
	else if (point.z == pmax_.z)
		return glm::vec3(0, 0, -1);
	else
		return glm::vec3();
}
glm::vec3 const& Box::getPMin() const {
	return pmin_;
}
glm::vec3 const& Box::getPMax() const {
	return pmax_;
}



void Box::setPMin(glm::vec3	const& pmin) {
	pmin_ = pmin;
}
void Box::setPMax(glm::vec3 const& pmax) {
	pmax_ = pmax;
}

