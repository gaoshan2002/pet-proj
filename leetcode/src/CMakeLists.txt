file(GLOB_RECURSE LEETCODE_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#set(LEETCODE_LIB_SRCS ${LEETCODE_LIB_SRCS} ${SRCS} PARENT_SCOPE)

################################################################################
# Source code sub-directories
################################################################################
#add_subdirectory(valid_number)


################################################################################
# Create leetcode Library
################################################################################

set( LEETCODE_LIB_LINK_LIBRARIES  rt )

add_library( leetcode ${LEETCODE_LIB_SRCS} )
#target_link_libraries( leetcode ${LEETCODDE_LIB_LINK_LIBRARIES} )
set_target_properties( leetcode PROPERTIES CLEAN_DIRECT_OUTPUT 1 OUTPUT_NAME "leetcode")
set_target_properties( leetcode PROPERTIES VERSION "1.0.0" SOVERSION "1" )

if( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
    install( TARGETS leetcode DESTINATION usr/lib64 )
else()
    install( TARGETS leetcode DESTINATION usr/lib )
endif()

                                      