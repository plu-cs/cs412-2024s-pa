import * as DefaultController from './main-default';
import * as CompositeController from './main-composite';
import * as ZoomController from './main-zoom';

window.addEventListener("DOMContentLoaded", main);
window.addEventListener('resize', onWindowResize, false);

type controller = {
    draw: () => void,
    init: () => void
};
const mainController : controller = {
    draw: null,
    init: null
};

function main() {
    const hash = window.location.hash;

    if( hash === "#zoom" ) {
        mainController.init = ZoomController.init;
        mainController.draw = ZoomController.draw;
    } else if( hash === "#composite" ) {
        mainController.init = CompositeController.init;
        mainController.draw = CompositeController.draw;
    } else {
        mainController.init = DefaultController.init;
        mainController.draw = DefaultController.draw;
    }
    mainController.init();
    onWindowResize();
}

function onWindowResize() {
    const canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    const container = document.getElementById('canvas-container') as HTMLElement;
    
    // Resize the canvas
    let width = container.clientWidth // width with padding
    let height = container.clientHeight // height with padding

    canvas.width = width;
    canvas.height = height;

    mainController.draw();
}