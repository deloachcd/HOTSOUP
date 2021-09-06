#include <functional>

#include <GLFW/glfw3.h>

#include "include/glDebug.hpp"

namespace glwin {
    class contextWindow {
        public:
            contextWindow(int width, int height, const char* title,
                GLFWmonitor* monitor, bool fullscreen);
            int getWinWidth();
            int getWinHeight();
            int getFbWidth();
            int getFbHeight();
            void windowSizeCallback(GLFWwindow* w, int width, int height);
            void framebufferSizeCallback(GLFWwindow* w, int width, int height);

        private:
            int win_width;
            int win_height;
            int fb_width;
            int fb_height;
            GLFWwindow* glfw_window;
            GLFWmonitor* display;
    };

    contextWindow::contextWindow(int width, int height, const char* title,
            GLFWmonitor* monitor, bool fullscreen) {
        this->win_width = width;
        this->fb_width = width;
        this->win_height = height;
        this->fb_height = height;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (fullscreen) {
            this->glfw_window = glfwCreateWindow(this->win_width, this->win_height, "Sanity check", monitor, NULL);
        } else {
            this->glfw_window = glfwCreateWindow(this->win_width, this->win_height, "Sanity check", NULL, NULL);
        }

        if (!this->glfw_window) {
            GL_LOG_ERROR() << "ERROR: could not open window with GLFW3";
            glfwTerminate();
        }
        /* TODO: figure out how to implement callbacks properly
         * so that this class definition is actually functional
         */
        /* glfwSetWindowSizeCallback(this->glfw_window, */ 
        /*         this->windowSizeCallback); */
        /* glfwSetFramebufferSizeCallback(this->glfw_window, */ 
        /*         this->framebufferSizeCallback); */

        glfwMakeContextCurrent(this->glfw_window);
    }

    int contextWindow::getWinWidth() {
        return this->win_width;
    }

    int contextWindow::getWinHeight() {
        return this->win_height;
    }

    int contextWindow::getFbWidth() {
        return this->fb_width;
    }

    int contextWindow::getFbHeight() {
        return this->fb_height;
    }

    void contextWindow::windowSizeCallback(GLFWwindow* w, int width, int height) {
        this->win_width = width;
        this->win_height = height;
    }

    void contextWindow::framebufferSizeCallback(GLFWwindow* w, int width, 
            int height) {
        this->fb_width = width;
        this->fb_height = height;
    }

    class glWin {
        public:
            glWin(int width, int height, const char* title,
                GLFWmonitor* monitor, GLFWwindow* share);
            GLFWwindow* getGlfwWindow();
            int getWinWidth();
            int getWinHeight();
            int getFbWidth();
            int getFbHeight();
            void setWinSizeParams(int width, int height);
            void setFbSizeParams(int width, int height);

        private:
            int win_width;
            int win_height;
            int fb_width;
            int fb_height;
            std::string title;
            GLFWwindow* glfw_window;
            GLFWmonitor* display;
    };

    glWin::glWin(int width, int height, const char* title,
                    GLFWmonitor* monitor, GLFWwindow* share) {
        this->win_width = width;
        this->fb_width = width;
        this->win_height = height;
        this->fb_height = height;
        this->title = title;

        this->glfw_window = glfwCreateWindow(
                this->win_width,
                this->win_height,
                title,
                monitor,
                share
            );

        if (!this->glfw_window) {
            GL_LOG_ERROR() << "ERROR: could not open window with GLFW3";
            glfwTerminate();
        }
    }

    GLFWwindow* glWin::getGlfwWindow() {
        return this->glfw_window;
    }

    int glWin::getWinWidth() {
        return this->win_width;
    }

    int glWin::getWinHeight() {
        return this->win_height;
    }

    int glWin::getFbWidth() {
        return this->fb_width;
    }

    int glWin::getFbHeight() {
        return this->fb_height;
    }

    void glWin::setWinSizeParams(int width, int height) {
        this->win_width = width;
        this->win_height = height;
    }

    void glWin::setFbSizeParams(int width, int height) {
        this->fb_width = width;
        this->fb_height = height;
    }
}
