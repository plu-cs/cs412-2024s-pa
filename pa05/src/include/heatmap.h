#pragma once

#include <string>
#include <vector>

#include "common.h"

inline Color3f hex2color( const std::string & hex_string ) {
    float red = std::stol( hex_string.substr(1,2), nullptr, 16) / 255.0f;
    float green = std::stol( hex_string.substr(3,2), nullptr, 16) / 255.0f;
    float blue = std::stol( hex_string.substr(5,2), nullptr, 16) / 255.0f;
    return {red, green, blue};
}

class InfernoHeatmap {
    inline static const std::vector<Color3f> colors = [] {
        // Esri color ramps - Inferno Heatmap
        // #010005ff,#1c0f4bff,#520d8eff,#881b9eff,#bc2e9aff,#f04188ff,#ff5c6aff,#ff8345ff,#ffb71bff,#fff415ff,#ffff64ff,#ffffe1ff,#ffffebff
        std::vector<std::string> inferno_map_hex = {"#010005ff", "#1c0f4bff", "#520d8eff", "#881b9eff", "#bc2e9aff",
                                                    "#f04188ff", "#ff5c6aff", "#ff8345ff", "#ffb71bff", "#fff415ff",
                                                    "#ffff64ff", "#ffffe1ff", "#ffffebff"};

        std::vector<Color3f> colors;
        colors.reserve(inferno_map_hex.size());
        for( auto const & c : inferno_map_hex ) {
            colors.push_back(hex2color(c));
        }
        return colors;
    }();

public:
    /**
     * @param value between 0.0 and 1.0
     * @return corresponding color from the heatmap
     */
    inline static Color3f heatmap( float value ) {
        value = std::clamp(value, 0.f, 1.f);
        int index = std::clamp( (int)std::floor( value * (colors.size() + 1) ), 0, int(colors.size() - 1) );
        return colors[ index ];
    }
};




