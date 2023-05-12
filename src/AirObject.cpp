//
// Created by joelo on 23.03.2023.
//
#include "../include/AirObject.hpp"


std::shared_ptr<AirObject> AirObject::create(std::shared_ptr<BufferGeometry> geometry,
                                             std::shared_ptr<Material> material,
                                             float length, float wingArea,
                                             float liftCoeff, float dragCoeff,
                                             float angleOfAttack, float airDensity) {
    return std::shared_ptr<AirObject>(new AirObject(geometry, material, length, liftCoeff,
                                                    dragCoeff, wingArea, angleOfAttack, airDensity));
}

// Setting length of stl file to know bounds and scale
void AirObject::setAngleParameters(const float CLstall, const float aCrit,
                                   const float aStall, const float stallRate) {
    CLstall_ = CLstall;
    aCrit_ = aCrit * math::DEG2RAD;
    aStall_ = aStall * math::DEG2RAD;
    stallRate_ = stallRate;
}

void AirObject::setAngleOfAttack(float AoA) {
    angleOfAttack_ = AoA;
}

float AirObject::getAngleOfAttack() {
    return angleOfAttack_;
}

void AirObject::setControlledAngle(float gain, float maxRadPrSec, float dt) {
    float angleDiffPrFrame = gain * maxRadPrSec * dt;
    setAngleOfAttack(getAngleOfAttack() + angleDiffPrFrame);
}

float AirObject::calcLiftCoeffAngle() {
    float CLwAngle {};
    if(-aCrit_ <= angleOfAttack_ <= aCrit_) {
        CLwAngle = liftCoefficient_ + 2*math::PI * angleOfAttack_;
    } else if(aCrit_ < angleOfAttack_ <= aStall_) {
        CLwAngle = CLstall_ - std::pow(stallRate_ * (angleOfAttack_ - aCrit_), 2);
    } else if(-aStall_ <= angleOfAttack_ < -aCrit_) {
        CLwAngle = -CLstall_ + std::pow(stallRate_ * (angleOfAttack_ + aCrit_), 2);
    } else {
        CLwAngle = 0;
        std::cout << "No lift! Aircraft is stalling" << std::endl;
    }
    return CLwAngle;
}

// Calculat lift from different standards
float AirObject::calculateLift(float airspeed) {
    float lift = calcLiftCoeffAngle() * 0.5f * airDensity_ * std::pow(airspeed, 2) * wingArea_;
    if (liftCoefficient_ == 0) {
        std::cout << "Not all parameters are set, resulting in discrepancies calculations" << std::endl; // Use optional later
    }
    return lift;
}

float AirObject::calculateMaxLift(float maxAirspeed) {
    float maxLift = (liftCoefficient_ + 2*math::PI * aCrit_) * 0.5f * airDensity_ * std::pow(maxAirspeed, 2) * wingArea_;
    return maxLift;
}

void AirObject::setDragCoeff(float dragCoeff) {
    dragCoefficient_ = dragCoeff;
}

float AirObject::calculateDragCoeffAngle() {
    return dragCoefficient_ + 0.08 * angleOfAttack_ + 0.005 * pow(angleOfAttack_, 2);
}

float AirObject::calculateDrag(float airspeed) {
    return 0.5 * airDensity_ * airspeed * calculateDragCoeffAngle() * wingArea_;
}

void AirObject::createMesh() {
    aircraftFuselage_ = Mesh::create(geometry_, material_);
    aircraftFuselage_->name = "aircraftFuselage";
}

// Create aircraft mesh fuselage
std::shared_ptr<Mesh> AirObject::getMesh() {
    return aircraftFuselage_;
}

// Scale to make aircraft fit in the size of grid area
void AirObject::scaleModel(int gridSize) {
    float scaleNr = gridSize / fileLength_;
    aircraftFuselage_->scale *= scaleNr;
}

// Set aircraft model to middle position compared to grid
void AirObject::centerModel(int gridSize) {
    aircraftFuselage_->position.z = -(gridSize / 2);
}

void AirObject::setAirDensity(float air) {
    airDensity_ = air;
}

AirObject::~AirObject() {
    this->geometry_->dispose();
    this->material_->dispose();
  }