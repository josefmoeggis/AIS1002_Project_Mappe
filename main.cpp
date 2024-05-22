
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
    ControllableParameters control(anglePID, 100, 0, 0, 0, 10, 500, 1);
    control.setOptions("resources/B737_image_min.jpeg", "Boeing 737-800", 746 * 420,
                       "resources/SAS-A321LR_min.jpeg", "Navion", 1200 * 869,
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




    auto boeing = setupAircraft1(loader);
    auto navion = setupAircraft2(loader);
    auto cessna = setupAircraft3(loader);
    navion->setStartvalues(100, 0, 0, 30, 0, 0, 0, -20);

    std::shared_ptr<AirObject> aircraft = boeing;

    auto movementShell = Group::create();
    movementShell->add(aircraft->getMesh());
    auto propeller = getAirflowArrow(loader);
    scene->add(movementShell);

    float t = 0;
    float sec = 0;

    canvas.animate([&](float dt) {
switch (control.fileChoice) {
    case 0:
        aircraft = boeing;
        loopAircraft(movementShell, boeing, navion, cessna, switchPID, dt);
        break;
    case 1:
        aircraft = navion;
        loopAircraft(movementShell, navion, cessna, boeing, switchPID, dt);
        if (!(movementShell->getObjectByName("propeller"))){
            movementShell->add(propeller);
        }
        break;
    case 2:
        aircraft = cessna;
        loopAircraft(movementShell, cessna, boeing, navion, switchPID, dt);
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
            graphDrag.updateMesh(-100);
            sec = 0;
        }
        /*float angleGain = anglePID.regulate(control.setAngle,
                                            aircraft->getAngleOfAttack(), dt);
        aircraft->setControlledAngle(angleGain, 2, dt);*/


        if(control.setElevatorAngle != 0) {
            aircraft->updateLongitudinal(control.setElevatorAngle * math::RAD2DEG, dt);
            control.setElevatorAngle = 0;
        }
        else {
            aircraft->updateLongitudinal(0, dt);
        }
        if(control.setAileronAngle != 0 || control.setRudderAngle != 0) {
            aircraft->updateLateral(control.setAileronAngle * math::RAD2DEG, control.setRudderAngle * math::RAD2DEG * 5, dt);
            control.setAileronAngle = 0;
            control.setRudderAngle = 0;
        }
        else {
            aircraft->updateLateral(0, 0, dt);
        }

        movementShell->getObjectByName("propeller")->rotateX(control.targetAirspeed * dt * math::DEG2RAD);


        aircraft->updateLateral(0, 0, dt);

        movementShell->rotation.x = aircraft->getPitch();
        movementShell->rotation.z = aircraft->getRoll();
        movementShell->rotation.y = aircraft->getYaw();
        renderer.render(scene, camera);
        myUI.render();
        controls.enabled = !myUI.getMouseHover();
        t += dt;
        sec += dt;
    });
}
