#include "lambertian.h"

#include "objects/hittable.h"

namespace Materials
{
    Lambertian::Lambertian(const Color& albedo)
    : m_Albedo(albedo)
    {

    }

    bool Lambertian::Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const 
    {
        auto scatter_direction = record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.NearZero())
            scatter_direction = record.normal;

        scattered = Ray(record.point, scatter_direction);
        attenuation = m_Albedo;
        return true;
    }
}