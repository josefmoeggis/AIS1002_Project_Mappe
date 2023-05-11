//
// Created by joelo on 11.05.2023.
//

#ifndef THREEPP_VCPKG_TEST_UTILS_HPP
#define THREEPP_VCPKG_TEST_UTILS_HPP

#endif //THREEPP_VCPKG_TEST_UTILS_HPP



// Calculate m/s from knots
float knotsToMtrPrSec(float knots) {
    float metersPerSecond = knots * 0.514444444;
    return metersPerSecond;
}
