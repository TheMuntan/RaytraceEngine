cmake_minimum_required(VERSION 3.23)
project(RaytraceEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(RaytraceEngine main.cpp Coordinate.cpp Coordinate.h Ray.cpp Ray.h Objects/Object.cpp Objects/Object.h Objects/Sphere.cpp Objects/Sphere.h Objects/Cube.cpp Objects/Cube.h Objects/Plane.cpp Objects/Plane.h)
target_link_libraries(RaytraceEngine GL GLU glut)
