//
// Created by Johan Solbakken on 24/03/2022.
//

#include "moving_sphere.h"

namespace Object
{
    MovingSphere::MovingSphere(Point3 center0, Point3 center1, double time0, double time1, double radius,
                               std::shared_ptr<Materials::Material> material)
            : m_Center0(center0), m_Center1(center1), m_Time0(time0), m_Time1(time1), m_Radius
            (radius), m_Material_ptr(material)
    {

    }

    bool MovingSphere::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        Vec3 oc = ray.Origin() - Center(ray.Time());
        auto a = ray.Direction().LengthSquared();
        auto half_b = dot(oc, ray.Direction());
        auto c = oc.LengthSquared() - m_Radius * m_Radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        auto sqrtd = std::sqrt(discriminant);

        // Finding the nearest root
        auto root = (-half_b - sqrtd) / a;
        if (root < t_minimum || t_maximum < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_minimum || t_maximum < root)
            {
                return false;
            }
        }

        record.t = root;
        record.point = ray.At(record.t);
        auto outward_normal = (record.point - Center(ray.Time())) / m_Radius;
        record.set_face_normal(ray, outward_normal);
        record.material_ptr = m_Material_ptr;

        return false;
    }

    Point3 MovingSphere::Center(double time) const
    {
        return m_Center0 + ((time - m_Time0) / (m_Time1 - m_Time0)) * (m_Center1 - m_Center0);
    }

    bool MovingSphere::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        BVH::AABB box0(
                Center(time0) - Vec3(m_Radius, m_Radius, m_Radius),
                Center(time0) + Vec3(m_Radius, m_Radius, m_Radius)
                );
        BVH::AABB box1(
                Center(time1) - Vec3(m_Radius, m_Radius, m_Radius),
                Center(time1) + Vec3(m_Radius, m_Radius, m_Radius)
        );
        output_box = SurroundingBox(box0, box1);
        return false;
    }
}