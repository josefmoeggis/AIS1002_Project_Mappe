set(publicHeaderDir ${PROJECT_SOURCE_DIR}/include)
set(publicHeaders
        "AirObject.cpp"
        "Graph3D.cpp"
        "GUI.hpp"
        "PID.hpp"
        )
set(sources
        "AirObject.cpp"
        "Graph3D.cpp"
        )

add_library(threepp::threepp ALIAS threepp)
target_compile_features(threepp PUBLIC cxx_std_17)