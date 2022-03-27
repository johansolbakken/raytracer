//
// Created by Johan Solbakken on 25/03/2022.
//

#ifndef RAYTRACER_CHECKER_TEXTURE_H
#define RAYTRACER_CHECKER_TEXTURE_H

#include "texture.h"
#include "solid_color.h"

namespace texture
{
    class CheckerTexture : public Texture
    {
    public:
        CheckerTexture() {

        }
        CheckerTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd)
        : m_Odd(_odd), m_Even(_even)
        {

        }

        CheckerTexture(Color c1, Color c2) : m_Even(std::make_shared<SolidColor>(c1)), m_Odd
        (std::make_shared<SolidColor>(c2))
        {}

        Color Value(double u, double v, const Point3 &point) const override
        {
            auto sines = sin(10 * point.x()) * sin(10*point.y()) * sin(10*point.z());
            if (sines < 0)
                return m_Odd->Value(u, v, point);
            else
                return m_Even->Value(u, v, point);
        }

    private:
        std::shared_ptr<Texture> m_Even;
        std::shared_ptr<Texture> m_Odd;
    };
}

#endif //RAYTRACER_CHECKER_TEXTURE_H
