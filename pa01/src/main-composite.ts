import GUI, { Controller } from 'lil-gui';
import {Image, loadImage} from './image';
import * as Student from './student';

let canvas = null as HTMLCanvasElement;
let context = null as CanvasRenderingContext2D;

const bgImages : Record<string, string> = {
    cactus: 'small/cactus_in_dark-small.png',
    stars: 'small/milky-way-small.png',
    saturn: 'small/saturn-small.png'
};

const fgImages : Record<string, string> = {
    dog: 'alpha/dog-alpha.png',
    cat: 'alpha/yawning-cat-alpha.png'
};

const state : Record<string, any> = {
    bgImage: null as Image,
    fgImage: null as Image,
    compositeImage: null as Image,
    position: [0,0],
    fgImageName: fgImages['dog'],
    bgImageName: bgImages['stars'],
    mousePreviousPosition: [0,0]
};

const buttons = {
    composeButton: () => {
        state.compositeImage = Student.composite( state.fgImage, state.bgImage );
        draw();
    }
};

export function init() {
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    context = canvas.getContext("2d");
    canvas.addEventListener('mousedown', mouseDown);

    const mainGui = new GUI();
    mainGui.add( state, "fgImageName", fgImages )
        .name("Foreground: ")
        .onChange( (value : string) => selectImage(value, 'fgImage') );
    mainGui.add( state, "bgImageName", bgImages )
        .name("Background: ")
        .onChange( (value : string) => selectImage(value, 'bgImage') );
    mainGui.add( buttons, 'composeButton' ).name("Compose");

    selectImage(state.fgImageName, 'fgImage');
    selectImage(state.bgImageName, 'bgImage');
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

function selectImage( name : string, target : string ) {
    loadImage( `img/${name}` ).then( (img) => {
        state[target] = img;
        draw();
    });
}

export function draw() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    if( state.fgImage !== null ) {
        context.putImageData(state.fgImage.asImageData(), state.position[0], state.position[1]);
    }
    if( state.bgImage !== null ) {
        context.putImageData(state.bgImage.asImageData(), state.position[0] + 620, state.position[1]);
    }
    if( state.compositeImage !== null ) {
        context.putImageData(state.compositeImage.asImageData(), state.position[0] + 310, state.position[1] + 420);
    }
}