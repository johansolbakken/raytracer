//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_CORNELL_FOG_BOX_SCENE_H
#define RAYTRACER_CORNELL_FOG_BOX_SCENE_H

#include "scenes/scene.h"

#include "materials/lambertian.h"

#include "materials/diffuse_light.h"

#include "objects/BVHRect.h"

#include <objects/Box.h>

#include <objects/instance.h>

#include <objects/ConstantMedium.h>

namespace Scene
{
    class CornellFogScene : public Scene
    {
    public:
        Object::HittableList GetWorld() override
        {
            Object::HittableList objects;

            auto red   = std::make_shared<Materials::Lambertian>(Color(.65, .05, .05));
            auto white = std::make_shared<Materials::Lambertian>(Color(.73, .73, .73));
            auto green = std::make_shared<Materials::Lambertian>(Color(.12, .45, .15));
            auto light = std::make_shared<Materials::Light::DiffuseLight>(Color(7, 7, 7));

            objects.Add(std::make_shared<BVH::YZRect>(0, 555, 0, 555, 555, green));
            objects.Add(std::make_shared<BVH::YZRect>(0, 555, 0, 555, 0, red));
            objects.Add(std::make_shared<BVH::XZRect>(113, 443, 127, 432, 554, light));
            objects.Add(std::make_shared<BVH::XZRect>(0, 555, 0, 555, 555, white));
            objects.Add(std::make_shared<BVH::XZRect>(0, 555, 0, 555, 0, white));
            objects.Add(std::make_shared<BVH::XYRect>(0, 555, 0, 555, 555, white));

            std::shared_ptr<Object::Hittable> box1 = std::make_shared<Object::Box>(Point3(0,0,0), Point3(165,330,165)
                                                                                   , white);
            box1 = std::make_shared<Object::Instance::RotateY>(box1, 15);
            box1 = std::make_shared<Object::Instance::Translate>(box1, Vec3(265,0,295));

            std::shared_ptr<Object::Hittable> box2 = std::make_shared<Object::Box>(Point3(0,0,0), Point3(165,165,165)
                                                                                   , white);
            box2 = std::make_shared<Object::Instance::RotateY>(box2, -18);
            box2 = std::make_shared<Object::Instance::Translate>(box2, Vec3(130,0,65));

            objects.Add(std::make_shared<Object::ConstantMedium>(box1, 0.01, Color(0,0,0)));
            objects.Add(std::make_shared<Object::ConstantMedium>(box2, 0.01, Color(1,1,1)));

            return objects;
        }

        Renderer::Camera GetCamera() override
        {
            auto aspect_ratio = 1.0;
            auto background = Color(0,0,0);
            auto lookfrom = Point3(278, 278, -800);
            auto lookat = Point3(278, 278, 0);
            auto vfov = 40.0;

            return { lookfrom, lookat, {0,1,0}, aspect_ratio, vfov, 0.0, 1.0, background };
        }
    };
}

#endif //RAYTRACER_CORNELL_BOX_SCENE_H
