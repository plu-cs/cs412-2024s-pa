import {GUI, Controller} from 'lil-gui';
import {Image, loadImage} from './image';
import {LinearFilter, BoxFilter, Filter, MNCubicFilter} from './filter';
import {resample} from './student';
import { Rectangle } from './rectangle';

let canvas = null as HTMLCanvasElement;
let context = null as CanvasRenderingContext2D;

const images : Record<string, string> = {
    cactus: 'small/cactus_in_dark-small.png',
    dog: 'small/dog-small.png', 
    stars: 'small/milky-way-small.png',
    saturn: 'small/saturn-small.png',
    lines: 'small/lines-50.png'
};

const filters : Record<string, Filter> = {
    box: new BoxFilter(1.0),
    linear: new LinearFilter(1.0),
    cubic: new MNCubicFilter(2.0)
};

const state = {
    originalImage: null as Image,
    transformedImage: null as Image,
    imageSizeStr: "",
    position: [0,0],
    image: images['cactus'],
    filter: filters.box,
    filterRadius: 1.0,
    zoomRegion: new Rectangle(0, 0, 100, 100),
    zoomPct: 10,
    drawRegion: false,
    mousePreviousPosition: [0,0],
    regionStart: [0,0]
};

const buttons = {
    resetButton: () => { 
        state.position = [0,0]; 
        controllers.setImageSizeStr( state.originalImage );
        draw();
    },
    selectAll: () => {
        state.zoomRegion.set(0, 0, state.originalImage.width, state.originalImage.height);
        controllers.updateZoomRegionView();
        draw();
    },
    apply: () => {
        const scale = state.zoomPct / 100.0;
        const regionW = state.zoomRegion.maxx - state.zoomRegion.minx;
        const regionH = state.zoomRegion.maxy - state.zoomRegion.miny;
        const width = Math.round( regionW * scale );
        const height = Math.round( regionH * scale );
        state.filter.radius = state.filterRadius;
        state.transformedImage = resample(state.originalImage, state.filter, state.zoomRegion, width, height);
        state.drawRegion = false;
        controllers.drawRegionController.updateDisplay();
        draw();
    },
    download: () => {
        if( state.transformedImage !== null ) {
            state.transformedImage.download();
        }
    }
};

const controllers = {
    imageSizeStrController: null as Controller,
    zoomRegionControllers: [] as Array<Controller>,
    drawRegionController: null as Controller,
    setImageSizeStr: ( img: Image ) => {
        controllers.imageSizeStrController.setValue( `${img.width} x ${img.height}` );
    },
    updateZoomRegionView: () => {
        controllers.zoomRegionControllers.forEach( (c) => c.updateDisplay());
    }
};  

function mouseDown(evt : MouseEvent) {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;

    if( state.drawRegion ) {
        const x = mouseX - state.position[0];
        const y = mouseY - state.position[1];
        if( x < 0 || x > state.originalImage.width || y < 0 || y > state.originalImage.height ) return;
        state.regionStart[0] = x;
        state.regionStart[1] = y;
        updateRegionMouseDrag(x,y);
        draw();
    }

    state.mousePreviousPosition = [mouseX, mouseY];

    document.addEventListener('mousemove', mouseMotion);
    document.addEventListener('mouseup', mouseUp);
}

function updateRegionMouseDrag( x : number, y: number ) {
    let lowx = Math.min( x, state.regionStart[0] );
    let lowy = Math.min( y, state.regionStart[1] );
    let highx = Math.max( x, state.regionStart[0] );
    let highy = Math.max( y, state.regionStart[1] );
    
    state.zoomRegion.set(
        clamp( lowx, 0, state.originalImage.width ),
        clamp( lowy, 0, state.originalImage.height ),
        clamp( highx, 0, state.originalImage.width ),
        clamp( highy, 0, state.originalImage.height ) );

    controllers.updateZoomRegionView();
}

function clamp( value : number, min: number, max :number ) : number {
    return Math.min( max, Math.max(value, min) );
}

