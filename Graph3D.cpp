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

void Graph3D::updateLineVectors(float lift, float resolution) {
    float stepSize = (float)*gridSize_ / resolution;

    if(graphVectors_->empty()) {
        graphVectors_->push_back(Vector3 {grid_->position.x, -((float)*gridSize_ / 2), -((float)*gridSize_ / 2)});
    }

    graphVectors_->emplace_back(Vector3 {grid_->position.x, lift, graphVectors_->back().z + stepSize});

    if(graphVectors_->back().x >= (*gridSize_ / 2)) {
        graphVectors_->erase(graphVectors_->begin());
    }
}

std::vector<Vector3> Graph3D::getVectors() {
    return *graphVectors_;
}

void Graph3D::makeLine() {
    auto material = LineBasicMaterial::create();
    material->color = threepp::Color(0xB22222);
    auto geometry = BufferGeometry::create();
    geometry->setFromPoints(*graphVectors_);
    graphLine_ = Line::create(geometry, material);
}

std::shared_ptr<Line> Graph3D::getLine() {
    return graphLine_;
}

void Graph3D::setPosition() {
    grid_->position.set(- (*gridSize_ / 2), 0, 0);
    grid_->rotateX(math::PI / 2);
    grid_->rotateZ(math::PI / 2);
}