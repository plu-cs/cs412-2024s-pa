#pragma once

#include <nlohmann/json_fwd.hpp>
using nlohmann::json;

#include "surface.h"
#include "transform.h"

/**
 * A sphere centered at the origin with given radius.
 */
class Sphere : public Surface {

public:
    explicit Sphere(float radius = 1.0f, const Transform & t = Transform(),
                    const std::shared_ptr<Material> & material = nullptr) :
                    radius(radius), xform(t), material(material) {}
    explicit Sphere( const json & j );

    std::optional<HitRecord> intersect(Ray &ray) const override;

private:
    float radius = 1.0f;
    Transform xform = Transform();
    std::shared_ptr<Material> material = nullptr;
};