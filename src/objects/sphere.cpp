#include "sphere.h"

#include "materials/material.h"

namespace Object
{
    Sphere::Sphere()
    {

    }

    Sphere::Sphere(const Point3 &center, double radius, const std::shared_ptr<Materials::Material> &material)
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
        if (root < t_minimum || root > t_maximum) {
            root = (-half_b + sqrtd) / a;
            if (root < t_minimum || root > t_maximum) {
                return false;
            }
        }

        record.t = root;
        record.point = ray.At(record.t);
        Vec3 outward_normal = unit_vector((record.point - m_Center) / m_Radius);
        record.set_face_normal(ray, outward_normal);
        GetSphereUv(outward_normal, record.u, record.v);
        record.material_ptr = m_Material;

        return true;
    }

    bool Sphere::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        output_box = BVH::AABB(m_Center - Vec3(m_Radius, m_Radius, m_Radius),
                          m_Center + Vec3(m_Radius, m_Radius, m_Radius));
        return true;
    }

    void Sphere::GetSphereUv(const Point3 &p, double &u, double &v)
    {
        // p: a given point on the sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

        auto theta = acos(-p.y());
        auto phi = atan2(-p.z(), p.x()) + pi;

        u = phi / (2*pi);
        v = theta / pi;
    }
}