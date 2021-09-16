#include <GL/gl3w.h>

#include "../include/souputils/glDebug.hpp"
#include "../include/souputils/glfwHelpers.hpp"
#include "../include/souputils/convenience.hpp"

using namespace souputils::glfwhelpers;
using namespace souputils::gldebug;

void souputils::convenience::enableSoupDebugContext() {
	// window hints
	glfwSetWindowHintProfile(SOUP_GLFW_DEBUG_PROFILE);
	// debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// debug callbacks
    glDebugMessageCallback(glDebugCallback, nullptr);
    glfwSetErrorCallback(glfwErrorCallback);
	// initialize logfile
	glLogReset();
	glLogInfo("Renderer: %s", glGetString(GL_RENDERER));
	glLogInfo("OpenGL version supported: %s", glGetString(GL_VERSION));
}
