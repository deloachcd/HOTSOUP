#include <stdio.h>
#include <string>

#include <time.h>

#include <GL/gl3w.h>
#include "glDebug.hpp"

#define GL_LOG_FILE "log/gl.log"

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

			void logWrite(FILE* stream, GLenum log_level, GLenum msg_src, GLenum msg_type,
						  const char* msg_format, ...) {
				va_list args;
				time_t now = time(nullptr);
				char* date = ctime(&now);
				char flogParams[30];
				formattedLogParamsToBuffer(flogParams, log_level, msg_src, msg_type);

				va_start(args, msg_format);
				fprintf(stream, "%s | %s | ", date, flogParams);
				vfprintf(stream, msg_format, args);
				fprintf(stream, "\n");
				va_end(args);
			}
			void logAppend(const char* fname, GLenum log_level, GLenum msg_src,
						   GLenum msg_type, const char* format, ...) {
				FILE* fp;
				va_list args;
				fp = fopen(fname, "a");
				if (fp) {
					va_start(args, format);
					logWrite(fp, log_level, msg_src, msg_type, format, args);
					va_end(args);
					fclose(fp);
				} else {
					fprintf(stderr, "ERROR: could not open log file '%s' for writing!\n",
							fname);
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
												  const void* log_fname) {
	logAppend(static_cast<const char *>(log_fname), severity, source, type, msg);
}

void souputils::gldebug::logGLParams(const char* log_fname) {
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
	souputils::gldebug::glLogInfo(log_fname, "GL Context Params:");

	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		souputils::gldebug::glLogInfo(log_fname, "%s %s", names[i], v);
	}

	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	souputils::gldebug::glLogInfo(log_fname, "%s %d %d", names[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv (params[11], &s);
	souputils::gldebug::glLogInfo(log_fname, "%s %u", names[10],
								static_cast<unsigned int>(s));
}

void souputils::gldebug::glLogInfo(const char* fname, const char* format, ...) {
	va_list args;
	va_start(args, format);
	logAppend(fname, GL_DEBUG_SEVERITY_NOTIFICATION, GL_DEBUG_SOURCE_APPLICATION,
			  GL_DEBUG_TYPE_MARKER, format, args);
	va_end(args);
}

void souputils::gldebug::glLogError(const char* fname, const char* format, ...) {
	va_list args;
	va_start(args, format);
	logAppend(fname, GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SOURCE_APPLICATION,
			  GL_DEBUG_TYPE_ERROR, format, args);
	va_end(args);
}

void souputils::gldebug::glLogReset(const char* fname) {
	FILE* fp;
	fp = fopen(fname, "w");
	if (fp) {
		logWrite(fp, GL_DEBUG_SEVERITY_NOTIFICATION, GL_DEBUG_SOURCE_APPLICATION,
				 GL_DEBUG_TYPE_MARKER, "OpenGL log file initialized");
		fclose(fp);
	} else {
		fprintf(stderr, "ERROR: could not open log file '%s' for writing!\n",
				fname);
	}
}
