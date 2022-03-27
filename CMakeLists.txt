cmake_minimum_required(VERSION 3.2.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(raytracer)

add_subdirectory(RayTracerLib)
add_subdirectory(RayTracerApp)