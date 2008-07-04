cmake_minimum_required(VERSION 2.4)
project(hanoigl C)

add_executable(hanoigl main.c hanoi.c stack.c objects.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
set(libs ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

target_link_libraries(hanoigl ${libs})
