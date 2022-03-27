//
// Created by Johan Solbakken on 24/03/2022.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "common/core.h"

namespace BVH
{
    class AABB
    {
    public:
        AABB() = default;

        AABB(const Point3 &a, const Point3 &b) : m_Minimum(a), m_Maximum(b)
        {}

        inline Point3 Minimum() const { return m_Minimum; }
        inline Point3 Maximum() const { return m_Maximum; }

        bool Hit(const Ray& ray, double t_min, double t_max) const
        {
            for (int a = 0; a < 3; a++)
            {
                auto invD = 1.0f / ray.Direction()[a];
                auto t0 = (Minimum()[a] - ray.Origin()[a]) * invD;
                auto t1 = (Maximum()[a] - ray.Origin()[a]) * invD;

                if (invD < 0.0f)
                {
                    std::swap(t0, t1);
                }

                t_min = t0 > t_min ? t0 : t_min;
                t_max = t1 < t_min ? t1 : t_min;

                if (t_max <= t_min)
                {
                    return false;
                }
            }
            return true;
        }

    private:
        Point3 m_Minimum, m_Maximum;
    };

    inline AABB SurroundingBox(AABB box0, AABB box1)
    {
        Point3 small(fmin(box0.Minimum().x(), box1.Minimum().x()),
                     fmin(box0.Minimum().y(), box1.Minimum().y()),
                     fmin(box0.Minimum().z(), box1.Minimum().z()));
        Point3 big(fmax(box0.Maximum().x(), box1.Maximum().x()),
                   fmax(box0.Maximum().y(), box1.Maximum().y()),
                   fmax(box0.Maximum().z(), box1.Maximum().z()));
        return AABB(small, big);
    }
}


#endif //RAYTRACER_AABB_H
