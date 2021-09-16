#include <stdio.h>
#include <stdarg.h>
#include <string>

#include <time.h>

#include <GL/gl3w.h>

#include "glDebug.hpp"

#define GL_LOG_FILE "log/gl.log"
#define LOG_MSG_MAX_LEN 300

namespace souputils {
	namespace gldebug {
		namespace impl {
			void formattedLogParamsToBuffer(char * buff, GLenum log_level,
											GLenum msg_src, GLenum msg_type) {
				std::string log_level_str, msg_src_str, msg_type_str;

				switch (log_level) {
					case GL_DEBUG_SEVERITY_HIGH:
						log_level_str = "HIGH";
						break;
					case GL_DEBUG_SEVERITY_MEDIUM:
						log_level_str = "MED ";
						break;
					case GL_DEBUG_SEVERITY_LOW:
						log_level_str = "LOW ";
						break;
					case GL_DEBUG_SEVERITY_NOTIFICATION:
						log_level_str = "NOTF";
						break;
					default:
						log_level_str = "UNKN";
						break;
				}
				switch (msg_src) {
					case GL_DEBUG_SOURCE_API:
						msg_src_str = "API            ";
						break;
					case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
						msg_src_str = "WINDOW SYSTEM  " ;
						break;
					case GL_DEBUG_SOURCE_SHADER_COMPILER:
						msg_src_str = "SHADER COMPILER";
						break;
					case GL_DEBUG_SOURCE_THIRD_PARTY:
						msg_src_str = "THIRD PARTY    ";
						break;
					case GL_DEBUG_SOURCE_APPLICATION:
						msg_src_str = "APPLICATION    ";
						break;
					case GL_DEBUG_SOURCE_OTHER:
						msg_src_str = "UNKNOWN        ";
						break;
					default:
						msg_src_str = "UNKNOWN        ";
						break;
				}
				switch (msg_type) {
					case GL_DEBUG_TYPE_ERROR:
						msg_type_str = "ERR ";
						break;
					case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
						msg_type_str = "DEPR";
						break;
					case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
						msg_type_str = "UDEF";
						break;
					case GL_DEBUG_TYPE_PORTABILITY:
						msg_type_str = "PORT";
						break;
					case GL_DEBUG_TYPE_PERFORMANCE:
						msg_type_str = "PERF";
						break;
					case GL_DEBUG_TYPE_OTHER:
						msg_type_str = "OTHR";
						break;
					case GL_DEBUG_TYPE_MARKER:
						msg_type_str = "MRKR";
						break;
					default:
						msg_type_str = "UNKN";
						break;
				}
				sprintf(buff, "%s | %s | %s",
						log_level_str.c_str(), msg_src_str.c_str(), msg_type_str.c_str());
			}

			void logWrite(FILE* stream, GLenum log_level, GLenum msg_src,
						  GLenum msg_type, const char* msg) {
				time_t now = time(nullptr);
				char* date = ctime(&now);
				date[24] = '\0';  // strip trailing newline
				char flogParams[30];
				formattedLogParamsToBuffer(flogParams, log_level, msg_src, msg_type);

				if (log_level == GL_DEBUG_SEVERITY_HIGH) {
					fprintf(stderr, "%s | %s | %s\n", date, flogParams, msg);
				}
				fprintf(stream, "%s | %s | %s\n", date, flogParams, msg);
			}

			void logAppend(GLenum log_level, GLenum msg_src, GLenum msg_type,
						   const char* msg) {
				FILE* fp;
				fp = fopen(GL_LOG_FILE, "a");
				if (fp) {
					logWrite(fp, log_level, msg_src, msg_type, msg);
					fclose(fp);
				} else {
					fprintf(stderr, "ERROR: could not open log file '%s' for writing!\n",
							GL_LOG_FILE);
				}
			}
		}
	}
}

using namespace souputils::gldebug::impl;

void APIENTRY souputils::gldebug::glDebugCallback(GLenum source, GLenum type,
												  GLuint id, GLenum severity,
												  GLsizei length,
												  const GLchar *msg,
												  const void* data) {
	logAppend(severity, source, type, msg);
}

void souputils::gldebug::logGLParams() {
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
	souputils::gldebug::glLogInfo("GL Context Params:");

	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		souputils::gldebug::glLogInfo("%s %s", names[i], v);
	}

	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	souputils::gldebug::glLogInfo("%s %d %d", names[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv (params[11], &s);
	souputils::gldebug::glLogInfo("%s %u", names[10],
								  static_cast<unsigned int>(s));
}

void souputils::gldebug::glLogAtLevel(GLuint level, const char* format, ...) {
	va_list args;
	char buff[200];
	va_start(args, format);
	vsprintf(buff, format, args);
	va_end(args);
	logAppend(level, GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, buff);
}

void souputils::gldebug::glLogInfo(const char* format, ...) {
	va_list args;
	char buff[LOG_MSG_MAX_LEN];
	va_start(args, format);
	vsprintf(buff, format, args);
	glLogAtLevel(GL_DEBUG_SEVERITY_NOTIFICATION, buff);
	va_end(args);
}

void souputils::gldebug::glLogError(const char* format, ...) {
	va_list args;
	char buff[LOG_MSG_MAX_LEN];
	va_start(args, format);
	vsprintf(buff, format, args);
	glLogAtLevel(GL_DEBUG_SEVERITY_HIGH, format, args);
	va_end(args);
}

void souputils::gldebug::glLogReset() {
	FILE* fp;
	fp = fopen(GL_LOG_FILE, "w");
	if (fp) {
		logWrite(fp,
				 GL_DEBUG_SEVERITY_NOTIFICATION, GL_DEBUG_SOURCE_APPLICATION,
				 GL_DEBUG_TYPE_MARKER, "OpenGL log file initialized");
		fclose(fp);
	} else {
		fprintf(stderr, "ERROR: could not open log file '%s' for writing!\n",
				GL_LOG_FILE);
	}
}
