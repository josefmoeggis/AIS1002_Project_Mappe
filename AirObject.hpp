//
// Created by joelo on 23.03.2023.
//

#ifndef AIS2001_AEROFOILTESTING_AIROBJECT_HPP
#define AIS2001_AEROFOILTESTING_AIROBJECT_HPP
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/threepp.hpp"
#include "iostream"
#include "vector"

using namespace threepp;


class AirObject: public Mesh {
public:
    void setAS(double as);


    float calculateLift();





private:
    double airspeed_;
    float liftCoefficient_;
    float dragCoefficient_;
    float airDensity_;
    std::vector<double> previousAS;

};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
