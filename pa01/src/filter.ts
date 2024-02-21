
/**
 * Abstract class for reconstruction filters.
 */
export abstract class Filter {
    radius : number;  // Filter radius (pixel space)

    constructor( radius : number ) {
        if( radius < 0 ) throw new Error(`Invalid radius: ${radius}`);
        this.radius = radius;
    }

    abstract evaluate1D(s : number) : number;
    abstract evaluate2D(x : number, y: number) : number;
}

/**
 * The box filter.
 */
export class BoxFilter extends Filter {

    evaluate1D(x : number) : number {
        x = Math.abs(x);
        if( x <= this.radius ) return 1.0 / (2.0 * this.radius);
        else return 0.0; 
    }

    evaluate2D( x : number, y : number ) : number {
        return this.evaluate1D(x) * this.evaluate1D(y);
    }
}

/**
 * Linear filter
 */
export class LinearFilter extends Filter {
    evaluate1D(x : number) : number {
        const scale = this.radius;
        x = Math.abs(x) / scale;
        if (x <= 1.0)
            return ( 1.0 - x ) / scale;
        return 0.0;
    }

    evaluate2D( x : number, y : number ) : number {
        return this.evaluate1D(x) * this.evaluate1D(y);
    }
}

/**
 * The cubic Mitchell-Netravalli filter.
 */
export class MNCubicFilter extends Filter {

    evaluate1D(x : number) : number {
        const scale = this.radius / 2.0;
        x = Math.abs(x) / scale;
        const x1 = (1 - x);
        const x2 = (2 - x);
        const c = 1.0 / (18.0 * scale);
    
        if( x < 1 ) {
            return (-21.0 * x1 * x1 * x1 + 27.0 * x1 * x1 + 9.0 * x1 + 1.0) * c;
        } else if( x < 2 ) {
            return (7.0 * x2 * x2 * x2 - 6.0 * x2 * x2) * c;
        } else {
            return 0.0;
        }
    }

    evaluate2D( x : number, y : number ) : number {
        return this.evaluate1D(x) * this.evaluate1D(y);
    }
}
