#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <vector>

int main(int argc, char* argv[]) {


	unsigned const width = 1000;
	unsigned const height = 1000;
	std::string const filename = "./checkerboard.ppm";

	Renderer app(width, height, filename, sdfloader);

	std::thread thr([&app]() { app.render(); });

	Window win(glm::ivec2(width,height));

	SDFLoader sdfloader = SDFLoader();
	sdfloader.readFile("scene.sdf"); 


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
