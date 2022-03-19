#include "ray.h"
#include "vector/vec3.h"

Ray::Ray()
: m_Origin(0, 0, 0), m_Direction(1, 0, 0)
{

}

Ray::Ray(const Point3& origin, const Vec3& direction)
: m_Origin(origin), m_Direction(direction)
{

}

Point3 Ray::At(double t) const
{
    return m_Origin + t * m_Direction;
}