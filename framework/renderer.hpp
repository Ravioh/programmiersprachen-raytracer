// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include <map>
#include <shape.h>
#include "sdfloader.h"
#include <optional_hit.h>
#include <scene.h>

class Renderer {
public:
	Renderer(Scene const& scene, unsigned w, unsigned h, std::string const& file);

  void render();
  void write(Pixel const& p);


  void testOutput();

  Color calculateColor(const Shape* hit_obj, glm::vec3 const& hit_point, Ray const& first_ray, unsigned int depth);
  void calculateReflectedColor(Color & final_color, glm::vec3 hit_obj, Ray const& ray, unsigned int depth);
  bool Shadow(Ray const& sec_ray) const;


  inline std::vector<Color> const& colorbuffer() const {
    return colorbuffer_;
  }


  unsigned get_width() const;
  unsigned get_height() const;
  std::string get_filename() const;
  Scene get_scene() const;

  


  OptionalHit intersect(Ray const& ray) const;



private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;


  Scene scene_;
  Camera camera_;
  

  std::vector<Light> lights_;
  std::vector<std::shared_ptr<Shape>> shapes_;


};

#endif // #ifndef BUW_RENDERER_HPP
