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
    AirObject(std::shared_ptr<BufferGeometry> geometry, std::shared_ptr<Material> material, float length,
              float liftCoeff,
              float dragCoeff, float wingArea, float angleOfAttack, float airDensity = 1.293)
            : geometry_(geometry), material_(material), fileLength_(std::make_shared<float>(length)),
              liftCoefficient_(std::make_shared<float>(liftCoeff)),
              dragCoefficient_(std::make_shared<float>(dragCoeff)),
              wingArea_(std::make_shared<float>(wingArea)), angleOfAttack_(std::make_shared<float>(angleOfAttack)),
              airDensity_(std::make_shared<float>(airDensity)) {}


    void setAngleParameters(float CLstall, float aCrit, float aStall, float stallRate);

    void setAngleOfAttack(float AoA);

    float getAngleOfAttack();

    void setControlledAngle(float gain, float maxRadPrSec, float dt);

    float calcLiftCoeffAngle();

    float calculateLift(float airspeed);

    float calculateMaxLift(float airspeed);

    float calculateDrag();

    void createMesh();

    std::shared_ptr<Mesh> getMesh();

    void scaleModel(int gridSize);

    void centerModel(int gridSize);

    float knotsToMtrPrSec(float knots);

    void setAirDensity(float air);


private:
//    Physical parameters
    const std::shared_ptr<float> fileLength_;
    const std::shared_ptr<float> liftCoefficient_;
    const std::shared_ptr<float> dragCoefficient_;
    const std::shared_ptr<float> wingArea_;
//    Aerodynamic parameters
    std::shared_ptr<float> CLstall_;
    std::shared_ptr<float> aCrit_;
    std::shared_ptr<float> aStall_;
    std::shared_ptr<float> stallRate_;


    std::shared_ptr<float> angleOfAttack_;

    std::shared_ptr<float> airDensity_;
//    Not needed in the start - using standard density without using temp, pressure & gas constant
    std::shared_ptr<float> temp_;
    std::shared_ptr<float> press_;
    std::shared_ptr<float> gasConst_;

//    Mesh of the aircraft
    std::shared_ptr<BufferGeometry> geometry_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> aircraftFuselage_;
};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
