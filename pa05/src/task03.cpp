#include <catch2/catch_test_macros.hpp>
#include "transform.h"
#include "matchers.h"

/*
 * Task 3 - Implement the Transform class.  Look at the TODOs in include/transform.h.
 * Implement the methods there and run the tests in this file.  Iterate until all
 * tests pass.
 */
TEST_CASE( "Transform point - scale" ) {
    Mat4 m;
    m = linalg::scaling_matrix(Vec3f{2,-3,4});
    Transform t{m};

    Vec3f point{0.8f, 0.2f, 1.f };
    Vec3f result = t.transform_point(point);

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{1.6f, -0.6f, 4.0f}, 0.0001f));
}

TEST_CASE( "Transform point - translate" ) {
    Mat4 m;
    m = linalg::translation_matrix(Vec3f{2,-3,4});
    Transform t{m};

    Vec3f point{1.f, 1.f, 1.f };
    Vec3f result = t.transform_point(point);

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{3.0f, -2.0f, 5.0f}, 0.0001f));
}

TEST_CASE( "Transform point - rotate" ) {
    Mat4 m;
    m = linalg::rotation_matrix(linalg::rotation_quat(Vec3f{0.f, 1.0f, 0.0f}, (float)(M_PI / 2)));
    Transform t{m};

    Vec3f result = t.transform_point({1.f, 0.f, 0.f });

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{0.0f, 0.0f, -1.0f}, 0.0001f));
}

TEST_CASE( "Transform vector - scale" ) {
    Mat4 m = linalg::scaling_matrix(Vec3f{2,-3,4});
    Transform t{m};

    Vec3f v{0.8f, 0.2f, 1.f };
    Vec3f result = t.transform_vector(v);

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{1.6f, -0.6f, 4.0f}, 0.0001f));
}

TEST_CASE( "Transform vector - translate" ) {
    Mat4 m = linalg::translation_matrix(Vec3f{2,-3,4});
    Transform t{m};

    Vec3f v{1.f, 1.f, 1.f };
    Vec3f result = t.transform_vector(v);

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{1.f, 1.f, 1.f}, 0.0001f));
}

TEST_CASE( "Transform vector - rotate" ) {
    Mat4 m;
    m = linalg::rotation_matrix(linalg::rotation_quat(Vec3f{0.f, 1.0f, 0.0f}, (float)(M_PI / 2)));
    Transform t{m};

    Vec3f result = t.transform_vector({1.f, 0.f, 0.f });

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{0.0f, 0.0f, -1.0f}, 0.0001f));
}

TEST_CASE( "Transform normal - scale" ) {
    Mat4 m = linalg::scaling_matrix(Vec3f{1,2,1});
    Transform t{m};

    Vec3f result = t.transform_normal(normalize(Vec3f{1.f, 1.f, 0.f }));

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{0.89443f, 0.44721f, 0.0f}, 0.0001f));
}

TEST_CASE( "Transform normal - shear" ) {
    Mat4 m{{1,0,0,0}, {5,1,0,0}, {0,0,1,0}, {0,0,0,1}};
    Transform t{m};

    Vec3f result = t.transform_normal({0.f, 1.f, 0.f });

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{0.0, 1.f, 0.0f}, 0.0001f));
}

TEST_CASE( "Transform normal - shear and translate" ) {
    Mat4 m{{1,0,0,0}, {5,1,0,0}, {0,0,1,0}, {5,6,7,1}};
    Transform t{m};

    Vec3f result = t.transform_normal({0.f, 1.f, 0.f });

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{0.f, 1.f, 0.f}, 0.0001f));
}

TEST_CASE( "Transform normal - rotate" ) {
    Mat4 m = linalg::rotation_matrix(linalg::rotation_quat(Vec3f{0.f, 1.0f, 0.0f}, (float)(M_PI / 2)));
    Transform t{m};

    Vec3f result = t.transform_normal({1.f, 0.f, 0.f });

    REQUIRE_THAT( result, ApproxEqualsVec(Vec3f{0.0f, 0.0f, -1.0f}, 0.0001f));
}

TEST_CASE("Transform Ray - translation") {
    Mat4 m = linalg::translation_matrix(Vec3f{2, 4, -1});
    Transform t{m};

    Ray r{ {0,0,0}, {0,1,0}};
    Ray result = t.transform_ray(r);

    REQUIRE_THAT( result.o, ApproxEqualsVec(Vec3f{2, 4, -1.0f}, 0.0001f));
    REQUIRE_THAT( result.d, ApproxEqualsVec(Vec3f{0, 1, 0.f}, 0.0001f));
}

TEST_CASE("Transform Ray - tmin and tmax should be unchanged") {
    Mat4 m = linalg::translation_matrix(Vec3f{2, 4, -1});
    Transform t{m};

    Ray r{ {0,0,0}, {0,1,0}, 1, 100};
    Ray result = t.transform_ray(r);

    REQUIRE_THAT( result.o, ApproxEqualsVec(Vec3f{2, 4, -1.0f}, 0.0001f));
    REQUIRE_THAT( result.d, ApproxEqualsVec(Vec3f{0, 1, 0.f}, 0.0001f));
    REQUIRE( result.mint == 1.0f );
    REQUIRE( result.maxt == 100.0f );
}