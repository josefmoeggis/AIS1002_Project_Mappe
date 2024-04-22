//
// Created by joelo on 23.03.2023.
//
#include "../include/AirObject.hpp"


std::shared_ptr<AirObject> AirObject::create(std::shared_ptr<BufferGeometry> geometry,
                                             std::shared_ptr<Material> material,
                                             float length, float wingArea,
                                             float liftCoeff, float dragCoeff,
                                             float angleOfAttack) {
    return std::shared_ptr<AirObject>(new AirObject(geometry, material, length, liftCoeff,
                                                    dragCoeff, wingArea, angleOfAttack));
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
    if((-aCrit_ <= angleOfAttack_) && (angleOfAttack_ <= aCrit_)) {
        CLwAngle = liftCoefficient_ + 2*math::PI * angleOfAttack_;
    } else if((aCrit_ < angleOfAttack_) && (angleOfAttack_ <= aStall_)) {
        CLwAngle = CLstall_ - pow(stallRate_ * (angleOfAttack_ - aCrit_), 2);
    } else if((-aStall_ <= angleOfAttack_) && (angleOfAttack_ < -aCrit_)) {
        CLwAngle = -CLstall_ + pow(stallRate_ * (angleOfAttack_ + aCrit_), 2);
    } else {
        CLwAngle = 0;
        std::cout << "No lift! Aircraft is stalling" << std::endl;
    }
    return CLwAngle;
}

float AirObject::calcAirDensity(float temp, float altitude) {
    float airDensity = 0;
    if(altitude < 11000) {
        airDensity = getStdRho() * pow(temp / (temp + (getTempLapsRate() * altitude)), // Combines two equations (finds T from temp laps rate)
                                       1 + ((getG() * getMolMass()) / (getGasConst() * getTempLapsRate())));
    } else if (altitude >= 11000) {
        airDensity = getRho_11km() * exp(-(getG() * getMolMass() * (altitude - 11000)) / (getGasConst() * temp));
    } else {
        std::cout << "Altitude or temperature out of bounds" << std::endl;
    }
    std::cout << "Air density: " << airDensity << std::endl;
    return airDensity;
}

// Calculate lift from different standards
float AirObject::calculateLift(float airspeed, float temp, float altitude) {
    float lift = calcLiftCoeffAngle() * 0.5f * calcAirDensity(temp, altitude) * std::pow(airspeed, 2) * wingArea_;
    if (liftCoefficient_ == 0) {
        std::cout << "Not all lift parameters are set" << std::endl; // Use optional later
    }
    return lift;
}

float AirObject::calculateMaxLift(float maxAirspeed) {
    float maxLift = (liftCoefficient_ + 2*math::PI * 10 * math::DEG2RAD) * 0.5f * 0.5 * pow(maxAirspeed, 2) * wingArea_;
    return maxLift;
}

void AirObject::setDragCoeff(float dragCoeff) {
    dragCoefficient_ = dragCoeff;
}

float AirObject::calcDragCoeffAngle() {
    return dragCoefficient_ + 0.08 * angleOfAttack_ + 0.005 * pow(angleOfAttack_, 2);
}

float AirObject::calculateDrag(float airspeed, float temp, float altitude) {
    return 0.5 * calcAirDensity(temp, altitude) * airspeed * calcDragCoeffAngle() * wingArea_;
}

float AirObject::calculateMaxDrag(float maxAirspeed) {
    return 0.5 * 1.225 * maxAirspeed * dragCoefficient_ +
    0.08 * angleOfAttack_ + 0.005 * pow(40 * math::DEG2RAD, 2) * wingArea_;
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

AirObject::~AirObject() {
    this->geometry_->dispose();
    this->material_->dispose();
  }