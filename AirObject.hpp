//
// Created by joelo on 23.03.2023.
//

#ifndef AIS2001_AEROFOILTESTING_AIROBJECT_HPP
#define AIS2001_AEROFOILTESTING_AIROBJECT_HPP
#include "threepp/core/Object3D.hpp"
#include "iostream"
#include "vector"


class AirObject: public Mesh {
public:
    void setAS(double as);


    double calculateLift();





private:
    double airspeed;
    double drag;
    std::vector<double> previousAS;

};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
