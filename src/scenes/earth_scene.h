//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_EARTH_SCENE_H
#define RAYTRACER_EARTH_SCENE_H

#include "scene.h"
#include "textures/image_texture.h"

namespace Scene
{
    class EarthScene : public Scene
    {
    public:
        std::shared_ptr<Renderer::Camera> GetCamera() override
        {
            const auto aspect_ratio = 16.0 / 9.0;

            Point3 lookfrom(13, 2, 3);
            Point3 lookat(0, 0, 0);
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

            auto earth_texture = std::make_shared<texture::ImageTexture>("../res/images/earthmap.jpg");
            auto earth_surface = std::make_shared<Materials::Lambertian>(earth_texture);
            auto globe = std::make_shared<Object::Sphere>(Point3(0,0,0), 2, earth_surface);
            objects.Add(globe);

            return std::make_shared<Object::HittableList>(objects);
        }
    };
}

#endif //RAYTRACER_EARTH_SCENE_H
