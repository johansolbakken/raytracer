//
// Created by Johan Solbakken on 27/03/2022.
//

#include "materials/diffuse_light.h"
#include "textures/solid_color.h"

namespace Materials::Light
{
    DiffuseLight::DiffuseLight(std::shared_ptr<texture::Texture> albedo)
            : m_Emit(albedo)
    {}

    DiffuseLight::DiffuseLight(Color color)
            : m_Emit(std::make_shared<texture::SolidColor>(color))
    {}

    bool DiffuseLight::Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const
    {
        return false;
    }

    Color DiffuseLight::Emitted(double u, double v, const Point3 &point) const
    {
        return m_Emit->Value(u, v, point);
    }
}
