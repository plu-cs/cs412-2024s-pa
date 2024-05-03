#pragma once

#include "common.h"
class Material;

/**
 * This struct stores information about a ray-surface intersection.
 */
struct HitRecord {
    float t = 0.0f;     ///< Ray distance for the hit
    Vec3f p;            ///< The world-space intersection point
    Vec3f gn;           ///< The geometric normal at the intersection point
    Vec3f sn;           ///< The shading normal at the intersection point
    std::shared_ptr<Material> material; ///< The material of the intersected surface

    HitRecord() = default;
};