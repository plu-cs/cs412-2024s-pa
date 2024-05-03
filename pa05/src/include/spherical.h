#pragma once

#include "common.h"

inline Vec2f direction_to_spherical( const Vec3f & v ) {
    float phi = std::atan2(-v.y, -v.x) + M_PI;
    float theta = std::acos(std::clamp(v.z, -1.f, 1.f));
    return {phi, theta};
}