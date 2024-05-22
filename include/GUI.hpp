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
    float setElevatorAngle;
    float setAileronAngle;
    float setRudderAngle;
    float targetTemp;
    float targetAltitude;
    bool reset;
    int fileChoice;
    float prevSetAngle = 0;
    std::vector<Triple<std::optional<std::string>, std::optional<std::string>, std::optional<float>>> imagePaths {}; // storing path string and pixels

    PID& pid;

    bool updateElevator = false;
    bool updateAileron = false;
    bool updateRudder = false;

    explicit ControllableParameters(PID& pid, float targetAirspeed = 0, float setElevatorAngle = 0, float setAileronAngle = 0, float setRudderAngle = 0, float targetTemp = 288.15, float targetAltitude = 5000, int fileChoice = 0, bool reset = 0)
            : targetAirspeed(targetAirspeed), setElevatorAngle(setElevatorAngle), setAileronAngle(setAileronAngle), setRudderAngle(setRudderAngle), targetTemp(targetTemp),
              targetAltitude(targetAltitude), fileChoice(fileChoice), pid(pid), reset(reset) {}


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

        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize(ImVec2(350, 420));
        ImGui::Begin("Control Parameters", NULL);

        ImGui::SetCursorPos(ImVec2(90, 30));
        ImGui::Text("Control Airspeed");
        ImGui::SetCursorPos(ImVec2(30, 50));
        ImGui::SliderFloat("knots", &controlOptions_.targetAirspeed, 0, 400);

        ImGui::SetCursorPos(ImVec2(65, 80));
        ImGui::Text("Elevator Angle");
        ImGui::SetCursorPos(ImVec2(30, 100));
        if (ImGui::SliderAngle("Elevator degrees", &controlOptions_.setElevatorAngle, -40, 40)) {
            controlOptions_.updateElevator = true;
        }

        ImGui::SetCursorPos(ImVec2(65, 130));
        ImGui::Text("Aileron Angle");
        ImGui::SetCursorPos(ImVec2(30, 150));
        if (ImGui::SliderAngle("Aileron degrees", &controlOptions_.setAileronAngle, -40, 40)) {
            controlOptions_.updateAileron = true;
        }

        ImGui::SetCursorPos(ImVec2(65, 180));
        ImGui::Text("Rudder Angle");
        ImGui::SetCursorPos(ImVec2(30, 200));
        if (ImGui::SliderAngle("Rudder degrees", &controlOptions_.setRudderAngle, -40, 40)) {
            controlOptions_.updateRudder = true;
        }

        ImGui::SetCursorPos(ImVec2(185, 250));
        ImGui::TextColored(ImVec4(39, 158, 138, 255), "Altitude");
        ImGui::SetCursorPos(ImVec2(190, 270));
        ImGui::VSliderFloat("ft", ImVec2(50, 120), &controlOptions_.targetAltitude, 0, 60000);

        ImGui::SetCursorPos(ImVec2(255, 250));
        ImGui::TextColored(ImVec4(39, 278, 138, 255), "Temp Sea lvl");
        ImGui::SetCursorPos(ImVec2(270, 270));
        ImGui::VSliderFloat("C", ImVec2(50, 120), &controlOptions_.targetTemp, -50, 50);

        ImGui::SetCursorPos(ImVec2(45, 240));
        ImGui::Text("Change Aircraft");
        ImGui::SetCursorPos(ImVec2(40, 260));
        if (ImGui::Button(controlOptions_.imagePaths.at(0).y->c_str(), ImVec2(120, 30))) {
            controlOptions_.fileChoice = 0;
        }
        ImGui::SetNextWindowBgAlpha(1);
        ImGui::SetCursorPos(ImVec2(40, 300));
        if (ImGui::Button(controlOptions_.imagePaths.at(1).y->c_str(), ImVec2(120, 30))) {
            controlOptions_.fileChoice = 1;
        }
        ImGui::SetCursorPos(ImVec2(40, 340));
        if (ImGui::Button(controlOptions_.imagePaths.at(2).y->c_str(), ImVec2(120, 30))) {
            controlOptions_.fileChoice = 2;
        }

        ImGui::SetCursorPos(ImVec2(40, 380));
        if (ImGui::Button("Reset init values", ImVec2(120, 30))) {
            controlOptions_.reset = true;
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
