//
// Created by joelo on 23.03.2023.
//
#include <cmath>
#include "AirObject.hpp"

// Setting length of stl file to know bounds and scale
void AirObject::setLength(float length) {
    fileLength_ = std::make_shared<float>(length);
}

// Setting airspeed
void AirObject::setAS(double airspeed) {
    airspeed_ = std::make_shared<double>(airspeed);
}

// Setting lift coefficient
void AirObject::setLiftCoefficient(float liftcoefficient) {
    liftCoefficient_ = std::make_shared<float>(liftcoefficient);
}

// Setting wing area
void AirObject::setWingArea(float wingArea) {
    wingArea_ = std::make_shared<float>(wingArea);
}

void AirObject::setAngleOfAttack(float AoA) {
    angleOfAttack_ = std::make_shared<float>(AoA);
}

// Calculat lift from different standards
std::shared_ptr<double> AirObject::calculateLift() {
    std::shared_ptr<double> lift = std::make_shared<double>(
            0.5f * *airDensity_ * std::pow(*airspeed_, 2) * *wingArea_ * *liftCoefficient_);
    return lift;
}

// Create aircraft mesh fuselage
std::shared_ptr<Mesh> AirObject::createMesh() {
    aircraftFuselage_ = Mesh::create(geometry_, material_);
    return aircraftFuselage_;
}

// Scale to make aircraft fit in the size of grid area
void AirObject::scaleToFit(int gridSize) {
    float scaleNr = gridSize / *fileLength_;
    aircraftFuselage_->scale *= scaleNr;
}

