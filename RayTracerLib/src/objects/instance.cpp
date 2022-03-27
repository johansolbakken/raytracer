//
// Created by Johan Solbakken on 26/03/2022.
//

#include "objects/instance.h"

namespace Object::Instance
{
    //
    //  Translate
    //

    Translate::Translate(std::shared_ptr<Hittable> model, const Vec3 &displacement)
    : m_Model(model), m_Offset(displacement)
    {}

    bool Translate::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        Ray moved_r(ray.Origin() - m_Offset, ray.Direction(), ray.Time());
        if (!m_Model->Hit(moved_r, t_minimum, t_maximum, record))
            return false;

        record.point += m_Offset;
        record.set_face_normal(moved_r, record.normal);

        return true;
    }

    bool Translate::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        if (!m_Model->BoundingBox(time0, time1, output_box))
            return false;

        output_box = BVH::AABB(output_box.Minimum()+m_Offset, output_box.Maximum()+m_Offset);
        return true;
    }

    //
    //  RotateY
    //

    RotateY::RotateY(std::shared_ptr<Hittable> model, double angle)
    : m_Model(model)
    {
        auto radians = degrees_to_radians(angle);
        m_SinTheta = sin(radians);
        m_CosTheta = cos(radians);
        m_HasBox = m_Model->BoundingBox(0, 1, m_Bbox);

        Point3 min(infinity, infinity, infinity);
        Point3 max(-infinity, -infinity, -infinity);

        for (int i = 0; i < 2; i ++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    auto x = i * m_Bbox.Maximum().x() + (1-i)*m_Bbox.Minimum().x();
                    auto y = j * m_Bbox.Maximum().y() + (1-j)*m_Bbox.Minimum().y();
                    auto z = k * m_Bbox.Maximum().z() + (1-k)*m_Bbox.Minimum().z();

                    auto newx = m_CosTheta * x + m_SinTheta * z;
                    auto newz = -m_SinTheta * x + m_CosTheta * z;

                    Vec3 tester(newx, y, newz);

                    for (int c = 0; c < 3; c++)
                    {
                        min[c] = fmin(min[c], tester[c]);
                        max[c] = fmax(max[c], tester[c]);
                    }
                }
            }
        }
        m_Bbox = BVH::AABB(min,max);
    }

    bool RotateY::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        auto origin = ray.Origin();
        auto direction = ray.Direction();

        origin[0] = m_CosTheta*ray.Origin()[0] - m_SinTheta*ray.Origin()[2];
        origin[2] = m_SinTheta*ray.Origin()[0] + m_CosTheta*ray.Origin()[2];

        direction[0] = m_CosTheta*ray.Direction()[0] - m_SinTheta*ray.Direction()[2];
        direction[2] = m_SinTheta*ray.Direction()[0] + m_CosTheta*ray.Direction()[2];

        Ray rotated_r(origin, direction, ray.Time());
        if (!m_Model->Hit(rotated_r, t_minimum, t_maximum, record))
            return false;

        auto p = record.point;
        auto normal = record.normal;

        p[0] = m_CosTheta*record.point[0] + m_SinTheta*record.point[2];
        p[2] = -m_SinTheta*record.point[0] + m_CosTheta*record.point[2];

        record.point = p;
        record.set_face_normal(rotated_r, normal);

        return true;
    }

    bool RotateY::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        output_box = m_Bbox;
        return m_HasBox;
    }
}