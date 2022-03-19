#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

namespace Object
{
    class HittableList : public Hittable
    {
    public:
        HittableList();
        HittableList(std::shared_ptr<Hittable> object);

        inline void Clear() { m_Objects.clear(); }
        inline void Add(std::shared_ptr<Hittable> object) { m_Objects.push_back(object); }

        virtual bool Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> m_Objects;
    };

}