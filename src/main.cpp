#include "renderer/renderer.h"
#include "scenes/random_scene.h"
#include "scenes/two_spheres_scene.h"
#include "scenes/two_noise_spheres_scene.h"
#include "scenes/mirror_scene.h"
#include "scenes/earth_scene.h"

#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
    std::string filename = "image.ppm";
    if (argc > 1)
    {
        filename = std::string(argv[1]);
    }

    std::ofstream ofstream(filename, std::ios::out);

    Scene::EarthScene scene;

    Renderer::image_info renderer_info = {0};
    renderer_info.width = 720;
    renderer_info.recursion_depth = 25;
    renderer_info.samples_per_pixel = 50;

    Renderer::Renderer renderer;
    renderer.SetStream(&ofstream);
    renderer.Render(*scene.GetCamera(), *scene.GetWorld(), renderer_info);

    ofstream.close();
}