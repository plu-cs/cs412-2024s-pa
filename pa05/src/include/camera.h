#pragma once

#include <nlohmann/json.hpp>
using nlohmann::json;

#include "common.h"
#include "ray.h"
#include "transform.h"

/**
 * Represents a pinhole perspective camera.  The image plane is positioned at
 * z = -focal_dist with a size determined by the field of view and the image
 * aspect ratio.
 */
class Camera {
public:
    explicit Camera( const json& j = json({}) );

    /**
     * Generate a camera ray.
     *
     * @param sample the position on the image plane in pixel coordinates
     * @return a ray that originates at the camera's position and passes
     *         through the image plane at sample
     */
    Ray generate_ray( const Vec2f & sample ) const;

    Vec2i get_resolution() const { return resolution; }

private:
    Transform xform;              ///< Transform to world coordinates
    Vec2f image_plane_size{1, 1}; ///< Dimensions of the image plane
    Vec2i resolution{512, 512};   ///< Resolution of the image
    float focal_dist{1.f};        ///< Focal distance (distance to image plane)
};