
enum ColorSpace {
    RGB, HSL
};

/**
 * Objects of this class represent the color of a pixel in some color space.  The default
 * color space is RGB.  It includes the alpha component as a separate component.  All 4 components
 * should range between 0.0 and 1.0.  If they are out of that range, the results of some operations
 * are undefined.
 */
export class Pixel {
    data   : number[];   // [R,G,B] or [H,S,L], etc.
    alpha  : number;   
    cSpace : ColorSpace;

    constructor( c1 : number = 0, c2 : number = 0, c3 : number = 0, a : number = 1, space: ColorSpace = ColorSpace.RGB ) {
        this.data = [0,0,0];
        this.alpha = a;

        this.data[0] = c1;
        this.data[1] = c2;
        this.data[2] = c3;
        this.cSpace = space;
    }

    /**
     * Set this pixel to the given values in RGB space.
     * @param red 
     * @param green 
     * @param blue 
     */
    setRgb( red : number, green : number, blue : number ) : void {
        this.cSpace = ColorSpace.RGB;
        this.data[0] = red;
        this.data[1] = green;
        this.data[2] = blue;
    }

    /**
     * @param val a value that will be used to scale each of the color components
     * @returns a new Pixel that is equal to this Pixel, scaled by val.
     */
    scale( val : number ) : Pixel {
        return new Pixel( this.data[0] * val, this.data[1] * val, this.data[2] * val, this.alpha, this.cSpace );
    }

    /**
     * @param p a Pixel to add to this one
     * @returns a new Pixel that is equal to this Pixel plus p
     */
    add( p : Pixel ) : Pixel {
        return new Pixel(this.data[0] + p.data[0], this.data[1] + p.data[1], this.data[2] + p.data[2], this.alpha, this.cSpace );
    }

    /**
     * @returns the luminance of this Pixel.  The color space must be RGB, or this throws Error.
     */
    luminance( ) : number {
        if( this.cSpace !== ColorSpace.RGB ) throw new Error("Color space must be RGB.");
        return 0.2126 * this.data[0] + 0.7152 * this.data[1] + 0.0722 * this.data[2];
    }

    /**
     * Assures that the color and alpha components are between 0.0 and 1.0.  If not, they are clamped
     * to the nearest end of that range.
     */
    clamp() {
        this.data[0] = Math.min(1, Math.max(this.data[0], 0));
        this.data[1] = Math.min(1, Math.max(this.data[1], 0));
        this.data[2] = Math.min(1, Math.max(this.data[2], 0));
        this.alpha   = Math.min(1, Math.max(this.alpha, 0));
    };

    /**
     * Converts from RGB to HSL space:  Algorithm based on: https://en.wikipedia.org/wiki/HSL_and_HSV and
     *   https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
     *
     * @returns a new Pixel that is as close as possible to the same color in the HSL color
     * space.  This pixel must be in RGB space, otherwise an error is thrown.
     */
    rgbToHsl() : Pixel {
        if( this.cSpace !== ColorSpace.RGB ) throw new Error("Color space must be RGB.");

        const r = this.data[0],
              g = this.data[1],
              b = this.data[2];
        const max = Math.max(r, g, b),
              min = Math.min(r, g, b);
        let h, s, l = (max + min) / 2;
    
        if ( max === min ) {
            h = s = 0; // achromatic
        } else {
            let d = max - min;
            s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
            switch( max ) {
                case r: h = (g - b) / d + (g < b ? 6 : 0); break;
                case g: h = (b - r) / d + 2; break;
                case b: h = (r - g) / d + 4; break;
            }
            h /= 6;
        }
    
        return new Pixel(h, s, l, this.alpha, ColorSpace.HSL);
    }

    /**
     * Converts from HSL to RGB space:  Algorithm based on: https://en.wikipedia.org/wiki/HSL_and_HSV and
     *   https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
     *
     * @returns a new Pixel that is as close as possible to the same color in the RGB color
     * space.  This pixel must be in HSL space, otherwise an error is thrown.
     */
    hslToRgb() : Pixel {
        if( this.cSpace !== ColorSpace.HSL ) throw new Error("Color space must be HSL.");

        const h = this.data[0];
        const s = this.data[1];
        const l = this.data[2];
      
        var hueToRGB = function( m1 : number, m2 : number, h : number ) {
            h = ( h < 0 ) ? h + 1 : ((h > 1) ? h - 1 : h);
            if ( h * 6 < 1 ) return m1 + (m2 - m1) * h * 6;
            if ( h * 2 < 1 ) return m2;
            if ( h * 3 < 2 ) return m1 + (m2 - m1) * (0.66666 - h) * 6;
            return m1;
        };
      
        const m2 = (l <= 0.5) ? l * (s + 1) : l + s - l * s;
        const m1 = l * 2 - m2;
        return new Pixel(
          hueToRGB( m1, m2, h + 1 / 3 ),
          hueToRGB( m1, m2, h         ),
          hueToRGB( m1, m2, h - 1 / 3 ),
          this.alpha,
          ColorSpace.RGB
        );
    }
}

