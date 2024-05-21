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
    //std::cout << "Air density: " << airDensity << std::endl;
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

void AirObject::setStartvalues(float longitudinalSpeed, float normalSpeed, float pitchRate, float pitchAttitude,
                               float lateralSpeed, float rollRate, float yawRate, float rollAttitude){
    longitudinalSpeed_ = longitudinalSpeed;
    normalSpeed_ = normalSpeed;
    pitchRate_ = pitchRate;
    pitchAttitude_ = pitchAttitude;
    lateralSpeed_ = lateralSpeed;
    rollRate_ = rollRate;
    yawRate_ = yawRate;
    rollAttitude_ = rollAttitude;
}

void AirObject::updateLongitudinal(float elevatorDeflection, float dt) {
    elevatorDefl_ = elevatorDeflection;
    longitudinalAcc_ = (-0.09148) * longitudinalSpeed_ + 0.04242 * normalSpeed_ - 32.17 * pitchAttitude_;
    normalAcc_ = 10.51 * longitudinalSpeed_ - 3.066 * normalSpeed_ + 152 * pitchRate_;
    derivPitchRate_ = 0.2054 * longitudinalSpeed_ - 0.05581 * normalSpeed_ - 2.114 * pitchRate_ - 12.64 * elevatorDefl_;
    derivPitchAttitude_ = pitchRate_;

    longitudinalSpeed_ += longitudinalAcc_ * dt;
    normalSpeed_ += normalAcc_ * dt;
    pitchRate_ += derivPitchRate_ * dt;
    pitchAttitude_ += derivPitchAttitude_ * dt;

    absPitchAttitude_ = pitchAttitude_ * math::DEG2RAD;
    std::cout << "Elevator Deflection: " << elevatorDefl_ << std::endl;
    std::cout << "Longitudinal Speed: " << longitudinalSpeed_ << std::endl;
    std::cout << "Normal Speed: " << normalSpeed_ << std::endl;
    std::cout << "Pitch Rate: " << pitchRate_ << std::endl;
    std::cout << "Pitch Attitude: " << pitchAttitude_ << std::endl;
}

float AirObject::getPitch(){
    return absPitchAttitude_;
}

void AirObject::updateLateral(float aileronDeflection, float rudderDeflection, float dt) {
    aileronDefl_ = aileronDeflection;
    rudderDefl_ = rudderDeflection;
    lateralAcc_ = -0.093 * lateralSpeed_ - 152.6 * yawRate_ + 32.17 * rollAttitude_ + 3.469 * rudderDefl_;
    derivRollRate_ = -0.059 * lateralSpeed_ - 5.816 * rollRate_ + 1.854 * yawRate_ + 15.74 * aileronDefl_ + 1.380 * rudderDefl_;
    derivYawRate_ = 0.030 * lateralSpeed_ - 0.548 * rollRate_ - 0.953 * yawRate_ + 0.486 * aileronDefl_ - 4.288 * rudderDefl_;
    derivRollAttitude_ = rollRate_;

    // Update the state variables by integrating the derivatives
    lateralSpeed_ += lateralAcc_ * dt;
    rollRate_ += derivRollRate_ * dt;
    yawRate_ += derivYawRate_ * dt;
    rollAttitude_ += derivRollAttitude_ * dt;

    // Intermediate value that is not included in the state space
    yawAttitude_ += yawRate_ * dt;

    absRollAttitude_ = rollAttitude_ * math::DEG2RAD;
    absYawAttitude_ = yawAttitude_ * math::DEG2RAD;
}

float AirObject::getRoll(){
    return absRollAttitude_;
}

float AirObject::getYaw(){
    return absYawAttitude_;
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