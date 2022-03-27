//
// Created by Johan Solbakken on 25/03/2022.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H

#include "common/core.h"

namespace texture
{
    class Texture
    {
    public:
        virtual Color Value(double u, double v, const Point3& point) const = 0;
    };
};

#endif //RAYTRACER_TEXTURE_H
