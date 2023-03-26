//
// Created by joelo on 23.03.2023.
//

#include "AirObject.hpp"

// Setting length of stl file to know bounds and scale
void AirObject::setLength(int length) {
    fileLength_ = length;
}

// Setting airspeed
void AirObject::setAS(double airspeed) {
    airspeed_ = airspeed;
}

// Setting lift coefficient
void AirObject::setLiftCoefficient(float liftcoefficient) {
    liftCoefficient_ = liftcoefficient;
}

// Setting wing area
void AirObject::setWingArea(float wingArea) {
    wingArea_ = wingArea;
}

void AirObject::setAngleOfAttack(float AoA) {
    angleOfAttack_ = AoA;
}

// Calculat lift from different standards
float AirObject::calculateLift() {
    float lift = (1/2) * airDensity_ * std::pow(airspeed_, 2) * wingArea_ * liftCoefficient_;
    return lift;
}

