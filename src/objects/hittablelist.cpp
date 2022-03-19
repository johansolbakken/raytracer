#include "hittablelist.h"

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
}