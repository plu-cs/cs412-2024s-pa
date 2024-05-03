#pragma once

#include "common.h"
#include "ray.h"

using linalg::mul;

/**
 * Represents an affine transformation and its inverse.
 */
class Transform {
public:

    Mat4 m;     ///< The transformation matrix
    Mat4 m_inv; ///< The inverse of the transformation matrix

    Transform() : m( linalg::identity ), m_inv(linalg::identity ) {}
    explicit Transform( const Mat4 & matrix ) : m(matrix), m_inv(linalg::inverse(matrix)) {}
    Transform( const Mat4 & matrix, const Mat4 & matrix_inverse ) : m(matrix), m_inv(matrix_inverse) {}

    Transform operator*( const Transform & rhs ) const {
        return { mul(m, rhs.m), mul(rhs.m_inv, m_inv) };
    }

    Transform inverse() const {
        return Transform(m_inv, m);
    }

    Vec3f transform_point( const Vec3f point ) const {
        // ========================== TASK 3 ===========================================================
        // TODO: Transform the point by this matrix.  Points can be affected by translations,
        //   use a 1.0 in the 4th homogeneous coordinate when multiplying.  Return a 3-component vector.
        //   To get the first three components of a Vec4f v use v.xyz().

        return {};  // Replace this
    }

    Vec3f transform_vector( const Vec3f & vector ) const {
        // ========================== TASK 3 ===========================================================
        // TODO: Transform the vector by this matrix.  Vectors should not be affected by translations,
        //   use a 0.0 in the 4th homogeneous coordinate to support this.  Return a 3-component vector.
        //   To get the first three components of a Vec4f v use v.xyz().
        
        return {};  // Replace this
    }

    Vec3f transform_normal( const Vec3f & normal ) const {
        // ========================== TASK 3 ===========================================================
        // TODO: Return a Vec3f that is transformed by this Transform.  Normals are
        //   transformed differently than other vectors, you must use the inverse transpose of the
        //   matrix.  The inverse is available in m_inv.  As with vectors, use a 0.0 in the 4th
        //   homogeneous coordinate to avoid translation.  Make sure to return a normalized unit vector.

        return {};  // Replace this
    }

    Ray transform_ray( const Ray & ray ) const  {
        // ========================== TASK 3 ===========================================================
        // TODO: Transform the ray's origin and direction and return a new Ray with the transformed
        //   values.  You can use the above methods to transform the origin and direction.  Make sure
        //   that you maintain the Ray's mint and maxt values.
        
        return {};  // Replace this
    }
};