#include "sphere.h"

#include "materials/material.h"

namespace Object
{
    Sphere::Sphere()
    {

    }

    Sphere::Sphere(const Point3 &center, double radius, const std::shared_ptr<Materials::Material>& material)
        : m_Center(center), m_Radius(radius), m_Material(material)
    {
    }

    bool Sphere::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        Vec3 oc = ray.Origin() - m_Center;
        auto a = ray.Direction().LengthSquared();
        auto half_b = dot(oc, ray.Direction());
        auto c = oc.LengthSquared() - m_Radius * m_Radius;

        auto descriminant = half_b * half_b - a * c;
        if (descriminant < 0)
            return false;
        auto sqrtd = std::sqrt(descriminant);

        // Finding the nearest root that lies in the acceptable range
        auto root = (-half_b - sqrtd) / a;
        if (root < t_minimum || root > t_maximum)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_minimum || root > t_maximum)
            {
                return false;
            }
        }

        record.t = root;
        record.point = ray.At(record.t);
        Vec3 outward_normal = unit_vector((record.point - m_Center) / m_Radius);
        record.set_face_normal(ray, outward_normal);
        record.material_ptr = m_Material;

        return true;
    }
}