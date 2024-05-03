#include "common.h"
#include "ray.h"
#include "material.h"
#include "spherical.h"
#include "image.h"
#include "heatmap.h"
#include "progressbar.h"

#include <cmath>

/**
 * This file includes a number of tests for the `Lambertian` and `Metal` materials.  For each test
 * a single incoming ray is scattered from the material.  A histogram is generated from the scattered
 * rays and written out as an image.  The colors in the image represent the frequency of rays scattered
 * in the direction that corresponds to the pixel. 
 */
void test_scatter( const Vec3f & incoming_dir, const HitRecord & hit, const Material & material, int samples,
                   const Vec2i &image_size, const std::string & output_file ) {

    std::vector<float> histogram(image_size.x * image_size.y, 0.f);
    int valid_samples = 0;
    Ray incoming_ray{{}, incoming_dir };
    bool nan_or_inf = false;
    int below_hemi_count = 0;

    ProgressBar pb{uint64_t(samples)};
    for( int i = 0; i < samples; i++ ) {
        std::optional<ScatterInfo> scat = material.scatter(incoming_ray, hit);
        if(! scat ) continue;

        if( ! ( std::isfinite(scat->scattered.d.x) && std::isfinite(scat->scattered.d.y) && std::isfinite(scat->scattered.d.z) ) ) {
            nan_or_inf = true;
            continue;
        }

        Vec3f dir = normalize(scat->scattered.d);

        if( dot(dir, hit.sn) < -1e-6 ) {
            below_hemi_count++;
            continue;
        }

        Vec2f s = direction_to_spherical( dir );
        Vec2f pixelf = s * image_size * Vec2f{INV_TWOPI, INV_PI};
        Vec2i pixel{pixelf};

        float sin_theta = std::max(1e-8f, std::sqrt(std::max(1.0f - dir.z * dir.z, 0.0f)));
        float weight    = histogram.size() / (M_PI * 2.0f * M_PI * sin_theta * samples);
        float val = histogram[ (image_size.x * pixel.y) + pixel.x ] + weight;

        if( !std::isfinite(val) ) {
            fmt::print("NaN or Infinite\n");
            continue;
        }
        histogram[ (image_size.x * pixel.y) + pixel.x ] = val;

        valid_samples++;
        ++pb;
    }
    pb.set_done();

    if( nan_or_inf ) {
        throw LutertException("ERROR: detected NaN or Infinite values in some scattered rays.\n");
    }

    if( below_hemi_count > 0 ) {
        throw LutertException("ERROR: some scattered rays were below the surface.  This should not happen.\n");
    }

    double pct_ok = (100.0 * valid_samples) / samples;
    fmt::print("{:.1f}% of rays were valid.\n", pct_ok );

    if( pct_ok < 90.0 ) {
        throw LutertException("ERROR: too many rays were invalid!\n");
    }

    // Find 99.95% largest value, to avoid outliers
    std::vector<float> values = histogram;
    std::sort(values.begin(), values.end());
    float max = values[int((values.size() - 1) * 0.9995)];

    // Upsample by a factor of 4 in each dimension and apply heatmap
    int upscale = 4;
    Vec2i large_size = image_size * upscale;
    Image hist_image( large_size.x, large_size.y );
    for( int y = 0; y < large_size.y; y++ ) {
        for(int x = 0; x < large_size.x ; x++ ) {
            float value = histogram[ image_size.x * (y/upscale) + (x/upscale) ] * (1.f / max);
            hist_image(x, y) = InfernoHeatmap::heatmap(value);
        }
    }

    hist_image.save_png(output_file);
}

int main() {
    fmt::print("\n-----------------------------------------------------------\n");
    fmt::print("Task 6 - Scatter tests\n");
    fmt::print("-----------------------------------------------------------\n");

    Vec2i image_size{256, 128};
    int samples = 1000 * linalg::product(image_size);
    HitRecord hit;

    fmt::print("\nLambertian material - normal (0,0,1)\n");
    fmt::print("Testing {} rays...\n", samples);
    Lambertian lambertian_material;
    std::string output_file = "report/renders/06_test_scatter_lambertian_01.png";
    hit.gn = hit.sn = normalize( Vec3f{0, 0, 1} );
    test_scatter({0.0f, 0.25f, -1.0f}, hit, lambertian_material,
                 samples, image_size, output_file);
    fmt::print("Histogram written to: {}\n", output_file);

    hit.gn = hit.sn = normalize( Vec3f{0.25, 0.5, 1.0} );
    output_file = "report/renders/06_test_scatter_lambertian_02.png";
    fmt::print("\nLambertian material - normal ({:.1f},{:.1f},{:.1f})\n", hit.sn.x, hit.sn.y, hit.sn.z);
    fmt::print("Testing {} rays...\n", samples);
    test_scatter({0.0f, 0.25f, -1.0f}, hit, lambertian_material,
                 samples, image_size,output_file );
    fmt::print("Histogram written to: {}\n", output_file);

    Metal metal_material1{ {{"roughness", 0.1f}} };
    output_file = "report/renders/06_test_scatter_metal_smooth_01.png";
    hit.gn = hit.sn = normalize(Vec3f{0.f, 0.f, 1.0f});
    fmt::print("\nMetal material - smooth (roughness 0.1), normal ({:.1f},{:.1f},{:.1f})\n", hit.sn.x, hit.sn.y, hit.sn.z);
    fmt::print("Testing {} rays...\n", samples);
    test_scatter({0.0f, 0.25f, -1.0f}, hit, metal_material1,
                 samples, image_size, output_file );
    fmt::print("Histogram written to: {}\n", output_file);

    hit.gn = hit.sn = normalize( Vec3f{0.25, 0.5, 1.0} );
    fmt::print("\nMetal material - smooth (roughness 0.1), normal ({:.1f},{:.1f},{:.1f})\n", hit.sn.x, hit.sn.y, hit.sn.z);
    fmt::print("Testing {} rays...\n", samples);
    output_file = "report/renders/06_test_scatter_metal_smooth_02.png";
    test_scatter({0.0f, 0.25f, -1.0f}, hit, metal_material1,
                 samples, image_size, output_file);
    fmt::print("Histogram written to: {}\n", output_file);

    Metal metal_material2{ {{"roughness", 0.5f}} };
    hit.gn = hit.sn = normalize( Vec3f{0.f, 0.f, 1.0f} );
    fmt::print("\nMetal material - rough (roughness 0.5), normal ({:.1f},{:.1f},{:.1f})\n", hit.sn.x, hit.sn.y, hit.sn.z);
    fmt::print("Testing {} rays...\n", samples);
    output_file = "report/renders/06_test_scatter_metal_rough_01.png";
    test_scatter({0.0f, 0.25f, -1.0f}, hit, metal_material2,
                 samples, image_size, output_file);
    fmt::print("Histogram written to: {}\n", output_file);

    hit.gn = hit.sn = normalize( Vec3f{0.25, 0.5, 1.0} );
    fmt::print("\nMetal material - rough (roughness 0.5), normal ({:.1f},{:.1f},{:.1f})\n", hit.sn.x, hit.sn.y, hit.sn.z);
    fmt::print("Testing {} rays...\n", samples);
    output_file = "report/renders/06_test_scatter_metal_rough_02.png";
    test_scatter({0.0f, 0.25f, -1.0f}, hit, metal_material2,
                 samples, image_size, output_file);
    fmt::print("Histogram written to: {}\n", output_file);
}