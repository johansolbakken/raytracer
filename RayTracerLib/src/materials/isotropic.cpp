//
// Created by Johan Solbakken on 27/03/2022.
//

#include "materials/isotropic.h"
#include "common/core.h"
#include "textures/solid_color.h"
#include "objects/hittable.h"

namespace Materials
{
    Isotropic::Isotropic(Color c)
    : m_Albedo(std::make_shared<texture::SolidColor>(c))
    {}

    Isotropic::Isotropic(std::shared_ptr<texture::Texture> tex)
    :m_Albedo(tex)
    {}

    bool Isotropic::Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const
    {
        scattered = Ray(record.point, random_in_unit_sphere(), inRay.Time());
        attenuation = m_Albedo->Value(record.u, record.v, record.point);
        return true;
    }

}