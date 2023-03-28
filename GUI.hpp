//
// Created by joelo on 28.03.2023.
//
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/threepp.hpp"
#ifndef THREEPP_VCPKG_TEST_GUI_HPP
#define THREEPP_VCPKG_TEST_GUI_HPP
using namespace threepp;

struct ControllableParameters {
    double targetAirspeed;
    float targetAngleOfAttack;
    explicit ControllableParameters()
};

struct GUI : imgui_context {
    explicit Gui(const Canvas& canvas, ControllableParameters& opt)


};


#endif //THREEPP_VCPKG_TEST_GUI_HPP
