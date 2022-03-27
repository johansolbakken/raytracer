//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "hittablelist.h"

namespace Object
{
    class Box : public Hittable
    {
    public:
        Box(){}
        Box(const Point3 &p0, const Point3 &p1, std::shared_ptr<Materials::Material> ptr);

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        Point3 m_BoxMin;
        Point3 m_BoxMax;
        HittableList m_Sides;
    };
}


#endif //RAYTRACER_BOX_H
