// Remember continuous integration kopier fra threepp config file
#include "include/AirObject.hpp"
#include "include/Graph3D.hpp"
#include "include/GUI.hpp"
#include "include/SceneSetup.hpp"
#include "threepp/renderers/GLRenderer.hpp"
#include "threepp/helpers/AxesHelper.hpp"
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/controls/OrbitControls.hpp"
#include "threepp/loaders/STLLoader.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"


using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas{Canvas::Parameters().size({1280, 720})
                    .title("Aircraft Lift 3D Graph").favicon("resources/airplane_2_icon.jpeg")};
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

//    Testing AirObject
    STLLoader loader;
    std::shared_ptr<BufferGeometry> aircraft1;
    if(control.fileChoice == 1) {
        aircraft1 = loader.load("resources/B737_800.stl");
    } else if (control.fileChoice == 2) {
        aircraft1 = loader.load("resources/A320neo.stl");
    }
    auto material1 = MeshPhongMaterial::create();
    material1->flatShading = true;
    material1->color = Color::beige;
    AirObject Aircraft1(aircraft1, material1, 40000.0, 0.77, 0.33, 470, 0);
    Aircraft1.setAngleParameters(1.6, 14, 20, 1.3);
    Aircraft1.setAirDensity(1.225);
    Aircraft1.createMesh();
    Aircraft1.scaleModel(1000);
    Aircraft1.centerModel(1000);
    Aircraft1.getMesh()->rotateY(math::PI);
    scene->add(Aircraft1.getMesh());

//    Create grid object
    Graph3D Graph(1000, 20);
    Graph.setPosition();
    scene->add(Graph.getGrid());

    float t = 0;
    float sec = 0;

    canvas.animate([&](float dt) {


//     Testing line segments
        if (sec >= 1) {
            Graph.updateLineVectors(Aircraft1.calculateLift(control.targetAirspeed), 20);
            Graph.adjustGraphToFit(Aircraft1.calculateMaxLift(300));
            Graph.makeLine(scene);
            scene->add(Graph.getLine());
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
