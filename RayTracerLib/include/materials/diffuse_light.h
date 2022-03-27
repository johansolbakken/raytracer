//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_DIFFUSE_LIGHT_H
#define RAYTRACER_DIFFUSE_LIGHT_H

#include "material.h"
#include "textures/texture.h"

namespace Materials::Light
{
    class DiffuseLight : public Material
    {
    public:
        DiffuseLight(std::shared_ptr<texture::Texture> albedo);
        DiffuseLight(Color color);

        bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const override;
        Color Emitted(double u, double v, const Point3 &point) const override;

    private:
        std::shared_ptr<texture::Texture> m_Emit;
    };
}

#endif //RAYTRACER_DIFFUSE_LIGHT_H
