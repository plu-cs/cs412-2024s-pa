#include "sphere.h"
#include "json.h"
#include "materiallib.h"

 Sphere::Sphere(const json &j) {
    radius = j.value("radius", radius);
    xform  = j.value("transform", xform);
    if( j.contains("material") ) {
        material = MaterialLib::find(j.value("material", std::string("")));
    }
}

std::optional<HitRecord> Sphere::intersect( Ray &ray) const {
    // ===================== TASK 5 =================================================
    // TODO: Task 5 - implement Sphere::intersect
    //   Implement ray-sphere intersection.  
    //   Before computing the intersection, transform the ray into the object's local
    //   system using the inverse of the transform (xform).  In the sphere's local coordinate
    //   system it is centered at the origin, and the radius is stored in the field named
    //   radius.
    // 
    //   If the ray misses the sphere, return {} (empty).
    //   Otherwise, create a HitRecord struct, fill in all fields and return it.
    //   Ray-Sphere intersection is covered in Chapter 6.1 - 6.3 in RIOW.  For this
    //   application, we store two normals: a shading normal and a geometric normal.
    //   For Spheres, they will both be the same.
    //   
    //   The values in HitRecord must be in world coordinates, so they will need to be
    //   transformed back to world coordinates before returning.  The ray's parameter (t)
    //   does not need to be transformed.
    //
    //   If the intersection distance must be within the Ray's [mint, maxt] range, otherwise,
    //   this method should return false (and leave hit unmodified).
    //
    //   Note: unlike the text, we do not flip the normal when the ray hits the back side
    //   of the object.


    // You should only execute the code below if you successfully hit something
    HitRecord hit;
    // hit.t   = t;   // Ray t at the intersection
    // hit.p   = p;   // The hit point
    // hit.gn  = n;   // The geometric normal at the hit point
    // hit.sn  = n;   // The shading normal at the hit point
    hit.material = material;

    return hit;
}
