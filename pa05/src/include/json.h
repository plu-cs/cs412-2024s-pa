#pragma once

#include <nlohmann/json.hpp>
#include <linalg.h>
#include <fmt/core.h>

#include "common.h"
#include "transform.h"

using nlohmann::json;

namespace linalg {

    template<class T, int N>
    inline void to_json(json& j, const vec<T, N> & v) {
        for( int i = 0; i < v.size(); i++ )
            j.push_back( v[i] );
    }

    template<class T, int N>
    inline void from_json(const json& j, vec <T, N> & v) {
        if( ! j.is_array() ) {
            throw LutertParseException(fmt::format("Can't parse Vec{} - must be an array.", N));
        }

        if( j.size() != N ) {
            throw LutertParseException(fmt::format("Can't parse Vec{} - invalid array size {}.", N, j.size()));
        }

        for( int i = 0; i < N; i++ ) {
            j.at(i).get_to(v[i]);
        }
    }

    inline void from_json(const json& j, mat<float, 4, 4> & m) {
        if( j.contains("translate") ) {
            Vec3f v = j.value("translate", Vec3f(0,0,0));
            m = translation_matrix(v);
        } else if( j.contains("rotate") ) {
            Vec4f v = j.value("rotate", Vec4f({0.0f, 0, 1, 0}));
            m = rotation_matrix(linalg::rotation_quat(Vec3f{v.y, v.z, v.w}, (float)(v.x * M_PI / 180.0f)));
        } else if( j.contains("scale") ) {
            Vec3f v = j.value("scale", Vec3f(1,1,1));
            m = scaling_matrix(v);
        } else if( j.contains("from") ) {
            Vec3f from = j.value( "from", Vec3f{0,0,1});
            Vec3f at = j.value("at", Vec3f{0,0,0});
            Vec3f up = j.value("up", Vec3f{0,1,0});

            Vec3f n = normalize(from - at);
            Vec3f u = normalize(cross(up, n));
            Vec3f v = normalize(cross(n, u));

            m = Mat4(Vec4f(u, 0.f), Vec4f(v, 0.f), Vec4f(n, 0.f), Vec4f(from, 1.f));
        } else {
            throw LutertParseException("Unrecognized transformation");
        }
    }

} // namespace linalg

inline void to_json(json& j, const Transform & t) {
    // TODO: Implement this
}

inline void from_json(const json& j, Transform & t) {
    linalg::mat<float, 4, 4> m{linalg::identity};
    if( j.is_object() ) {
        j.get_to(m);
    } else if( j.is_array() ) {
        for (auto& element : j) {
            m = mul(element.template get<Mat4>(), m);
        }
    } else {
        throw LutertParseException("Transformation must be an object or array");
    }
    t = Transform{m};
}

