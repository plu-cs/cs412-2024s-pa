
#include <fmt/core.h>

#include "image.h"
#include "camera.h"

Color3f vec2color(const Vec3f &dir);
Color3f ray2color(const Ray &r);

// TASK 2: NO CHANGES are needed to this file.  For this task, all changes will be
//   in the Camera class.
void task02() {
    fmt::print("\n");
    fmt::print("--------------------------------------------------------\n"
               "Task 2: Camera class generate_ray\n"
               "--------------------------------------------------------\n");

    // Setup the output image
    Image ray_image(200, 100);

    // Set up a camera with some reasonable parameters
    Camera camera({
        {"vfov", 90.f},
        {"resolution", Vec2i(ray_image.width(), ray_image.height())},
        {"fdist", 1.f}
    });

    // loop over all pixels and ask the camera to generate a ray
    for (int y = 0; y < ray_image.height(); y++) {
        for (int x = 0; x < ray_image.width(); x++) {
            // We add 0.5 to the pixel coordinate to center the ray within the pixel
            auto ray = camera.generate_ray(Vec2f(x + 0.5f, y + 0.5f));
            ray_image(x, y) = ray2color(ray);
        }
    }

    std::string filename("report/renders/02_camera_ray_image.png");
    fmt::print("Saving ray image to {}....", filename);
    ray_image.save_png(filename);
}

Color3f vec2color(const Vec3f &dir) {
    return 0.5f * (dir + 1.f);
}

Color3f ray2color(const Ray &r) {
    return vec2color(normalize(r.d));
}

int main( ) {
    try {
        task02();
    } catch( std::exception & ex ) {
        fmt::print("ERROR: {}", ex.what() );
        return 1;
    }
    return 0;
}
