#include <fmt/core.h>

#include "image.h"
#include "camera.h"
#include "sphere.h"

Color3f vec2color(const Vec3f &dir);
Vec3f intersection2color(Ray &r, const Sphere &sphere);

// This test generates a render of a single sphere, with colors determined by the
// normal vector at the intersection point.
void task05_render() {
    fmt::print("\n");
    fmt::print("--------------------------------------------------------\n"
               "Task 5: Sphere image\n"
               "--------------------------------------------------------\n");

    // Setup the output image
    Image ray_image(200, 100);
    Sphere sphere(1.f);

    // Set up a camera with some reasonable parameters
    Camera camera({
              {"vfov", 45.f},
              {"resolution", Vec2i(ray_image.width(), ray_image.height())},
              {"fdist", 1.f},
              {"transform", {{"from", {0.0f, 0.0f, 3.0f}}, {"at", {0.0f, 0.0f, 0.0f}}, {"up", {0.0f, 1.0f, 0.0f}}} }
      });

    for (int y = 0; y < ray_image.height(); y++) {
        for (int x = 0; x < ray_image.width(); x++) {

            // We add 0.5 to the pixel coordinate to center the ray within the pixel
            auto ray = camera.generate_ray(Vec2f(x + 0.5f, y + 0.5f));

            // If we hit the sphere, output the sphere normal; otherwise,
            // convert the ray direction into a color so we can have some visual
            // debugging
            ray_image(x, y) = intersection2color(ray, sphere);
        }
    }

    std::string filename("report/renders/05_sphere_intersect.png");
    fmt::print("Saving ray image to {}....", filename);
    ray_image.save_png(filename);
}

int main( ) {
    try {
        task05_render();
    } catch( std::exception & ex ) {
        fmt::print("ERROR: {}", ex.what() );
        return 1;
    }
    return 0;
}

Color3f vec2color(const Vec3f &dir) {
    return 0.5f * (dir + 1.f);
}

Vec3f intersection2color(Ray &r, const Sphere &sphere) {
    std::optional<HitRecord> hit = sphere.intersect(r);
    if (hit)
        return vec2color(normalize(hit->sn));
    else
        return vec2color(normalize(r.d));
}

