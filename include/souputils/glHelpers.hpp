#include <string>
#include <memory>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#ifndef GL_USER_HELPERS_H
#define GL_USER_HELPERS_H

namespace souputils {
	namespace glhelpers {
		struct shaderSrc {
			GLuint type;
			char* source;
		};

		extern float WIDESCREEN_SCALING_DIVISOR;

		/* primary window and default framebuffer helpers */
		void glLinkProgramSafe(GLuint program);

		/* shader program helpers */
		std::unique_ptr<shaderSrc> loadShaderFile(GLuint shadertype,
												  const char* filepath);
		GLuint compileShader(GLuint type, const char* source);
		GLuint compileShaderSrc(const shaderSrc* shader_src);
		GLuint compileSimpleShaderProgram(const char* vertex_shader_fname,
										  const char* fragment_shader_fname);
		void reloadShaderProgramFromFiles(GLuint* program,
										  const char* vertex_shader_fname,
										  const char* fragment_shader_fname);

		/* buffer creation and loading helpers */
		typedef std::unique_ptr<float[]> ufloat_ptr;

		// create vbos directly from arrays of glm vectors
		GLuint vboFromFlattenedVectorArray(glm::vec2* vector_arr, size_t size_arr);
		GLuint vboFromFlattenedVectorArray(glm::vec3* vector_arr, size_t size_arr);
		GLuint vboFromFlattenedVectorArray(glm::vec4* vector_arr, size_t size_arr);

		// flattening for small, stack-allocated arrays using GLM types
		float* flatten(glm::vec2* arr_vectors, float buffer[], size_t size_arr);
		float* flatten(glm::vec3* arr_vectors, float buffer[], size_t size_arr);
		float* flatten(glm::vec4* arr_vectors, float buffer[], size_t size_arr);

		// flattening for arrays on the heap
		std::unique_ptr<float[]> flatten(glm::vec2* arr_vectors, size_t size_arr);
		std::unique_ptr<float[]> flatten(glm::vec3* arr_vectors, size_t size_arr);
		std::unique_ptr<float[]> flatten(glm::vec4* arr_vectors, size_t size_arr);
	}
}

#endif // GL_USER_HELPERS_H
