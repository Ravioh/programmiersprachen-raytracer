
#include "sdfloader.h"
#include "scene.h"
#include <cstdlib>
#include <thread>
#include <cmath>
#include <map>
#include <material.h>

using namespace std; 

SDFLoader::SDFLoader()
        {}

Scene SDFLoader::load_scene(std::string file) {  


	Scene scene{};
	std::ifstream ifs(file);

	char line[256];
	std::cout << "\nSDF File content:\n\n" << std::endl;

	if (ifs.is_open()) {

		while (ifs.good()) {

			ifs.getline(line, 256);
			std::cout << line << std::endl;
			std::vector<std::string> words = splitLine(line);
			unsigned int i = 0;
			while (i < words.size()) {


				if (words[i].compare("define") == 0) {


					if (words[i + 1].compare("material") == 0) {
						std::string name = words[i + 2];
						Color ks = Color(
							std::stof(words[i + 9]),
							std::stof(words[i + 10]),
							std::stof(words[i + 11])
						);
						Color ka = Color(
							std::stof(words[i + 3]),
							std::stof(words[i + 4]),
							std::stof(words[i + 5])
						);
						Color kd = Color(
							std::stof(words[i + 6]),
							std::stof(words[i + 7]),
							std::stof(words[i + 8])
						);
						float m = std::stof(words[i + 12]);

						std::shared_ptr<Material> temp_ptr = std::make_shared<Material>(Material{ name, ka, kd, ks, m });
						scene.materials_.insert({ name, temp_ptr });

						i = i + 13;
					


					} else if (words[i + 1].compare("shape") == 0) {


						if (words[i + 2].compare("sphere") == 0) {
							std::string name = words[i + 3];
							glm::vec3 center = glm::vec3(
								std::stod(words[i + 4]),
								std::stod(words[i + 5]),
								std::stod(words[i + 6])
								);
							double radius = std::stod(words[i + 7]);
							Material material = checkMaterialName(words[i + 8]);
							auto new_sphere = std::make_shared<Sphere>(name, center, radius, material);
							scene.shapes_.push_back(new_sphere);
							i = i + 9;


						} else if (words[i + 2].compare("plane") == 0) {
							std::string name = words[i + 3];
							glm::vec3 normal = glm::vec3(
								std::stod(words[i + 4]),
								std::stod(words[i + 5]),
								std::stod(words[i + 6])
								);
							double d = std::stod(words[i + 7]);
							Material material = checkMaterialName(words[i + 8]);
							auto globbi = std::make_shared<Plane>(name, normal, d, material);
							scene.shapes_.push_back(globbi);
							i = i + 9;

						} else if (words[i + 2].compare("box") == 0) {
							std::string name = words[i + 3];
							glm::vec3 p0 = glm::vec3(
								std::stod(words[i + 4]),
								std::stod(words[i + 5]),
								std::stod(words[i + 6])
								);
							glm::vec3 p1 = glm::vec3(
								std::stod(words[i + 7]),
								std::stod(words[i + 8]),
								std::stod(words[i + 9])
								);
							Material material = checkMaterialName(words[i + 10]);
							auto new_box = std::make_shared<Box>(name, p0, p1, material);
							scene.shapes_.push_back(new_box);
							i = i + 11;


							/*	} else if (words[i + 2] == "triangle") {
							std::string name = words [i+3];
							glm::vec3 left = glm:vec3(
								std::stof(words[i + 4])
								std::stof(words[i + 5]),
								std::stof(words[i + 6])
								);
							glm::vec3 right = glm:vec3(
								std::stof(words[i + 7]),
								std::stof(words[i + 8]),
								std::stof(words[i + 9]) };
								glm::vec3 top = glm:vec3(
								std::stof(words[i + 10]),
								std::stof(words[i + 11]),
								std::stof(words[i + 12]) };
						
							}*/



						//If shape not supported
						} else {
							std::cout << "Error, usage of unknown shape." << std::endl;
						}

					//Camera
					} else if (words[i + 1].compare("camera") == 0) {
						std::string name = words[i + 2];
						double opening_angle = std::stod(words[i + 3]);
						scene.camera_.name = name;
						scene.camera_.opening_angle = opening_angle;
						i = i + 4;




					//Lightsource
					} else if (words[i + 1].compare("light") == 0) {
						std::string name = words[i + 2];
						glm::vec3 position = glm::vec3(
							std::stod(words[i + 3]),
							std::stod(words[i + 4]),
							std::stod(words[i + 5])
						);
						Color la = Color(
							std::stof(words[i + 6]),
							std::stof(words[i + 7]),
							std::stof(words[i + 8])
						);
						Color ld = Color(
							std::stof(words[i + 9]),
							std::stof(words[i + 10]),
							std::stof(words[i + 11])
						);
						Light manni(name, position, la, ld);
						scene.lights_.push_back(manni);
						i = i + 12;

					} else {
						std::cout << "Error, parameters set wrong?" << std::endl;
					}

				} else {
					i++;
				}
			}
		}
	} else {
		std::cout << "Could not open SDF File" << std::endl;
	}
	std::cout << "\nFile sucessfully read!(scherz)\n" << std::endl;

	return scene;
}


//material from scene.h 
Material Scene::checkMaterialName(const std::string name)const{


	//this one is working, as tested with the sdf file -> did not find green material (and crashed the whole thing tho)
	std::shared_ptr<Material> material;
	std::map<std::string, std::shared_ptr<Material>>::const_iterator  it;
	it = materials_.find(name);

	if (it != materials_.end()){
		material = it->second;

	}
	else {
		 std::cout << "Error parsing file. No material given or not found. Name of the material: " << name << std::endl;
	 }
	

	//testing to see if function was broken 
	/*std::string heiko = "Bob"; 
	Material bob = Material(heiko, Color(255, 0, 0), Color(255, 0, 0), Color(255, 0, 0), 1.0f);*/

	return *material;
}




std::vector<std::string> SDFLoader::splitLine(std::string line) {
	std::vector<std::string> words;
	std::stringstream ssin(line);
	while (ssin.good()){
		std::string word;
		ssin >> word;
		words.push_back(word);
	}
	return words;
}

