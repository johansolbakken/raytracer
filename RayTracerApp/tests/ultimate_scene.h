//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef ULTIMATE_SCENE
#define ULTIMATE_SCENE

#include "scenes/scene.h"

#include <materials/isotropic.h>
#include <materials/diffuse_light.h>
#include <materials/metal.h>
#include <materials/lambertian.h>
#include <materials/dielectric.h>

#include <textures/noise_texture.h>
#include <textures/image_texture.h>

#include <objects/BVHNode.h>
#include <objects/BVHRect.h>
#include <objects/Box.h>
#include <objects/instance.h>
#include <objects/ConstantMedium.h>
#include <objects/moving_sphere.h>
#include <objects/sphere.h>
#include <objects/instance.h>


namespace Scene
{
    class UltimateScene : public Scene
    {
    public:
        Object::HittableList GetWorld() override
        {
            // GROUND
            Object::HittableList boxes1;
            auto ground = std::make_shared<Materials::Lambertian>(Color(0.48, 0.83, 0.53));

            const int boxes_per_side = 20;
            for (int i = 0; i < boxes_per_side; i++) {
                for (int j = 0; j < boxes_per_side; j++) {
                    auto w = 100.0;
                    auto x0 = -1000.0 + i * w;
                    auto z0 = -1000.0 + j * w;
                    auto y0 = 0.0;
                    auto x1 = x0 + w;
                    auto y1 = random_double(1, 101);
                    auto z1 = z0 + w;

                    boxes1.Add(std::make_shared<Object::Box>(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
                }
            }

            Object::HittableList objects;

            objects.Add(std::make_shared<BVH::BVHNode>(boxes1, 0, 1));
/*
            objects.Add(std::make_shared<Object::Box>(
                    Point3(0, 0, 0), Point3(100, 100, 100), ground
                    ));
*/
            // LIGHT
            auto light = std::make_shared<Materials::Light::DiffuseLight>(Color(7, 7, 7));
            objects.Add(std::make_shared<BVH::XZRect>(123, 423, 147, 412, 554, light));
/*
            // Moving Sphere
            auto center1 = Point3(400, 400, 200);
            auto center2 = center1 + Vec3(30, 0, 0);
            auto moving_sphere_material = std::make_shared<Materials::Lambertian>(Color(0.7, 0.3, 0.1));
            objects.Add(std::make_shared<Object::MovingSphere>(center1, center2, 0, 1, 50, moving_sphere_material));

            // DIELECTRIC
            objects.Add(std::make_shared<Object::Sphere>(Point3(260, 150, 45), 50,
                                                         std::make_shared<Materials::Dielectric>(1.5)));

            // METAL
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(0, 150, 145), 50, std::make_shared<Materials::Metal>(Color(0.8, 0.8, 0.9), 1.0)
            ));


            auto boundary = std::make_shared<Object::Sphere>(Point3(360, 150, 145), 70,
                                                             std::make_shared<Materials::Dielectric>(1.5));
            objects.Add(boundary);
            objects.Add(std::make_shared<Object::ConstantMedium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
            boundary = std::make_shared<Object::Sphere>(Point3(0, 0, 0), 5000,
                                                        std::make_shared<Materials::Dielectric>(1.5));
            objects.Add(std::make_shared<Object::ConstantMedium>(boundary, .0001, Color(1, 1, 1)));

            auto emat = std::make_shared<Materials::Lambertian>(std::make_shared<texture::ImageTexture>("/Users/johansolbakken/Developer/raytracer/RayTracerApp/res/images/earthmap.jpg"));
            objects.Add(std::make_shared<Object::Sphere>(Point3(400, 200, 400), 100, emat));
            auto pertext = std::make_shared<texture::NoiseTexture>(0.1);
            objects.Add(std::make_shared<Object::Sphere>(Point3(220, 280, 300), 80,
                                                         std::make_shared<Materials::Lambertian>(pertext)));


            Object::HittableList boxes2;
            auto white = std::make_shared<Materials::Lambertian>(Color(.73, .73, .73));
            int ns = 1000;
            for (int j = 0; j < ns; j++) {
                boxes2.Add(std::make_shared<Object::Sphere>(Point3::Random(0, 165), 10, white));
            }

            objects.Add(std::make_shared<Object::Instance::Translate>(
                                std::make_shared<Object::Instance::RotateY>(
                                        std::make_shared<BVH::BVHNode>(boxes2, 0.0, 1.0), 15),
                                Vec3(-100, 270, 395)
                        )
            );
*/
            return objects;
        }

        Renderer::Camera GetCamera() override
        {
            auto aspect_ratio = 1.0;
            auto background = Color(0, 0, 0);
            auto lookfrom = Point3(478, 278, -600);
            auto lookat = Point3(278, 278, 0);
            auto vfov = 40.0;

            return {lookfrom, lookat, {0, 1, 0}, aspect_ratio, vfov, 0.0, 1.0, background};
        }
    };
}

#endif //RAYTRACER_CORNELL_BOX_SCENE_H
