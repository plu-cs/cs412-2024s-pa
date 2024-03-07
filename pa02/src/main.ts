import {controller as part1controller} from './part1';
import {controller as part2controller} from './part2';
import {controller as part3controller} from './part3';
import {controller as part4controller} from './part4';

window.addEventListener("DOMContentLoaded", main);
window.addEventListener('resize', onWindowResize, false);

type controller = {
    draw: () => void,
    init: () => void,
    resize: () => void
};
let mainController : controller = null;

let canvas : HTMLCanvasElement = null;

function main() {
    canvas = document.querySelector('#main-canvas');
    const hash = window.location.hash;

    if( hash === "#p1" ) {
        mainController = part1controller;
    } else if( hash === "#p2" ) {
        mainController = part2controller;
    } else if( hash == "#p3" ) {
        mainController = part3controller;
    } else if( hash == "#p4" ) {
        mainController = part4controller;
    } else {
        mainController = part1controller;
    }
    mainController.init();
    onWindowResize();
}

function onWindowResize() {
    const container = document.getElementById('canvas-container');
    
    // Resize the canvas
    canvas.width = container.clientWidth;
    canvas.height = container.clientHeight;
    
    mainController.resize();
    mainController.draw();
}