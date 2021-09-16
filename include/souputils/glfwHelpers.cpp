#include <stdio.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "../include/souputils/glDebug.hpp"
#include "../include/souputils/glfwHelpers.hpp"

namespace souputils {
	namespace glfwhelpers {
		float WIDESCREEN_SCALING_DIVISOR = 0.5625f;

		void glfwErrorCallback(int error, const char* desc) {
			fprintf(stderr, "GLFW error: (%d) %s\n", error, desc);
		}

		std::unique_ptr<glfwDisplayObjects> glfwGetDisplayObjects() {
			std::unique_ptr<glfwDisplayObjects> d(new glfwDisplayObjects);
			d->monitor = glfwGetPrimaryMonitor();
			d->vidmode = glfwGetVideoMode(d->monitor);
			return d;
		}

		void glfwSetWindowHintProfile(glfwWindowHintProfile profile) {
			// Profiles get hardcoded here
			if (profile == SOUP_GLFW_DEBUG_PROFILE) {
				// 4.3 context for glDebugCallback
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
			} else if (profile == SOUP_GLFW_RELEASE_PROFILE) {
				
			} else {
				fprintf(stderr, "WARNING: invalid glfwWindowHintProfile will not be applied!");
			}
		}

		void updateGlViewportOnWindowResize(GLFWwindow* window, int width, int height) {
			// pass this to glfwSetFramebufferSizeCallback()
			glViewport(0, 0, width, height);
		}

		void updateFPSCounter(GLFWwindow* window, fpsCounter* frame_counter) {
			double current_seconds;
			double elapsed_seconds;
			current_seconds = glfwGetTime();
			elapsed_seconds = current_seconds - frame_counter->seconds_since_last_render;
			/* limit updates to 4 per second */
			if (elapsed_seconds > 0.25) {
				// update frame counter object
				frame_counter->seconds_since_last_render = current_seconds;
				frame_counter->frames = 0;

				// update FPS in window title
				char tmp[256];
				double fps = static_cast<double>(frame_counter->frames) / elapsed_seconds;
				sprintf (tmp, "opengl @ fps: %.2f", fps);
				glfwSetWindowTitle (window, tmp);
			}
			frame_counter->frames++;
		}
	}
}
