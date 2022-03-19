#pragma once

#include "vector/vec3.h"

class Ray
{
public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction);

    inline Point3 Origin() const { return m_Origin; }
    inline Vec3 Direction() const { return m_Direction; }

    Point3 At(double t) const;

private:
    Point3 m_Origin;
    Vec3 m_Direction;
};