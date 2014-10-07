# - Try to find GoogleTest
# Once done this will define
#  GOOGLE_TEST_FOUND - System has GoogleTest
#  GOOGLE_TEST_INCLUDE_DIRS - The Google Test include directories
#  GOOGLE_TEST_LIBRARIES - The libraries needed to use Google Test
#  GOOGLE_TEST_DEFINITIONS - Compiler switches required for using GoogleTest

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "nios2")
    set(GOOGLE_TEST_DEFINITIONS -D__native_client__ -DGTEST_OS_UCOSII -DGTEST_HAS_GLOBAL_STRING=0 -DGTEST_HAS_GLOBAL_WSTRING=0 -DGTEST_HAS_POSIX_RE=0 -DGTEST_HAS_PTHREAD=0 -DGTEST_HAS_RTTI=0 -DGTEST_HAS_STD_WSTRING=0 -DGTEST_HAS_SEH=0 -DGTEST_LINKED_AS_SHARED_LIBRARY=0 -DGTEST_HAS_STREAM_REDIRECTION=0 -DGTEST_CREATE_SHARED_LIBRARY=0)
endif()

find_path(GOOGLE_TEST_INCLUDE_DIR gtest/gtest.h
          HINTS ${INSTALL_PREFIX}/include 
                ${INSTALL_PREFIX}/usr/include
          PATH_SUFFIXES GoogleTest/include )

find_library(GOOGLE_TEST_LIBRARY NAMES libgtest.a gtest
             HINTS ${INSTALL_PREFIX}/lib
                   ${INSTALL_PREFIX}/usr/lib 
                   ${INSTALL_PREFIX}/lib64 
                   ${INSTALL_PREFIX}/usr/lib64
             PATH_SUFFIXES gtest )

set(GOOGLE_TEST_LIBRARIES ${GOOGLE_TEST_LIBRARY} )
set(GOOGLE_TEST_INCLUDE_DIRS ${GOOGLE_TEST_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set GOOGLE_TEST_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GoogleTest  DEFAULT_MSG
                                  GOOGLE_TEST_LIBRARY GOOGLE_TEST_INCLUDE_DIR)

mark_as_advanced(GOOGLE_TEST_LIBRARY GOOGLE_TEST_INCLUDE_DIR)