function mouseUp( evt : MouseEvent ) {
    document.removeEventListener('mousemove', mouseMotion);
    document.removeEventListener('mouseup', mouseUp);
}

function mouseMotion( evt : MouseEvent ) {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;

    if( state.drawRegion ) {
        const x = mouseX - state.position[0];
        const y = mouseY - state.position[1];
        updateRegionMouseDrag(x, y);
    } else {
        const deltaX = mouseX - state.mousePreviousPosition[0];
        const deltaY = mouseY - state.mousePreviousPosition[1];

        state.mousePreviousPosition[0] = mouseX;
        state.mousePreviousPosition[1] = mouseY;
        
        state.position[0] += deltaX;
        state.position[1] += deltaY;
    }
    draw();
}

export function init() {
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    context = canvas.getContext("2d");
    canvas.addEventListener('mousedown', mouseDown);

    const mainGui = new GUI();
    mainGui.add( state, "image", images )
        .name("Image: ")
        .onChange( selectImage );
    mainGui.add( buttons, 'resetButton' ).name("Reset");
    mainGui.add(buttons, 'download').name("Download");
    controllers.imageSizeStrController = mainGui.add( state, "imageSizeStr" ).name("Size").disable();
    const zoomGui = mainGui.addFolder("Zoom");
    controllers.drawRegionController = zoomGui.add( state, "drawRegion" );
    const lowxCtl = zoomGui.add( state.zoomRegion, "minx" ).name("low x").onFinishChange( (val: number) => {
        state.zoomRegion.minx = clamp(val, 0, state.originalImage.width);
        controllers.updateZoomRegionView();
        draw();
    } );
    const lowyCtl = zoomGui.add( state.zoomRegion, "miny" ).name("low y").onFinishChange((val: number) => {
        state.zoomRegion.miny = clamp(val, 0, state.originalImage.height);
        controllers.updateZoomRegionView();
        draw();
    });
    const highxCtl = zoomGui.add( state.zoomRegion, "maxx" ).name("high x").onFinishChange((val: number) => {
        state.zoomRegion.maxx = clamp(val, 0, state.originalImage.width);
        controllers.updateZoomRegionView();
        draw();
    });
    const highyCtl = zoomGui.add( state.zoomRegion, "maxy" ).name("high y").onFinishChange((val: number) => {
        state.zoomRegion.maxy = clamp(val, 0, state.originalImage.height);
        controllers.updateZoomRegionView();
        draw();
    });
    controllers.zoomRegionControllers.push( lowxCtl, lowyCtl, highxCtl, highyCtl);
    zoomGui.add( state, "zoomPct", 1, 1000, 5).name("Zoom %");
    zoomGui.add( buttons, "selectAll" ).name("Select All");

    const filterGui = mainGui.addFolder("Filter");
    filterGui.add( state, "filter", filters ).name("Filter");
    filterGui.add( state, "filterRadius", 1.0, 20.0, 1.0 ).name("Filter radius:");
    filterGui.add( buttons, "apply" ).name("Apply");

    selectImage(images['cactus']);
}

function selectImage( name : string ) {
    loadImage( `img/${name}` ).then( (img) => {
        state.originalImage = img;
        buttons.resetButton();
        buttons.selectAll();
    });
}

export function draw() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    if( state.originalImage !== null ) {
        context.putImageData(state.originalImage.asImageData(), state.position[0], state.position[1]);
        context.strokeStyle = "rgb(255,0,0)";
        context.strokeRect(
            state.zoomRegion.minx + state.position[0], 
            state.zoomRegion.miny + state.position[1], 
            state.zoomRegion.maxx - state.zoomRegion.minx, 
            state.zoomRegion.maxy - state.zoomRegion.miny );

        if( state.transformedImage !== null ) {
            context.putImageData(state.transformedImage.asImageData(), state.position[0], 
                state.position[1] + state.originalImage.height + 20);
        }
        
    }
}