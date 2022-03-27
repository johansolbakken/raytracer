//
// Created by Johan Solbakken on 26/03/2022.
//

#include "objects/Box.h"

#include "objects/BVHRect.h"

namespace Object
{
    Box::Box(const Point3 &p0, const Point3 &p1, std::shared_ptr<Materials::Material> ptr)
    {
        m_BoxMin = p0;
        m_BoxMax = p1;

        m_Sides.Add(std::make_shared<BVH::XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
        m_Sides.Add(std::make_shared<BVH::XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

        m_Sides.Add(std::make_shared<BVH::XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
        m_Sides.Add(std::make_shared<BVH::XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));

        m_Sides.Add(std::make_shared<BVH::YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
        m_Sides.Add(std::make_shared<BVH::YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));

    }

    bool Box::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        return m_Sides.Hit(ray, t_minimum, t_maximum, record);
    }

    bool Box::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        output_box = BVH::AABB(m_BoxMin, m_BoxMax);
        return true;
    }
}