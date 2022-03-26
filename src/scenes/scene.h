#pragma once

#include "objects/hittable.h"
#include "renderer/camera.h"

#include <memory>

namespace Scene
{
    class Scene
    {
    public:
        Scene() {}
        virtual ~Scene() {};
        virtual std::shared_ptr<Object::Hittable> GetWorld() = 0;
        virtual std::shared_ptr<Renderer::Camera> GetCamera() = 0;
    };
}