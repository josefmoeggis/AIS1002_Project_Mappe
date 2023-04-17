cmake_minimum_required(VERSION 3.15)
project(threepp_vcpkg_test)

set(CMAKE_CXX_STANDARD 17)
find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

find_package(Bullet CONFIG)

if (BULLET_FOUND AND NOT TARGET Bullet::Bullet)
    add_library(Bullet::Bullet INTERFACE IMPORTED Graph3D.hpp Graph3D.hpp GUI.hpp GUI.hpp Graph3D.cpp tests/test_object.cpp tests/test_object.cpp)
    if("${BULLET_INCLUDE_DIRS}" MATCHES ".*/bullet$")
        target_include_directories(Bullet::Bullet INTERFACE "${BULLET_INCLUDE_DIRS}/..")
    endif()
    target_link_libraries(Bullet::Bullet INTERFACE ${BULLET_LIBRARIES})
endif ()


file(COPY "${CMAKE_SOURCE_DIR}/resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test main.cpp AirObject.cpp Graph3D.cpp tests/test_object.cpp tests/test_object.cpp)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui)

