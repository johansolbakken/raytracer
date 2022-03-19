#pragma once

#include "common/core.h"

#include "materials/material.h"

struct hit_record
{
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Materials::Material> material_ptr;
    double t;
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
    };
}