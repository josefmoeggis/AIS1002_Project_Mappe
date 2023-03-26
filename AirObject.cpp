//
// Created by joelo on 23.03.2023.
//

#include "AirObject.hpp"

// Setting length of stl file to know bounds and scale
void AirObject::setLength(std::shared_ptr<int> length) {
    fileLength_ = length;
}

// Setting airspeed
void AirObject::setAS(std::shared_ptr<double> airspeed) {
    airspeed_ = airspeed;
}

// Setting lift coefficient
void AirObject::setLiftCoefficient(std::shared_ptr<float> liftcoefficient) {
    liftCoefficient_ = liftcoefficient;
}

// Setting wing area
void AirObject::setWingArea(std::shared_ptr<float> wingArea) {
    wingArea_ = wingArea;
}

void AirObject::setAngleOfAttack(std::shared_ptr<float> AoA) {
    angleOfAttack_ = AoA;
}

// Calculat lift from different standards
std::shared_ptr<float> AirObject::calculateLift() {
    std::shared_ptr<float> lift = (1/2) * airDensity_ * std::pow(airspeed_, 2) * wingArea_ * liftCoefficient_;
    return lift;
}

