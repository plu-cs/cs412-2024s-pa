#include <catch2/catch_test_macros.hpp>
#include "transform.h"
#include "matchers.h"
#include "sphere.h"
#include "spherical.h"

/*
 * Task 5 - Implement the Sphere::intersect function in sphere.cpp, then
 * run the tests in this file.
 */
TEST_CASE( "Untransformed sphere - hit" ) {
    Sphere s;
    Ray   test_ray{Vec3f(-0.25f, 0.5f, 4.0f), Vec3f(0.0f, 0.0f, -1.0f) };

    // Should intersect successfully
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( hit.has_value() );

    float correct_t = 3.170844f;
    Vec3f correct_p(-0.25f, 0.5f, 0.829156f);
    Vec3f correct_n(-0.25f, 0.5f, 0.829156f);

    REQUIRE_THAT( hit->t, Catch::Matchers::WithinAbs(correct_t, 0.00001f) );
    REQUIRE_THAT( hit->p, ApproxEqualsVec(correct_p, 0.00001f));
    REQUIRE_THAT( hit->gn, ApproxEqualsVec(correct_n, 0.00001f));
    REQUIRE_THAT( hit->sn, ApproxEqualsVec(correct_n, 0.00001f));
}

TEST_CASE( "Untransformed sphere - miss" ) {
    Sphere s;
    Ray   test_ray{Vec3f(-1.05f, 0.0f, 4.0f), Vec3f(0.0f, 0.0f, -1.0f) };

    // Should miss
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( !hit.has_value() );
}

TEST_CASE( "Transformed sphere - hit" ) {
    auto m = linalg::scaling_matrix(Vec3f{2.0f, 1.0f, 0.5f});
    m = linalg::mul( linalg::translation_matrix(Vec3f{0.0f, 0.25f, 5.0f}), m);

    Sphere s{1.0f, Transform(m)};
    Ray   test_ray{Vec3f(1.0f, 0.5f, 8.0f), Vec3f(0.0f, 0.0f, -1.0f) };

    // Should intersect successfully
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( hit.has_value() );

    float correct_t = 2.585422f;
    Vec3f correct_p(1.0f, 0.5f, 5.41458f);
    Vec3f correct_n(0.147442f, 0.147442f, 0.978019f);

    REQUIRE_THAT( hit->t, Catch::Matchers::WithinAbs(correct_t, 0.00001f) );
    REQUIRE_THAT( hit->p, ApproxEqualsVec(correct_p, 0.00001f));
    REQUIRE_THAT( hit->gn, ApproxEqualsVec(correct_n, 0.00001f));
    REQUIRE_THAT( hit->sn, ApproxEqualsVec(correct_n, 0.00001f));
}

TEST_CASE( "Transformed sphere - miss" ) {
    auto m = linalg::scaling_matrix(Vec3f{2.0f, 1.0f, 0.5f});

    Sphere s{1.0f, Transform(m)};
    Ray   test_ray{Vec3f(5.0f, 0.0f, 0.55f), Vec3f(-1.0f, 0.0f, 0.0f) };

    // Should intersect successfully
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( !hit.has_value() );
}

TEST_CASE( "Untransformed sphere - miss - less than mint" ) {
    Sphere s;
    Ray   test_ray{Vec3f(0.0f, 0.0f, 4.0f), Vec3f(0.0f, 0.0f, -1.0f), 5.01 };

    // Should miss
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( ! hit.has_value() );
}

TEST_CASE( "Untransformed sphere - miss - greater than maxt" ) {
    Sphere s;
    Ray   test_ray{Vec3f(0.0f, 0.0f, 4.0f), Vec3f(0.0f, 0.0f, -1.0f), 0.001f, 2.9f };

    // Should miss
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( ! hit.has_value() );
}

TEST_CASE( "Untransformed sphere - hit - ray starts inside sphere -z" ) {
    Sphere s;
    Ray   test_ray{Vec3f(0.f, 0.f, -0.5f), Vec3f(0.0f, 0.0f, -1.0f) };

    // Should intersect successfully
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( hit.has_value() );

    float correct_t = 0.5f;
    Vec3f correct_p(0.0f, 0.0f, -1.f);
    Vec3f correct_n(0.0f, 0.f, -1.f);

    REQUIRE_THAT( hit->t, Catch::Matchers::WithinAbs(correct_t, 0.00001f) );
    REQUIRE_THAT( hit->p, ApproxEqualsVec(correct_p, 0.00001f));
    REQUIRE_THAT( hit->gn, ApproxEqualsVec(correct_n, 0.00001f));
    REQUIRE_THAT( hit->sn, ApproxEqualsVec(correct_n, 0.00001f));
}

TEST_CASE( "Untransformed sphere - hit - ray starts inside sphere +z" ) {
    Sphere s;
    Ray   test_ray{Vec3f(0.f, 0.f, 0.5f), Vec3f(0.0f, 0.0f, 1.0f) };

    // Should intersect successfully
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( hit.has_value() );

    float correct_t = 0.5f;
    Vec3f correct_p(0.0f, 0.0f, 1.f);
    Vec3f correct_n(0.0f, 0.f, 1.f);

    REQUIRE_THAT( hit->t, Catch::Matchers::WithinAbs(correct_t, 0.00001f) );
    REQUIRE_THAT( hit->p, ApproxEqualsVec(correct_p, 0.00001f));
    REQUIRE_THAT( hit->gn, ApproxEqualsVec(correct_n, 0.00001f));
    REQUIRE_THAT( hit->sn, ApproxEqualsVec(correct_n, 0.00001f));
}

TEST_CASE( "Transformed sphere - hit - ray starts inside sphere -z" ) {
    Sphere s{1.0f, Transform( linalg::translation_matrix(Vec3f{2.0f, 1.0f, 3.0f}) )};
    Ray   test_ray{Vec3f(2.f, 1.f, 3.0f), Vec3f(0.0f, 0.0f, -1.0f) };

    // Should intersect successfully
    std::optional<HitRecord> hit = s.intersect(test_ray);
    CHECK( hit.has_value() );

    float correct_t = 1.0f;
    Vec3f correct_p(2.0f, 1.0f, 2.f);
    Vec3f correct_n(0.0f, 0.f, -1.f);

    REQUIRE_THAT( hit->t, Catch::Matchers::WithinAbs(correct_t, 0.00001f) );
    REQUIRE_THAT( hit->p, ApproxEqualsVec(correct_p, 0.00001f));
    REQUIRE_THAT( hit->gn, ApproxEqualsVec(correct_n, 0.00001f));
    REQUIRE_THAT( hit->sn, ApproxEqualsVec(correct_n, 0.00001f));
}
