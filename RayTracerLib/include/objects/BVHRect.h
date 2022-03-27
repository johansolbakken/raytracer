//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_BVHRECT_H
#define RAYTRACER_BVHRECT_H

#include "common/core.h"
#include "hittable.h"

namespace BVH
{

    // ---------------- XY -----------------
    class XYRect : public Object::Hittable
    {
    public:
        XYRect() {}
        ~XYRect(){}

        XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Materials::Material> material)
        : m_X0(x0), m_X1(x1), m_Y0(y0), m_Y1(y1), m_K(k), m_MaterialPtr(material)
        {}

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;

        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        std::shared_ptr<Materials::Material> m_MaterialPtr;
        double m_X0, m_X1, m_Y0, m_Y1, m_K;
    };

    // ---------------- XZ -----------------

    class XZRect : public Object::Hittable
    {
    public:
        XZRect() {}
        ~XZRect(){}

        XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Materials::Material> material)
                : m_X0(x0), m_X1(x1), m_Z0(z0), m_Z1(z1), m_K(k), m_MaterialPtr(material)
        {}

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;

        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        std::shared_ptr<Materials::Material> m_MaterialPtr;
        double m_X0, m_X1, m_Z0, m_Z1, m_K;
    };

    // ---------------- YZ -----------------

    class YZRect : public Object::Hittable
    {
    public:
        YZRect() {}
        ~YZRect(){}

        YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Materials::Material> material)
                : m_Y0(y0), m_Y1(y1), m_Z0(z0), m_Z1(z1), m_K(k), m_MaterialPtr(material)
        {}

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;

        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        std::shared_ptr<Materials::Material> m_MaterialPtr;
        double m_Y0, m_Y1, m_Z0, m_Z1, m_K;
    };
}

#endif //RAYTRACER_BVHRECT_H
