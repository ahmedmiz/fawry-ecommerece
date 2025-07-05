cmake_minimum_required(VERSION 3.10)
project(fawry-eCommerce)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Include directories
include_directories(src)

# Find all source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/models/*/*.cpp"
    "src/services/*.cpp"
)

# Find all header files
file(GLOB_RECURSE HEADERS 
    "src/*.h"
    "src/models/*/*.h"
    "src/interface/*.h"
    "src/services/*.h"
)

# Create main executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra -O0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2 -DNDEBUG)
endif()

# Enable testing
enable_testing()

# Create test executable
file(GLOB TEST_SOURCES "src/tests/*.cpp")
if(TEST_SOURCES)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES} ${SOURCES} ${HEADERS})
    target_compile_options(${PROJECT_NAME}_tests PRIVATE -g -Wall -Wextra)
    
    # Add test
    add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
endif()

# Print configuration info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source files: ${SOURCES}") 