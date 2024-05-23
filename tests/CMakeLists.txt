
add_executable(test_object test_AirObject.cpp)
add_test(NAME test_object COMMAND test_object)
target_link_libraries(test_object PUBLIC Catch2::Catch2 threepp::threepp)
target_link_libraries(test_object PRIVATE headerLib)
target_include_directories(test_object PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests)

add_executable(test_Graph3D test_Graph3D.cpp)
add_test(NAME test_Graph3D COMMAND test_object)
target_link_libraries(test_Graph3D PUBLIC Catch2::Catch2 threepp::threepp)
target_link_libraries(test_Graph3D PRIVATE headerLib)
target_include_directories(test_Graph3D PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests)

add_executable(test_Controls test_Controls.cpp)
add_test(NAME test_Controls COMMAND test_Controls)
target_link_libraries(test_Controls PUBLIC Catch2::Catch2 threepp::threepp)
target_link_libraries(test_Controls PRIVATE headerLib)
target_include_directories(test_Controls PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests)