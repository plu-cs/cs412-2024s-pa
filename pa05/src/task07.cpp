#include <fmt/core.h>
#include <memory>

#include "sphere.h"
#include "material.h"
#include "camera.h"
#include "image.h"
#include "progressbar.h"

/**
 * ================ TASK 7 =========================
 * Implement recursive ray tracing for a test scene.
 * Look for TODO comments below.
 */
Color3f recursive_color(const Ray & ray, const Group & scene, int depth);

void task07_render() {
    const int num_samples = 128;
    Image image{300, 150};
    Camera camera({
              {"vfov", 45.f},
              {"resolution", {image.width(), image.height()}},
              {"focal_dist", 1.f},
              {"transform", {{"from", {1.9f, 0.8f, -3.5f}}, {"at", {1.9f, 0.8f, 0.0f}}, {"up", {0.0f, 1.0f, 0.0f}}}},
      });

    std::shared_ptr<Material> ground = std::make_shared<Lambertian>( json{ { "albedo", {0.5f,0.5f,0.5f}} } );
    std::shared_ptr<Material> matte = std::make_shared<Lambertian>( json{ { "albedo", {1.0f, 0.25f, 0.25f}} } );
    std::shared_ptr<Material> shiny = std::make_shared<Metal>( json{ { "albedo", {1.0f, 1.0f, 1.0f} }, {"roughness", 0.3f} } );

    auto floor = std::make_shared<Sphere>( 1000.0f,
                                            Transform( linalg::translation_matrix( Vec3f{0, -1000.0f, 0} )),
                                            ground );
    auto shiny_sphere = std::make_shared<Sphere>( 1.0f,
        Transform( linalg::translation_matrix( Vec3f{0, 1.0f, 1} )),
        shiny );
    auto matte_sphere = std::make_shared<Sphere>( 1.0f,
        Transform( linalg::translation_matrix( Vec3f{3.0f, 1.0f, 0} )),
        matte );

    Group scene;
    scene.add(floor);
    scene.add(shiny_sphere);
    scene.add(matte_sphere);

    {
        ProgressBar pb{ uint64_t(image.width() * image.height()) };

        for (int y = 0; y < image.height(); y++ ) {
            for (int x = 0; x < image.width(); x++ ) {

                // Add 0.5 to center the ray within the pixel 
                auto ray = camera.generate_ray(Vec2f(x + 0.5f, y + 0.5f));
                Color3f color = Color3f(0.0f);

                // ======================= TASK 7 ========================================
                // TODO: Call recursive_color `num_samples` times and average the
                // results. Store the average in the variable `color`


                image(x, y) = color;
                ++pb;
            }
        }
    }

    std::string filename("report/renders/07_recursive_raytrace.png");
    image.save_png(filename);
}

Color3f recursive_color( const Ray & camera_ray, const Group & scene, int depth) {
    const int max_depth = 64;
    Ray ray = camera_ray;  // Make a copy that can be modified.

    // =================== TASK 7 =================================================
    // TODO: Implement this function to recursively trace scattered rays.
    //
    // Pseudo-code:
    //
    // if scene.intersect is successful
    // 		if depth < max_depth and hit.material->scatter(....) is successful:
    //			recursive_color = call this function recursively with the scattered ray and increased depth
    //          return attenuation * recursive_color
    //		else
    //			return black;
    // else:
    // 		return white

    return {0,0,0};  // Replace this.
}

int main( ) {
    try {
        task07_render();
    } catch( std::exception & ex ) {
        fmt::print("ERROR: {}", ex.what() );
        return 1;
    }
    return 0;
}