// An invisible canvas used for converting images to ImageData objects
const imageCanvas : HTMLCanvasElement = document.createElement('canvas');

/**
 * A class that represents an image.
 */
export class Image {
    #pixels : Uint8ClampedArray;  // The pixel data
    #w : number;  // Width
    #h : number;  // Height

    get width() : number { return this.#w; }
    get height() : number { return this.#h; }

    constructor( width : number, height : number, imageData : ImageData = null ) {
        this.#w = width;
        this.#h = height;
        this.#pixels = imageData === null ? new Uint8ClampedArray( 4 * width * height ) : imageData.data;
    }

    private pixelIndex( x : number, y : number ) : number {
        return 4 * (y * this.#w + x);
    }

    /**
     * Returns the color at the given location.  The origin is the upper left corner of the image,
     * and the y coordinate increases downward from the origin.  
     * 
     * @param x the x coordinate.  Must be an integer, such that 0 <= x < width
     * @param y the y coordinate.  Must be an integer, such that 0 <= y < height
     * @returns a Pixel representing the color at that location.  Modifying the returned Pixel object does not change
     * the image.  To do so, use setPixel.
     */
    getPixel( x : number, y : number ) : Pixel {
        const idx = this.pixelIndex(x,y);
        return new Pixel(
            this.#pixels[idx+0] / 255,
            this.#pixels[idx+1] / 255,
            this.#pixels[idx+2] / 255,
            this.#pixels[idx+3] / 255
        );
    }

    /**
     * Modifies the color of a pixel at the given location.  
     * 
     * @param x the x coordinate.  Must be an integer, such that 0 <= x < width
     * @param y the y coordinate.  Must be an integer, such that 0 <= y < height
     * @param value the value that will be used to modify the pixel in this image.
     */
    setPixel( x : number, y : number, value : Pixel ) : void {
        if( value.cSpace !== ColorSpace.RGB ) throw new Error("Color space must be RGB");
        const idx = this.pixelIndex(x, y);
        this.#pixels[idx+0] = value.data[0] * 255;
        this.#pixels[idx+1] = value.data[1] * 255;
        this.#pixels[idx+2] = value.data[2] * 255;
        this.#pixels[idx+3] = value.alpha * 255;
    }

    /**
     * @returns a new ImageData object that can be used for display in a canvas
     */
    asImageData() : ImageData {
        return new ImageData( this.#pixels, this.#w, this.#h );
    }

    /**
     * Send the image to the browser for downloading as a PNG file.
     * 
     * @param fileName the file name, defaults to "download.png"
     */
    download( fileName : string = "download.png" ) : void {
        const ctx = imageCanvas.getContext('2d');
        imageCanvas.width = this.width;
        imageCanvas.height = this.height;
        ctx.putImageData(this.asImageData(), 0, 0);
        const image = imageCanvas.toDataURL("image/png");
        const aEl = document.createElement('a');
        aEl.setAttribute("download", fileName);
        aEl.setAttribute("href", image);
        aEl.click();
        aEl.remove();
    }
}

/**
 * Asynchronous function for downloading images and converting to Image objects.
 * 
 * @param path the absolute or relative URL of the file to download
 * @returns a Promise that resolves to an Image object upon success.
 */
export function loadImage( path : string ) : Promise<Image> {
    const imageElement : HTMLImageElement = document.createElement('img');
    return new Promise<Image>( (resolve, reject) => {
        imageElement.addEventListener('load', (e) => {
            const image = e.target as HTMLImageElement;
            const ctx = imageCanvas.getContext('2d');
            imageCanvas.width = image.width;
            imageCanvas.height = image.height;
            ctx.drawImage(image, 0, 0);
            const id = ctx.getImageData(0,0,image.width, image.height);
            imageCanvas.width = 1;
            imageCanvas.height = 1;    
            resolve( new Image(image.width, image.height, id) );
        });
        imageElement.addEventListener('error', () => {
            const message = `Failed to load image: ${path}`;
            reject(message);
        });
        imageElement.src = path;
    }).finally( () => imageElement.remove() );
}