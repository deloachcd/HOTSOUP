#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <memory>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../include/souputils/glDebug.hpp"
#include "../include/souputils/glHelpers.hpp"

using namespace souputils::gldebug;
using namespace souputils::glhelpers;

std::unique_ptr<shaderSrc>
souputils::glhelpers::loadShaderFile(GLuint shadertype, 
									 const char* filepath) {
	/* NOTE: this will not work with files over 4GB, so let's try
	not to load in any huge fucking shaders with this! */
	FILE* shader_stream = fopen(filepath, "r");
	if (!shader_stream) {
		fprintf(stderr, "Failed to load shader file '%s'!", filepath);
		return NULL;
	}
	std::unique_ptr<shaderSrc> new_shader(new shaderSrc);

	size_t file_length;
	fseek(shader_stream, 0, SEEK_END);
	file_length = ftell(shader_stream);
	fseek(shader_stream, 0, SEEK_SET);

	new_shader->source = static_cast<char *>(malloc(file_length+1));
	if (new_shader->source) {
		fread(new_shader->source, file_length, 1, shader_stream);
		new_shader->source[file_length] = '\0';
	}
	fclose(shader_stream);

	new_shader->type = shadertype;
	return new_shader;
}

GLuint souputils::glhelpers::compileShader(GLuint type,
										   const char* source) {
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		char message[2048];
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		glGetShaderInfoLog(id, length, &length, message);
		glLogError("Failed to compile %s shader, FUCK! %s",
				(type == GL_VERTEX_SHADER ? "vertex" : "fragment"),
				message);
	}
	return id;
}

GLuint
souputils::glhelpers::compileShaderSrc(const shaderSrc* shader_src) {
	return compileShader(shader_src->type, shader_src->source);
}

void souputils::glhelpers::glLinkProgramSafe(GLuint program) {
	int result;
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		int max_length = 2048;
		int length = 0;
		char message[max_length];
		glGetProgramInfoLog(program, max_length, &length, message);
		glLogError("Failed to link shader program, SHIT!");
		glLogError("%s", message);
	}
}

template <typename vect_type, std::size_t vect_dimensions>
float* stack_flatten(vect_type* arr_vectors, float buffer[],
					 size_t size_arr) {
	size_t n_vectors = size_arr/sizeof(vect_type);
	for (unsigned int i = 0; i < n_vectors; i++) {
		for (unsigned int j = 0; j < vect_dimensions; j++) {
			buffer[(i*vect_dimensions)+j] = arr_vectors[i][j];
		}
	}
	return buffer;
}

template <typename vect_type, std::size_t vect_dimensions>
std::unique_ptr<float[]> heap_flatten(vect_type* arr_vectors,
									  size_t size_arr) {
	size_t n_vectors = size_arr/sizeof(vect_type);
	std::unique_ptr<float[]> buffer(new float[n_vectors*3]);
	for (unsigned int i = 0; i < n_vectors; i++) {
		for (unsigned int j = 0; j < vect_dimensions; j++) {
			buffer[(i*vect_dimensions)+j] = arr_vectors[i][j];
		}
	}
	return buffer;
}

float*
souputils::glhelpers::flatten(glm::vec2* arr_vectors, float buffer[],
							  size_t size_arr) {
	return stack_flatten<glm::vec2, 2>(arr_vectors, buffer, size_arr);
}

float*
souputils::glhelpers::flatten(glm::vec3* arr_vectors, float buffer[],
							  size_t size_arr) {
	return stack_flatten<glm::vec3, 3>(arr_vectors, buffer, size_arr);
}

float*
souputils::glhelpers::flatten(glm::vec4* arr_vectors, float buffer[],
							  size_t size_arr) {
	return stack_flatten<glm::vec4, 4>(arr_vectors, buffer, size_arr);
}

std::unique_ptr<float[]>
souputils::glhelpers::flatten(glm::vec2* arr_vectors, size_t size_arr) {
	return heap_flatten<glm::vec2, 2>(arr_vectors, size_arr);
}

std::unique_ptr<float[]>
souputils::glhelpers::flatten(glm::vec3* arr_vectors, size_t size_arr) {
	return heap_flatten<glm::vec3, 3>(arr_vectors, size_arr);
}

std::unique_ptr<float[]>
souputils::glhelpers::flatten(glm::vec4* arr_vectors, size_t size_arr) {
	return heap_flatten<glm::vec4, 4>(arr_vectors, size_arr);
}
