#pragma once

#include "vector/vec3.h"

class Ray
{
public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction, double time = 0.0);

    inline Point3 Origin() const { return m_Origin; }
    inline Vec3 Direction() const { return m_Direction; }
    inline double Time() const { return m_Time; }

    Point3 At(double t) const;

private:
    Point3 m_Origin;
    Vec3 m_Direction;
    double m_Time;
};