//
// Created by Johan Solbakken on 24/03/2022.
//

#ifndef RAYTRACER_BVHNODE_H
#define RAYTRACER_BVHNODE_H

#include "common/core.h"

#include "hittable.h"
#include "hittablelist.h"

namespace BVH
{
    class BVHNode : public Object::Hittable
    {
    public:
        BVHNode();
        BVHNode(const Object::HittableList& list, double t0, double t1);
        BVHNode(const std::vector<std::shared_ptr<Object::Hittable>>& src_objects, size_t start, size_t end, double
        t0, double t1);

        bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;
        bool BoundingBox(double time0, double time1, AABB &output_box) const override;

    private:
        std::shared_ptr<Object::Hittable> m_Left;
        std::shared_ptr<Object::Hittable> m_Right;
        AABB m_Box;
    };

    inline bool box_compare(const std::shared_ptr<Object::Hittable> a, const std::shared_ptr<Object::Hittable> b, int
    axis) {
        AABB box_a;
        AABB box_b;

        if (!a->BoundingBox(0,0, box_a) || !b->BoundingBox(0,0, box_b))
            std::cerr << "No bounding box in bvh_node constructor.\n";

        return box_a.Minimum().e[axis] < box_b.Minimum().e[axis];
    }


    inline bool box_x_compare (const std::shared_ptr<Object::Hittable> a, const std::shared_ptr<Object::Hittable> b) {
        return box_compare(a, b, 0);
    }

    inline bool box_y_compare (const std::shared_ptr<Object::Hittable> a, const std::shared_ptr<Object::Hittable> b) {
        return box_compare(a, b, 1);
    }

    inline bool box_z_compare (const std::shared_ptr<Object::Hittable> a, const std::shared_ptr<Object::Hittable> b) {
        return box_compare(a, b, 2);
    }
}

#endif //RAYTRACER_BVHNODE_H
