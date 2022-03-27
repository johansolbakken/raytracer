#include "materials/lambertian.h"

#include "objects/hittable.h"
#include "textures/solid_color.h"

namespace Materials
{
    Lambertian::Lambertian(const Color& albedo)
    : m_Albedo(std::make_shared<texture::SolidColor>(albedo))
    {

    }

    Lambertian::Lambertian(std::shared_ptr<texture::Texture> a)
    : m_Albedo(a)
    {

    }

    bool Lambertian::Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const 
    {
        auto scatter_direction = record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.NearZero())
            scatter_direction = record.normal;

        scattered = Ray(record.point, scatter_direction, inRay.Time());
        attenuation = m_Albedo->Value(record.u, record.v, record.point);
        return true;
    }


}