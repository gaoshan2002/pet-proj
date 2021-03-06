
################################################################################
# Add Google test framework
################################################################################  
    
find_package(GoogleTest REQUIRED)

include_directories(${GOOGLE_TEST_INCLUDE_DIRS})
link_directories(${GOOGLE_TEST_LIBRARIES})

################################################################################
# Create a temporary directory that unitests can use
################################################################################
set(TEST_TEMP_DIR ${CMAKE_BINARY_DIR}/test_temp)
file(MAKE_DIRECTORY ${TEST_TEMP_DIR})

################################################################################
# Unittest configuration
################################################################################  
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Valgrind)

################################################################################
# Add test subdirectories
##############################################################################

add_subdirectory(time_diff)
add_subdirectory(lockless_ring)

################################################################################
# Create unittest executable
################################################################################
    
# Create test executable
add_executable(util_libs_tests ${TEST_SRCS} gtest.cpp)

target_link_libraries(util_libs_tests  ${GOOGLE_TEST_LIBRARIES}
                                        pthread
                                        )

add_test(util_libs_tests util_libs_tests)

if(VALGRIND_FOUND)
    add_test(util_libs_memCheck ${VALGRIND_BIN} --error-exitcode=1 ${CMAKE_BINARY_DIR}/unit_tests/util_libs_tests)
endif()
         
install(TARGETS util_libs_tests DESTINATION usr/sbin)
    
