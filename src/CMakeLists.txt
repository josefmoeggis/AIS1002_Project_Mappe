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

target_compile_features(threepp PUBLIC cxx_std_17)
add_library(threepp::threepp ALIAS threepp)