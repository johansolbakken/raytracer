#include "objects/hittablelist.h"

namespace Object
{

    HittableList::HittableList()
    {
    }

    HittableList::HittableList(std::shared_ptr<Hittable> object)
    {
        Add(object);
    }

    bool HittableList::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        hit_record temporary_record;
        bool hit_anything = false;
        auto closest_so_far = t_maximum;

        for (const auto &object : m_Objects)
        {
            if (object->Hit(ray, t_minimum, closest_so_far, temporary_record))
            {
                hit_anything = true;
                closest_so_far = temporary_record.t;
                record = temporary_record;
            }
        }

        return hit_anything;
    }

    bool HittableList::BoundingBox(double time0, double time1, BVH::AABB &output_box) const
    {
        if (m_Objects.empty()) return false;

        BVH::AABB temp_box;
        bool first_box = true;

        for (const auto& object : m_Objects)
        {
            if (!object->BoundingBox(time0, time1, temp_box)) return false;
            output_box = first_box ? temp_box : SurroundingBox(output_box, temp_box);
            first_box = false;
        }

        return true;
    }
}