cmake_minimum_required(VERSION 3.15)
project(AIS1002_Project_Mappe)

set(CMAKE_CXX_STANDARD 17)
set(publicHeaderDir ${PROJECT_SOURCE_DIR}/include)
set(publicHeaders
        "AirObject.cpp"
        "Graph3D.cpp"
        "GUI.hpp"
        "PID.hpp"
        "Utils.hpp"
        "SceneSetup.cpp"
        )
set(sources
        "AirObject.cpp"
        "Graph3D.cpp"
        "SceneSetup.cpp"
        )

add_library(threepp::threepp ALIAS threepp)
target_compile_features(threepp PUBLIC cxx_std_17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(driveSimulation main.cpp test_object.cpp)
target_include_directories(AIS1002_Project_Mappe/include PUBLIC "${CMAKE_SOURCE_DIR}")

target_link_libraries(AIS1002_Project_Mappe PRIVATE threepp::threepp)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_subdirectory(tests)