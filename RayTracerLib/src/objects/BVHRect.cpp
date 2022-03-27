//
// Created by Johan Solbakken on 26/03/2022.
//

#include "objects/BVHRect.h"

namespace BVH
{

    // ---------------- XY -----------------

    bool XYRect::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        auto t = (m_K - ray.Origin().z()) / ray.Direction().z();
        if (t < t_minimum || t > t_maximum)
            return false;

        auto x = ray.Origin().x() + t * ray.Direction().x();
        auto y = ray.Origin().y() + t * ray.Direction().y();

        if (x < m_X0 || x > m_X1 || y < m_Y0 || y > m_Y1)
            return false;

        record.u = (x - m_X0) / (m_X1 - m_X0);
        record.v = (y - m_Y0) / (m_Y1 - m_Y0);
        record.t = t;

        auto outward_normal = Vec3(0, 0, 1);
        record.set_face_normal(ray, outward_normal);
        record.material_ptr = m_MaterialPtr;
        record.point = ray.At(t);
        return true;
    }

    bool XYRect::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        output_box = AABB(Point3(m_X0, m_Y0, m_K - 0.0001), Point3(m_X1, m_Y1, m_K + 0.0001));
        return true;
    }

    // ---------------- XZ -----------------

    bool XZRect::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        auto t = (m_K - ray.Origin().y()) / ray.Direction().y();
        if (t < t_minimum || t > t_maximum)
            return false;
        auto x = ray.Origin().x() + t * ray.Direction().x();
        auto z = ray.Origin().z() + t * ray.Direction().z();
        if (x < m_X0 || x > m_X1 || z < m_Z0 || z > m_Z1)
            return false;
        record.u = (x - m_X0) / (m_X1 - m_X0);
        record.v = (z - m_Z0) / (m_Z1 - m_Z0);
        record.t = t;
        auto outward_normal = Vec3(0, 1, 0);
        record.set_face_normal(ray, outward_normal);
        record.material_ptr = m_MaterialPtr;
        record.point = ray.At(t);
        return true;
    }

    bool XZRect::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        output_box = AABB(Point3(m_X0, m_K - 0.0001, m_Z0), Point3(m_X1, m_K + 0.0001, m_Z1));
        return true;
    }

    // ---------------- YZ -----------------

    bool YZRect::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        auto t = (m_K - ray.Origin().x()) / ray.Direction().x();
        if (t < t_minimum || t > t_maximum)
            return false;
        auto y = ray.Origin().y() + t * ray.Direction().y();
        auto z = ray.Origin().z() + t * ray.Direction().z();
        if (y < m_Y0 || y > m_Y1 || z < m_Z0 || z > m_Z1)
            return false;
        record.u = (y - m_Y0) / (m_Y1 - m_Y0);
        record.v = (z - m_Z0) / (m_Z1 - m_Z0);
        record.t = t;
        auto outward_normal = Vec3(1, 0, 0);
        record.set_face_normal(ray, outward_normal);
        record.material_ptr = m_MaterialPtr;
        record.point = ray.At(t);
        return true;
    }

    bool YZRect::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        output_box = AABB(Point3(m_K - 0.0001, m_Y0, m_Z0), Point3(m_K + 0.0001, m_Y1, m_Z1));
        return true;
    }
}