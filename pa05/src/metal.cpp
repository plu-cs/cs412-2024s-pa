#include "material.h"
#include "random.h"

/**
 * ==================================== TASK 6 =========================================================== 
 * Implement scattering from a metal material.  If the scatter is successful, return a ScatterInfo struct
 * with the `scattered` field containing the scattered Ray and the value of this material's `albedo` in
 * the `attenuation` field.  
 * 
 * The scattered ray's origin should be set to the intersection point (hit.p). To compute the scattered 
 * ray's direction, use the `reflect` function to calculate the reflected
 * direction, and add a random vector on the unit sphere (function `random_on_unit_sphere`) scaled 
 * by `roughness`.
 * 
 * It is possible that the scattered direction may be below the surface.  Check for this with the
 * dot product of the scattered direction and the shading normal.  If it is below the surface,
 * return false.  Otherwise, return {} (empty).
 */
std::optional<ScatterInfo> Metal::scatter( const Ray & r, const HitRecord & hit ) const {
    return {};  // replace this
}
