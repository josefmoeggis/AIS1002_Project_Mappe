// Remember continuous integration kopier fra threepp config file
#include "include/AirObject.hpp"
#include "include/Graph3D.hpp"
#include "include/GUI.hpp"
#include "include/SceneSetup.hpp"
#include "threepp/renderers/GLRenderer.hpp"
#include "threepp/helpers/AxesHelper.hpp"
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/controls/OrbitControls.hpp"


using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas{Canvas::Parameters().size({1280, 720})
                    .title("Aircraft Lift 3D graph").favicon("resources/airplane_2_icon.jpeg")};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

//    Setting up visual axes
    auto axes = AxesHelper::create(100);

    // Setting up camera
    auto camera = PerspectiveCamera::create(60, canvas.getAspect(), 0.1f, 3000);
    camera->position.x = 600;
    OrbitControls controls{camera, canvas};

    // Scene creation
    auto scene = Scene::create();
//    scene->add(grid);
    scene->add(axes);

    //    Add light
    auto light = setLight();
    scene->add(light);

//    Setting sky
    auto mySky = setSky(light);
    scene->add(mySky);

    PID myPID(0.4, 0.01f, 0.0f);
    myPID.setWindupGuard(0.5f);

//    Controls from GUI
    ControllableParameters control(myPID);
    control.setOptrions();
    GUI myUI(canvas, control);

//    Create grid object
    Graph3D graph(1000, 20);
    graph.setPosition();
    scene->add(graph.getGrid());

    SceneSetup setup(scene, control);

    float t = 0;
    float sec = 0;

    canvas.animate([&](float dt) {
switch (control.fileChoice) {
    case 0:
        setup.loopAircraft1();
        scene = setup.getScene();
    case 1:
        setup.loopAircraft2();
        scene = setup.getScene();
    case 2:
        setup.loopAircraft3();
        scene = setup.getScene();
}


//     Testing line segments
        if (sec >= 1) {
            graph.updateLineVectors(Aircraft1.calculateLift(control.targetAirspeed), 20);
            graph.adjustGraphToFit(Aircraft1.calculateMaxLift(300));
            graph.makeLine(scene);
            scene->add(graph.getLine());
            sec = 0;
        }
        float angleGain = myPID.regulate(control.targetAngleOfAttack,
                                                  Aircraft1.getAngleOfAttack(), dt);
        Aircraft1.setControlledAngle(angleGain, 2, dt);
        Aircraft1.getMesh()->rotation.x = Aircraft1.getAngleOfAttack() + math::PI;
        renderer.render(scene, camera);
//        std::cout << Aircraft1.getAngleOfAttack() * math::RAD2DEG << std::endl;
        myUI.render();
        controls.enabled = !myUI.getMouseHover();

        t += dt;
        sec += dt;
    });
}
