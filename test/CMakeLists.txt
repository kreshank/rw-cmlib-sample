file (GLOB_RECURSE UTESTS unit_tests/*.cpp)
file (GLOB_RECURSE TEST_H test_utils/*.hpp)

add_executable(run_tests test_driver_main.cpp ${UTESTS} ${TEST_H})

target_link_libraries(run_tests PRIVATE core)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/test)