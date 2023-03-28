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
    Graph3D() {}

    std::shared_ptr<GridHelper> createGrid(int size, int divisions, Color color);

    std::shared_ptr<int> getGridSize();

    std::shared_ptr<int> getDivisions();

    void updateLine(std::shared_ptr<float> lift, float resolution);

    std::shared_ptr<Line> showLine();



private:

    std::shared_ptr<int> gridSize_;
    std::shared_ptr<int> divisions_;
    std::shared_ptr<GridHelper> grid_;
    std::shared_ptr<std::vector<Vector3>> graphLine_;
};


#endif //THREEPP_VCPKG_TEST_GRAPH3D_HPP
