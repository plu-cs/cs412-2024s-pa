#pragma once

#include "common.h"

class Ray {
public:
    Ray() : o{0,0,0}, d{0,0,-1}, mint{EPSILON}, maxt{std::numeric_limits<float>::infinity()}{}

    /**
     * Construct a Ray object with the given origin and direction.
     *
     * @param origin The origin of the Ray.
     * @param direction The direction of the Ray.
     */
    Ray( const Vec3f & origin, const Vec3f & direction, float mint = EPSILON, float maxt = std::numeric_limits<float>::infinity()) :
            o(origin),
            d(direction),
            mint(mint),
            maxt(maxt) { }

    /**
     * Compute the point on the Ray that is a distance dist from the Ray's origin.
     *
     * @param dist The distance from the origin of the ray.
     * @return The point on the Ray at the distance dist.
     */
    Vec3f at( float t ) const {
        return o + (d * t);
    }


    Vec3f o;     ///< The origin of the ray
    Vec3f d;     ///< The direction of this ray
    float mint;  ///< Minimum distance along the ray segment
    float maxt;  ///< Maximum distance along the ray segment

    /**
     * A small value that is used to initialize the start of the Ray. This is used
     * to help avoid self intersections when reflecting from a surface.
     */
    constexpr static const float EPSILON = 0.001f;
};