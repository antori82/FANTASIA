#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "agrum" for configuration "Release"
set_property(TARGET agrum APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(agrum PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/agrum.lib"
  )

list(APPEND _cmake_import_check_targets agrum )
list(APPEND _cmake_import_check_files_for_agrum "${_IMPORT_PREFIX}/lib/agrum.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
