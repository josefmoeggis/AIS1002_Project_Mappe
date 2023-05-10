//
// Created by joelo on 01.05.2023.
//
// This is the file from which all the setup information is added, more specifically the positioning and functions that clear up some space from the main file.

#ifndef THREEPP_VCPKG_TEST_SCENESETUP_HPP
#define THREEPP_VCPKG_TEST_SCENESETUP_HPP
#include "threepp/lights/DirectionalLight.hpp"
#include "threepp/objects/Sky.hpp"
#include "threepp/loaders/STLLoader.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include "threepp/scenes/Scene.hpp"
#include "threepp/materials/ShaderMaterial.hpp"
#include "threepp/objects/Group.hpp"
#include "../include/GUI.hpp"
#include "../include/AirObject.hpp"


using namespace threepp;

std::shared_ptr<DirectionalLight> setLight();

std::shared_ptr<Sky> setSky(std::shared_ptr<DirectionalLight> light);

//    Configurations set in these functions
std::shared_ptr<AirObject> setupAircraft1(STLLoader loader);

std::shared_ptr<AirObject> setupAircraft2(STLLoader loader);

std::shared_ptr<AirObject> setupAircraft3(STLLoader loader);

//    Setup for the loop
void loopAircraft(std::shared_ptr<Scene> scene,std::shared_ptr<Group> movementShell, std::shared_ptr<AirObject> aircraftModel1,
                  std::shared_ptr<AirObject> aircraftModel2, std::shared_ptr<AirObject> aircraftModel3);




#endif //THREEPP_VCPKG_TEST_SCENESETUP_HPP
