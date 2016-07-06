#ifndef BUW_SDF_LOADER_HPP
#define BUW_SDF_LOADER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "material.h"
#include "shape.h"
#include "sphere.h"
#include "plane.h"
#include "box.h"
#include "camera.h"
#include "light.h"
#include <memory>
#include "scene.h"  //#include "scene.h"
#include <map>

class SDFLoader {
public:
	SDFLoader();

	static std::vector<std::string> splitLine(std::string line);
	void readFile(std::string file);
	std::map<std::string, std::shared_ptr<Material>> getMaterials();
	std::vector<std::shared_ptr<Shape>> getShapes();
	std::vector<Light> getLights();
	Camera getCamera();
	Material checkMaterialName(std::string name);



private:
    // move to Scenes
	std::map<std::string, std::shared_ptr<Material>> materials_;
	//std::vector<Material*> materials_; // TODO remove
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::vector<Light> lights_;
	Camera camera_;
};

#endif // BUW_SDF_LOADER_HPP
