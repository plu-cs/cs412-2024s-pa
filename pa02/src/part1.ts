import GUI from 'lil-gui';
import * as Shapes from './shapes';
import {mat4} from 'gl-matrix';
import { WireframeMesh } from './wireframe-mesh';

// Add any module level variables here

// Called when the angle is changed in the GUI.  The angle is provided in degrees.
export function angleChanged( angle : number ) : void {
    // TODO: implement this method (replace the console.log)
    console.log(`angle changed = ${angle}`);

    draw();  // Draw the scene (indirectly calls drawShapes below)
}

// Called when the scale is changed in the GUI.
export function scaleChanged( value : number ) : void {
    // TODO: implement this method (replace the console.log)
    console.log(`scale changed = ${value}`);

    draw();  // Draw the scene (indirectly calls drawShapes below)
}

// Called when the mouse button is pressed down.
// x and y is the mouse position
export function mouseDown( x : number, y : number ) : void {
    // TODO: implement this method (replace console.log)
    console.log(`mouseDown: ${x} ${y}`);

    draw();  // Draw the scene (indirectly calls drawShapes below)
}

// Called when the mouse is moved while the button is pressed down.
// x and y is the mouse position
export function mouseDrag( x : number, y : number ) : void {
    // TODO: implement this method (replace console.log)
    console.log(`mouseDrag: ${x} ${y}`);

    draw();  // Draw the scene (indirectly calls drawShapes below)
}

// Do not call this method directly.  This method is called by code within the main module.
// Instead, call Main.draw(), which will clear the screen and then call this method.
export function drawShapes( ctx : CanvasRenderingContext2D ) : void {
    
    // TODO: modify the code below to apply appropriate transformation matrices to each
    // object (see assignment).  For each object, set up the transformation matrix and
    // pass it to the `draw` method.  Currently, we're just passing the identity matrix.

    const m = mat4.create();  // Create an identity matrix

    ctx.strokeStyle = "red";
    scene.leftCube.draw(ctx, m);
    
    ctx.strokeStyle = "blue";
    scene.rightCube.draw(ctx, m);

    ctx.strokeStyle = "black";
    scene.sphere.draw(ctx, m);
}

///////////////////////////////////////////////////////////
///////////  Do not modify the code below /////////////////
///////////////////////////////////////////////////////////

let canvas = null as HTMLCanvasElement;

export const scene = {
    sphere:    null as WireframeMesh,
    leftCube:  null as WireframeMesh,
    rightCube: null as WireframeMesh
};

export const controller = {
    draw,
    init,
    resize: () => {}
};

const guiState = {
    angle: 0.0,
    scale: 1.0
};

function setupScene() {
    const m = mat4.create();
    mat4.translate(m, m, [0,0,0]);
    scene.sphere = (Shapes.sphere(0.25, 20, 30, m));

    mat4.identity(m);
    mat4.translate(m, m, [-.7,0,-1]);
    scene.leftCube = (Shapes.cube(0.4, m));

    mat4.identity(m);
    mat4.translate(m, m, [.7,0,0]);
    scene.rightCube = (Shapes.cube(0.4, m));
}

function init() {
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    canvas.addEventListener('mousedown', (evt) => {
        const mouseX = evt.pageX - canvas.offsetLeft;
        const mouseY = evt.pageY - canvas.offsetTop;
        if( evt.button === 0 ) {
            document.addEventListener('mousemove', mouseMotion);
            document.addEventListener('mouseup', mouseUp);

            mouseDown(mouseX, mouseY);
        }
    });

    const gui = new GUI();
    gui.add( guiState, "angle", -180.0, 180.0 ).name("Cube rotation: ")
        .onChange((v : number) => angleChanged(v));
    gui.add( guiState, "scale", 1, 10.0 ).name("Sphere scale: ")
        .onChange((v : number) => scaleChanged(v));

    setupScene();
    draw();
}

function draw() {
    const ctx = canvas.getContext('2d');
    
    ctx.fillStyle = 'rgb(255,255,255)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    ctx.strokeStyle = 'rgb(0,0,0)';
    if( scene.sphere !== null ) drawShapes(ctx);
}

function mouseMotion( evt : MouseEvent ) : void {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;
    mouseDrag(mouseX, mouseY);
}

function mouseUp( evt : MouseEvent ) : void {
    document.removeEventListener('mousemove', mouseMotion);
    document.removeEventListener('mouseup', mouseUp);
}