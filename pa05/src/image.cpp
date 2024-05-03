#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <linalg.h>
#include <cmath>
#include <fmt/core.h>

#include "image.h"

void Image::save_png(const std::string & filename, float bias) const {

    std::vector<uint8_t> image_out(size.x * size.y * 3, 0);

    for( int x = 0; x < size.x; x++ ) {
        for(int y = 0; y < size.y; y++ ) {
            Color3f pix_color = image_data[ index_1(x,y) ];
            pix_color *= bias;

            // Make infinite colors stand out as magenta
            if( !std::isfinite(pix_color.x) || !std::isfinite(pix_color.y) || !std::isfinite(pix_color.z) ) {
                pix_color = {1.0f, 0.0f, 1.0f};
            }

            Color3f srgb = linalg::clamp( to_sRGB(pix_color), 0.0f, 1.0f );
            int offset = 3 * (x + y * size.x);
            image_out[ offset + 0 ] = static_cast<uint8_t>(srgb.x * 255);
            image_out[ offset + 1 ] = static_cast<uint8_t>(srgb.y * 255);
            image_out[ offset + 2 ] = static_cast<uint8_t>(srgb.z * 255);
        }
    }

    int result = stbi_write_png(filename.c_str(), size.x, size.y, 3,
                   image_out.data(),
                   3 * sizeof(uint8_t) * size.x);

    if(result == 0) {
        throw std::runtime_error( fmt::format("Error writing to file: {}", filename) );
    }
}