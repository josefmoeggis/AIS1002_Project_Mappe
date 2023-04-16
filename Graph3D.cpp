//
// Created by joelo on 28.03.2023.
//
#include "threepp/objects/Line.hpp"
#include "threepp/threepp.hpp"
#include "Graph3D.hpp"

//FIX THIS
void  Graph3D::createGrid(int size, int divisions, Color color) {
    grid_ = GridHelper::create(size, divisions, color, color);
}

std::shared_ptr<GridHelper> Graph3D::getGrid() {
    return grid_;
}

int Graph3D::getGridSize() {
    return *gridSize_;
}

int Graph3D::getDivisions() {
    return *divisions_;
}

void Graph3D::updateLine(float lift, float resolution) {
    float stepSize = (float)*gridSize_ / resolution;
    if(graphLine_->size() == 0) {
        graphLine_->emplace_back(Vector3 {grid_->position.x, -((float)*gridSize_ / 2), -((float)*gridSize_ / 2)});
    }
    if(graphLine_->back().x >= ((float)*gridSize_ / 2)) {
        graphLine_->erase(graphLine_->begin());
    }
    graphLine_->emplace_back(Vector3 {grid_->position.x, lift, graphLine_->back().z + stepSize});
}

std::shared_ptr<Line> Graph3D::getLine() {
    auto material = LineBasicMaterial::create();
    material->color = threepp::Color(0xB22222);
    auto geometry = BufferGeometry::create();
    geometry->setFromPoints(*graphLine_);
    auto graphLine = Line::create(geometry, material);
    return graphLine;
}

void Graph3D::setPosition() {
    grid_->position.set(-*gridSize_ / 2, 0, 0);
    grid_->rotateX(math::PI / 2);
    grid_->rotateZ(math::PI / 2);
}