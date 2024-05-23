//
// Created by joelo on 11.05.2023.
//

#ifndef THREEPP_VCPKG_TEST_UTILS_HPP
#define THREEPP_VCPKG_TEST_UTILS_HPP

// Calculate m/s from knots
static float knotsToMtrPrSec(float knots) {
    return knots * 0.514444444;
}

static float feetToMtr(float feet) {
    return feet * 0.3048;
}

static float celsiusToKelvin(float celsius) {
    return celsius + 273;
}

static float getG() {
    return 9.80665;
}

static float getT_0() {
    return 273 + 20;
}

static float getMolMass() {
    return 0.0289644;
}

static float getGasConst() {
    return 8.31447;
}

static float getTempLapsRate() {
    return -0.0065;
}

static float getStdRho() {
    return 1.225;
}

static float getRho_11km() {
    return 0.3648;
}

#endif //THREEPP_VCPKG_TEST_UTILS_HPP