#include <GL/gl3w.h>

#include "../include/souputils/glDebug.hpp"
#include "../include/souputils/glfwHelpers.hpp"
#include "../include/souputils/convenience.hpp"

using namespace souputils::glfwhelpers;
using namespace souputils::gldebug;

void souputils::convenience::enableSoupDebugContext() {
	// debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// debug callbacks
    glDebugMessageCallback(glDebugCallback, nullptr);
    glfwSetErrorCallback(glfwErrorCallback);
	// initialize logfile
	glLogReset();
}
