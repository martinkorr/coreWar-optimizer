cmake_minimum_required(VERSION 3.10)
project(CoreWarOptimizer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GAlib headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Link GAlib library
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Find Boost
find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

# Add the source files and create the executable
add_executable(corewar_optimizer main.cpp)

# Find and enable OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(corewar_optimizer PUBLIC OpenMP::OpenMP_CXX)
    message(STATUS "OpenMP support enabled.")
else()
    message(FATAL_ERROR "OpenMP support not found!")
endif()

# Set default number of threads for OpenMP to 8
add_compile_definitions(DEFAULT_NUM_THREADS=16)

# Link the GAlib and Boost libraries
target_link_libraries(corewar_optimizer PUBLIC GAlib Boost::unit_test_framework)
