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
void AirObject::setAS(float airspeed) {
    airspeed_ = std::make_shared<float>(airspeed);
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
float AirObject::calculateLift() {
    float lift = 0.5f * *airDensity_ * std::pow(*airspeed_, 2) * *wingArea_ * *liftCoefficient_;
    return lift;
}

// Create aircraft mesh fuselage
std::shared_ptr<Mesh> AirObject::createMesh() {
    aircraftFuselage_ = Mesh::create(geometry_, material_);
    return aircraftFuselage_;
}

// Scale to make aircraft fit in the size of grid area
void AirObject::scaleModel(int gridSize) {
    float scaleNr = gridSize / *fileLength_;
    aircraftFuselage_->scale *= scaleNr;
}

// Set aircraft model to middle position compared to grid
void AirObject::centerModel(int gridSize) {
    aircraftFuselage_->position.z = -(gridSize / 2);
}

// Calculate m/s from knots
float AirObject::knotsToMtrPrSec(float knots) {
    float metersPerSecond = knots * 0.514444444;
    return metersPerSecond;
}

void AirObject::setAirDensity(float air) {
    airDensity_ = std::make_shared<float>(air);
}

