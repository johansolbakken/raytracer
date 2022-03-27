#pragma once

#include "material.h"
#include "textures/texture.h"

namespace Materials
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const Color& albedo);
        Lambertian(std::shared_ptr<texture::Texture> albedo);
        virtual bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const override;
        
    private:
        std::shared_ptr<texture::Texture> m_Albedo;
    };

}