add_executable(test_AirObject test_object.cpp)
add_test(NAME testAirObject COMMAND test_sphere)
target_link_libraries(test_AirObject PUBLIC Catch::Catch2 threepp::threepp)