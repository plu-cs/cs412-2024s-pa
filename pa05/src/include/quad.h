#pragma once

#include "surface.h"
#include "transform.h"
#include "json.h"

/**
 * A quad defined in the x-y plane, centered at the origin with size defined by size.x and size.y.
 */
class Quad : public Surface {

public:
    explicit Quad(Vec2f size = {1,1}, const Transform & t = Transform(),
                    const std::shared_ptr<Material> & material = nullptr) :
            size(size), xform(t), material(material) {}
    explicit Quad( const json & j );

    std::optional<HitRecord> intersect(Ray &ray) const override;

private:
    Vec2f size = {1.0f, 1.0f};
    Transform xform;
    std::shared_ptr<Material> material = nullptr;
};