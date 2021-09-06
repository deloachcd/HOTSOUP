#include <string>
#include <memory>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#ifndef GL_USER_HELPERS_H
#define GL_USER_HELPERS_H

#define N_VECTORS(vcollection, vtype) sizeof(vcollection)/sizeof(vtype)
#define N_VECT2(vcollection) N_VECTORS(vcollection, glm::vec2)
#define N_VECT3(vcollection) N_VECTORS(vcollection, glm::vec3)
#define N_VECT4(vcollection) N_VECTORS(vcollection, glm::vec4)
#define VECT2_BUFFERLEN(vcollection) N_VECTORS(vcollection, glm::vec2) * 2
#define VECT3_BUFFERLEN(vcollection) N_VECTORS(vcollection, glm::vec3) * 3
#define VECT4_BUFFERLEN(vcollection) N_VECTORS(vcollection, glm::vec4) * 4

//#define WIDESCREEN_SCALING_DIVISOR 0.5625f

namespace glhelpers {
    struct displayObjects {
        GLFWmonitor* monitor;
        const GLFWvidmode* vidmode;
    };
    struct shaderSrc {
        GLuint type;
        std::string source;
    };
    class SimpleTimer {
        private:
            double previous_seconds;
            double current_seconds;
            double elapsed_seconds;

        public:
            SimpleTimer();
            void update();
            double getElapsedSeconds();
    };

    extern float WIDESCREEN_SCALING_DIVISOR;

    /* convenience helpers */
    std::unique_ptr<displayObjects> getDisplayObjects();

    /* primary window and default framebuffer helpers */
    GLFWwindow* glfwCreatePrimaryWindow(int width, int height,
            const char* title, GLFWmonitor* monitor,
            GLFWwindow* share);
    void gl_link_program(GLuint program);
    void glfw_primary_window_size_callback(GLFWwindow* window, int width, int 
            height);
    void glfw_default_framebuffer_size_callback(GLFWwindow* window, int width,
            int height);
    int get_glfw_primary_window_width();
    int get_glfw_primary_window_height();
    int get_glfw_default_fb_width();
    int get_glfw_default_fb_height();
    
    /* shader program helpers */
    std::unique_ptr<shaderSrc> load_shader_file(GLuint shadertype, 
            const std::string filepath);
    GLuint compile_shader(GLuint type, const std::string& source);
    GLuint compile_shaderSrc(const shaderSrc* shader_src);
    void gl_link_program(GLuint program);
    
    /* buffer creation and loading helpers */
    typedef std::unique_ptr<float[]> ufloat_ptr;

    // flattening for small, stack-allocated arrays using GLM types
    float* flatten(glm::vec2* arr_vectors, float buffer[], size_t size_arr);
    float* flatten(glm::vec3* arr_vectors, float buffer[], size_t size_arr);
    float* flatten(glm::vec4* arr_vectors, float buffer[], size_t size_arr);
    float* flatten(glm::mat2 matrix, float buffer[]);
    float* flatten(glm::mat3 matrix, float buffer[]);
    float* flatten(glm::mat4 matrix, float buffer[]);

    // flattening for arrays on the heap
    std::unique_ptr<float[]> flatten(glm::vec2* arr_vectors, size_t size_arr);
    std::unique_ptr<float[]> flatten(glm::vec3* arr_vectors, size_t size_arr);
    std::unique_ptr<float[]> flatten(glm::vec4* arr_vectors, size_t size_arr);

    /* matrix helpers */
    glm::mat4 rot3d_matrix(int theta, char axis);

    /* misc helpers */
    void update_fps_counter (GLFWwindow* window);
}

#endif // GL_USER_HELPERS_H
