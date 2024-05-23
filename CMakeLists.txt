cmake_minimum_required(VERSION 3.15)
project(AIS1002_project)

set(CMAKE_CXX_STANDARD 17)
find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
#find_package(Bullet CONFIG)

#if (BULLET_FOUND AND NOT TARGET Bullet::Bullet)
#    add_library(Bullet::Bullet INTERFACE IMPORTED src/SceneSetup.cpp include/SceneSetup.hpp)
#    if("${BULLET_INCLUDE_DIRS}" MATCHES ".*/bullet$")
#        target_include_directories(Bullet::Bullet INTERFACE "${BULLET_INCLUDE_DIRS}/..")
#    endif()
#    target_link_libraries(Bullet::Bullet INTERFACE ${BULLET_LIBRARIES})
#endif ()

#if (NOT TARGET "matplotlib::matplotlib")
#    find_package(Python3 COMPONENTS Interpreter Development)
#    if (Python3_FOUND)
#        find_path(MATPLOTLIB_CPP_INCLUDE_DIRS "matplotlibcpp.h")
#        if (MATPLOTLIB_CPP_INCLUDE_DIRS)
#            add_library(matplotlib::matplotlib INTERFACE IMPORTED)
#            target_compile_definitions(matplotlib::matplotlib INTERFACE WITHOUT_NUMPY HAS_MATPLOTLIB)
#            target_link_libraries(matplotlib::matplotlib INTERFACE Python3::Python)
#            target_include_directories(matplotlib::matplotlib INTERFACE "${MATPLOTLIB_CPP_INCLUDE_DIRS}" ${Python3_INCLUDE_DIRS})
#            set(matplotlib_FOUND TRUE)
#        else()
#            set(matplotlib_FOUND FALSE)
#        endif()
#    endif()
#
#endif()

include(FetchContent)
FETCHCONTENT_DECLARE(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v2.13.8
)
FETCHCONTENT_MAKEAVAILABLE(Catch2)
include_directories(${catch2_SOURCE_DIR}/single_include)


file(COPY "${CMAKE_SOURCE_DIR}/resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "${CMAKE_SOURCE_DIR}/resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

set(SOURCES
        src/AirObject.cpp
        src/Graph3D.cpp
        src/SceneSetup.cpp)
set(HEADERS
        include/PID.hpp
        include/GUI.hpp
        include/Utils.hpp
        include/AirObject.hpp
        include/SceneSetup.hpp
        include/PID.hpp
)

add_subdirectory(src)
add_subdirectory(tests)
add_executable(driveSimulation main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(driveSimulation PRIVATE threepp::threepp imgui::imgui)
target_include_directories(driveSimulation PRIVATE "${CMAKE_SOURCE_DIR}/include")
enable_testing()

