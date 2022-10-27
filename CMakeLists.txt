cmake_minimum_required(VERSION 3.23)
project(RaytraceEngine)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(RaytraceEngine main.cpp Coordinate.cpp Coordinate.h Ray.cpp Ray.h Objects/Object.cpp Objects/Object.h Objects/Sphere.cpp Objects/Sphere.h Objects/Cube.cpp Objects/Cube.h)
target_link_libraries(RaytraceEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
