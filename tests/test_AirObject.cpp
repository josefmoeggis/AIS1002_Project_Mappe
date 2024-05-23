//
// Created by joelo on 14.05.2023.
//
#include "AirObject.hpp"
#include "Utils.hpp"
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
                                      370,0.33, 0.035, 0);
    aircraft->createMesh();
    aircraft->getMesh()->name = "Aircraft";
    Scene scene;

    scene.add(aircraft->getMesh());

    CHECK(scene.getObjectByName("Aircraft"));

    SECTION("Calculate lift coefficient depending on angle of attack") {
        aircraft->setAngleParameters(1.6, 14, 20, 1.3);
        float CLwAngle = aircraft->calcLiftCoeffAngle();
        CHECK((CLwAngle > 0 && CLwAngle < 1));
    }

    SECTION("Set angle of attack") {
        aircraft->setAngleOfAttack(2);
        CHECK(aircraft->getAngleOfAttack() == 2);
    }

    SECTION("Calculate air density") {
        float airDensity = aircraft->calcAirDensity(celsiusToKelvin(10), 10000);
        CHECK(airDensity < 1.225);
    }

    SECTION("Calculate air density decreases with altitude") {
        float previousVal = 1.225;
        for(float i = 1000; i < 20000; i += 1000) {
            float currentVal = aircraft->calcAirDensity(celsiusToKelvin(30), i);
            CHECK(previousVal > currentVal);
            previousVal = currentVal;
        }
    }

    SECTION("Calculate change in lift coefficient depending on angle of attack") {
        aircraft->setAngleOfAttack(0);
        float previousVal = aircraft->calcLiftCoeffAngle();
        for (float i = 0; i < (math::DEG2RAD * 10); i += 0.3) {
            aircraft->setAngleOfAttack(i);
            float currentVal = aircraft->calcLiftCoeffAngle();
            CHECK(previousVal <= currentVal);
            previousVal = currentVal;
        }
        aircraft->setAngleOfAttack(math::DEG2RAD * 21);
        float currentVal = aircraft->calcLiftCoeffAngle();
        CHECK(previousVal >= currentVal);
    }

    SECTION("Calculate lift combining both air density calculation and angle of attack") {
        aircraft->setAngleOfAttack(0);
        float previousVal = 0;
        for(float i = 10; i < 400; i += 50) {
            float currentVal = aircraft->calculateLift(knotsToMtrPrSec(i), celsiusToKelvin(30), 2000);
            CHECK(previousVal <= currentVal);
            std::cout << currentVal << std::endl;
            previousVal = currentVal;
        }
    }

    SECTION("Calculate lift combining both air density calculation and angle of attack") {
        float previousVal = 0;
        for(float i = 10; i < 400; i += 50) {
            float currentVal = aircraft->calculateDrag(knotsToMtrPrSec(i), celsiusToKelvin(30), 2000);
            CHECK(previousVal <= currentVal);
            std::cout << currentVal << std::endl;

            previousVal = currentVal;
        }
    }
}
