import {controller as part1controller} from './main1';
import {controller as part2controller} from './main2';
import {controller as part3controller} from './main3';

window.addEventListener("DOMContentLoaded", main);

type controller = {
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
    } else {
        mainController = part1controller;
    }

    mainController.init();
    window.addEventListener( "resize", mainController.resize );
}
