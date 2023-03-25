//
// Created by joelo on 23.03.2023.
//

#include "AirObject.hpp"

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

// Calculat lift from different standards
float AirObject::calculateLift() {
    float lift = (1/2) * airDensity_ * std::pow(airspeed_, 2) * wingArea_ * liftCoefficient_;
    return lift;
}

