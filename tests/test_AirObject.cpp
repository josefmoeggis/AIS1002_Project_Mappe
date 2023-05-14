//
// Created by joelo on 14.05.2023.
//
#include "AirObject.hpp"
#include "threepp/loaders/STLLoader.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include "threepp/scenes/Scene.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Aircraft Setup") {
    STLLoader loader;
    auto geometry = loader.load("resources/Cessna_172.stl");
    auto material = MeshPhongMaterial::create();
    auto aircraft = AirObject::create(geometry, material, 800,
                                      16.17,0.33, 0.035, 0);
    aircraft->createMesh();
    aircraft->getMesh()->name = "Aircraft";
    Scene scene;

    scene.add(aircraft->getMesh());
    REQUIRE(scene.getObjectByName("Aircraft"));

}
