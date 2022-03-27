#pragma once

#include "material.h"

namespace Materials
{
    class Dielectric : public Material
    {
    public:
        Dielectric(double indexOfRefraction);
        virtual bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const override;

    private:
        static double Reflectance(double cosine, double ref_idx);

    private:
        double m_IndexOfRefraction;
    };
}