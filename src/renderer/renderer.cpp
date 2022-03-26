#include "renderer.h"

#include <thread>

#include "concurrency/semaphore.h"
#include "concurrency/ringbuffer.h"
#include "concurrency/threadpool.h"

#include "objects/hittablelist.h"

#include "renderer_objects.h"

namespace Renderer
{
    Color Renderer::RayColor(const Ray &ray, const Object::Hittable &world, int depth) const
    {
        hit_record record;

        if (depth <= 0)
        {
            return Color(0, 0, 0);
        }

        if (world.Hit(ray, 0.001, infinity, record))
        {
            Ray scattered;
            Color attenuation;
            if (record.material_ptr->Scatter(ray, record, attenuation, scattered))
                return attenuation * RayColor(scattered, world, depth - 1);
            return Color(0, 0, 0);
        }

        Vec3 unit_direction = unit_vector(ray.Direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

    void Renderer::WriteColor(std::ostream &out, Color pixel_color, int samples_per_pixel) const
    {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        auto scale = 1.0 / samples_per_pixel;
        r = std::sqrt(scale * r);
        g = std::sqrt(scale * g);
        b = std::sqrt(scale * b);

        *m_Output << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }

    void Renderer::Render(const Camera &camera, const Object::Hittable &world, const image_info &imageInfo) const
    {
        int image_width = imageInfo.width;
        int image_height = static_cast<int>(image_width / camera.GetAspectRatio());
        *m_Output<< "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height; j >= 0; j--)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; i++)
            {
                Color pixel_color(0, 0, 0);

                for (int s = 0; s < imageInfo.samples_per_pixel; s++)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    Ray r = camera.GetRay(u, v);
                    pixel_color += RayColor(r, world, imageInfo.recursion_depth);
                }

                WriteColor(std::cout, pixel_color, imageInfo.samples_per_pixel);
            }
        }

        std::cerr << "\nDone.\n";
    }



/////////////////

    void Renderer::GammaAndScale(Color &color, int colorScale, int samplesPerPixel) const
    {
        auto scale = 1.0 / samplesPerPixel;

        auto r = std::sqrt(scale * color.x());
        auto g = std::sqrt(scale * color.y());
        auto b = std::sqrt(scale * color.z());

        color.e[0] = static_cast<int>(colorScale * clamp(r, 0.0, 0.999));
        color.e[1] = static_cast<int>(colorScale * clamp(g, 0.0, 0.999));
        color.e[2] = static_cast<int>(colorScale * clamp(b, 0.0, 0.999));
    }

    void Renderer::Gamma(Color &color) const
    {

        auto r = std::sqrt(color.x());
        auto g = std::sqrt(color.y());
        auto b = std::sqrt(color.z());

        color.e[0] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
        color.e[1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
        color.e[2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
    }

    std::shared_ptr<Image> Renderer::RenderImage(const Camera &camera, const Object::Hittable &world, const image_info &image_info) const
    {
        auto image = std::make_shared<Image>(image_info.width, camera.GetAspectRatio());

        int image_width = static_cast<int>(image->GetWidth());
        int image_height = static_cast<int>(image->GetHeight());

        for (int j = image_height; j >= 0; j--)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; i++)
            {
                Color pixel_color(0, 0, 0);

                for (int s = 0; s < image_info.samples_per_pixel; s++)
                {
                    auto u = (static_cast<double>(i) + random_double()) / static_cast<double>(image_width - 1);
                    auto v = (static_cast<double>(j) + random_double()) / static_cast<double>(image_height - 1);
                    Ray r = camera.GetRay(u, v);
                    pixel_color += RayColor(r, world, image_info.recursion_depth);
                }

                pixel_color /= image_info.samples_per_pixel;
                Gamma(pixel_color);

                image->WriteColor(i, j, pixel_color);
            }
        }

        return image;
    }
}