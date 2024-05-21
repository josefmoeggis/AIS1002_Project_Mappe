//
// Created by joelo on 23.03.2023.
//

#ifndef AIS2001_AEROFOILTESTING_AIROBJECT_HPP
#define AIS2001_AEROFOILTESTING_AIROBJECT_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "threepp/extras/imgui/imgui_context.hpp"
#include "threepp/core/BufferGeometry.hpp"
#include "threepp/materials/Material.hpp"
#include "threepp/objects/Mesh.hpp"
#include "threepp/math/MathUtils.hpp"
#include "Utils.hpp"

using namespace threepp;


class AirObject {
public:
    AirObject(std::shared_ptr<BufferGeometry> geometry, std::shared_ptr<Material> material, float length,
              float wingArea, float liftCoeff,
              float dragCoeff, float angleOfAttack)
            : geometry_(geometry), material_(material), fileLength_(length),
              liftCoefficient_(liftCoeff), dragCoefficient_(dragCoeff),
              wingArea_(wingArea), angleOfAttack_(angleOfAttack) {}


    void setAngleParameters(float CLstall, float aCrit, float aStall, float stallRate);

    void setAngleOfAttack(float AoA);

    float getAngleOfAttack();

    void setControlledAngle(float gain, float maxRadPrSec, float dt);

    float calcLiftCoeffAngle();

    float calcAirDensity(float temp, float altitude);

    float calculateLift(float airspeed, float temp, float altitude);

    float calculateMaxLift(float airspeed);

    void updateLongitudinal(float elevatorDeflection, float dt);

    void setDragCoeff(float dragCoeff);

    float calcDragCoeffAngle();

    float calculateDrag(float airspeed, float temp, float altitude);

    float calculateMaxDrag(float airspeed);

    void createMesh();

    std::shared_ptr<Mesh> getMesh();

    void scaleModel(int gridSize);

    void centerModel(int gridSize);

    ~AirObject();

    static std::shared_ptr<AirObject> create(std::shared_ptr<BufferGeometry> geometry,
                                       std::shared_ptr<Material> material,
                                       float length, float wingArea,
                                       float liftCoeff = 0.77, float dragCoeff = 0.3,
                                       float angleOfAttack = 0);


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

//    Physics parameters
    float aileronDefl_ = 0;
    float elevatorDefl_ = 0;
    float rudderDefl_ = 0;
    float thrust_ = 0;

    float rollAttitude_ = 0;
    float pitchAttitude_ = 0;
    float yawAttitude_ = 0;

    float derivRollAttitude_ = 0;
    float derivPitchAttitude_ = 0;
    float derivYawAttitude_ = 0;

    float rollRate_ = 0;
    float pitchRate_ = 0;
    float yawRate_ = 0;

    float derivRollRate_ = 0;
    float derivPitchRate_ = 0;
    float derivYawRate_ = 0;

    float longitudinalAcc_ = 0;
    float lateralAcc_ = 0;
    float normalAcc_ = 0;

    float longitudinalSpeed_ = 0;
    float lateralSpeed_ = 0;
    float normalSpeed_ = 0;

    float altitude_ = 0;


//    Mesh of the aircraft
    std::shared_ptr<BufferGeometry> geometry_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> aircraftFuselage_;
};


#endif //AIS2001_AEROFOILTESTING_AIROBJECT_HPP
