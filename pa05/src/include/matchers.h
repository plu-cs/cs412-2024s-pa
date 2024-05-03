#pragma once

#include "common.h"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

struct Vec3fMatcher : Catch::Matchers::MatcherGenericBase {
    Vec3fMatcher(Vec3f const& v, float tol): v{ v }, tol{tol} {}

    bool match(Vec3f const& other) const {
        auto matcherX = Catch::Matchers::WithinAbs(v.x, tol);
        auto matcherY = Catch::Matchers::WithinAbs(v.y, tol);
        auto matcherZ = Catch::Matchers::WithinAbs(v.z, tol);

        return matcherX.match(other.x) && matcherY.match(other.y) && matcherZ.match(other.z);
    }

    std::string describe() const override {
        return fmt::format(" is not within {} of {}", tol, v);
    }

private:
    Vec3f const& v;
    float tol;
};

auto ApproxEqualsVec(const Vec3f& expected, float tol) -> Vec3fMatcher {
    return Vec3fMatcher{expected, tol};
}
