//
// Created by joelo on 28.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_GRAPH3D_HPP
#define THREEPP_VCPKG_TEST_GRAPH3D_HPP
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/threepp.hpp"
#include "iostream"
#include "vector"
using namespace threepp;

class Graph3D : Object3D {
//    Create constructor
public:
    Graph3D(int gridSize, int divisions, Color gridColor = 0x0000FF, Color graphColor = 0xADFF2F)
    {
        this->gridSize_ = std::make_shared<int>(gridSize);
        this->divisions_ = std::make_shared<int>(divisions);
        this->gridColor_ = std::make_shared<Color>(gridColor);
        this->graphColor_ = std::make_shared<Color>(graphColor);

        createGrid(gridSize, divisions, gridColor);
    }


    void createGrid(int size, int divisions, Color color);

    std::shared_ptr<GridHelper> getGrid();

    int getGridSize();

    int getDivisions();

    void updateLine(float lift, float resolution); // Also starts line

    std::shared_ptr<Line> getLine();

    void setPosition();


private:

    std::shared_ptr<int> gridSize_;
    std::shared_ptr<int> divisions_;
    std::shared_ptr<GridHelper> grid_;
    std::shared_ptr<Color> gridColor_;
    std::shared_ptr<Color> graphColor_;
    std::shared_ptr<std::vector<Vector3>> graphLine_;
};


#endif //THREEPP_VCPKG_TEST_GRAPH3D_HPP
