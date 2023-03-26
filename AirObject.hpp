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
    AirObject() {
}

    void setLength(std::shared_ptr<int> length);

    void setAS(std::shared_ptr<double> airspeed);

    void setLiftCoefficient(std::shared_ptr<float> liftcoefficient);

    void setWingArea(std::shared_ptr<float> wingArea);

    void setAngleOfAttack(std::shared_ptr<float> AoA);

    std::shared_ptr<float> calculateLift();

    std::shared_ptr<float> calculateDrag();







private:
    std::shared_ptr<int> fileLength_;
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

protected:
    AirObject(std::shared_ptr<BufferGeometry> geometry, std::shared_ptr<Material> material, std::shared_ptr<int> length, std::shared_ptr<float> liftCoeff, std::shared_ptr<float> dragCoeff, std::shared_ptr<float> wingArea);

};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
