//
// Created by joelo on 01.05.2023.
//

#ifndef THREEPP_VCPKG_TEST_SCENESETUP_HPP
#define THREEPP_VCPKG_TEST_SCENESETUP_HPP
#include "threepp/lights/DirectionalLight.hpp"
#include "threepp/objects/Sky.hpp"
#include "threepp/loaders/STLLoader.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include "threepp/scenes/Scene.hpp"
#include "../include/GUI.hpp"
#include "../include/AirObject.hpp"

using namespace threepp;

std::shared_ptr<DirectionalLight> setLight();

std::shared_ptr<Sky> setSky(std::shared_ptr<DirectionalLight> light);

class SceneSetup {
public:
    SceneSetup (std::shared_ptr<Scene> inputScene, ControllableParameters control) : scene_(inputScene), control_(control) {}

//    Configurations set in these functions
    void setupAircraft1();

    void setupAircraft2();

    void setupAircraft3();

//    Setup for the loop
    void loopAircraft1();

    void loopAircraft2();

    void loopAircraft3();

    std::shared_ptr<Scene> getScene();

private:
    ControllableParameters control_;
    std::shared_ptr<Scene> scene_;

};


#endif //THREEPP_VCPKG_TEST_SCENESETUP_HPP
