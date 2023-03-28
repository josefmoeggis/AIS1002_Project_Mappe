// Remember continuous integration kopier fra threepp config file
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/threepp.hpp"
#include "iostream"
#include "AirObject.hpp"
#include "Graph3D.hpp"
#include "GUI.hpp"
#include "threepp/materials/ShaderMaterial.hpp"
#include "threepp/objects/Sky.hpp"
#include "threepp/objects/Line.hpp"
#include "vector"

using namespace threepp;

int main() {
    // Canvas creation
    Canvas canvas{Canvas::Parameters().size({1280, 720}).antialiasing(1)};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);



//    renderer.setClearColor(Color::aliceblue);
// Setting up grid
    auto grid = GridHelper::create(1000, 20, Color::blue, Color::blue);
    grid->position.x = -1000 / 2;
    grid->rotateX(math::PI / 2);
    grid->rotateZ(math::PI / 2);

//    Setting up imgui
//    ImGui_ImplGlfw_NewFrame();
//    auto imguiContext = ImGuiContext;
//    auto imgui = ImGui_ImplOpenGL3_CreateDeviceObjects();


//    Setting up visual axes
    auto axes = AxesHelper::create(100);

    // Setting up camera
    auto camera = PerspectiveCamera::create(60, canvas.getAspect(), 0.1f, 3000);
    camera->position.x = 600;
    OrbitControls controls{camera, canvas};


    // Scene creation
    auto scene = Scene::create();
    scene->add(grid);
    scene->add(axes);

    //    Add light
    auto light = DirectionalLight::create(0xffffff);
    light->position.set(100, 10, 100);
    scene->add(light);


//    Setting sky
    auto mySky = Sky::create();
    mySky->scale.setScalar(10000);
    mySky->material()->as<ShaderMaterial>()->uniforms->at("turbidity").value<float>() = 10;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("rayleigh").value<float>() = 1;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("mieCoefficient").value<float>() = 0.005;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("mieDirectionalG").value<float>() = 0.8;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("sunPosition").value<Vector3>().copy(light->position);
    scene->add(mySky);

    //BulletWrapper bullet(Vector3::Y * -9.81f); Save for bullet setup

    renderer.enableTextRendering();
    auto& textHandle = renderer.textHandle("Hello World");
    textHandle.setPosition(0, canvas.getSize().height - 30);
    textHandle.scale = 1;


//    Testing AirObject
    STLLoader loader;

    auto aircraft1 = loader.load(
            "resources/B737_800.stl");
    auto material1 = MeshPhongMaterial::create();
    material1->flatShading = true;
    material1->color = Color::beige;
    AirObject Aircraft1(aircraft1, material1, 40000.0, 0.77, 0.33, 470, 0);
    auto Boeing = Aircraft1.createMesh();
    Aircraft1.scaleModel(1000);
    Aircraft1.centerModel(1000);
    Boeing->rotateY(math::PI);

    scene->add(Boeing);


// Testing line segments
    std::vector<Vector3> points;
    points.emplace_back(threepp::Vector3 {3, 5, 6});
    points.emplace_back(threepp::Vector3 {23, 5, 6});
    points.emplace_back(threepp::Vector3 {100, 100, 100});
    auto material = LineBasicMaterial::create();
    material->color = threepp::Color(0xB22222);
    auto geometry = BufferGeometry::create();
    geometry->setFromPoints(points);
    auto line = Line::create(geometry, material);
    scene->add(line);

//    canvas.onWindowResize([&](WindowSize size) {
//        camera->aspect = size.getAspect();
//        camera->updateProjectionMatrix();
//        renderer.setSize(size);
//        textHandle.setPosition(0, size.height - 30);
//    });

    float t = 0;

    canvas.animate([&](float dt) {
        renderer.render(scene, camera);

        t += dt;


    });
}
