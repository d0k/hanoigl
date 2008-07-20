cmake_minimum_required(VERSION 2.4)
project(hanoigl C)

add_executable(hanoigl main.c hanoi.c stack.c objects.c)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW libglfw)
if(NOT GLFW_FOUND)
  find_path(GLFW_INCLUDE_DIRS GL/glfw.h PATHS /usr/include /usr/local/include /opt/local/include C:/glfw/include)
  find_library(GLFW_LIBRARIES glfw PATHS /usr/lib /usr/local/lib /opt/local/lib C:/glfw/lib)
endif(NOT GLFW_FOUND)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS}) # blame CMake if this doesn't work
set(libs ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})

# WTF doesn't pkg-config find the frameworks
if(UNIX AND APPLE)
	find_library(AGL_FRAMEWORK AGL)
	find_library(CARBON_FRAMEWORK Carbon)
	set(libs ${libs} ${AGL_FRAMEWORK} ${CARBON_FRAMEWORK})
endif(UNIX AND APPLE)

target_link_libraries(hanoigl ${libs})
