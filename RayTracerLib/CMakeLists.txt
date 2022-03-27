#
#   Ray tracer library
#
add_library(RayTracerLib STATIC
        src/materials/dielectric.cpp
        src/materials/lambertian.cpp
        src/materials/metal.cpp
        src/materials/isotropic.cpp
        src/materials/diffuse_light.cpp

        src/concurrency/semaphore.cpp
        src/concurrency/threadpool.cpp

        src/objects/Box.cpp
        src/objects/instance.cpp
        src/objects/BVHNode.cpp
        src/objects/BVHRect.cpp
        src/objects/hittablelist.cpp
        src/objects/moving_sphere.cpp
        src/objects/sphere.cpp
        src/objects/ConstantMedium.cpp

        src/renderer/camera.cpp
        src/renderer/ray.cpp
        src/renderer/renderer.cpp

        src/textures/image_texture.cpp
        )

target_include_directories(RayTracerLib PUBLIC include)
include_directories(RayTracerLib PUBLIC vendor)

