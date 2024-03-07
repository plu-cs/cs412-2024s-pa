import GUI from 'lil-gui';
import * as Shapes from './shapes';
import { WireframeMesh } from './wireframe-mesh';
import {mat4} from 'gl-matrix';

// TODO - Part 2 - Implement these methods as described in the assignment.

// Called when the angle is changed in the GUI.  angle is provided in degrees.
export function redSphereAngleChanged( angle : number ) : void {
    draw();
}   

// Called when the green sphere's angle is changed in the GUI.  angle is in degrees.
export function greenSphereAngleChanged( angle : number ) : void {
    draw();
}   

// Called when the cylinder's scale is changed in the GUI.
export function cylinderScaleChanged( value : number ) : void {
    draw();
}

// Do not call this method directly.  This method is called by code within the main module.
// Instead, call draw(), which will clear the screen and then call this method.
export function drawShapes( ctx : CanvasRenderingContext2D ) : void {
    const m = mat4.create();

    ctx.strokeStyle = "red";
    scene.sphere1.draw(ctx, m);

    ctx.strokeStyle = "green";
    scene.sphere2.draw(ctx, m);
    
    ctx.strokeStyle = "blue";
    scene.cylinder.draw(ctx, m);
}

///////////////////////////////////////////////////////////
///////////  Do not modify the code below /////////////////
///////////////////////////////////////////////////////////

let canvas = null as HTMLCanvasElement;

export const scene = {
    sphere1:   null as WireframeMesh,
    sphere2:   null as WireframeMesh,
    cylinder:  null as WireframeMesh
};

export const controller = {
    draw,
    init,
    resize: () => {}
};

const guiState = {
    redSphereAngle: 0.0,
    greenSphereAngle: 0.0,
    cylinderScale: 1.0
};

function setupScene() {
    const m = mat4.create();
    mat4.translate(m, m, [-0.5,0.5,0]);
    scene.sphere1 = Shapes.sphere(0.25, 20, 30, m);

    mat4.identity(m);
    mat4.translate(m, m, [0.1,-0.3,0]);
    scene.sphere2 = Shapes.sphere(0.05, 12, 12, m);

    mat4.identity(m);
    mat4.translate(m, m, [.5,0,0]);
    mat4.rotateZ(m, m, 45.0 * Math.PI / 180.0);
    mat4.scale(m, m, [1,0.75,1]);
    mat4.translate(m, m, [0,-0.5,0]);
    scene.cylinder = Shapes.cylinder(0.15, 30, 30, m);
}

function init() {
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;

    let value = { value: 10 };
    const gui = new GUI();
    gui.add( guiState, "redSphereAngle", -180.0, 180.0 ).name("Red sphere rotation: ")
        .onChange((v : number) => redSphereAngleChanged(v));
    gui.add( guiState, "greenSphereAngle", -180.0, 180.0 ).name("Green sphere rotation: ")
        .onChange((v : number) => greenSphereAngleChanged(v));
    gui.add( guiState, "cylinderScale", 0.5, 10.0 ).name("Cylinder scale: ")
        .onChange((v : number) => cylinderScaleChanged(v));

    setupScene();
    draw();
}

export function draw() {
    const ctx = canvas.getContext('2d');
    
    ctx.fillStyle = 'rgb(255,255,255)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    ctx.strokeStyle = 'rgb(0,0,0)';
    if( scene.sphere1 !== null ) drawShapes(ctx);
}
