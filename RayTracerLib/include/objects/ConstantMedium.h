//
// Created by Johan Solbakken on 27/03/2022.
//

#ifndef RAYTRACER_CONSTANTMEDIUM_H
#define RAYTRACER_CONSTANTMEDIUM_H

#include "hittable.h"
#include "textures/texture.h"

namespace Object
{
    class ConstantMedium : public Hittable
    {
    public:
        ConstantMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<texture::Texture> tex);
        ConstantMedium(std::shared_ptr<Hittable> boundary, double density, Color color);

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, BVH::AABB &output_box) const override;

    private:
        std::shared_ptr<Hittable> m_Boundary;
        std::shared_ptr<Materials::Material> m_PhaseFunction;
        double m_NegInvDensity;
    };
}

#endif //RAYTRACER_CONSTANTMEDIUM_H
