import {Image, loadImage} from './image';
import {GUI} from 'lil-gui';
import * as Student from './student';

let canvas = null as HTMLCanvasElement;
let context = null as CanvasRenderingContext2D;

const images : Record<string, string> = {
    cactus1: 'cactus_in_dark-small.png',
    cactus2: 'cactus-small.png',
    dog: 'dog-small.png', 
    stars: 'milky-way-small.png',
    saturn: 'saturn-small.png',
    cat: 'yawning-cat-small.png',
    goldengate: 'goldengate.jpg'
};

const state = {
    originalImage: null as Image,
    transformedImage: null as Image,
    selectedImage: images.dog,
    brightness: 0.0,
    contrast: 0.0,
    vignette: {
        innerR: 0.25,
        outerR: 1.0
    },
    position: [0,0],
    mousePreviousPosition: [0,0],
    sigma: 1.0,
    rotAngle: 0.0
};

const buttons = {
    download: () => {
        if( state.transformedImage !== null ) {
            state.transformedImage.download();
        } else if( state.originalImage !== null ) {
            state.originalImage.download();
        }
    },
    reset: () => {
        state.transformedImage = null;
        draw();
    },
    applyGrayscale: () => {
        state.transformedImage = Student.grayscale(state.originalImage);
        draw();
    },
    applyBrightness: () => {
        state.transformedImage = Student.brightness(state.originalImage, state.brightness);
        draw();
    },
    applyContrast: () => {
        state.transformedImage = Student.contrastFilter(state.originalImage, state.contrast);
        draw();
    },
    applyVignette: () => {
        state.transformedImage = Student.vignetteFilter(state.originalImage, state.vignette.innerR, state.vignette.outerR);
        draw();
    },
    applyHistogram: () => {
        state.transformedImage = Student.histogramFilter(state.originalImage);
        draw();
    },
    applyBlur: () => {
        state.transformedImage = Student.gaussianBlur(state.originalImage, state.sigma);
        draw();
    },
    applyEdge: () => {
        state.transformedImage = Student.edgeFilter(state.originalImage);
        draw();
    },
    applySharpen: () => {
        state.transformedImage = Student.sharpenFilter(state.originalImage);
        draw();
    },
    applyQuantize: () => {
        state.transformedImage = Student.quantize(state.originalImage);
        draw();
    },
    applyRandomDither: () => {
        state.transformedImage = Student.randomDither(state.originalImage);
        draw();
    },
    applyBayerDither: () => {
        state.transformedImage = Student.bayerDither(state.originalImage);
        draw();
    },
    applyFsDither: () => {
        state.transformedImage = Student.floydSteinbergDither(state.originalImage);
        draw();
    },
    applyRotate: () => {
        state.transformedImage = Student.rotate(state.originalImage, state.rotAngle * Math.PI / 180.0);
        draw();
    },
    applySwirl: () => {
        state.transformedImage = Student.swirl(state.originalImage);
        draw();
    }
};

function selectImage( name : string ) : void {
    loadImage( `img/small/${name}` ).then( (img) => {
        state.originalImage = img;
        state.transformedImage = null;
        draw();
    });
}

export function init() {
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    context = canvas.getContext("2d");
    canvas.addEventListener('mousedown', mouseDown);

    selectImage(state.selectedImage);

    const mainGui = new GUI();
    mainGui.add( state, "selectedImage", images )
        .name("Image: ")
        .onChange( selectImage );
    mainGui.add(buttons, "download").name("Download");
    mainGui.add(buttons, "reset").name("Reset");
    const colorFolder = mainGui.addFolder("Color / Luminance").close();
    colorFolder.add( buttons, 'applyGrayscale' ).name("Grayscale");
    colorFolder.add( state, 'brightness', -1.0, 1.0, 0.05).name("Brightness");
    colorFolder.add( buttons, 'applyBrightness' ).name("Apply Brightness");
    colorFolder.add( state, 'contrast', -1.0, 1.0, 0.05).name("Contrast");
    colorFolder.add( buttons, 'applyContrast' ).name("Apply Contrast");
    colorFolder.add( state.vignette, 'innerR', 0.0, 1.0, 0.05).name("Inner R");
    colorFolder.add( state.vignette, 'outerR', 0.0, 1.0, 0.05).name("Outer R");
    colorFolder.add( buttons, 'applyVignette' ).name("Vignette");
    colorFolder.add( buttons, 'applyHistogram' ).name("Histogram Eq.");
    const convFolder = mainGui.addFolder("Convolutions").close();
    convFolder.add( state, "sigma", 1, 10, 1.0 ).name("Sigma");
    convFolder.add(buttons, 'applyBlur').name("Blur");
    convFolder.add(buttons, 'applyEdge').name("Edge");
    convFolder.add(buttons, 'applySharpen').name("Sharpen");
    const ditherFolder = mainGui.addFolder("Dither").close();
    ditherFolder.add(buttons, 'applyQuantize').name("Quantize");
    ditherFolder.add(buttons, 'applyRandomDither').name("Random Dither");
    ditherFolder.add(buttons, 'applyBayerDither').name("Bayer Dither");
    ditherFolder.add(buttons, 'applyFsDither').name("Floyd-Steinberg Dither");
    const resampFolder = mainGui.addFolder("Resampling").close();
    resampFolder.add( state, "rotAngle", -90, 90, 1.0 ).name("Angle");
    resampFolder.add(buttons, 'applyRotate').name("Rotate");
    resampFolder.add(buttons, 'applySwirl').name("Swirl");
}

export function draw() {
    context.clearRect(0, 0, canvas.width, canvas.height);

    if( state.transformedImage !== null ) {
        context.putImageData(state.transformedImage.asImageData(), state.position[0] + 10, state.position[1] + 10 );
    } else if( state.originalImage !== null ) {
        context.putImageData(state.originalImage.asImageData(), state.position[0] + 10, state.position[1] + 10);
    }
}

function mouseDown(evt : MouseEvent) {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;

    state.mousePreviousPosition = [mouseX, mouseY];

    document.addEventListener('mousemove', mouseMotion);
    document.addEventListener('mouseup', mouseUp);
}

function mouseUp( evt : MouseEvent ) {
    document.removeEventListener('mousemove', mouseMotion);
    document.removeEventListener('mouseup', mouseUp);
}

function mouseMotion( evt : MouseEvent ) {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;

    const deltaX = mouseX - state.mousePreviousPosition[0];
    const deltaY = mouseY - state.mousePreviousPosition[1];

    state.mousePreviousPosition[0] = mouseX;
    state.mousePreviousPosition[1] = mouseY;
    
    state.position[0] += deltaX;
    state.position[1] += deltaY;

    draw();
}
