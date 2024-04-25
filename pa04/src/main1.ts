import GUI from 'lil-gui';
import { LineBasicMaterial, LineSegments, Mesh, 
    MeshBasicMaterial, PerspectiveCamera, Scene, WebGLRenderer } from 'three';
import { ObjLoader } from './obj';
import {OrbitControls} from 'three/examples/jsm/controls/OrbitControls.js';
import {VertexNormalsHelper} from 'three/examples/jsm/helpers/VertexNormalsHelper.js';
import { TriMesh } from './tri-mesh';

export const controller = { init, resize };

let canvas : HTMLCanvasElement;
let scene : Scene;
let camera : PerspectiveCamera;
let renderer : WebGLRenderer;

const normalLength = 0.02;
const meshPath = 'data/bunny_high.obj';

const meshData = {
    triMesh: null as TriMesh,
    solidMesh: null as Mesh,
    edgeMesh : null as LineSegments,
    normalsHelper : null as VertexNormalsHelper
};

const buttons = {
    generate: () => {
        meshData.triMesh.generateNormals();
        const geom = meshData.triMesh.asTriangleGeometry();
        meshData.solidMesh.geometry.dispose();
        meshData.solidMesh.geometry = geom;
        if( meshData.normalsHelper !== null ) {
            scene.remove(meshData.normalsHelper);
            meshData.normalsHelper.geometry.dispose();
        }
        meshData.normalsHelper = new VertexNormalsHelper(meshData.solidMesh, normalLength);
        scene.add(meshData.normalsHelper);
    }
};

function init() {
    scene = new Scene();
    canvas = document.getElementById('main-canvas') as HTMLCanvasElement;
    camera = new PerspectiveCamera( 48, canvas.width / canvas.height, 0.1, 1000 );
    const controls = new OrbitControls(camera, canvas);
    camera.position.z = 1.5;
    renderer = new WebGLRenderer({ canvas });

    const gui = new GUI();
    gui.add( buttons, "generate" );

    ObjLoader.load(meshPath)
        .then( (objMesh) => {
            objMesh.centerAndScale();
            meshData.triMesh = objMesh.asTriMesh();
            
            const triGeom = meshData.triMesh.asTriangleGeometry();
            const triLines = meshData.triMesh.asLineGeometry();

            let meshMaterial = new MeshBasicMaterial({ 
                color: '#00ffff',
                polygonOffset: true,
                polygonOffsetFactor: 1,
                polygonOffsetUnits: 1 });
            meshData.solidMesh = new Mesh(triGeom, meshMaterial);
            meshData.edgeMesh = new LineSegments(triLines, new LineBasicMaterial({color: '#000000'}));

            scene.add(meshData.solidMesh);
            scene.add(meshData.edgeMesh);
        });

    resize();
    window.requestAnimationFrame(draw);
}

function draw() {
    renderer.render( scene, camera );
    window.requestAnimationFrame( draw );
}

function resize() {
    const container = document.getElementById('canvas-container');
    renderer.setSize( container.clientWidth, container.clientHeight );
    camera.aspect = container.clientWidth / container.clientHeight;
    camera.updateProjectionMatrix();
}