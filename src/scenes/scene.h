#pragma once

#include "objects/hittable.h"
#include <memory>

namespace Scene
{
    class Scene
    {
    public:
        Scene() {}
        virtual ~Scene() {};
        virtual std::shared_ptr<Object::Hittable> GetWorld() = 0;
    };
}