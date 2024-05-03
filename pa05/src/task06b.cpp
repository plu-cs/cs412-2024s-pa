#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "common.h"
#include "matchers.h"
#include "material.h"

/*
 * Task 6 - Dielectric tests
 */
TEST_CASE( "Entering a dielectric ior - 1.5" ) {
    Vec3f ray_d =  normalize(Vec3f(1.0f, -1.0f, 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.5f} } );
    hit.material = material;
    
    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( scat.has_value() );
    Vec3f attenuation = scat->attenuation;
    Ray scattered = scat->scattered;

    float sintheta_i = sqrtf( (1 - ray_d.y * ray_d.y) );
    float sintheta_o = sqrtf( (1 - scattered.d.y * scattered.d.y) );
    Vec3f scattered_expected{ 0.47140455, -0.8819171, 0 };

    REQUIRE_THAT( attenuation, ApproxEqualsVec(Vec3f{1,1,1}, 0.00001f));
    REQUIRE_THAT( 1.5f / 1.0f, Catch::Matchers::WithinAbs(sintheta_i / sintheta_o, 0.00001f) );
    REQUIRE_THAT( scattered.d, ApproxEqualsVec(scattered_expected, 0.00001f));
}

TEST_CASE( "Entering a dielectric ior - 1.3" ) {
    Vec3f ray_d =  normalize(Vec3f(1.0f, -1.0f, 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.3f} } );
    hit.material = material;
    
    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( scat.has_value() );
    Vec3f attenuation = scat->attenuation;
    Ray scattered = scat->scattered;

    float sintheta_i = sqrtf( (1 - ray_d.y * ray_d.y) );
    float sintheta_o = sqrtf( (1 - scattered.d.y * scattered.d.y) );
    Vec3f scattered_expected{ 0.54393f, -0.83913f, 0.0f };

    REQUIRE_THAT( attenuation, ApproxEqualsVec(Vec3f{1,1,1}, 0.00001f));
    REQUIRE_THAT( 1.3f / 1.0f, Catch::Matchers::WithinAbs(sintheta_i / sintheta_o, 0.00001f) );
    REQUIRE_THAT( scattered.d, ApproxEqualsVec(scattered_expected, 0.00001f));
}

TEST_CASE( "Exiting a dielectric ior - 1.5" ) {
    Vec3f ray_d =  normalize(Vec3f(0.5f, -1.0f, 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,-1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.5f} } );
    hit.material = material;

    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( scat.has_value() );
    Vec3f attenuation = scat->attenuation;
    Ray scattered = scat->scattered;

    float sintheta_i = sqrtf( (1 - ray_d.y * ray_d.y) );
    float sintheta_o = sqrtf( (1 - scattered.d.y * scattered.d.y) );
    Vec3f scattered_expected{ 0.67082f, -0.74162f, 0.0f };

    REQUIRE_THAT( attenuation, ApproxEqualsVec(Vec3f{1,1,1}, 0.00001f));
    REQUIRE_THAT( 1.0f / 1.5f, Catch::Matchers::WithinAbs(sintheta_i / sintheta_o, 0.00001f) );
    REQUIRE_THAT( scattered.d, ApproxEqualsVec(scattered_expected, 0.00001f));
}

TEST_CASE( "Exiting a dielectric ior - 1.3" ) {
    Vec3f ray_d =  normalize(Vec3f(1.0f, -1.0f, 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,-1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.3f} } );
    hit.material = material;
    
    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( scat.has_value() );
    Vec3f attenuation = scat->attenuation;
    Ray scattered = scat->scattered;

    float sintheta_i = sqrtf( (1 - ray_d.y * ray_d.y) );
    float sintheta_o = sqrtf( (1 - scattered.d.y * scattered.d.y) );
    Vec3f scattered_expected{ 0.91924f, -0.3937f, 0.0f };

    REQUIRE_THAT( attenuation, ApproxEqualsVec(Vec3f{1,1,1}, 0.00001f));
    REQUIRE_THAT( 1.0f / 1.3f, Catch::Matchers::WithinAbs(sintheta_i / sintheta_o, 0.00001f) );
    REQUIRE_THAT( scattered.d, ApproxEqualsVec(scattered_expected, 0.00001f));
}

TEST_CASE( "Exiting a dielectric - total internal reflection - ior 1.5" ) {
    Vec3f ray_d =  normalize(Vec3f(1.0f, -1.0f, 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,-1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.5f} } );
    hit.material = material;
    
    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( !scat.has_value() );
}

TEST_CASE( "Exiting a dielectric - total internal reflection - ior 1.3" ) {
    Vec3f ray_d =  normalize(Vec3f(1.3f, -1.0f, 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,-1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.3f} } );
    hit.material = material;

    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( ! scat.has_value() );
}

TEST_CASE( "Exiting a dielectric - total internal reflection near critical angle - ior 1.333" ) {
    float theta = deg2rad(48.7f);
    Vec3f ray_d =  normalize(Vec3f(sinf(theta), -cosf(theta), 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,-1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.333f} } );
    hit.material = material;
    
    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( ! scat.has_value() );
}

TEST_CASE( "Exiting a dielectric ior - 1.333 - near critical angle" ) {
    float theta = deg2rad(48.5f);
    Vec3f ray_d =  normalize(Vec3f(sinf(theta), -cosf(theta), 0.0f));
    Ray   test_ray{Vec3f(0.0f, 0.0f, 0.0f), ray_d};
    HitRecord hit;
    hit.p = {0,0,0};
    hit.sn = hit.gn = {0,-1,0};

    std::shared_ptr<Material> material = std::make_shared<Dielectric>( json{ {"ior", 1.333f} } );
    hit.material = material;

    std::optional<ScatterInfo> scat = material->scatter(test_ray, hit);
    REQUIRE( scat.has_value() );
    Vec3f attenuation = scat->attenuation;
    Ray scattered = scat->scattered;

    float sintheta_i = sqrtf( (1 - ray_d.y * ray_d.y) );
    float sintheta_o = sqrtf( (1 - scattered.d.y * scattered.d.y) );
    Vec3f scattered_expected{ 0.99836f, -0.05728f, 0.0f };

    REQUIRE_THAT( attenuation, ApproxEqualsVec(Vec3f{1,1,1}, 0.00001f));
    REQUIRE_THAT( 1.0f / 1.333f, Catch::Matchers::WithinAbs(sintheta_i / sintheta_o, 0.00001f) );
    REQUIRE_THAT( scattered.d, ApproxEqualsVec(scattered_expected, 0.00001f));
}