#include <renderer/renderer.h>
/*#include "../tests/random_scene.h"
#include "../tests/two_spheres_scene.h"
#include "../tests/two_noise_spheres_scene.h"
#include "../tests/mirror_scene.h"
#include "../tests/earth_scene.h"
#include "../tests/cornell_box_fog_scene.h"
#include "../tests/cornell_box_scene.h"*/
#include "../tests/ultimate_scene.h"

#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
    std::string filename = "image.ppm";
    if (argc > 1) {
        filename = std::string(argv[1]);
    }

    std::ofstream ofstream(filename, std::ios::out);

    Scene::UltimateScene scene;

    Renderer::image_info renderer_info = {0};
    renderer_info.width = 800;
    renderer_info.recursion_depth = 25;
    renderer_info.samples_per_pixel = 200;

    Renderer::Renderer renderer;

    renderer.SetStream(&ofstream);
    renderer.Render(scene.GetCamera(), scene.GetWorld(), renderer_info);

    ofstream.close();
}