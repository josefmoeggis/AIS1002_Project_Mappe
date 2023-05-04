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
    int fileChoice;
    std::vector<Triple<std::optional<std::string>, std::optional<std::string>, std::optional<float>>> imagePaths {}; // storing path string and pixels

    PID& pid;


    explicit ControllableParameters(PID& pid, float targetAirspeed = 0, float targetAngleOfAttack = 0, int fileChoice = 0)
                                    : targetAirspeed(targetAirspeed), targetAngleOfAttack(targetAngleOfAttack * math::DEG2RAD), fileChoice(fileChoice), pid(pid) {}
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
        style.Colors[ImGuiCol_WindowBg] = ImVec4(255, 0, 255, 250);
        style.WindowRounding = 6;
        style.FrameRounding = 4;
        style.GrabRounding = 4;
    }

    void onRender() override {
        ImGuiStyle& style = ImGui::GetStyle();
        setStyle(style);

        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetWindowSize((ImVec2(400, 150)));
        ImGui::Begin("Control Parameters", NULL);

        ImGui::Text("Control Airspeed");
        ImGui::SliderFloat("knots", &controlOptions_.targetAirspeed, 0, 400);
        ImGui::Text("Control Angle of Attack");
        ImGui::SliderAngle("degrees", &controlOptions_.targetAngleOfAttack, -40, 40);

        if(ImGui::Button("CHANGE AIRCRAFT")) {
            ImGui::SetNextWindowPos(ImVec2(50, 50), 0, {});
            ImGui::SetNextWindowSize(ImVec2(100, 400));
            ImGui::Begin("Select Aircraft", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImTextureID image1 = ImGui::GetIO().Fonts->AddFontFromFileTTF(controlOptions_.imagePaths.at(0).x.value().c_str(), controlOptions_.imagePaths.at(0).z.value());
            ImGui::ImageButton(controlOptions_.imagePaths.at(0).y.value().c_str(),image1, Vector2(90, 50));
ImGui::Button(controlOptions_.imagePaths.at(0).y, Vector2(90, 125));
        }



//        ImTextureID image1 = ImGui::GetIO().Fonts->AddFontFromFileTTF(controlOptions_.path1.c_str(), {});
//        ImTextureID image2 = ImGui::GetIO().Fonts->AddFontFromFileTTF(controlOptions_.path2.c_str(), {});
//        ImGui::Text("Choose Aircraft type");
//        if(ImGui::ImageButton(image1, ImVec2())) {
//            controlOptions_.fileChoice = 1;
//        }
//        if(ImGui::ImageButton(image2, ImVec2())) {
//            controlOptions_.fileChoice = 2;
//        }

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
