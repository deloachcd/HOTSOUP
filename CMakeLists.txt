CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(project)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

CMAKE_POLICY(SET CMP0072 NEW)  # use GLVND over legacy OpenGL
FIND_PACKAGE(OpenGL REQUIRED)

INCLUDE_DIRECTORIES(deps)
ADD_SUBDIRECTORY(deps/glfw)
ADD_SUBDIRECTORY(deps/glm)
INCLUDE_DIRECTORIES(deps/gl3w/include)
ADD_LIBRARY(gl3w STATIC deps/gl3w/src/gl3w.c deps/gl3w/include/GL/gl3w.h)

ADD_LIBRARY(stb_image STATIC deps/stb/stb_image.h include/stb/stb_image.c)
SET_TARGET_PROPERTIES(stb_image PROPERTIES LINKER_LANGUAGE C)

# Linking in my own mini-libraries
ADD_LIBRARY(gldebug STATIC include/glDebug.cpp include/glDebug.hpp)
ADD_LIBRARY(glhelpers STATIC include/glHelpers.cpp include/glHelpers.hpp)
#ADD_LIBRARY(soupdebug STATIC
#  include/souputils/glDebug.hpp
#  include/souputils/glDebug.cpp
#  )
#ADD_LIBRARY(soupglhelpers STATIC
#  include/souputils/glHelpers.hpp
#  include/souputils/glHelpers.cpp
#  )
#ADD_LIBRARY(soupglfwhelpers STATIC
#  include/souputils/glfwHelpers.hpp
#  include/souputils/glfwHelpers.cpp
#  )
#ADD_LIBRARY(soupconvenience STATIC
#  include/souputils/convenience.hpp
#  include/souputils/convenience.cpp
#  )
ADD_LIBRARY(souputils STATIC
  include/souputils/glDebug.hpp
  include/souputils/glDebug.cpp
  include/souputils/glHelpers.hpp
  include/souputils/glHelpers.cpp
  include/souputils/glfwHelpers.hpp
  include/souputils/glfwHelpers.cpp
  include/souputils/convenience.hpp
  include/souputils/convenience.cpp
  )

TARGET_LINK_LIBRARIES(glhelpers glfw)
TARGET_LINK_LIBRARIES(glhelpers glm)

TARGET_LINK_LIBRARIES(souputils gl3w)
TARGET_LINK_LIBRARIES(souputils glfw)
TARGET_LINK_LIBRARIES(souputils glm)
TARGET_LINK_LIBRARIES(souputils OpenGL::GL)

ADD_COMPILE_OPTIONS(
  # Warning options
  -Wall -Wextra -pedantic -Wshadow -Wparentheses -Wreturn-type -Wmissing-braces
  -Wmultiple-inheritance -Wvirtual-inheritance -Wsign-conversion
  # Language feature limiting
  -fno-exceptions -fno-rtti -fno-implicit-templates -fconstexpr-depth=1 -fno-common
  )

ADD_SUBDIRECTORY(stove/burner)
