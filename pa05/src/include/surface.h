#pragma once

#include "hitrecord.h"
#include "ray.h"

/**
 * Base class for surfaces.
 *
 * A surface represents the geometry in the scene.  A surface could be a shape
 * like a sphere or a collection of shapes like a mesh.
 */
class Surface {

public:
    virtual ~Surface() = default;

    virtual std::optional<HitRecord> intersect( Ray & ray ) const {
        throw LutertException("Intersection is not supported for this surface.");
    }

};

class Group : public Surface {

public:
    Group() = default;

    void add( const std::shared_ptr<Surface> & s ) {
        surfaces.push_back(s);
    }

    virtual std::optional<HitRecord> intersect( Ray & ray ) const override;

private:
    std::vector<std::shared_ptr<Surface>> surfaces;
};