#pragma once

#include "common/core.h"

#include "objects/aabb.h"

#include "materials/material.h"

struct hit_record
{
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Materials::Material> material_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const Ray &ray, const Vec3 &outward_normal)
    {
        front_face = dot(ray.Direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

namespace Object
{
    class Hittable
    {
    public:
        virtual bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const = 0;
        virtual bool BoundingBox(double time0, double time1, BVH::AABB& output_box) const = 0;
    };
}