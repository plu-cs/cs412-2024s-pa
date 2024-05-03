#include "material.h"
#include "random.h"

/* 
==================== TASK 6 ============================================
TODO: Implement scattering (transmission) through a dielectric.  
The index of refraction is stored in the instance variable `ior` and 
the index of refraction outside the material is assumed to be 1.0.

The algorithm will be described in class and is also covered in
RTOW Sections 11.2 - 11.4.  For this implementation, there 
are at least the following differences:
 * If there is total internal reflection, return {} (empty)
 * Upon success, return a ScatterInfo struct with attenuation set to {1,1,1} and 
   scatter set to the scattered (refracted) ray which begins at the intersection point
   (hit.p) has the transmitted/refracted direction.
 * Rather than computing the refracted direction directly, call the function refract().
   Note that this function returns std::optional<Vec3f>.
   If the return value does not exist, then there is total internal reflection.
 * Make sure to determine whether you are entering or leaving the material.  Unlike the
   online text, we do not flip the normal upon intersection.  You'll need to determine 
   whether we are entering or leaving the material and flip the normal if necessary.
   To determine this, use the dot product of the ray direction and hit.sn.  You also need
   to compute the ratio of the IOR on the incident side over the IOR on the transmitted
   side, which will be different depending on whether the ray is entering or leaving.
 * Call the function `schlick_fresnel` to compute the Fresnel term.
*/
std::optional<ScatterInfo> Dielectric::scatter( const Ray & r, const HitRecord & hit ) const {
    return {};  // Replace this
}