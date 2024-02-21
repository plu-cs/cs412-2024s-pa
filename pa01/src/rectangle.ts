
/**
 * Utility class for representing a rectangle.  Used to target a region of an image.
 */
export class Rectangle {
    minx: number;  // Minimum x coordinate
    miny: number;  // Minimum y coordinate
    maxx: number;  // Maximum x coordinate
    maxy: number;  // Maximum y coordinate

    constructor( minx : number, miny: number, maxx: number, maxy: number ) {
        this.set(minx, miny, maxx, maxy);
    }

    /**
     * Set the dimensions of this Rectangle.
     * 
     * @param minx Minimum x coordinate
     * @param miny Minimum y coordinate
     * @param maxx Maximum x coordinate
     * @param maxy Maximum y coordinate
     */
    set( minx : number, miny: number, maxx: number, maxy: number ) : void {
        this.minx = minx;
        this.miny = miny;
        this.maxx = maxx;
        this.maxy = maxy;
    }

    /**
     * @returns the width of this Rectangle
     */
    width() {
        return this.maxx - this.minx;
    }

    /**
     * @returns the height of this Rectangle
     */
    height() {
        return this.maxy - this.miny;
    }
}