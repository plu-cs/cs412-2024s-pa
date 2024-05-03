#include <fmt/core.h>
#include "image.h"
#include "ray.h"

Color3f vec2color(const Vec3f &dir);
Color3f ray2color(const Ray &r);

void task01( ) {
    fmt::print("\n");
    fmt::print("--------------------------------------------------------\n"
               "TASK 1: Generating rays by hand \n"
               "--------------------------------------------------------\n");

    // The output image
    Image ray_image(200, 100);

    const Vec3f camera_origin(0.f, 0.f, 0.f);
    const float image_plane_width  = 4.f;
    const float image_plane_height = 2.f;

    // loop over all pixels and generate one ray for each
    for (int y = 0; y < ray_image.height(); y++ ) {
        for (int x = 0; x < ray_image.width(); x++ ) {

            Vec3f ray_origin;
            Vec3f ray_direction;

            // -------------------- TASK 1 ---------------------------------------------------------------
            // TODO: Find a ray that starts at camera_origin and goes through the center of
            //   the pixel at (x, y).  The pixel grid is located on the image plane at z = -1,
            //   centered on the z axis.  The grid extends from (left to right) -image_plane_width / 2 to
            //   image_plane_width/2 in the x direction and from  (top to bottom) +image_plane_height / 2
            //   to -image_plane_height/2 in the y direction.
            //   Compute ray_origin and ray_direction such that the ray goes through the center of each
            //   pixel.
            //   For details, consult RTOW Section 4.2


            auto ray = Ray{ray_origin, ray_direction};

            // Generate a color for the ray based on its direction 
            ray_image(x, y) = ray2color(ray);
        }
    }

    std::string filename("report/renders/01_manual_ray_image.png");
    fmt::print("Saving image to {}....\n", filename);
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
        task01();
    } catch( std::exception & ex ) {
        fmt::print("ERROR: {}", ex.what() );
        return 1;
    }
    return 0;
}