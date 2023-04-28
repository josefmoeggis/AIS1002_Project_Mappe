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

void Graph3D::adjustGraphToFit() {
    float peakVal {};
    for(Vector3 line : *graphVectors_) {
        if (line.y > peakVal) {
            peakVal = line.y;
        }
    }
    while(peakVal > *gridSize_) {
        peakVal -= peakVal / (float)*divisions_;
        scaleFactor_ = std::make_shared<float>(*scaleFactor_ - (*scaleFactor_ / (float)*divisions_));
        std::cout << peakVal << std::endl;
    }

    while((peakVal < *gridSize_ / *divisions_) && (peakVal != 0)) {
        peakVal += peakVal / (float)*divisions_;
        scaleFactor_ = std::make_shared<float>(*scaleFactor_ + (*scaleFactor_ / (float)*divisions_));
    }
    for(int i = 0; i < graphVectors_->size(); i++) {
        graphVectors_->at(i).y *= *scaleFactor_;
    }
    std::cout << *scaleFactor_ << std::endl;
}

void Graph3D::updateLineVectors(float graphVal, float resolution) {
    float stepSize = (float)*gridSize_ / resolution;
    if(graphVectors_->empty()) {
        graphVectors_->push_back(Vector3 {
            grid_->position.x - 10,
            -((float)*gridSize_ / 2),
            ((float)*gridSize_ / 2)});
    }
    graphVectors_->emplace_back(Vector3 {
        grid_->position.x -10,
        graphVal - ((float)*gridSize_ / 2),
        graphVectors_->back().z - stepSize});

    if(graphVectors_->back().z < -(*gridSize_ / 2)) {
        std::cout << "Shifting back" << std::endl;
        graphVectors_->erase(graphVectors_->begin());
        for (int i = 0; i < graphVectors_->size(); i++) {   // Shift the vector coordinates to the left on the graph to be within the grid
            graphVectors_->at(i).z += stepSize;
        }
    }

}

std::vector<Vector3> Graph3D::getVectors() {
    return *graphVectors_;
}

void Graph3D::makeLine(std::shared_ptr<Scene> scene) {
    if (scene->getObjectByName("LastVector")) {
        scene->remove(graphLine_);
    }
    auto material = LineBasicMaterial::create();
    material->color = *graphColor_;
    auto geometry = BufferGeometry::create();
    geometry->setFromPoints(*graphVectors_);
    graphLine_ = Line::create(geometry, material);
    graphLine_->name = "LastVector";
}

std::shared_ptr<Line> Graph3D::getLine() {
    return graphLine_;
}

void Graph3D::setPosition() {
    grid_->position.set(- (*gridSize_ / 2), 0, 0);
    grid_->rotateX(math::PI / 2);
    grid_->rotateZ(math::PI / 2);
}