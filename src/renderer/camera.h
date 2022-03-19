#pragma once

#include "ray/ray.h"
#include "vector/vec3.h"

namespace Renderer
{
    class Camera
    {
    public:
        Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double aspect_ratio, double vfov, double aperture, double focus_dist, double shutterOpenTime = 0, double shutterCloseTime = 0);
        Ray GetRay(double u, double v) const;

        double GetAspectRatio() const { return m_AspectRatio; }

    private:
        double m_AspectRatio;
        
        Point3 m_Origin;
        Vec3 m_Horizontal;
        Vec3 m_Vertical;
        Vec3 m_LowerLeftCorner;

        int m_Width;
        int m_Height;

        Vec3 m_U, m_V, m_W;
        double m_LensRadius;

        double m_ShutterOpenTime; //time0
        double m_ShutterCloseTime; // time1
    };
}