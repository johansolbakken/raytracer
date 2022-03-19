#pragma once
#include "material.h"

namespace Materials
{
    class Metal : public Material
    {
    public:
        Metal(const Color &albedo, double fuzz);
        virtual bool Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const override;

    private:
        static double Reflectance(double cosine, double ref_idx);

    private:
        Color m_Albedo;
        double m_Fuzz;
    };
}