#include <sstream>

#include <GL/gl3w.h>

#ifndef GL_USER_DEBUG_H
#define GL_USER_DEBUG_H

#define GL_LOG_RESET() gldebug::Log::reset()
#define GL_LOG_INFO() gldebug::Log().writer(GL_DEBUG_SEVERITY_NOTIFICATION, GL_DEBUG_SOURCE_THIRD_PARTY, GL_DEBUG_TYPE_MARKER)
#define GL_LOG_ERROR() gldebug::Log().writer(GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SOURCE_THIRD_PARTY, GL_DEBUG_TYPE_ERROR)

namespace gldebug {
    void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *msg, const void *data);
    void glfwErrorCallback(int error, const char* desc);
    void logGLParams();

    class Log {
        public:
            Log();
            ~Log();
            enum logLevel{ LOG_STANDARD, LOG_ERROR };
            std::ostringstream& writer(GLenum log_level, GLenum msg_src, GLenum msg_type);
            static void reset();
        
        protected:
            std::ostringstream os;
            GLenum severity;
    };
}

#endif // GL_USER_DEBUG_H
