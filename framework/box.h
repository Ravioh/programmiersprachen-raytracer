#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <iosfwd>
#include <color.hpp>
#include <glm/glm.hpp>
#include "plane.h"
#include "shape.h"


class Box : public Shape {
public:
	Box();
	Box(std::string name, glm::vec3 pmin, glm::vec3 pmax, Material material);
	~Box();

	 std::string getName();
	 Material getMaterial() const;
	 glm::vec3 getNormalAt(glm::vec3 point) const;
	 double intersect(Ray ray);
	

	//Setting attributes of box
	void setName(std::string name);
	void setPMin(glm::vec3 pmin);
	void setPMax(glm::vec3 pmax);
	void setMaterial(Material material);
	

	//Min and Max Point to build box
	glm::vec3 getPMin();
	glm::vec3 getPMax();


private:
	std::string name_;
	glm::vec3 pmin_;
	glm::vec3 pmax_;
	Material material_;
};

#endif // BUW_BOX_HPP