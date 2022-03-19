cmake_minimum_required(VERSION 3.13)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE src "src/**")

add_executable(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC src)