//
// Created by Johan Solbakken on 25/03/2022.
//


#ifndef RAYTRACER_TWO_NOISE_SPHERES_SCENE_H
#define RAYTRACER_TWO_NOISE_SPHERES_SCENE_H

#include "scenes/scene.h"
#include "textures/noise_texture.h"
#include "materials/lambertian.h"
#include "materials/diffuse_light.h"

#include "objects/BVHRect.h"
#include "objects/sphere.h"

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

        Renderer::Camera GetCamera() override
        {
            const auto aspect_ratio = 16.0 / 9.0;

            Point3 lookfrom(26, 3, 6);
            Point3 lookat(0, 2, 0);
            Vec3 vup(0, 1, 0);

            auto vfov = 20.0;
            auto aperture = 0.0;
            auto dist_to_focus = 10.0;


            return {lookfrom, lookat, vup, aspect_ratio, vfov, aperture,
                                                      dist_to_focus, Color(0, 0, 0),
                                                      0.0, 1.0};
        }

        Object::HittableList GetWorld() override
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

            auto difflight = std::make_shared<Materials::Light::DiffuseLight>(Color(4, 4, 4));
            objects.Add(std::make_shared<BVH::XYRect>(3, 5, 1, 3, -2, difflight));

            return objects;
        }
    };
}

#endif //RAYTRACER_TWO_SPHERES_SCENE_H
