#include "quad.h"
#include "materiallib.h"

Quad::Quad(const json &j) {
    size = j.value("size", size);
    xform = j.value("transform", xform);
    if( j.contains("material") ) {
        material = MaterialLib::find(j.value("material", std::string("")));
    }
}

std::optional<HitRecord> Quad::intersect(Ray &ray) const {
    // Transform Ray into local space
    Ray xray = xform.inverse().transform_ray(ray);

    // If z is 0.0, ray is parallel to quad's plane
    if( std::fabs(xray.d.z) < 1e-5f ) {
        return {};
    }

    // Intersection of ray and x-y plane
    float t = -xray.o.z / xray.d.z;
    if( t < xray.mint || t > xray.maxt ) return {};

    auto p = xray.at(t);
    if( std::fabs(p.x) > size.x * 0.5f || std::fabs(p.y) > size.y * 0.5f ) return {};

    // We have a hit!
    HitRecord hit;
    hit.p = xform.transform_point(p);
    hit.t = t;
    hit.gn = hit.sn = xform.transform_normal({0,0,1});
    hit.material = material;
    return hit;
}