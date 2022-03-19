#pragma once

#include "material.h"

namespace Materials
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const Color& albedo);
        virtual bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const override;
        
    private:
        Color m_Albedo;
    };

}