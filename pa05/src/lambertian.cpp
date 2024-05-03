#include "material.h"
#include "random.h"

/**
 * ==================================== TASK 6 ===========================================================
 * Implement Lambertian scattering.  Scatter the incoming ray in a random direction (cosine weighted) in 
 * the hemisphere oriented along the normal, and return a ScatterInfo struct containing the scattered ray
 * in the `scattered` field of the ScatterInfo struct.  The origin of the ray should be the intersection
 * point (hit.p), and select the direction by adding a random unit vector to the shading normal (available 
 * in the HitRecord object), then normalizing.
 * 
 * You can generate a random unit vector by calling the random_on_unit_sphere() function from "random.h".
 * The origin of the outgoing ray should be the hit point (hit.p).  Set `attenuation` in the ScatterInfo
 * struct to the value of this material's `albedo`.  
 * 
 * There is a small chance that the scattered direction will be close to (0,0,0).
 * In this case, set the scattered ray's direction to the shading normal (hit.sn).
 */
std::optional<ScatterInfo> Lambertian::scatter( const Ray & r, const HitRecord & hit ) const {
    return {};  // replace this
}
