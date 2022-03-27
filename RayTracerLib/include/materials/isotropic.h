//
// Created by Johan Solbakken on 27/03/2022.
//

#ifndef RAYTRACER_ISOTROPIC_H
#define RAYTRACER_ISOTROPIC_H

#include "material.h"
#include "textures/texture.h"

namespace Materials
{
    class Isotropic : public Material
    {
    public:
        Isotropic(Color c);
        Isotropic(std::shared_ptr<texture::Texture> tex);

        bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const override;

    private:
        std::shared_ptr<texture::Texture> m_Albedo;
    };
}

#endif //RAYTRACER_ISOTROPIC_H
