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
