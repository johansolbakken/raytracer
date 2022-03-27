#pragma once

#include "common/core.h"
#include "camera.h"
#include "../objects/hittable.h"
#include "image.h"

#include <memory>

namespace Renderer
{
    struct image_info
    {
        int width = 800;
        int recursion_depth = 50;
        int samples_per_pixel = 8;
    };

    class Renderer
    {
    public:
        void Render(const Camera &camera, const Object::Hittable &world, const image_info &imageInfo) const;
        std::shared_ptr<Image> RenderImage(const Camera& camera, const Object::Hittable &world, const image_info &image_info) const;

        inline void SetStream(std::ostream *ofstream)
        {
            m_Output = ofstream;
        }

    private:
         Color RayColor(const Ray &ray, const Color& background, const Object::Hittable &world, int depth) const;
         void WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) const;
         void GammaAndScale(Color& color, int colorScale, int samplesPerPixel) const; 
         void Gamma(Color &color) const;

    private:
        std::ostream* m_Output = nullptr;
    };

    
}