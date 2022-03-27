#include "materials/metal.h"

#include "objects/hittable.h"

namespace Materials
{
    Metal::Metal(const Color &albedo, double fuzz)
        : m_Albedo(albedo), m_Fuzz(fuzz)
    {
    }
    bool Metal::Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const
    {
        Vec3 reflected = reflect(unit_vector(inRay.Direction()), record.normal);
        scattered = Ray(record.point, reflected + m_Fuzz * random_in_unit_sphere(), inRay.Time());
        attenuation = m_Albedo;
        return (dot(scattered.Direction(), record.normal) > 0);
    }
}