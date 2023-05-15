//
// Created by joelo on 28.03.2023.
//
#include "../include/Graph3D.hpp"

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

void Graph3D::adjustGraphToFit(float maxVal) {
    // This code was meant to adjust the graph automatically depending on vector values
    // will be added later
/*    float peakVal {};
    float minVal {};
    for(Vector3 line : *graphVectors_) {
        if (line.y > peakVal) {
            peakVal = line.y;
        }
        if (line.y < minVal) {
            minVal = line.y;
        }
    }
    if((peakVal > 2 * *gridSize_) && (*scaleFactor_ < 1e8)) { // Adjust for large difference in
        int timesGrid = (int)peakVal * *gridSize_;
        std::cout << "timesGrid: " << timesGrid << std::endl;
        scaleFactor_ = std::make_shared<float>(*scaleFactor_ / (float)timesGrid);
    }
    if((minVal < -*gridSize_) && (*scaleFactor_ > 1e-8)) {
        int timesGrid = -((int)minVal * *gridSize_);
        std::cout << "timesGrid: " << timesGrid << std::endl;
        scaleFactor_ = std::make_shared<float>(*scaleFactor_ / (float)timesGrid);
    }

    while((peakVal > *gridSize_) && (*scaleFactor_ < 1e8)) {
        peakVal -= peakVal / (float)*divisions_;
        scaleFactor_ = std::make_shared<float>(*scaleFactor_ - (*scaleFactor_ / (float)*divisions_));
    }
    std::cout << peakVal << std::endl;
    while((peakVal < *gridSize_ / *divisions_) && (peakVal != 0) && (*scaleFactor_ > 1e-8)) {
        peakVal += peakVal / (float)*divisions_;
        scaleFactor_ = std::make_shared<float>(*scaleFactor_ + (*scaleFactor_ / (float)*divisions_));
    }
    std::cout << "peakVal: " << peakVal << std::endl; */

    scaledVectors_ = std::make_shared<std::vector<Vector3>>(*graphVectors_);
    scaleFactor_ = std::make_shared<float>(*gridSize_ / maxVal);
    for(int i = 0; i < graphVectors_->size(); i++) {
        scaledVectors_->at(i).y = ((*scaledVectors_)[i].y * *scaleFactor_) - *gridSize_ / 2;
    }
}

void Graph3D::updateLineVectors(float graphVal, float resolution) {
    float stepSize = (float)*gridSize_ / resolution;
    if(graphVectors_->empty()) {
        graphVectors_->push_back(Vector3 {
            grid_->position.x + 10,
            0,
            ((float)*gridSize_ / 2)});
    }
    graphVectors_->emplace_back(Vector3 {
        grid_->position.x + 10,
        graphVal,
        graphVectors_->back().z - stepSize});

    if(graphVectors_->back().z < -(*gridSize_ / 2)) {
        graphVectors_->erase(graphVectors_->begin());
        for (int i = 0; i < graphVectors_->size(); i++) {   // Shift the vector coordinates to the left on the graph to be within the grid
            graphVectors_->at(i).z = graphVectors_->at(i).z + stepSize;
        }
    }
}

std::vector<Vector3> Graph3D::getVectors() {
    return *graphVectors_;
}

void Graph3D::makeLine(std::shared_ptr<Scene> scene) {
    if (scene->getObjectByName("LastLine")) {
        scene->remove(graphLine_);
    }
    auto material = LineBasicMaterial::create();
    material->color = *graphColor_;
    auto geometry = BufferGeometry::create();
    geometry->setFromPoints(*scaledVectors_);
    graphLine_ = Line::create(geometry, material);
    graphLine_->name = "LastLine";
}

std::shared_ptr<Line> Graph3D::getLine() {
    return graphLine_;
}

void Graph3D::setPosition() {
    grid_->position.set(- (*gridSize_ / 2), 0, 0);
    grid_->rotateX(math::PI / 2);
    grid_->rotateZ(math::PI / 2);
}

float Graph3D::lastGraphVal() {
    return (*graphVectors_).back().y;
}

std::shared_ptr<Mesh> Graph3D::createMesh(std::shared_ptr<BufferGeometry> arrowGeometry) {
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = *graphColor_;
    auto arrow = Mesh::create(arrowGeometry, material);
    arrow->rotateY(math::PI /2);
    arrow->scale.setScalar( 2);
    return arrow;
}

void Graph3D::updateMesh(float distanceFromGrid) {
    arrow_->position.y = scaledVectors_->back().y;
    arrow_->position.x = scaledVectors_->back().x;
    arrow_->position.z = scaledVectors_->back().z + distanceFromGrid;
}

std::shared_ptr<Mesh> Graph3D::getMesh() {
    return arrow_;
}