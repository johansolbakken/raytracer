#include "renderer/camera.h"

namespace Renderer
{

    Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double aspect_ratio, double vfov, double aperture,
                   double focus_dist,Color background,double shutterOpenTime, double shutterCloseTime)
    : m_ShutterOpenTime(shutterOpenTime), m_ShutterCloseTime(shutterCloseTime), m_BackgroundColor(background)
    {
        m_AspectRatio = aspect_ratio;

        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        m_W = unit_vector(lookfrom - lookat);
        m_U = unit_vector(Cross(vup, m_W));
        m_V = Cross(m_W, m_U);

        m_Origin = lookfrom;
        m_Horizontal = focus_dist * viewport_width * m_U;
        m_Vertical = focus_dist * viewport_height * m_V;
        m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - focus_dist * m_W;

        m_LensRadius = aperture / 2;
    }

    Ray Camera::GetRay(double s, double t) const
    {
        Vec3 rd = m_LensRadius * random_in_unit_disk();
        Vec3 offset = m_U * rd.x() + m_V * rd.y();

        return Ray(
            m_Origin + offset,
            m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset, random_double(m_ShutterOpenTime, m_ShutterCloseTime));
    }
}