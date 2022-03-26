//
// Created by Johan Solbakken on 24/03/2022.
//

#ifndef RAYTRACER_MOVING_SPHERE_H
#define RAYTRACER_MOVING_SPHERE_H

#include "common/core.h"
#include "objects/hittable.h"

namespace Object
{

    class MovingSphere : public Hittable
    {
    public:
        MovingSphere() = default;
        MovingSphere(Point3 center0, Point3 center1, double time0, double time1, double radius,
                     std::shared_ptr<Materials::Material> material);

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;


        Point3 Center(double time) const;

    private:
        Point3 m_Center0, m_Center1;
        double m_Time0 = 0, m_Time1 = 0;
        double m_Radius = 1;
        std::shared_ptr<Materials::Material> m_Material_ptr;
    };

}


#endif //RAYTRACER_MOVING_SPHERE_H
