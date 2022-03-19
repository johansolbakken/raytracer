#pragma once

#include "common/core.h"

struct hit_record;

namespace Materials
{
    class Material
    {
    public:
        virtual bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const = 0;
    };
}