#include "ray.h"
#include "vector/vec3.h"

Ray::Ray()
: m_Origin(0, 0, 0), m_Direction(1, 0, 0)
{

}

Ray::Ray(const Point3& origin, const Vec3& direction, double time)
: m_Origin(origin), m_Direction(direction), m_Time(time)
{

}

Point3 Ray::At(double t) const
{
    return m_Origin + t * m_Direction;
}