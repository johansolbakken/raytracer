#include "materials/dielectric.h"

#include "objects/hittable.h"

namespace Materials
{

    Dielectric::Dielectric(double indexOfRefraction)
        : m_IndexOfRefraction(indexOfRefraction)
    {
    }

    bool Dielectric::Scatter(const Ray &inRay, const hit_record &record, Color &attenuation, Ray &scattered) const
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = record.front_face ? (1.0 / m_IndexOfRefraction) : m_IndexOfRefraction;

        Vec3 unit_direction = unit_vector(inRay.Direction());
        double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 direction;

        if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > random_double())
            direction = reflect(unit_direction, record.normal);
        else
            direction = refract(unit_direction, record.normal, refraction_ratio);

        scattered = Ray(record.point, direction, inRay.Time());
        return true;
    }
    
    double Dielectric::Reflectance(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
}
