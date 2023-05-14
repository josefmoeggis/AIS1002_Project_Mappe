
#include "include/AirObject.hpp"
#include "include/Graph3D.hpp"
#include "include/GUI.hpp"
#include "include/SceneSetup.hpp"
#include "threepp/renderers/GLRenderer.hpp"
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/controls/OrbitControls.hpp"
#include "threepp/objects/Group.hpp"

using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas{Canvas::Parameters().size({1920, 1080}).antialiasing(4)
                    .title("Aircraft Lift 3D graphLift").favicon("resources/airplane_2_icon.jpeg")};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    // Setting up camera
    auto camera = PerspectiveCamera::create(60, canvas.getAspect(), 0.1f, 3000);
    camera->position.x = 1000;
    OrbitControls controls{camera, canvas};

    // Scene creation
    auto scene = Scene::create();

    //    Add light
    auto light = setLight();
    scene->add(light);

//    Setting sky
    auto mySky = setSky(light);
    scene->add(mySky);

    PID anglePID(0.4, 0.01f, 0.0f);
    anglePID.setWindupGuard(0.5f);
    PID switchPID(0.4, 0.01f, 0.0f);

//    Controls from GUI
    ControllableParameters control(anglePID, 100, 0, 10, 500, 1);
    control.setOptions("resources/B737_image_min.jpeg", "Boeing 737-800", 746 * 420,
                       "resources/SAS-A321LR_min.jpeg", "Airbus A320", 1200 * 869,
                       "resources/Cessna_172S_Skyhawk.jpg", "Cessna 172", 220 * 164);
    GUI myUI(canvas, control);

    STLLoader loader;
//    Create grid object
    Graph3D graphLift(1000, 20, loader.load("resources/LiftArrow.stl"));
    graphLift.setPosition();
    Graph3D graphDrag(1000, 20, loader.load("resources/DragArrow.stl"), 0x000000, 0xFF0000); // Not adding grid to scene only graph line
    graphDrag.setPosition();
    scene->add(graphLift.getGrid());
    scene->add(graphLift.getMesh());
    scene->add(graphDrag.getMesh());


    auto airflowArrow = getAirflowArrow(loader);
    scene->add(airflowArrow);

    auto boeing = setupAircraft1(loader);
    auto airbus = setupAircraft2(loader);
    auto cessna = setupAircraft3(loader);

    std::shared_ptr<AirObject> aircraft = boeing;

    auto movementShell = Group::create();
    movementShell->add(aircraft->getMesh());
    scene->add(movementShell);

    float t = 0;
    float sec = 0;

    canvas.animate([&](float dt) {
switch (control.fileChoice) {
    case 0:
        aircraft = boeing;
        loopAircraft(movementShell, boeing, airbus, cessna, switchPID, dt);
        break;
    case 1:
        aircraft = airbus;
        loopAircraft(movementShell, airbus, cessna, boeing, switchPID, dt);
        break;
    case 2:
        aircraft = cessna;
        loopAircraft(movementShell, cessna, boeing, airbus, switchPID, dt);
        break;
}
        if (sec >= 0.1) {
            graphLift.updateLineVectors(aircraft->calculateLift(knotsToMtrPrSec(control.targetAirspeed),
                                                                celsiusToKelvin(control.targetTemp), feetToMtr(control.targetAltitude)), 200);
            graphLift.adjustGraphToFit(aircraft->calculateMaxLift(400));
            graphLift.makeLine(scene);
            scene->add(graphLift.getLine());
            graphLift.updateMesh(-10);
            graphDrag.updateLineVectors(aircraft->calculateDrag(knotsToMtrPrSec(control.targetAirspeed),
                                                                celsiusToKelvin(control.targetTemp), feetToMtr(control.targetAltitude)), 200);
            graphDrag.adjustGraphToFit(aircraft->calculateMaxDrag(knotsToMtrPrSec(400)));
            graphDrag.makeLine(scene);
            scene->add(graphDrag.getLine());
            graphDrag.updateMesh(-60);
            sec = 0;
        }
        float angleGain = anglePID.regulate(control.targetAngleOfAttack,
                                            aircraft->getAngleOfAttack(), dt);
        aircraft->setControlledAngle(angleGain, 2, dt);
        movementShell->rotation.x = aircraft->getAngleOfAttack();
        renderer.render(scene, camera);
        myUI.render();
        controls.enabled = !myUI.getMouseHover();

        t += dt;
        sec += dt;
    });
}
