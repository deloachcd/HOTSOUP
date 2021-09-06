#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>

#include <time.h>
#include <stdarg.h>
#include <string.h>

#include <GL/gl3w.h>

#include "glDebug.hpp"

#define GL_LOG_FILE "log/gl.log"

namespace gldebug {

    void logGLParams() {
        GLenum params[] = {
            GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
            GL_MAX_CUBE_MAP_TEXTURE_SIZE,
            GL_MAX_DRAW_BUFFERS,
            GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
            GL_MAX_TEXTURE_IMAGE_UNITS,
            GL_MAX_TEXTURE_SIZE,
            GL_MAX_VARYING_FLOATS,
            GL_MAX_VERTEX_ATTRIBS,
            GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
            GL_MAX_VERTEX_UNIFORM_COMPONENTS,
            GL_MAX_VIEWPORT_DIMS,
            GL_STEREO,
        };
        const char* names[] = {
            "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
            "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
            "GL_MAX_DRAW_BUFFERS",
            "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
            "GL_MAX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_TEXTURE_SIZE",
            "GL_MAX_VARYING_FLOATS",
            "GL_MAX_VERTEX_ATTRIBS",
            "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
            "GL_MAX_VIEWPORT_DIMS",
            "GL_STEREO",
        };
        GL_LOG_INFO() << "GL Context Params:";

        // integers - only works if the order is 0-10 integer return types
        for (int i = 0; i < 10; i++) {
            int v = 0;
            glGetIntegerv (params[i], &v);
            GL_LOG_INFO() << names[i] << " " << v;
        }

        // others
        int v[2];
        v[0] = v[1] = 0;
        glGetIntegerv (params[10], v);
        GL_LOG_INFO() << names[10] << " " << v[0] << " " << v[1];
        unsigned char s = 0;
        glGetBooleanv (params[11], &s);
        GL_LOG_INFO() << names[11] << " " << (unsigned int)s;
    } 

    void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *msg, const void *data) {
        Log().writer(severity, source, type) << msg;
    }

    void glfwErrorCallback(int error, const char* desc) {
        GL_LOG_ERROR() << "GLFW error: " << error << " " << desc;
    }

    std::ostringstream& Log::writer(GLenum log_level, GLenum msg_src, GLenum msg_type) {
        this->severity = log_level;

        time_t now = time(nullptr);
        char* date  = ctime(&now);
        date[strcspn(date, "\n")] = '\0';
        this->os << date;
        
        this->os << " | ";
        switch (log_level) {
            case GL_DEBUG_SEVERITY_HIGH:
            this->os << "HIGH";
            break;
            case GL_DEBUG_SEVERITY_MEDIUM:
            this->os << "MED ";
            break;
            case GL_DEBUG_SEVERITY_LOW:
            this->os << "LOW ";
            break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
            this->os << "NOTF";
            break;
            default:
            this->os << "UNKN";
            break;
        }
        this->os << " | ";
        switch (msg_src) {
            case GL_DEBUG_SOURCE_API:
            this->os << "API            ";
            break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            this->os << "WINDOW SYSTEM  " ;
            break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
            this->os << "SHADER COMPILER";
            break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
            this->os << "THIRD PARTY    ";
            break;
            case GL_DEBUG_SOURCE_APPLICATION:
            this->os << "APPLICATION    ";
            break;
            case GL_DEBUG_SOURCE_OTHER:
            this->os << "UNKNOWN        ";
            break;
            default:
            this->os << "UNKNOWN        ";
            break;
        }
        this->os << " | ";
        switch (msg_type) {
            case GL_DEBUG_TYPE_ERROR:
            this->os << "ERR ";
            break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            this->os << "DEPR";
            break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            this->os << "UDEF";
            break;
            case GL_DEBUG_TYPE_PORTABILITY:
            this->os << "PORT";
            break;
            case GL_DEBUG_TYPE_PERFORMANCE:
            this->os << "PERF";
            break;
            case GL_DEBUG_TYPE_OTHER:
            this->os << "OTHR";
            break;
            case GL_DEBUG_TYPE_MARKER:
            this->os << "MRKR";
            break;
            default:
            this->os << "UNKN";
            break;
        }
        this->os << " | ";

        return this->os;
    }

    void Log::reset() {
        std::ofstream outfile;
        outfile.open(GL_LOG_FILE);
        if (!outfile) {
            std::cerr << "ERROR: could not open GL_LOG_FILE " << GL_LOG_FILE
                << " for writing." << std::endl;
        }
        time_t now = time(nullptr);
        char* date  = ctime(&now);
        outfile << "GL_LOG_FILE initialized at " << date;
        outfile.close();
    }

    Log::Log() {}

    Log::~Log() {
        std::string msg = this->os.str();
        if (this->severity == GL_DEBUG_SEVERITY_HIGH || 
                this->severity == GL_DEBUG_SEVERITY_MEDIUM) {
            std::cerr << msg << std::endl;
        }
        std::ofstream outfile;
        outfile.open(GL_LOG_FILE, std::ios::app);
        if (!outfile) {
            std::cerr << "ERROR: could not open GL_LOG_FILE " << GL_LOG_FILE
                << " for appending." << std::endl;
        }
        outfile << msg << std::endl;
        outfile.close();
    }
}
