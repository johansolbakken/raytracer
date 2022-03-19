#include "common/core.h"

#include "renderer/renderer.h"

#include "scenes/random_scene.h"


int main()
{
    Scene::RandomScene scene;

    const auto aspect_ratio = 4.0 / 3.0;

    // Camera
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Renderer::Camera camera(lookfrom, lookat, vup, aspect_ratio, 20.0, aperture, dist_to_focus);

    // Image
    Renderer::image_info renderer_info = {0};
    renderer_info.width = 800;
    renderer_info.recursion_depth = 4;
    renderer_info.samples_per_pixel = 8;

    Renderer::Renderer renderer;
    renderer.Render(camera, *scene.GetWorld(), renderer_info);
    
    /*auto pImage = renderer.RenderImage(camera, *scene.GetWorld(), renderer_info);

    int image_width = pImage->GetWidth();
    int image_height = pImage->GetHeight();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height; j >= 0; j--)
    {
        for (int i = 0; i < image_width; i++)
        {
            Color data = pImage->Data()[i + j * image_height];
            std::cout << data.x() << ' '
                    << data.y() << ' '
                    << data.z() << '\n';
        }
    }*/
}