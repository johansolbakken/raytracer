//
// Created by Johan Solbakken on 25/03/2022.
//

#ifndef RAYTRACER_SOLID_COLOR_H
#define RAYTRACER_SOLID_COLOR_H

#include "texture.h"

namespace texture
{
    class SolidColor : public Texture
    {
    public:
        SolidColor() {}
        SolidColor(Color c) : m_ColorValue(c) {}
        SolidColor(double red, double green, double blue) : m_ColorValue(red, green, blue) {}

        Color Value(double u, double v, const Point3 &point) const override
        {
            return m_ColorValue;
        }

    private:
        Color m_ColorValue;

    };
}

#endif //RAYTRACER_SOLID_COLOR_H
