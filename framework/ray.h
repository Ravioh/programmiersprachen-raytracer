#ifndef RAY_H
#define RAY_H



#include <glm/glm.hpp>

struct Ray {

	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 direction_inv;


	Ray()
		: origin(0.0), direction(0.0,0.0,1.0)
	{}



	Ray(glm::vec3 const& origin_in, glm::vec3 const& direction_in) : origin( origin_in ), direction( direction_in ) {};

    unsigned depth;



};

#endif		/*RAY_H*/