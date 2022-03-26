//
// Created by Johan Solbakken on 25/03/2022.
//

#include "scene.h"

#ifndef RAYTRACER_TWO_SPHERES_SCENE_H
#define RAYTRACER_TWO_SPHERES_SCENE_H

namespace Scene
{
    class TwoSpheresScene : public Scene
    {
    public:
        TwoSpheresScene()
        {}

        ~TwoSpheresScene()
        {}

        std::shared_ptr<Renderer::Camera> GetCamera() override
        {
            const auto aspect_ratio = 16.0 / 9.0;

            Point3 lookfrom(13, 2, 3);
            Point3 lookat(0, 0, 0);
            Vec3 vup(0, 1, 0);

            auto vfov = 40.0;
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
            objects.Add(std::make_shared<Object::Sphere>(Point3(0, -10, 0), 10, std::make_shared<Materials::Lambertian>
                    (checker)));
            objects.Add(std::make_shared<Object::Sphere>(Point3(0, 10, 0), 10, std::make_shared<Materials::Lambertian>
                    (checker)));

            return std::make_shared<Object::HittableList>(objects);
        }
    };
}

#endif //RAYTRACER_TWO_SPHERES_SCENE_H
