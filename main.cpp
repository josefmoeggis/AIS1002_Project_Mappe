
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/threepp.hpp"
#include "iostream"
#include "AirObject.hpp"

using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    // Setting up camera
    auto camera = PerspectiveCamera::create(60, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = -150;

    OrbitControls controls{camera, canvas};

    // Scene creation
    auto scene = Scene::create();


    //BulletWrapper bullet(Vector3::Y * -9.81f); Save for bullet setup

//    renderer.enableTextRendering();
//    auto& textHandle = renderer.textHandle("Hello World");
//    textHandle.setPosition(0, canvas.getSize().height - 30);
//    textHandle.scale = 1;


//    Testing AirObject
    STLLoader loader;
    auto aircraft1 = loader.load("C:/Users/joelo/GitHub_projects/AIS2001_AerofoilTesting/resources/B737_800.stl"); // Make relative and figure out bug
    auto material1 = MeshPhongMaterial::create();
    material1->flatShading = true;
    material1->color = Color::beige;
    auto Boeing = AirObject::create(aircraft1, material1);
    Boeing->position.x  = 50;
    scene->add(Boeing);


//    Add light
    auto light = HemisphereLight::create(Color::aliceblue, Color::grey);
    scene->add(light);



    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
//        textHandle.setPosition(0, size.height - 30);
    });

    float t = 0;

    canvas.animate([&](float dt) {
        renderer.render(scene, camera);

        t+=dt;



    });
}
