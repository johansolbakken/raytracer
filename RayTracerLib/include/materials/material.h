#pragma once

#include "common/core.h"

struct hit_record;

namespace Materials
{
    class Material
    {
    public:
        virtual Color Emitted(double u, double v, const Point3 &point) const
        { return {0, 0, 0}; }

        virtual bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const = 0;
    };
}