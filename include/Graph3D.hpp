//
// Created by joelo on 28.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_GRAPH3D_HPP
#define THREEPP_VCPKG_TEST_GRAPH3D_HPP
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/helpers/GridHelper.hpp"
#include "threepp/materials/LineBasicMaterial.hpp"
#include "threepp/math/MathUtils.hpp"
#include "threepp/scenes/Scene.hpp"
#include "threepp/objects/Mesh.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include <iostream>
#include <vector>

using namespace threepp;

class Graph3D : Object3D {
//    Create constructor
public:
    Graph3D(int gridSize, int divisions, std::shared_ptr<BufferGeometry> arrowGeometry, Color gridColor = 0x0000FF, Color graphColor = 0xFFFFFF)
    {
        this->gridSize_ = std::make_shared<int>(gridSize);
        this->divisions_ = std::make_shared<int>(divisions);
        this->gridColor_ = std::make_shared<Color>(gridColor);
        this->graphColor_ = std::make_shared<Color>(graphColor);

        createGrid(gridSize, divisions, gridColor);

        arrow_ = createMesh(arrowGeometry);

        graphVectors_ = std::make_shared<std::vector<Vector3>>();
        scaledVectors_ = std::make_shared<std::vector<Vector3>>();
        scaleFactor_ = std::make_shared<float>(1);
    }


    void createGrid(int size, int divisions, Color color);

    std::shared_ptr<GridHelper> getGrid();

    std::shared_ptr<Mesh> createMesh(std::shared_ptr<BufferGeometry> arrowGeometry);

    void updateMesh(float distanceFromGrid);

    std::shared_ptr<Mesh> getMesh();

    int getGridSize();

    int getDivisions();

    void adjustGraphToFit(float maxVal);

    void updateLineVectors(float graphVal, float resolution); // Also starts line

    std::vector<Vector3> getVectors();

    void makeLine(std::shared_ptr<Scene> scene);

    std::shared_ptr<Line> getLine();

    void setPosition();


private:

    std::shared_ptr<int> gridSize_;
    std::shared_ptr<int> divisions_;
    std::shared_ptr<Mesh> arrow_;
    std::shared_ptr<float> scaleFactor_;
    std::shared_ptr<GridHelper> grid_;
    std::shared_ptr<Color> gridColor_;
    std::shared_ptr<Color> graphColor_;
    std::shared_ptr<std::vector<Vector3>> graphVectors_;
    std::shared_ptr<std::vector<Vector3>> scaledVectors_;
    std::shared_ptr<Line> graphLine_;
};


#endif //THREEPP_VCPKG_TEST_GRAPH3D_HPP
