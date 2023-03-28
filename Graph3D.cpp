//
// Created by joelo on 28.03.2023.
//
#include "threepp/objects/Line.hpp"
#include "threepp/threepp.hpp"
#include "Graph3D.hpp"


std::shared_ptr<GridHelper> Graph3D::createGrid(int size, int divisions, Color color) {
    auto grid = GridHelper::create(size, divisions, color, color);
    return grid;
}

std::shared_ptr<int> Graph3D::getGridSize() {
    return gridSize_;
}

std::shared_ptr<int> Graph3D::getDivisions() {
    return divisions_;
}

void Graph3D::updateLine(std::shared_ptr<float> lift, float resolution) {
    float stepSize = (float)*gridSize_ / resolution;
    if(graphLine_->size() == 0) {
        graphLine_->emplace_back(Vector3 {grid_->position.x, -((float)*gridSize_ / 2), -((float)*gridSize_ / 2)});
    }
    if(graphLine_->back().x >= ((float)*gridSize_ / 2)) {
        graphLine_->erase(graphLine_->begin());
    }
    graphLine_->emplace_back(Vector3 {grid_->position.x, static_cast<float>(*lift), graphLine_->back().z + stepSize});
}

std::shared_ptr<Line> Graph3D::showLine() {
    auto material = LineBasicMaterial::create();
    material->color = threepp::Color(0xB22222);
    auto geometry = BufferGeometry::create();
    geometry->setFromPoints(*graphLine_);
    auto graphLine = Line::create(geometry, material);
    return graphLine;
}