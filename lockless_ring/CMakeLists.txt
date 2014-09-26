cmake_minimum_required(VERSION 2.6.4)
message(STATUS "CMake version: "${CMAKE_VERSION})
project(LocklessRing CXX C)

################################################################################
# CMake configuration
################################################################################
set(CMAKE_ECLIPSE_VERSION 3.7)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

enable_testing()

option(BUILD_SHARED_LIBS "Build package with shared libraries." OFF)

# Force warning free project
add_definitions( -Werror -Wall )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Add profiling support
include(Profiling)
    
################################################################################
# Main include paths
################################################################################

include_directories( ${PROJECT_SOURCE_DIR}/include
                     ${CMAKE_INSTALL_PREFIX}/usr/include )
    
################################################################################
# Add external libraries
################################################################################


################################################################################
# Add sub directories
################################################################################
add_subdirectory(unit_tests)

