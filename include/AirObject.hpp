//
// Created by joelo on 23.03.2023.
//

#ifndef AIS2001_AEROFOILTESTING_AIROBJECT_HPP
#define AIS2001_AEROFOILTESTING_AIROBJECT_HPP

#include "threepp/extras/imgui/imgui_context.hpp"
#include "iostream"
#include "vector"
#include "threepp/core/BufferGeometry.hpp"
#include "threepp/materials/Material.hpp"
#include "threepp/objects/Mesh.hpp"
#include "threepp/math/MathUtils.hpp"

using namespace threepp;


class AirObject {
public:
    AirObject(std::shared_ptr<BufferGeometry> geometry, std::shared_ptr<Material> material, float length,
              float wingArea, float liftCoeff,
              float dragCoeff, float angleOfAttack, float airDensity)
            : geometry_(geometry), material_(material), fileLength_(length),
              liftCoefficient_(liftCoeff), dragCoefficient_(dragCoeff),
              wingArea_(wingArea), angleOfAttack_(angleOfAttack),
              airDensity_(airDensity) {}


    void setAngleParameters(float CLstall, float aCrit, float aStall, float stallRate);

    void setAngleOfAttack(float AoA);

    float getAngleOfAttack();

    void setControlledAngle(float gain, float maxRadPrSec, float dt);

    float calcLiftCoeffAngle();

    float calculateLift(float airspeed);

    float calculateMaxLift(float airspeed);

    void setDragCoeff(float dragCoeff);

    float calculateDragCoeffAngle();

    float calculateDrag(float airspeed);

    void createMesh();

    std::shared_ptr<Mesh> getMesh();

    void scaleModel(int gridSize);

    void centerModel(int gridSize);

    float knotsToMtrPrSec(float knots);

    void setAirDensity(float air);

    ~AirObject();

    static std::shared_ptr<AirObject> create(std::shared_ptr<BufferGeometry> geometry,
                                       std::shared_ptr<Material> material,
                                       float length, float wingArea,
                                       float liftCoeff = 0.77, float dragCoeff = 0.3,
                                       float angleOfAttack = 0, float airDensity = 1.293);


private:
//    Physical parameters
    const float fileLength_;
    const float liftCoefficient_;
    float dragCoefficient_;
    const float wingArea_;
//    Aerodynamic parameters
    float CLstall_;
    float aCrit_;
    float aStall_;
    float stallRate_;


    float angleOfAttack_;

    float airDensity_;
//    Not needed in the start - using standard density without using temp, pressure & gas constant
    float temp_;
    float press_;
    float gasConst_;

//    Mesh of the aircraft
    std::shared_ptr<BufferGeometry> geometry_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> aircraftFuselage_;
};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
