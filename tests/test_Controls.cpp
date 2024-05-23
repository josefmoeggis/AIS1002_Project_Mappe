//
// Created by joelo on 14.05.2023.
//
#include "GUI.hpp"
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Control inputs setup") {
    PID testPid;
    ControllableParameters control(testPid);

    SECTION("Inputs to pid") {
        CHECK(control.pid.regulate(10, 0, 1/60) != 0);
    }

    SECTION("Target airspeed") {
        CHECK(control.targetAirspeed == 0);
    }

    SECTION("Target angle of attack") {
        CHECK(control.targetAngleOfAttack == 0);
    }

    SECTION("Target temperature") {
        CHECK(std::round(control.targetTemp) == std::round(288.15));
    }

    SECTION("Target altitude") {
        CHECK(control.targetAltitude == 5000);
    }

    SECTION("File choice") {
        CHECK(control.fileChoice == 0);
    }
}

TEST_CASE("Struct Triple works") {
    float myFloat = 23.23;
    int myInt = 40;
    std::string myString = "Hello world";
    Triple triple(myFloat, myInt, myString);
    CHECK(triple.x == myFloat);
    CHECK(triple.y == myInt);
    CHECK(triple.z == myString);
}