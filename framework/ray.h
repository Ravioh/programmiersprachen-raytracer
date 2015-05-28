#include <glm/glm.hpp >

struct Ray {
	Ray() { 
		origin = glm::vec3(); 
		direction = glm::vec3();
	}
	Ray(glm::vec3 origin_in, glm::vec3 direction_in) : origin( origin_in ), direction( direction_in ) {};
	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 direction_inv;
    unsigned depth;
};