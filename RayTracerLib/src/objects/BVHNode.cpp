//
// Created by Johan Solbakken on 24/03/2022.
//

#include "objects/BVHNode.h"

namespace BVH
{
    BVHNode::BVHNode()
    {

    }

    BVHNode::BVHNode(const Object::HittableList &list, double t0, double t1)
    {

    }

    BVHNode::BVHNode(const std::vector<std::shared_ptr<Object::Hittable>> &src_objects, size_t start, size_t end,
                     double t0, double t1)
    {
        auto objects = src_objects;

        int axis = random_int(0, 2);
        auto comparator = (axis == 0) ? box_x_compare
                                      : (axis == 1) ? box_y_compare
                                                    : box_z_compare;

        size_t object_span = end - start;
        if (object_span == 1) {
            m_Left = m_Right = objects[start];
        } else if (object_span == 2) {
            if (comparator(objects[start], objects[start + 1])) {
                m_Left = objects[start];
                m_Right = objects[start + 1];
            } else {
                m_Left = objects[start + 1];
                m_Right = objects[start];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);
            auto mid = start + object_span / 2;
            m_Left = std::make_shared<BVHNode>(objects, start, mid, t0, t1);
            m_Right = std::make_shared<BVHNode>(objects, mid, end, t0, t1);
        }

        AABB box_left, box_right;

        if (!m_Left->BoundingBox(t0, t1, box_left)
        || !m_Right->BoundingBox(t0, t1, box_right))
        {
            std::cerr << "No bounding box in bvh_node constructor.\n";
        }

        m_Box = SurroundingBox(box_left, box_right);
    }


    bool BVHNode::Hit(const Ray &ray, double t_minimum, double t_maximum, hit_record &record) const
    {
        if (!m_Box.Hit(ray, t_minimum, t_maximum)) {
            return false;
        }

        bool hit_left = m_Left->Hit(ray, t_minimum, t_maximum, record);
        bool hit_right = m_Right->Hit(ray, t_minimum, hit_left ? record.t : t_maximum, record);

        return hit_left || hit_right;
    }

    bool BVHNode::BoundingBox(double time0, double time1, AABB &output_box) const
    {
        output_box = m_Box;
        return true;
    }
}