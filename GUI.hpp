//
// Created by joelo on 28.03.2023.
//
// Trying to not make my GUI too gooey

#include "threepp/extras/imgui/imgui_context.hpp"
#include <iostream>
#include <memory>
#include "threepp/threepp.hpp"
#ifndef THREEPP_VCPKG_TEST_GUI_HPP
#define THREEPP_VCPKG_TEST_GUI_HPP
using namespace threepp;

// Inspired from PID regulator code in threepp
struct ControllableParameters {
    float targetAirspeed;
    float targetAngleOfAttack;
    int fileChoice;
    std::string path1;
    std::string path2;
//    std::string path3;


    explicit ControllableParameters(std::string path1 = nullptr, std::string path2 = nullptr, float targetAirspeed = 0,
                                    float targetAngleOfAttack = 0, int fileChoice = 1)
                                    : targetAirspeed(targetAirspeed), targetAngleOfAttack(targetAngleOfAttack),
                                    path1(path1), path2(path2), fileChoice(fileChoice) {}
};

struct GUI : imgui_context {

    GUI(const Canvas& canvas, ControllableParameters& controlOptions) // Research more if it can use shared_ptr
    : imgui_context(canvas.window_ptr()), controlOptions_(controlOptions) {}

    void onRender() override {

        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize({}, 0);
        ImGui::Begin("Control Parameters");

        ImGui::Text("Control Airspeed");
        ImGui::SliderFloat("knots", &controlOptions_.targetAirspeed, 0, 400);
        ImGui::Text("Control Angle of Attack");
        ImGui::SliderAngle("degrees", &controlOptions_.targetAngleOfAttack, -180, 180);

        ImTextureID image1 = ImGui::GetIO().Fonts->AddFontFromFileTTF(controlOptions_.path1.c_str(), 4000);
        ImTextureID image2 = ImGui::GetIO().Fonts->AddFontFromFileTTF(controlOptions_.path2.c_str(), 4000);
        ImGui::Text("Choose Aircraft type");
        if(ImGui::ImageButton(image1, ImVec2())) {
            controlOptions_.fileChoice = 1;
        }
        if(ImGui::ImageButton(image2, ImVec2())) {
            controlOptions_.fileChoice = 2;
        }
        ImGui::End();
    }


private:
    ControllableParameters& controlOptions_;
};


#endif //THREEPP_VCPKG_TEST_GUI_HPP
