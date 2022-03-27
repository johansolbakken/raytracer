//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_TRANSLATE_H
#define RAYTRACER_TRANSLATE_H

#include "hittable.h"

namespace Object::Instance
{
    class Translate : public Hittable
    {
    public:
        Translate(std::shared_ptr<Hittable> model, const Vec3& displacement);

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        std::shared_ptr<Hittable> m_Model;
        Vec3 m_Offset;
    };

    class RotateY : public Hittable
    {
    public:
        RotateY(std::shared_ptr<Hittable> model, double angle);

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        std::shared_ptr<Hittable> m_Model;
        double m_SinTheta;
        double m_CosTheta;
        bool m_HasBox;
        BVH::AABB m_Bbox;
    };
}

#endif //RAYTRACER_TRANSLATE_H
