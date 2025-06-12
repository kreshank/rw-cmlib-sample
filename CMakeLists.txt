cmake_minimum_required(VERSION 3.12)

project(cmlib LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Enable optimizations for release builds
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O3)
add_compile_options("-Wall" "-Wextra" "-pedantic")

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

# Include directories
include_directories(include)

# Add core source file libraries
add_library(core STATIC ${SOURCES})

# Main Executable
#add_executable(cmlib ${SOURCES} ${HEADERS})

#target_link_libraries(cmlib PRIVATE core)

#target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Test Executable
#add_executable(run_tests ${UTESTS})

#target_link_libraries(run_tests PRIVATE core)

#target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/test)

# Recursively build other projects
# add_subdirectory(examples)
add_subdirectory(test)