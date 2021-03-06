#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <scene.h>
#include "sdfloader.h"

int main(int argc, char* argv[])
{


	//load scene 

  SDFLoader loader = SDFLoader(); 
  Scene scene = loader.load_scene("materials.sdf");


  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";


  Renderer app(scene, width, height, filename);

  std::thread thr([&app]() { app.render(); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
