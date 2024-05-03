#pragma once

#include <pcg32.h>
#include "common.h"

/**
 * @returns the next random float in the range [0, 1)
*/
inline float next_float() {
    // Using a constant seed, change these to get a different RNG stream
    static pcg32 rng{42u, 54u};
    return rng.nextFloat();
}

/**
 * @returns a random point on the unit sphere centered at the origin.
*/
inline Vec3f random_on_unit_sphere() {
    float z1 = next_float();
    float z2 = next_float();

    float z = 1 - 2 * z1;
    float r = sqrtf(std::max( 0.f, 1.f - z * z) );
    float phi = 2 * M_PI * z2;
    return {r * std::cosf(phi), r * std::sinf(phi), z};
}