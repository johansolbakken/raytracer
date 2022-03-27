//
// Created by Johan Solbakken on 27/03/2022.
//

#include "objects/ConstantMedium.h"

#include "materials/isotropic.h"

namespace Object
{
    ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, double density, Color color)
    : m_Boundary(boundary), m_NegInvDensity(-1 / density), m_PhaseFunction(std::make_shared<Materials::Isotropic>(color))
    {}

    ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, double density,
                                   std::shared_ptr<texture::Texture> tex)
                                   : m_Boundary(boundary), m_NegInvDensity(-1 / density), m_PhaseFunction
                                   (std::make_shared<Materials::Isotropic>(tex))
    {}

    bool ConstantMedium::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        // Print occasional samples when debugging. To enable, set enableDebug true.
        constexpr bool enableDebug = false;
        const bool debugging = enableDebug && random_double() < 0.00001;

        hit_record record1, record2;
        if (!m_Boundary->Hit(ray, -infinity, infinity, record1))
            return false;

        if (!m_Boundary->Hit(ray, record1.t + 0.0001, infinity, record2))
            return false;

        if (debugging) std::cerr << "\nt_min=" << record1.t <<", t_max=" << record2.t << "\n";

        if (record1.t < t_minimum) record1.t = t_minimum;
        if (record2.t > t_maximum) record2.t = t_maximum;

        if (record1.t >= record2.t)
            return false;

        if (record1.t < 0)
            record1.t = 0;

        const auto ray_length = ray.Direction().Length();
        const auto distance_inside_boundary = (record2.t - record1.t) * ray_length;
        const auto hit_distance = m_NegInvDensity * log(random_double());

        if (hit_distance > distance_inside_boundary)
            return false;

        record.t = record1.t + hit_distance / ray_length;
        record.point = ray.At(record.t);

        if (debugging) {
            std::cerr << "hit_distance = " <<  hit_distance << '\n'
                      << "rec.t = " <<  record.t << '\n'
                      << "rec.p = " <<  record.point << '\n';
        }

        record.normal = Vec3(1,0,0);  // arbitrary
        record.front_face = true;     // also arbitrary
        record.material_ptr = m_PhaseFunction;

        return true;
    }

    bool ConstantMedium::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        return m_Boundary->BoundingBox(time0, time1, output_box);
    }
}
