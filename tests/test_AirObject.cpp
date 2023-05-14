//
// Created by joelo on 14.05.2023.
//
#include "AirObject.hpp"
#include "threepp/loaders/STLLoader.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include "threepp/scenes/Scene.hpp"
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>


TEST_CASE("Aircraft Setup and adding to scene") {

    STLLoader loader;
    auto geometry = loader.load("resources/Cessna_172.stl");

    auto material = MeshPhongMaterial::create();
    auto aircraft = AirObject::create(geometry, material, 800,
                                      16.17,0.33, 0.035, 0);
    aircraft->createMesh();
    aircraft->getMesh()->name = "Aircraft";
    Scene scene;

    scene.add(aircraft->getMesh());

    CHECK(scene.getObjectByName("Aircraft"));

    SECTION() {
        aircraft->setAngleParameters(1.6, 14, 20, 1.3);
        CHECK();
    }
}
