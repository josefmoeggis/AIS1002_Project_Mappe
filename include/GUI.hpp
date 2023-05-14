//
// Created by joelo on 28.03.2023.
//
// Trying to not make my GUI too gooey


#ifndef THREEPP_VCPKG_TEST_GUI_HPP
#define THREEPP_VCPKG_TEST_GUI_HPP

#include "PID.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/Canvas.hpp"

using namespace threepp;

// Create new class to store two strings and an int in the ControllableOptions struct
template<class Ty1, class Ty2, class Ty3>

struct Triple {
public:
    Ty1 x;
    Ty2 y;
    Ty3 z;

    Triple() : x{}, y{}, z{} {}
    Triple(Ty1 x_in, Ty2 y_in, Ty3 z_in) : x(x_in), y(y_in), z(z_in) {}

};

// Inspired from PID regulator code in threepp
struct ControllableParameters {
    float targetAirspeed;
    float targetAngleOfAttack;
    float targetTemp;
    float targetAltitude;
    int fileChoice;
    std::vector<Triple<std::optional<std::string>, std::optional<std::string>, std::optional<float>>> imagePaths {}; // storing path string and pixels

    PID& pid;


    explicit ControllableParameters(PID& pid, float targetAirspeed = 0, float targetAngleOfAttack = 0, float targetTemp = 288.15, float targetAltitude = 5000, int fileChoice = 0)
                                    : targetAirspeed(targetAirspeed), targetAngleOfAttack(targetAngleOfAttack * math::DEG2RAD), targetTemp(targetTemp),
                                    targetAltitude(targetAltitude), fileChoice(fileChoice), pid(pid) {}

                                    // This was meant for adding images of selectable aircraft to ImGui
    void setOptions(std::optional<std::string> path1 = std::nullopt, std::optional<std::string> name1 = std::nullopt, std::optional<float> size1 = std::nullopt,
                     std::optional<std::string> path2 = std::nullopt, std::optional<std::string> name2 = std::nullopt, std::optional<float> size2 = std::nullopt,
                     std::optional<std::string> path3 = std::nullopt, std::optional<std::string> name3 = std::nullopt, std::optional<float> size3 = std::nullopt) {
        if(path1.has_value() && name1.has_value()) {
            imagePaths.emplace_back(Triple<std::optional<std::string>, std::optional<std::string>,
                    std::optional<float>>(path1, name1, size1));
        }
        if(path2.has_value() && name2.has_value()) {
            imagePaths.emplace_back(Triple<std::optional<std::string>, std::optional<std::string>,
                    std::optional<float>>(path2, name2, size2));
        }
        if(path3.has_value() && name3.has_value()) {
            imagePaths.emplace_back(Triple<std::optional<std::string>, std::optional<std::string>,
                    std::optional<float>>(path3, name3, size3));
        }
    }
};

struct GUI : imgui_context {

    GUI(const Canvas& canvas, ControllableParameters& controlOptions) // Research more if it can use shared_ptr
    : imgui_context(canvas.window_ptr()), controlOptions_(controlOptions) {}

    void setStyle(ImGuiStyle& style) {
        style.Colors[ImGuiCol_WindowBg] = ImColor(68, 111, 212, 100);
        style.WindowRounding = 6;
        style.FrameRounding = 4;
        style.GrabRounding = 4;
//        style.Alpha = 0.5;
    }

    void onRender() override {
        ImGuiStyle &style = ImGui::GetStyle();
        setStyle(style);
//        ImGui::SetNextWindowBgAlpha(0.5f);
        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize((ImVec2(350, 300)));
        ImGui::Begin("Control Parameters", NULL);

        ImGui::SetCursorPos(ImVec2(90, 30));
        ImGui::Text("Control Airspeed");
        ImGui::SetCursorPos(ImVec2(30, 50));
        ImGui::SliderFloat("knots", &controlOptions_.targetAirspeed, 0, 400);
        ImGui::SetCursorPos(ImVec2(65, 80));
        ImGui::Text("Control Angle of Attack");
        ImGui::SetCursorPos(ImVec2(30, 100));
        ImGui::SliderAngle("degrees", &controlOptions_.targetAngleOfAttack, -40, 40);
        ImGui::SetCursorPos(ImVec2(185, 140));
        ImGui::TextColored(ImVec4(39, 158, 138, 255), "Altitude");
        ImGui::SetCursorPos(ImVec2(190, 160));
        ImGui::VSliderFloat("ft", ImVec2(50, 120), &controlOptions_.targetAltitude, 0, 60000);
        ImGui::SetCursorPos(ImVec2(255, 140));
        ImGui::TextColored(ImVec4(39, 158, 138, 255), "Temp Sea lvl");
        ImGui::SetCursorPos(ImVec2(270, 160));
        ImGui::VSliderFloat("C", ImVec2(50, 120), &controlOptions_.targetTemp, -50, 50);
        ImGui::SetCursorPos(ImVec2(45, 140));
        ImGui::Text("Change Aircraft");
        ImGui::SetCursorPos(ImVec2(40, 160));
        if (ImGui::Button(controlOptions_.imagePaths.at(0).y->c_str(), ImVec2(120, 30))) {
            controlOptions_.fileChoice = 0;
        }
        ImGui::SetNextWindowBgAlpha(1);
        ImGui::SetCursorPos(ImVec2(40, 200));
        if (ImGui::Button(controlOptions_.imagePaths.at(1).y->c_str(), ImVec2(120, 30))) {
            controlOptions_.fileChoice = 1;
        }
        ImGui::SetCursorPos(ImVec2(40, 240));
        if (ImGui::Button(controlOptions_.imagePaths.at(2).y->c_str(), ImVec2(120, 30))) {
            controlOptions_.fileChoice = 2;
        }

        mouseHover_ = ImGui::IsWindowHovered();
        ImGui::End();
    }

    bool getMouseHover() {
        return mouseHover_;
    }


private:
    ControllableParameters& controlOptions_;
    bool mouseHover_;
};


#endif //THREEPP_VCPKG_TEST_GUI_HPP
