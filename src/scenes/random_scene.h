#pragma once
#include "scene.h"

#include "objects/hittablelist.h"
#include "objects/sphere.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"

#include <memory>

namespace Scene
{
    class RandomScene : public Scene
    {
    public:
        RandomScene() {}

        virtual ~RandomScene() override {} 

        inline virtual std::shared_ptr<Object::Hittable> GetWorld() override
        {
            auto world = std::make_shared<Object::HittableList>();

            auto ground_material = std::make_shared<Materials::Lambertian>(Color(0.5, 0.5, 0.5));
            world->Add(std::make_shared<Object::Sphere>(Point3(0, -1000, 0), 1000, ground_material));

            for (int a = -11; a < 11; a++)
            {
                for (int b = -11; b < 11; b++)
                {
                    auto choose_mat = random_double();
                    Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                    if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
                    {
                        std::shared_ptr<Materials::Material> sphere_material;

                        if (choose_mat < 0.8)
                        {
                            // diffuse
                            auto albedo = Color::Random() * Color::Random();
                            sphere_material = std::make_shared<Materials::Lambertian>(albedo);
                            world->Add(std::make_shared<Object::Sphere>(center, 0.2, sphere_material));
                        }
                        else if (choose_mat < 0.95)
                        {
                            // metal
                            auto albedo = Color::Random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
                            sphere_material = std::make_shared<Materials::Metal>(albedo, fuzz);
                            world->Add(std::make_shared<Object::Sphere>(center, 0.2, sphere_material));
                        }
                        else
                        {
                            // glass
                            sphere_material = std::make_shared<Materials::Dielectric>(1.5);
                            world->Add(std::make_shared<Object::Sphere>(center, 0.2, sphere_material));
                        }
                    }
                }
            }

            auto material1 = std::make_shared<Materials::Dielectric>(1.5);
            world->Add(std::make_shared<Object::Sphere>(Point3(0, 1, 0), 1.0, material1));

            auto material2 = std::make_shared<Materials::Lambertian>(Color(0.4, 0.2, 0.1));
            world->Add(std::make_shared<Object::Sphere>(Point3(-4, 1, 0), 1.0, material2));

            auto material3 = std::make_shared<Materials::Metal>(Color(0.7, 0.6, 0.5), 0.0);
            world->Add(std::make_shared<Object::Sphere>(Point3(4, 1, 0), 1.0, material3));

            return world;
        }
    };
}