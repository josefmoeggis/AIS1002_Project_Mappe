add_library(threepp::threepp ALIAS threepp)
target_compile_features(threepp PUBLIC cxx_std_17)

set(publicHeaderDir ${PROJECT_SOURCE_DIR}/include)
set(publicHeaders
        "AirObject.hpp"
        "Graph3D.hpp"
        "GUI.hpp"
        "PID.hpp"
        "Utils.hpp"
        "SceneSetup.hpp"
        )
set(sources
        "AirObject.cpp"
        "Graph3D.cpp"
        "SceneSetup.cpp"
        )

add_library(headerLib ${sources})
target_include_directories(headerLib PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_sources(headerLib PUBLIC ${publicHeaders} ${sources})
target_link_libraries(headerLib PUBLIC threepp::threepp imgui::imgui)

