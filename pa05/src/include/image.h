#pragma once

#include <vector>
#include <string>

#include "common.h"

/**
 * A class that represents an image with pixels in linear RGB stored as floating
 * point values (0-1).
 * To write to a pixel in the image, use the overloaded () operator.  Example:
 *    my_image(x,y) = Color3f(1, 0, 1);
 * To write image to a file in PNG format use save_png(...)
 *
 */
class Image {
public:
    /// Empty image, size 0 x 0
    Image() : size(0, 0) {}

    /// Image with dimensions width x height
    Image( int width, int height ) :
        size( width, height ),
        image_data(width * height, {0,0,0} ) {}

    Color3f & operator()(int, int);

    /// Convert 2d index to linear index
    int index_1( int x, int y ) const {
        return y * size.x + x;
    }

    int width() const { return size.x; }
    int height() const { return size.y; }

    /**
     * Write this image to a file in PNG format.
     * @param filename output file path
     * @param bias an optional bias to apply (multiply) to each pixel
     */
    void save_png(const std::string & filename, float bias = 1.0f) const;

private:
    std::vector<Color3f> image_data;
    Vec2i size;
};

inline Color3f & Image::operator()(int x, int y ) {
    return image_data[index_1(x,y)];
}

/// Convert from linear RGB to sRGB
inline Color3f to_sRGB(const Color3f &c) {
    return linalg::select(
            linalg::lequal(c, 0.0031308f),
            c * 12.92f,
            (1.0f + 0.055f) * linalg::pow(c, 1.0f / 2.4f) - 0.055f);
}