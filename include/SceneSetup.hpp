//
// Created by joelo on 01.05.2023.
//

#ifndef THREEPP_VCPKG_TEST_SCENESETUP_HPP
#define THREEPP_VCPKG_TEST_SCENESETUP_HPP
#include "threepp/lights/DirectionalLight.hpp"
#include "threepp/objects/Sky.hpp"

using namespace threepp;

std::shared_ptr<DirectionalLight> setLight();

std::shared_ptr<Sky> setSky(std::shared_ptr<DirectionalLight> light);

class SceneSetup {
    SceneSetup(std::shared_ptr<Scene> inputScene) : scene_(inputScene) {}
    



private:
    std::shared_ptr<Scene> scene_;

};


#endif //THREEPP_VCPKG_TEST_SCENESETUP_HPP
