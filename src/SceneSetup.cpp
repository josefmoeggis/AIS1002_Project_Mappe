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

void SceneSetup::loopAircraft1() {
    if(!scene_->getObjectByName("Boeing")) {
        STLLoader loader;
        auto fuselage = loader.load("resources/B737_800.stl");
        auto material = MeshPhongMaterial::create();
        material->flatShading = true;
        material->color = Color::beige;
        AirObject boeing(fuselage, material, 40000.0, 0.77, 0.33, 470, 0);
        boeing.setAngleParameters(1.6, 14, 20, 1.3);
        boeing.setAirDensity(1.225);
        boeing.createMesh();
        boeing.scaleModel(1000);
        boeing.centerModel(1000);
        boeing.getMesh()->rotateY(math::PI);
        boeing.getMesh()->name = "Boeing";
        scene_->add(boeing.getMesh());
    }

}

void SceneSetup::loopAircraft2() {
    if(!scene_->getObjectByName("Airbus")) {
        STLLoader loader;
        auto fuselage = loader.load("resources/A320neo.stl");
        auto material = MeshPhongMaterial::create();
        material->flatShading = true;
        material->color = Color::beige;
        AirObject airbus(fuselage, material, 40000.0, 0.77, 0.33, 470, 0);
        airbus.setAngleParameters(1.6, 14, 20, 1.3);
        airbus.setAirDensity(1.225);
        airbus.createMesh();
        airbus.scaleModel(1000);
        airbus.centerModel(1000);
        airbus.getMesh()->rotateY(math::PI);
        airbus.getMesh()->name = "Airbus";
        scene_->add(airbus.getMesh());
    }

}

void SceneSetup::loopAircraft3() {
    if(!scene_->getObjectByName("Boeing")) {
        STLLoader loader;
        auto fuselage = loader.load("resources/Cessna_172.stl");
        auto material = MeshPhongMaterial::create();
        material->flatShading = true;
        material->color = Color::beige;
        AirObject cessna(fuselage, material, 40000.0, 0.77, 0.33, 470, 0);
        cessna.setAngleParameters(1.6, 14, 20, 1.3);
        cessna.setAirDensity(1.225);
        cessna.createMesh();
        cessna.scaleModel(1000);
        cessna.centerModel(1000);
        cessna.getMesh()->rotateY(math::PI);
        cessna.getMesh()->name = "Cessna";
        scene_->add(cessna.getMesh());
    }

}

std::shared_ptr<Scene> SceneSetup::getScene() {
    return scene_;
}