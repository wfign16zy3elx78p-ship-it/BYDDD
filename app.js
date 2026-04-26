import * as THREE from 'https://unpkg.com/three@0.161.0/build/three.module.js';
import { GLTFLoader } from 'https://unpkg.com/three@0.161.0/examples/jsm/loaders/GLTFLoader.js';
import { OrbitControls } from 'https://unpkg.com/three@0.161.0/examples/jsm/controls/OrbitControls.js';

const reveals = document.querySelectorAll('.reveal');
const io = new IntersectionObserver(
  (entries) => {
    entries.forEach((entry) => {
      if (entry.isIntersecting) entry.target.classList.add('visible');
    });
  },
  { threshold: 0.2 }
);
reveals.forEach((el) => io.observe(el));

const canvas = document.getElementById('carCanvas');
const loading = document.getElementById('loading');
const fallback = document.getElementById('fallback');

const renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));

const scene = new THREE.Scene();
scene.background = null;

const camera = new THREE.PerspectiveCamera(35, 1, 0.1, 100);
camera.position.set(0, 1.3, 5.5);

const ambientLight = new THREE.AmbientLight(0xffffff, 1.2);
scene.add(ambientLight);

const keyLight = new THREE.DirectionalLight(0xffffff, 2.2);
keyLight.position.set(6, 8, 5);
scene.add(keyLight);

const rimLight = new THREE.DirectionalLight(0x88aaff, 1.3);
rimLight.position.set(-7, 3, -4);
scene.add(rimLight);

const controls = new OrbitControls(camera, canvas);
controls.enableDamping = true;
controls.enablePan = false;
controls.minDistance = 3;
controls.maxDistance = 8;
controls.maxPolarAngle = Math.PI * 0.55;
controls.autoRotate = true;
controls.autoRotateSpeed = 0.8;

let carModel = null;
const paintTargets = [];
const headlightTargets = [];

function resizeRenderer() {
  const width = canvas.clientWidth;
  const height = canvas.clientHeight;
  renderer.setSize(width, height, false);
  camera.aspect = width / height;
  camera.updateProjectionMatrix();
}
window.addEventListener('resize', resizeRenderer);
resizeRenderer();

new GLTFLoader().load(
  'assets/byd-seal.glb',
  (gltf) => {
    carModel = gltf.scene;
    carModel.position.y = -0.7;
    carModel.scale.setScalar(1.2);

    carModel.traverse((obj) => {
      if (!obj.isMesh) return;

      obj.castShadow = true;
      obj.receiveShadow = true;

      const materialName = obj.material?.name?.toLowerCase() || '';
      const meshName = obj.name.toLowerCase();
      if (
        materialName.includes('paint') ||
        materialName.includes('body') ||
        meshName.includes('body')
      ) {
        paintTargets.push(obj.material);
      }
      if (
        materialName.includes('light') ||
        meshName.includes('headlight') ||
        meshName.includes('lamp')
      ) {
        obj.material.emissive = new THREE.Color('#111111');
        obj.material.emissiveIntensity = 0.2;
        headlightTargets.push(obj.material);
      }
    });

    scene.add(carModel);
    loading.hidden = true;
  },
  undefined,
  () => {
    loading.hidden = true;
    fallback.hidden = false;
  }
);

window.addEventListener('scroll', () => {
  if (!carModel) return;
  const spin = (window.scrollY / 800) * Math.PI * 2;
  carModel.rotation.y = spin;
});

canvas.addEventListener('pointerenter', () => {
  headlightTargets.forEach((mat) => {
    mat.emissive = new THREE.Color('#9cd3ff');
    mat.emissiveIntensity = 2.2;
  });
});

canvas.addEventListener('pointerleave', () => {
  headlightTargets.forEach((mat) => {
    mat.emissive = new THREE.Color('#111111');
    mat.emissiveIntensity = 0.2;
  });
});

document.querySelectorAll('.swatch').forEach((swatch) => {
  swatch.addEventListener('click', () => {
    const color = new THREE.Color(swatch.dataset.color);
    paintTargets.forEach((mat) => mat.color?.copy(color));
  });
});

function render() {
  controls.update();
  renderer.render(scene, camera);
  requestAnimationFrame(render);
}
render();
