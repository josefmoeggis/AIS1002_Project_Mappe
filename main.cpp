
#include "include/AirObject.hpp"
#include "include/Graph3D.hpp"
#include "include/GUI.hpp"
#include "include/SceneSetup.hpp"
#include "threepp/renderers/GLRenderer.hpp"
#include "threepp/helpers/AxesHelper.hpp"
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/controls/OrbitControls.hpp"
#include "threepp/objects/Group.hpp"
#include "include/Utils.hpp"

#include "threepp/extras/core/Font.hpp"
#include "threepp/loaders/FontLoader.hpp"

using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas{Canvas::Parameters().size({1920, 1080}).antialiasing(4)
                    .title("Aircraft Lift 3D graphLift").favicon("resources/airplane_2_icon.jpeg")};
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
    control.setOptions("resources/B737_image_min.jpeg", "Boeing 737-800", 746 * 420,
                       "resources/SAS-A321LR_min.jpeg", "Airbus A320", 1200 * 869,
                       "resources/Cessna_172S_Skyhawk.jpg", "Cessna 172", 220 * 164);
    GUI myUI(canvas, control);

//    Create grid object
    Graph3D graphLift(1000, 20);
    graphLift.setPosition();
    Graph3D graphDrag(1000, 20, 0x000000, 0xFF0000); // Not adding grid to scene only graph line
    graphDrag.setPosition();
    scene->add(graphLift.getGrid());

//    matplotlibcpp::plot
FontLoader fontLoader;
auto font = fontLoader.load("resources/Roboto_Bold.json");



    STLLoader loader;
    auto boeing = setupAircraft1(loader);
    auto airbus = setupAircraft2(loader);
    auto cessna = setupAircraft3(loader);

    std::shared_ptr<AirObject> aircraft = cessna;

    auto movementShell = Group::create();

    float t = 0;
    float sec = 0;

    canvas.animate([&](float dt) {
switch (control.fileChoice) {
    case 0:
        aircraft = boeing;
        loopAircraft(scene, movementShell, boeing, airbus, cessna);
        break;
    case 1:
        aircraft = airbus;
        loopAircraft(scene, movementShell, airbus, cessna, boeing);
        break;
    case 2:
        aircraft = cessna;
        loopAircraft(scene, movementShell, cessna, boeing, airbus);
        break;
}

//     Testing line segments
        if (sec >= 0.1) {
            graphLift.updateLineVectors(aircraft->calculateLift(knotsToMtrPrSec(control.targetAirspeed)), 200);
            graphLift.adjustGraphToFit(aircraft->calculateMaxLift(300));
            graphLift.makeLine(scene);
            scene->add(graphLift.getLine());
            graphDrag.updateLineVectors(aircraft->calculateDrag(knotsToMtrPrSec(control.targetAirspeed)), 200);
            graphDrag.adjustGraphToFit(aircraft->calculateMaxLift(knotsToMtrPrSec(300)));
            graphDrag.makeLine(scene);
            scene->add(graphDrag.getLine());
            sec = 0;
        }
        float angleGain = myPID.regulate(control.targetAngleOfAttack,
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
