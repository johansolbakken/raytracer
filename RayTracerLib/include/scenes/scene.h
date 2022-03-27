#pragma once

#include "../objects/hittable.h"
#include "../objects/hittablelist.h"
#include "../renderer/camera.h"

namespace Scene
{
    class Scene
    {
    public:
        Scene() {}
        virtual ~Scene() {};
        virtual Object::HittableList GetWorld() = 0;
        virtual Renderer::Camera GetCamera() = 0;
    };
}