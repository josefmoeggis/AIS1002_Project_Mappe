//
// Created by joelo on 01.05.2023.
//

#include "../include/SceneSetup.hpp"
#include "threepp/materials/ShaderMaterial.hpp"



std::shared_ptr<DirectionalLight> setLight() {
    auto light = DirectionalLight::create(0xffffff);
    light->position.set(100, 10, 100);
    return light;
}

std::shared_ptr<Sky> setSky(std::shared_ptr<DirectionalLight> light) {
    auto mySky = Sky::create();
    mySky->scale.setScalar(10000);
    mySky->material()->as<ShaderMaterial>()->uniforms->at("turbidity").value<float>() = 10;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("rayleigh").value<float>() = 1;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("mieCoefficient").value<float>() = 0.005;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("mieDirectionalG").value<float>() = 0.8;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("sunPosition").value<Vector3>().copy(light->position);
    return mySky;
}

std::shared_ptr<AirObject> setupAircraft1(STLLoader loader) {
    auto fuselage = loader.load("resources/B737_800.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::beige;
    auto boeing = AirObject::create(fuselage, material, 40000, 470);
    boeing->setAngleParameters(1.6, 14, 20, 1.3);
    boeing->setAirDensity(1.225);
    boeing->createMesh();
    boeing->scaleModel(1000);
    boeing->centerModel(1000);
    boeing->getMesh()->rotateY(math::PI);
    boeing->getMesh()->name = "Boeing";
    return boeing;
}

std::shared_ptr<AirObject> setupAircraft2(STLLoader loader) {
    auto fuselage = loader.load("resources/A320neo.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::beige;
    auto airbus = AirObject::create(fuselage, material, 4000, 470);
    airbus->setAngleParameters(1.6, 14, 20, 1.3);
    airbus->setAirDensity(1.225);
    airbus->createMesh();
    airbus->scaleModel(1000);
    airbus->centerModel(1000);
    airbus->getMesh()->name = "Airbus";
    return airbus;
}

std::shared_ptr<AirObject> setupAircraft3(STLLoader loader) {
    auto fuselage = loader.load("resources/Cessna_172.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::beige;
    auto cessna = AirObject::create(fuselage, material, 800,
                                    16.17,0.33, 0.029, 0);
    cessna->setAngleParameters(1.5, 12, 18, 1.3);
    cessna->setAirDensity(1.225);
    cessna->createMesh();
    cessna->scaleModel(1000);
    cessna->centerModel(1000);
    cessna->getMesh()->position.x += 200;
    cessna->getMesh()->position.z += 1400;
    cessna->getMesh()->position.y += (-500);
    cessna->getMesh()->rotateY(math::PI);
    cessna->getMesh()->name = "Cessna";
    return cessna;
}

void loopAircraft(std::shared_ptr<Scene> scene, std::shared_ptr<AirObject> aircraftModel1,
                  std::shared_ptr<AirObject> aircraftModel2, std::shared_ptr<AirObject> aircraftModel3) {
    if(!scene->getObjectByName(aircraftModel1->getMesh()->name)) {
        if(scene->getObjectByName(aircraftModel2->getMesh()->name)) {
            scene->remove(scene->getObjectByName(aircraftModel2->getMesh()->name));
        }
        if(scene->getObjectByName(aircraftModel3->getMesh()->name)) {
            scene->remove(scene->getObjectByName(aircraftModel3->getMesh()->name));
        }
        scene->add(aircraftModel1->getMesh());
    }
}


