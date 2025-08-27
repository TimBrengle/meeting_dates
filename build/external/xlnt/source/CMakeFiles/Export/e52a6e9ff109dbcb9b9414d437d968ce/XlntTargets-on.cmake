#----------------------------------------------------------------
# Generated CMake target import file for configuration "ON".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "xlnt::xlnt" for configuration "ON"
set_property(TARGET xlnt::xlnt APPEND PROPERTY IMPORTED_CONFIGURATIONS ON)
set_target_properties(xlnt::xlnt PROPERTIES
  IMPORTED_LOCATION_ON "${_IMPORT_PREFIX}/lib/libxlnt.so.1.5.0"
  IMPORTED_SONAME_ON "libxlnt.so.1.5.0"
  )

list(APPEND _cmake_import_check_targets xlnt::xlnt )
list(APPEND _cmake_import_check_files_for_xlnt::xlnt "${_IMPORT_PREFIX}/lib/libxlnt.so.1.5.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
