//
// Created by Johan Solbakken on 25/03/2022.
//


#ifndef RAYTRACER_TWO_NOISE_SPHERES_SCENE_H
#define RAYTRACER_TWO_NOISE_SPHERES_SCENE_H

#include "scene.h"
#include "textures/noise_texture.h"
#include "materials/lambertian.h"

#include <memory>

namespace Scene
{
    class TwoNoiseSpheresScene : public Scene
    {
    public:
        TwoNoiseSpheresScene()
        {}

        ~TwoNoiseSpheresScene()
        {}

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

            std::shared_ptr<texture::Texture> noiseTexture = std::make_shared<texture::NoiseTexture>(4);
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(0, -1000, 0),
                    1000,
                    std::make_shared<Materials::Lambertian>(noiseTexture))
            );
            objects.Add(std::make_shared<Object::Sphere>(
                    Point3(0, 2, 0),
                    2,
                    std::make_shared<Materials::Lambertian>(noiseTexture))
            );

            return std::make_shared<Object::HittableList>(objects);
        }
    };
}

#endif //RAYTRACER_TWO_SPHERES_SCENE_H
