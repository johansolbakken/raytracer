//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_MIRROR_SCENE_H
#define RAYTRACER_MIRROR_SCENE_H

#include "scene.h"

namespace Scene
{
    class MirrorScene : public Scene
    {
    public:
        std::shared_ptr<Renderer::Camera> GetCamera() override
        {
            const auto aspect_ratio = 16.0 / 9.0;

            Point3 lookfrom(-3, 2, -3 );
            Point3 lookat(2, 2, 1);
            Vec3 vup(0, 1, 0);

            auto vfov = 20.0;
            auto aperture = 0.0;
            auto dist_to_focus = 10.0;


            return std::make_shared<Renderer::Camera>(lookfrom, lookat, vup, aspect_ratio, vfov, aperture,
                                                      dist_to_focus,
                                                      0.0, 1.0);
        }

        std::shared_ptr<Object::Hittable> GetWorld() override
        {
            Object::HittableList objects;

            auto checker = std::make_shared<texture::CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
            auto metal = std::make_shared<Materials::Metal>(Color(1,1,1), 0);
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(0, -1000, 0),
                    1000,
                    std::make_shared<Materials::Lambertian>(checker)
            )) ;
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(-3, 2, 0),
                    2,
                    metal)
            );
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(0, 2, 3),
                    2,
                    metal)
            );
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(3, 2, 0),
                    2,
                    metal)
            );
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(0, 2, -3 ),
                    2,
                    metal)
            );
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(1, 1, 1 ),
                    1,
                    std::make_shared<Materials::Lambertian>(Color(0.2, 0.3, 0.8)))
            );

            return std::make_shared<Object::HittableList>(objects);
        }
    };
}

#endif //RAYTRACER_MIRROR_SCENE_H
