import GUI from 'lil-gui';
import { GLMesh } from './glmesh';
import * as Shapes from './gl-shapes';
import { ShaderProgram } from './shader';
import {mat4} from 'gl-matrix';
import vertSource from './shader/part4.vert.glsl';
import fragSource from './shader/part4.frag.glsl';

////////////////////////////////////////////////////////////////////
//  Do not modify the code below, your work for part 4 
//  is in src/shader/part4.vert.glsl
/////////////////////////////////////////////////////////////////////

let canvas = null as HTMLCanvasElement;

let gl = null as WebGL2RenderingContext;
let shader = null as ShaderProgram;

const shapes : Record<string, GLMesh> = {};

const mView : mat4 = mat4.create();

const guiState = {
    cubeRotation: 0.0,
    mousePrevious: [0,0],
    viewRotation: 0.0,
    lightPositionX: 10.0,
    lightPositionY: 5.0,
    lightPositionZ: 0.0
};

export const controller = {
    draw,
    init,
    resize
};

function init() {
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    gl = canvas.getContext('webgl2');
    canvas.addEventListener('mousedown', mouseDown);

    const gui = new GUI();
    gui.add( guiState, "cubeRotation", -180.0, 180.0 ).name("Cube rotation: ")
        .onChange( draw );
    gui.add( guiState, 'lightPositionX', -10, 10 ).name("Light Position X").onChange(draw);
    gui.add( guiState, 'lightPositionY', -10, 10 ).name("Light Position Y").onChange(draw);
    gui.add( guiState, 'lightPositionZ', -10, 10 ).name("Light Position Z").onChange(draw);

    shader = ShaderProgram.compile( gl, vertSource, fragSource );
    shader.use(gl);

    shapes['sphere'] = new GLMesh( gl, Shapes.sphere() );
    shapes['cube'] = new GLMesh( gl, Shapes.cube(0.4) );

    gl.clearColor(0.2, 0.2, 0.2, 1.0);
    gl.enable(gl.DEPTH_TEST);

    draw();
}

export function draw() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Set light position
    gl.uniform3f( shader.uniform(gl,'uLightPosition'), 
        guiState.lightPositionX, guiState.lightPositionY, guiState.lightPositionZ );

    // Set view matrix
    mat4.identity(mView);
    mat4.translate(mView, mView, [0,0,-2.5]);
    mat4.rotateX(mView,mView,guiState.viewRotation);
    gl.uniformMatrix4fv( shader.uniform(gl,'mView'), false, mView);

    // Draw shapes
    const m = mat4.create();
    mat4.scale(m, m, [0.25, 0.25, 0.25]);
    gl.uniformMatrix4fv(shader.uniform(gl,'mModel'), false, m);
    shapes['sphere'].render(gl);
    
    mat4.identity(m);
    mat4.rotateY(m, m, guiState.cubeRotation * Math.PI / 180.0);
    mat4.translate(m, m, [-.7,0,-1]);
    gl.uniformMatrix4fv(shader.uniform(gl,'mModel'), false, m);
    shapes['cube'].render(gl);

    mat4.identity(m);
    mat4.rotateY(m, m, guiState.cubeRotation * Math.PI / 180.0);
    mat4.translate(m, m, [.7,0,0]);
    gl.uniformMatrix4fv(shader.uniform(gl,'mModel'), false, m);
    shapes['cube'].render(gl);
}

function resize() {
    const container = document.getElementById('canvas-container');
    
    gl.viewport(0,0,canvas.width, canvas.height);

    const aspect = canvas.width / canvas.height;
    const proj = mat4.perspective(mat4.create(), 35.0 * Math.PI / 180.0, aspect, 0.1, 1000.0);
    gl.uniformMatrix4fv( shader.uniform(gl, 'mProjection'), false, proj);
}

function mouseDown( evt : MouseEvent ) : void {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;
    if( evt.button === 0 ) {
        document.addEventListener('mousemove', mouseMotion);
        document.addEventListener('mouseup', mouseUp);

        guiState.mousePrevious[0] = mouseX;
        guiState.mousePrevious[1] = mouseY;
    }
}

function mouseMotion( evt : MouseEvent ) : void {
    const mouseX = evt.pageX - canvas.offsetLeft;
    const mouseY = evt.pageY - canvas.offsetTop;

    const deltaY = mouseY - guiState.mousePrevious[1];

    guiState.viewRotation += deltaY * 0.05;

    guiState.mousePrevious[0] = mouseX;
    guiState.mousePrevious[1] = mouseY;
    draw();
}

function mouseUp( evt : MouseEvent ) : void {
    document.removeEventListener('mousemove', mouseMotion);
    document.removeEventListener('mouseup', mouseUp);
}
