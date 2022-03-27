#pragma once

#include "scenes/scene.h"

#include "objects/hittablelist.h"
#include "objects/sphere.h"
#include "objects/moving_sphere.h"

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"

#include "textures/checker_texture.h"

#include <memory>

namespace Scene
{
    class RandomScene : public Scene
    {
    public:
        RandomScene()
        {}

        virtual ~RandomScene() override
        {}

        inline virtual Object::HittableList GetWorld() override
        {
            Object::HittableList world;

            auto checker = std::make_shared<texture::CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
            world.Add(
                    std::make_shared<Object::Sphere>(
                            Point3(0, -1000, 0),
                            1000,
                            std::make_shared<Materials::Lambertian>(checker)
                    )
            );

            for (int a = -11; a < 11; a++) {
                for (int b = -11; b < 11; b++) {
                    auto choose_mat = random_double();
                    Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                    if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                        std::shared_ptr<Materials::Material> sphere_material;

                        if (choose_mat < 0.8) {
                            // diffuse
                            auto albedo = Color::Random() * Color::Random();
                            sphere_material = std::make_shared<Materials::Lambertian>(albedo);
                            //world->Add(std::make_shared<Object::Sphere>(center, 0.2, sphere_material));
                            auto center2 = center + Vec3(0, random_double(0, .5), 0);
                            world.Add(std::make_shared<Object::MovingSphere>(center, center2, 0.0, 1.0, 0.2,
                                                                              sphere_material));
                        } else if (choose_mat < 0.95) {
                            // metal
                            auto albedo = Color::Random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
                            sphere_material = std::make_shared<Materials::Metal>(albedo, fuzz);
                            world.Add(std::make_shared<Object::Sphere>(center, 0.2, sphere_material));
                        } else {
                            // glass
                            sphere_material = std::make_shared<Materials::Dielectric>(1.5);
                            world.Add(std::make_shared<Object::Sphere>(center, 0.2, sphere_material));
                        }
                    }
                }
            }

            auto material1 = std::make_shared<Materials::Dielectric>(1.5);
            world.Add(std::make_shared<Object::Sphere>(Point3(0, 1, 0), 1.0, material1));

            auto material2 = std::make_shared<Materials::Lambertian>(Color(0.4, 0.2, 0.1));
            world.Add(std::make_shared<Object::Sphere>(Point3(-4, 1, 0), 1.0, material2));

            auto material3 = std::make_shared<Materials::Metal>(Color(0.7, 0.6, 0.5), 0.0);
            world.Add(std::make_shared<Object::Sphere>(Point3(4, 1, 0), 1.0, material3));

            return world;
        }

        Renderer::Camera GetCamera() override
        {
            const auto aspect_ratio = 16.0 / 9.0;

            Point3 lookfrom(13, 2, 3);
            Point3 lookat(0, 0, 0);
            Vec3 vup(0, 1, 0);
            auto dist_to_focus = 10.0;
            auto aperture = 0.1;

            return {lookfrom, lookat, vup, aspect_ratio, 20, aperture,
                                                      dist_to_focus, Color(0.70, 0.80, 1.00)};
        }
    };
}