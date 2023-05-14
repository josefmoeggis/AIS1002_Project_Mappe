
add_executable(test_object test_AirObject.cpp)
add_test(NAME test_object COMMAND test_object)
target_link_libraries(test_object PUBLIC Catch2::Catch2 threepp::threepp)
target_link_libraries(test_object PUBLIC headerLib)
target_include_directories(test_object PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests)