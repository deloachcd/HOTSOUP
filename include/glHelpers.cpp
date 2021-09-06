#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "glDebug.hpp"
#include "glHelpers.hpp"

#define PI 3.14159265

namespace glhelpers {
    float WIDESCREEN_SCALING_DIVISOR = 0.5625f;

    SimpleTimer::SimpleTimer() {
        this->previous_seconds = glfwGetTime();
        this->current_seconds = glfwGetTime();
        this->elapsed_seconds = this->current_seconds - this->previous_seconds;
        this->previous_seconds = this->current_seconds;
    }

    void SimpleTimer::update() {
        this->current_seconds = glfwGetTime();
        this->elapsed_seconds = this->current_seconds - this->previous_seconds;
        this->previous_seconds = this->current_seconds;
    }

    double SimpleTimer::getElapsedSeconds() {
        return this->elapsed_seconds;
    }

    static int primary_window_width;
    static int primary_window_height;
    static int default_fb_width;
    static int default_fb_height;
    static int pwin_frames;
    static double pwin_seconds_since_last_render;

    std::unique_ptr<displayObjects> getDisplayObjects() {
        std::unique_ptr<displayObjects> d(new displayObjects);
        d->monitor = glfwGetPrimaryMonitor();
        d->vidmode = glfwGetVideoMode(d->monitor);
        return d;
    }

    GLFWwindow* glfwCreatePrimaryWindow(int width, int height,
            const char* title, GLFWmonitor* monitor,
            GLFWwindow* share) {
        primary_window_width = width;
        primary_window_height = height;
        default_fb_width = width;
        default_fb_height = height;
        return glfwCreateWindow(width, height, title, monitor, share);
    }

    void glfw_primary_window_size_callback(GLFWwindow* window, int width,
            int height) {
        primary_window_width = width;
        primary_window_height = width;
    }

    void glfw_default_framebuffer_size_callback(GLFWwindow* window, int width, 
            int height) {
        default_fb_width = width;
        default_fb_height = height;
    }

    int get_glfw_primary_window_width() {
        return primary_window_width;
    }

    int get_glfw_primary_window_height() {
        return primary_window_height;
    }

    int get_glfw_default_fb_width() {
        return default_fb_width;
    }

    int get_glfw_default_fb_height() {
        return default_fb_height;
    }

    std::unique_ptr<shaderSrc> load_shader_file(GLuint shadertype, 
            const std::string filepath) {
        std::ifstream stream(filepath);
        std::stringstream shader_sstr;
        std::string line;
        while (getline(stream, line)) {
            shader_sstr << line << "\n";
        }

        std::unique_ptr<shaderSrc> new_shader(new shaderSrc);
        new_shader->source = shader_sstr.str();
        new_shader->type = shadertype;
        return new_shader;
    }

    GLuint compile_shader(GLuint type, const std::string& source) {
        GLuint id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            char message[2048];
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            glGetShaderInfoLog(id, length, &length, message);
            GL_LOG_ERROR() << "Failed to compile "
                << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                << " shader, FUCK!";
            GL_LOG_ERROR() << message;
        }
        return id;
    }

    GLuint compile_shaderSrc(const shaderSrc* shader_src) {
        return compile_shader(shader_src->type, shader_src->source);
    }

    void gl_link_program(GLuint program) {
        int result;
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE) {
            int max_length = 2048;
            int length = 0;
            char message[max_length];
            glGetProgramInfoLog(program, max_length, &length, message);
            GL_LOG_ERROR() << "Failed to link shader program, SHIT!";
            GL_LOG_ERROR() << message;
        }
    }

    float* flatten(glm::vec2* arr_vectors, float buffer[], size_t size_arr) {
        size_t n_vectors = size_arr/sizeof(glm::vec2);
        for (unsigned int i = 0; i < n_vectors; i++) {
            buffer[i*2] = arr_vectors[i][0];
            buffer[(i*2)+1] = arr_vectors[i][1];
        }
        return buffer;
    }

    float* flatten(glm::vec3* arr_vectors, float buffer[], size_t size_arr) {
        size_t n_vectors = size_arr/sizeof(glm::vec3);
        for (unsigned int i = 0; i < n_vectors; i++) {
            buffer[i*3] = arr_vectors[i][0];
            buffer[(i*3)+1] = arr_vectors[i][1];
            buffer[(i*3)+2] = arr_vectors[i][2];
        }
        return buffer;
    }

    float* flatten(glm::vec4* arr_vectors, float buffer[], size_t size_arr) {
        size_t n_vectors = size_arr/sizeof(glm::vec4);
        for (unsigned int i = 0; i < n_vectors; i++) {
            buffer[i*4] = arr_vectors[i][0];
            buffer[(i*4)+1] = arr_vectors[i][1];
            buffer[(i*4)+2] = arr_vectors[i][2];
            buffer[(i*4)+3] = arr_vectors[i][3];
        }
        return buffer;
    }

    std::unique_ptr<float[]> flatten(glm::vec2* arr_vectors, size_t size_arr) {
        size_t n_vectors = size_arr/sizeof(glm::vec2);
        std::unique_ptr<float[]> buffer (new float[n_vectors*2]);
        for (unsigned int i = 0; i < n_vectors; i++) {
            buffer[i*2] = arr_vectors[i][0];
            buffer[(i*2)+1] = arr_vectors[i][1];
        }
        return buffer;
    }

    std::unique_ptr<float[]> flatten(glm::vec3* arr_vectors, size_t size_arr) {
        size_t n_vectors = size_arr/sizeof(glm::vec3);
        std::unique_ptr<float[]> buffer (new float[n_vectors*3]);
        for (unsigned int i = 0; i < n_vectors; i++) {
            buffer[i*3] = arr_vectors[i][0];
            buffer[(i*3)+1] = arr_vectors[i][1];
            buffer[(i*3)+2] = arr_vectors[i][2];
        }
        return buffer;
    }

    std::unique_ptr<float[]> flatten(glm::vec4* arr_vectors, size_t size_arr) {
        size_t n_vectors = size_arr/sizeof(glm::vec4);
        std::unique_ptr<float[]> buffer (new float[n_vectors*4]);
        for (unsigned int i = 0; i < n_vectors; i++) {
            buffer[i*4] = arr_vectors[i][0];
            buffer[(i*4)+1] = arr_vectors[i][1];
            buffer[(i*4)+2] = arr_vectors[i][2];
            buffer[(i*4)+3] = arr_vectors[i][3];
        }
        return buffer;
    }

    glm::mat4 rot3d_matrix(int theta, char axis) {
        double r = theta*PI/180;
        if (axis == 'x') {
            return glm::mat4(1.0f,    0.0f,    0.0f, 0.0f,
                             0.0f,  cos(r),  sin(r), 0.0f,
                             0.0f, -sin(r),  cos(r), 0.0f,
                             0.0f,    0.0f,    0.0f, 1.0f);
        } else if (axis == 'y') {
            return glm::mat4(cos(r), 0.0f, -sin(r), 0.0f,
                               0.0f, 1.0f,    0.0f, 0.0f,
                             sin(r), 0.0f,  cos(r), 0.0f,
                               0.0f, 0.0f,    0.0f, 1.0f);
        } else if (axis == 'z') {
            return glm::mat4( cos(r), sin(r), 0.0f, 0.0f,
                             -sin(r), cos(r), 0.0f, 0.0f,
                                0.0f,   0.0f, 1.0f, 0.0f,
                                0.0f,   0.0f, 0.0f, 1.0f);
        }
        // you shouldn't ever get here, so just return the identity matrix
        return glm::mat4(1.0f);
    }

    void update_fps_counter (GLFWwindow* window) {
        double current_seconds;
        double elapsed_seconds;
        current_seconds = glfwGetTime();
        elapsed_seconds = current_seconds - pwin_seconds_since_last_render;
        /* limit text updates to 4 per second */
        if (elapsed_seconds > 0.25) {
            pwin_seconds_since_last_render = current_seconds;
            char tmp[128];
            double fps = (double)pwin_frames / elapsed_seconds;
            sprintf (tmp, "opengl @ fps: %.2f", fps);glfwSetWindowTitle (window, tmp);
            pwin_frames = 0;
        }
        pwin_frames++;
    }
}
