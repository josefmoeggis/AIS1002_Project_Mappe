
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/threepp.hpp"
#include "iostream"

using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    // Setting up camera
    auto camera = PerspectiveCamera::create();
    camera->position.z = 5;

    OrbitControls controls{camera, canvas};

    // Scene creation
    auto scene = Scene::create();


    //BulletWrapper bullet(Vector3::Y * -9.81f); Save for bullet setup

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("Hello World");
    textHandle.setPosition(0, canvas.getSize().height - 30);
    textHandle.scale = 2;




    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height - 30);
    });

    float t = 0;

    canvas.animate([&](float dt) {
        renderer.render(scene, camera);
        t+=dt;



    });
}
