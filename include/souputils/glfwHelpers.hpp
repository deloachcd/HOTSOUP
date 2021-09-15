#include <string>
#include <memory>

#include <GLFW/glfw3.h>

#ifndef GL_USER_HELPERS_H
#define GL_USER_HELPERS_H

namespace souputils {
	namespace glfwhelpers {
		struct glfwDisplayObjects {
			GLFWmonitor* monitor;
			const GLFWvidmode* vidmode;
		};
		struct fpsCounter {
			int frames;
			double seconds_since_last_render;
		};
		enum glfwWindowHintProfile {
			SOUP_GLFW_DEBUG_PROFILE,
			SOUP_GLFW_RELEASE_PROFILE
		};
		extern float WIDESCREEN_SCALING_DIVISOR;

		/* error handling callback */
		void glfwErrorCallback(int error, const char* desc);

		/* convenience helpers */
		std::unique_ptr<glfwDisplayObjects> glfwGetDisplayObjects();
		void glfwSetWindowHintProfile(glfwWindowHintProfile profile);

		/* primary window and default framebuffer helpers */
		void updateGlViewportOnWindowResize(GLFWwindow* window, int width, int height);

		/* misc helpers */
		void updateFPSCounter(GLFWwindow* window);
	}
}

#endif // GL_USER_HELPERS_H
