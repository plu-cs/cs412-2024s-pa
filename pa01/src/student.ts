import {Image, Pixel} from './image';
import {Filter, MNCubicFilter} from './filter';
import {Rectangle} from './rectangle';

/**
 * Clamps a value to the range between low and high.
 *
 * @param value value to clamp
 * @param low minimum value
 * @param high maximum value
 * @returns value unchanged if value is between low and high, otherwise, returns
 * either low or high, whichever is closest to value.
 */
function clamp( value: number, low :number, high :number ) : number {
    return Math.max( low, Math.min(value, high) );
}

/**
 * Problem 1.1 - Grayscale
 * 
 * Provided for you.
 * 
 * @param source the input image
 * @returns a new Image that represents source converted to grayscale
 */
export function grayscale( source : Image ) : Image {
    const result = new Image(source.width, source.height);
    for( let i = 0; i < source.width; i++ ) {
        for( let j = 0; j < source.height; j++ ) {
            const p = source.getPixel(i,j);
            const lum = p.luminance();
            result.setPixel(i,j, new Pixel(lum,lum,lum));
        }
    }
    return result;
}

/**
 * Problem 1.2 - Brightness
 * 
 * Changes the brightness of the image by interpolating (mixing) with 
 * white (1,1,1) or black (0,0,0).
 * 
 * @param source the input image
 * @param ratio amount of change in brightness, between -1 and 1.  Negative values should make
 * the image darker, and positive values make it lighter.
 * @returns a new Image containing the result
 */
export function brightness( source :Image, ratio: number ) : Image {
    throw new Error("Not implemented");
}

/**
 * Problem 1.3 - Contrast - see assignment
 * 
 * @param source input image
 * @param alpha amount of contrast to apply, should be between -1 and 1 
 * @returns a new Image containing the result
 */
export function contrastFilter( source : Image, alpha : number ) : Image {
    throw new Error("Not implemented");
}

/**
 * Problem 1.4 - Vignette - see assignment
 * @param source input image
 * @param innerR inner radius as a percentage of the half diagonal of the image
 * @param outerR outer radius as a percentage of the half diagonal of the image
 * @return a new Image containing the result
 */
export function vignetteFilter( source :Image, innerR : number, outerR: number) : Image {
    throw new Error("Not implemented");
}


/**
 * Problem 1.5 - See assignment
 * @param source input Image
 * @return a new Image containing the result
 */
export function histogramFilter( source: Image ) : Image {
    throw new Error("Not implemented");
}

/**
 * Problem 2.1 - See assignment
 * @param source input Image
 * @return a new Image containing the result
 */
export function edgeFilter( source: Image ) : Image {
    throw new Error("Not implemented");
}

/**
 * Problem 2.2 - See assignment
 * @param source input Image
 * @return a new Image containing the result
 */
export function sharpenFilter( source: Image ) : Image {
   throw new Error("Not implemented");
}

/**
 * Problem 2.3 - Gaussian Blur
 * @param source the input image
 * @param sigma the value of sigma for the Gaussian function
 * @return a new Image containing the result
 */
export function gaussianBlur( source : Image, sigma : number ) : Image {
    throw new Error("Not implemented");
}

/**
 * Problem 3.1 - Quantize - Solution provided
 */
export function quantize( source : Image ) : Image {
    const gray = grayscale(source);
    const result = new Image(source.width, source.height);
    for( let y = 0; y < source.height; y++ ) {
        for( let x = 0; x < source.width; x++ ) {
            let p = gray.getPixel(x,y);
            let luma = p.data[0];
            let outP = new Pixel();
            if( luma > 0.5 ) {
                outP.setRgb(1,1,1);
            }
            result.setPixel(x,y,outP);
        }
    }
    return result;
}

/**
 * Problem 3.2 - Random Dither
 */
export function randomDither( source : Image ) : Image {
    throw new Error("Not implemented");
}

/**
 * Problem 3.3 - Bayer dither
 */
export function bayerDither( source : Image ) : Image {
    throw new Error("not implemented");
}

/**
 * Problem 3.4 - Floyd Steinberg Dither
 */
export function floydSteinbergDither( source : Image ) : Image {
    throw new Error("not implemented");
}

/**
 * Problem 4.1 - Zoom 
 * @param source input image
 * @param filter filter
 * @param region a region within the input image.  The output image must be a resampled version of
 *               this region only.
 * @param destWidth the width of the output image
 * @param destHeight the height of the output image
 */
export function resample( source : Image, filter: Filter, region : Rectangle, 
    destWidth : number, destHeight : number ) : Image {
        throw new Error("not implemented");
}

/**
 * Problem 4.2 - Rotate
 * 
 * Use the MNCubicFilter
 * 
 * @param source input image
 * @param angle angle of rotation in radians
 */
export function rotate( source: Image, angle : number ) : Image {
    throw new Error("not implemented");
}

/**
 * Problem 4.3 - Swirl
 * 
 * Use the MNCubicFilter
 * 
 * You can implement any image warp/swirl operation that you like here!   Have fun with this
 * one.  It doesn't need to look exactly like the example image.
 */
export function swirl( source :Image ) : Image {
    throw new Error("not implemented");
}

/**
 * An optional helper function that could be used with all problems in Part 4.  Pseudocode was provided
 * in class.
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param filter a filter
 * @param image the input image
 */
function reconstruct( x : number, y : number, filter: Filter, image: Image ) : Pixel {
    throw new Error("not implemented");
}

/**
 * Problem 5.1 - Composite
 * @param fgImage the foreground image
 * @param bgImage the background image
 * @returns a composited version of the two input images
 */
export function composite( fgImage : Image, bgImage : Image ) : Image {
    throw new Error("not implemented");
}