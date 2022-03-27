#pragma once

#include "hittable.h"

namespace Object
{
    class Sphere : public Hittable
    {
    public:
        Sphere();
        Sphere(const Point3 &center, double radius, const std::shared_ptr<Materials::Material>& material);

        virtual bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        static void GetSphereUv(const Point3& p, double& u, double& v);

    private:
        Point3 m_Center;
        double m_Radius;
        std::shared_ptr<Materials::Material> m_Material;
    };

}