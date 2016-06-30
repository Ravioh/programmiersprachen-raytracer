#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <iosfwd>
#include "color.hpp"
#include <glm/glm.hpp>
#include "plane.h"
#include "shape.h"


class Box : public Shape {
public:
	Box();
	Box(std::string const& name, glm::vec3 const& pmin, glm::vec3 const& pmax, Material const& material);

	 glm::vec3 getNormalAt(glm::vec3 const& point) const;
	 double intersect(Ray const& ray) const;
	 bool intersect_shadow(Ray const& ray) const override { return false; }


	//Setting attributes of box
	void setPMin(glm::vec3 const& pmin);
	void setPMax(glm::vec3 const& pmax);

	//Min and Max Point to build box
	glm::vec3 const& getPMin() const;
	glm::vec3 const& getPMax() const;


private:

	glm::vec3 pmin_;
	glm::vec3 pmax_;
};

#endif // BUW_BOX_HPP
