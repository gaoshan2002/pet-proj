# Add support for Profile build type to build binaries with profiling options

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Profile."
      FORCE)
endif()

list(APPEND CMAKE_BUILD_CONFIGURATIONS Profile)

set(CMAKE_C_FLAGS_PROFILE "-pg"
    CACHE STRING "profiling flags")
    
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_C_FLAGS_PROFILE}"
    CACHE STRING "profiling flags")
    
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "-pg"
    CACHE STRING "profiling flags")
    
mark_as_advanced(
    CMAKE_C_FLAGS_PROFILE
    CMAKE_CXX_FLAGS_PROFILE
    CMAKE_EXE_LINKER_FLAGS_PROFILE
    )
