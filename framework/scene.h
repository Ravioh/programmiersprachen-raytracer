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

	void render() const;
	void add(std::shared_ptr<Material> material);
	void add(std::shared_ptr<Shape> shape);
	void add(std::shared_ptr<Light> light);
	void add(std::shared_ptr<Camera> camera);

	std::vector<std::shared_ptr<Shape>> const& shapes() const;
	std::vector<std::shared_ptr<Material>> const& materials() const;
	std::vector<std::shared_ptr<Light>> const& lights() const;
	std::vector<std::shared_ptr<Camera>> const& cameras() const;

	/*
	void readFile(std::string file);
	std::map<std::string, std::shared_ptr<Material>> getMaterials();
	std::vector<std::shared_ptr<Shape>> getShapes();
	std::vector<Light> getLights();
	Camera getCamera();
	Material checkMaterialName(std::string name);*/


	std::vector<std::shared_ptr<Shape>> shapes_;
	std::map<std::string, Material> materials_;
	std::vector<std::shared_ptr<Light>> lights_;
	std::vector<std::shared_ptr<Camera>> cameras_;

	unsigned width = 600; 
	unsigned height = 600; 
};
#endif