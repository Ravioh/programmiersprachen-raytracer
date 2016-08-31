// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846


#include <scene.h>
#include "renderer.hpp"
#include <math.h>
#include <sdfloader.h>
#include <iostream>
#include "shape.h"
#include <optional_hit.h>
Renderer::Renderer(Scene const& scene, unsigned w, unsigned h, std::string const& file)
	: width_(w)
	, height_(h)
	, colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
	, filename_(file)
	, ppm_(width_, height_)
	, scene_(scene)
{}






void Renderer::render() {


	const std::size_t checkersize = 20;
	camera_ = scene_.camera_;
	shapes_ = scene_.shapes_;
	lights_ = scene_.lights_;

	camera_.position = glm::vec3(0, 0, tan((90.0 - camera_.opening_angle / 2.0) * M_PI / 180.0) * (double(width_) / 2.0));
	testOutput();

	Ray first_ray;
	unsigned int depth;
	depth = 4; 
	for (unsigned y = 0; y < height_; ++y) {
		for (unsigned x = 0; x < width_; ++x) {
			Pixel p(x, y);

			//first ray is created here
			glm::vec3 poip = glm::vec3(double(x) - double(width_) / 2.0, double(y) - double(height_) / 2.0, 0);
			first_ray.origin = camera_.position;
			first_ray.direction = poip - camera_.position;

			double delta = -1;
			Shape *closest_obj;
			for (unsigned int i = 0; i < shapes_.size(); ++i) {
				double d = shapes_[i]->intersect(first_ray);
				if (d > 1.0 && (d < delta || delta == -1)) {
					delta = d;
					closest_obj = shapes_[i].get();
				}
			}

			if (delta == -1) {
				p.color = Color(0.0, 0.0, 0.0); //background color -> nothing hit = black
			} else {
				glm::vec3 hit_point = first_ray.origin + (float) delta * first_ray.direction;
				p.color = calculateColor(closest_obj, hit_point, first_ray, depth);
			}
			
			

			// draw pixel
			write(p);
		}
	}
	ppm_.save(filename_);
}


void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}




void Renderer::testOutput() {
	std::cout << "Objects in scene:" << std::endl;
	for (unsigned int i = 0; i < shapes_.size(); ++i) {
		std::cout << "Object names: " << shapes_[i]->getName() << std::endl;
	}
	for (unsigned int i = 0; i < lights_.size(); ++i) {
		std::cout << "Lightsource: " << lights_[i].getName() << std::endl;
	}
	std::cout << "Camera used: " << camera_.name << " | Focal Length: " << camera_.position.z << std::endl;
}
Color Renderer::calculateColor(const Shape* hit_obj, glm::vec3 const& hit_point, Ray const& first_ray, unsigned int  depth)  {
	Color final_color;
	float c = 0.001;



	for (unsigned int i = 0; i < lights_.size(); ++i) {

		glm::vec3 n = hit_obj->getNormalAt(hit_point);
		glm::vec3 l = lights_[i].getPosition() - hit_point;

		Ray sec_ray = Ray(hit_point, l);

		Color diffuse_light;
		Color specular_light;
		if (!Shadow(sec_ray) && glm::dot(glm::normalize(n), glm::normalize(l)) > 0) {

			Color Ip = lights_[i].getLD();
			Color kd = hit_obj->getMaterial().getKD();
			diffuse_light = (Ip * kd * glm::dot(glm::normalize(n), glm::normalize(l)));

			glm::vec3 r = 2 * glm::dot(glm::normalize(n), glm::normalize(l)) * glm::normalize(n) - glm::normalize(l); //reflection 
			glm::vec3 v = glm::normalize(first_ray.direction);
			float rv = glm::dot(r, v);

			v *= -1;
			if (glm::dot(r, v) > 0) { //if hit 
				double m = hit_obj->getMaterial().getM();
				Color ks = hit_obj->getMaterial().getKS();
				specular_light = ks * pow(glm::dot(r, v), m);
			}
			else {
				specular_light = Color(0.0, 0.0, 0.0);
			}
		}
		else {

			diffuse_light = Color(0.0, 0.0, 0.0);
			specular_light = Color(0.01, 0.01, 0.01);
		}




		/*
		Color reflect = hit_obj->getMaterial().getKS();
		
		if (depth > 1)
		{
			glm::vec3 v = (first_ray.direction);
			float vn = glm::dot(n, v);
			glm::vec3 r =  glm::normalize(v - 2 * vn*n);   // reflection vector

			Ray reflectionRay{ hit_point, r };
			reflectionRay.origin += reflectionRay.direction * c;

			Color reflectedColor = calculateColor(hit_obj, hit_point, reflectionRay, depth -1);   // recursion
	
			
			final_color += (reflectedColor)*(reflect);
	
	
		}*/

		final_color += diffuse_light + specular_light;
		

	}


		Color Ia = lights_[0].getLA();
		Color ka = hit_obj->getMaterial().getKA();
		Color ambient_light = Ia * ka;
		final_color += ambient_light;

		return final_color;
	}



bool Renderer::Shadow(Ray const& sec_ray) const {
	
	for (unsigned int i = 0; i < shapes_.size(); ++i) {
     	double d = shapes_[i]->intersect(sec_ray);
		if (d > 0 && d < 1)
			return true;
	}
	return false;
}


