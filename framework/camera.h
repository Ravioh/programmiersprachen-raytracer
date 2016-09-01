#ifndef CAMERA_H
#define CAMERA_H



#include <glm/glm.hpp>

struct Camera {

	
	double opening_angle;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 upvector;
	glm::vec3 origin; 
	std::string name;
	
	
	void set_position(glm::vec3 position, int const&);
	void set_direction(glm::vec3 const&);
	void set_fov(double const&);
	void set_name(std::string const&);
	void translate(glm::vec3 const& t);
	void rotate(float deg, glm::vec3 const& axis); 




};

#endif /*CAMERA_H*/

