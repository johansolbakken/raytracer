cmake_minimum_required(VERSION 3.13)


project(RayTracerApp VERSION 1.0)



add_executable(RayTracerApp src/main.cpp)

# Ray tracer library
target_link_libraries(RayTracerApp PUBLIC RayTracerLib)
target_link_directories(RayTracerApp PUBLIC ../RayTracerLib)
target_include_directories(RayTracerApp PUBLIC ../RayTracerLib/include)