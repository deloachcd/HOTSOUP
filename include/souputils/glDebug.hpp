#include <stdio.h>

#include <GL/gl3w.h>

#ifndef SOUP_GL_DEBUG_H
#define SOUP_GL_DEBUG_H

namespace souputils {
	namespace gldebug {
		// Non-programmer facing
		namespace impl {
			void formattedLogParamsToBuffer(char * buff, GLenum log_level,
											GLenum msg_src, GLenum msg_type);

			void logWrite(FILE* stream, GLenum log_level, GLenum msg_src,
						  GLenum msg_type, const char* msg);
			void logAppend(GLenum log_level, GLenum msg_src, GLenum msg_type,
						   const char* msg);
		}

		// Programmer facing
		void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
									  GLenum severity, GLsizei length,
									  const GLchar* msg,
									  const void* log_fname);

		void logGLParams();
		void glLogAtLevel(GLuint level, const char* format, ...);
		void glLogInfo(const char* format, ...);
		void glLogError(const char* format, ...);
		void glLogReset();
	}
}

#endif // SOUP_GL_DEBUG_H
