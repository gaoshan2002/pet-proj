# - Try to find Valgrind for testing
# Once done this will define
#  VALGRIND_BIN - Valgrind binary
#  VALGRIND_FOUND - Valgrind has been found

find_program(VALGRIND_BIN valgrind)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set VALGRIND_SAKER_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Valgrind  DEFAULT_MSG
                                  VALGRIND_BIN)

mark_as_advanced(VALGRIND_BIN)
