#pragma once

#include <linalg.h>
#include <fmt/format.h>
#include <optional>
#include <cmath>

using Color3f = linalg::vec<float, 3>;
using Color4f = linalg::vec<float, 4>;
using Vec2f = linalg::vec<float, 2>;
using Vec3f = linalg::vec<float, 3>;
using Vec4f = linalg::vec<float, 4>;
using Vec2i = linalg::vec<int, 2>;
using Vec3i = linalg::vec<int, 3>;
using Mat4 = linalg::mat<float, 4, 4>;

using linalg::dot;
using linalg::cross;
using linalg::normalize;
using linalg::length;
using linalg::length2;

#undef M_PI
#define M_PI         3.14159265358979323846f
#define INV_PI       0.31830988618379067154f
#define INV_TWOPI    0.15915494309189533577f

inline float deg2rad( float degrees ) {
    return (float)( degrees * M_PI / 180.0 );
}

class LutertParseException : public std::runtime_error {
public:
    LutertParseException( const std::string & message ) : std::runtime_error(message) {}
};

class LutertException : public std::runtime_error {
public:
    LutertException( const std::string & message ) : std::runtime_error(message) {}
};

template <class T, int N> struct fmt::formatter<linalg::vec<T,N>> : formatter<string_view> {
    auto format(linalg::vec<T,N> c, format_context& ctx) const {
        std::vector<T> v;
        for( int i = 0; i < N; i++ ) {v.push_back(c[i]);}
        std::string s = fmt::format("[{}]", fmt::join(v, ", "));
        return formatter<string_view>::format(s, ctx);
    }
};

template <class T> struct fmt::formatter<linalg::mat<T,4,4>> : formatter<string_view> {
    auto format(linalg::mat<T,4,4> m, format_context& ctx) const {
        std::string s;
        for( int i = 0; i < 4; i++ ) {
            s += fmt::format("| {:6.2f} {:6.2f} {:6.2f} {:6.2f} |\n",
                             m[0][i], m[1][i], m[2][i], m[3][i]);
        }
        return formatter<string_view>::format(s, ctx);
    }
};

/**
 * Compute the reflected direction around a surface normal.
 * @param in the incoming direction (towards the surface)
 * @param n the surface normal
 * @return the reflected direction
 */
inline Vec3f reflect( const Vec3f & in, const Vec3f & n ) {
    return in - 2 * dot(in, n) * n;
}

/**
 * Compute the refracted direction through an interface.
 * @param v_in the incoming direction (pointing towards the surface)
 * @param n the surface normal (pointing away from the surface), must be normalized
 * @param ior_ratio the ratio of the index of refraction on the incident side to the index of
 *            refraction on the transmitted side.
 * @return the refracted direction or empty if refraction is not possible, i.e. there
 *         is total internal reflection.
 */
inline std::optional<Vec3f> refract( const Vec3f & v_in, const Vec3f & n, float ior_ratio ) {
    Vec3f v = normalize(v_in);

    // Check for total internal reflection
    float minus_cos_theta_i = dot(v, n);
    float d = 1.f - ior_ratio * ior_ratio * ( 1.f - minus_cos_theta_i * minus_cos_theta_i );
    if( d < 0.f ) return {};  // Internal reflection

    // Calculate refracted direction
    return ior_ratio * ( v - n * minus_cos_theta_i ) - n * sqrtf(d);
}

/**
 * Schlick approximation for the fresnel reflectance.
 * @param cos_theta_i cosine of the incoming angle with the normal
 * @param ior_ratio the ratio of the index of refraction on the incident side to the index of
 *            refraction on the transmitted side.
 * @return the reflectance
 */
inline float schlick_fresnel( float cos_theta_i, float ior_ratio ) {
    auto r0 = (1.f - ior_ratio) / ( 1 + ior_ratio);
    r0 = r0 * r0;
    return r0 + (1 - r0) * powf((1 - cos_theta_i),5);
}
