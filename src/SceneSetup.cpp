//
// Created by joelo on 01.05.2023.
//

#include "../include/SceneSetup.hpp"


std::shared_ptr<DirectionalLight> setMySky() {
    auto light = DirectionalLight::create(0xffffff);
    light->position.set(100, 10, 100);
    return light;
}
