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


class AirObject {
public:
    AirObject(std::shared_ptr<BufferGeometry> geometry, std::shared_ptr<Material> material, std::shared_ptr<double> length, std::shared_ptr<float> liftCoeff,
              std::shared_ptr<float> dragCoeff, std::shared_ptr<float> wingArea, std::shared_ptr<float> angleOfAttack)
              : geometry_(geometry), material_(material), fileLength_(length), liftCoefficient_(liftCoeff), dragCoefficient_(dragCoeff),
              wingArea_(wingArea), angleOfAttack_(angleOfAttack) {}

    void setLength(std::shared_ptr<double> length);

    void setAS(std::shared_ptr<double> airspeed);

    void setLiftCoefficient(std::shared_ptr<float> liftcoefficient);

    void setWingArea(std::shared_ptr<float> wingArea);

    void setAngleOfAttack(std::shared_ptr<float> AoA);

    std::shared_ptr<double> calculateLift();

    std::shared_ptr<float> calculateDrag();

    std::shared_ptr<Mesh> createMesh();







private:
    std::shared_ptr<double> fileLength_;
    std::shared_ptr<double> airspeed_;
    std::shared_ptr<float> liftCoefficient_;
    std::shared_ptr<float> dragCoefficient_;
    std::shared_ptr<float> wingArea_;

    std::shared_ptr<float> angleOfAttack_;


    std::shared_ptr<float> airDensity_;
//    Not needed in the start - using standard density without using temp, pressure & gas constant
    std::shared_ptr<float> temp_;
    std::shared_ptr<float> press_;
    std::shared_ptr<float> gasConst_;
    std::shared_ptr<std::vector<double>> previousAS;

//    Mesh of the aircraft
    std::shared_ptr<BufferGeometry> geometry_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> aircraftFuselage_;
};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
