cmake_minimum_required(VERSION 3.15)
project(AIS1002_Project_Mappe)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(test main.cpp test_object.cpp)
target_include_directories(AIS1002_Project_Mappe PUBLIC "${CMAKE_SOURCE_DIR}")

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