//
// Created by Johan Solbakken on 25/03/2022.
//

#ifndef RAYTRACER_NOISE_TEXTURE_H
#define RAYTRACER_NOISE_TEXTURE_H

#include "texture.h"
#include "perlin.h"

namespace texture
{
    class NoiseTexture : public Texture
    {
    public:
        NoiseTexture() = default;
        NoiseTexture(double scale) : m_Scale(scale) {}

        Color Value(double u, double v, const Point3 &point) const override
        {
            return Color(1,1,1) * 0.5 * (1.0 + sin(m_Scale * point.z() + 10 * m_Noise.Turb(  point)));
        }

    private:
        perlin::Perlin m_Noise;
        double m_Scale;
    };
}

#endif //RAYTRACER_NOISE_TEXTURE_H
