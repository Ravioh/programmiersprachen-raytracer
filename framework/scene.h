#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include <memory>
#include <material.h>
#include <camera.h>
#include <light.h>
#include <shape.h>
#include <map>

struct Scene {

	Scene();
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::map<std::string, std::shared_ptr<Material>> materials_;
	std::vector<Light> lights_;
	Camera camera_;
	
	
	unsigned width = 600; 
	unsigned height = 600; 
};
#endif