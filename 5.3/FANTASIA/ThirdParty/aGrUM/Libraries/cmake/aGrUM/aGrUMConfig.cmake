# Find the aGrUM includes and library
#
# AGRUM_INCLUDE_DIRS - where to find the includes
# AGRUM_CXX_FLAGS - mandatory CXX flags
# AGRUM_LIBRARY - aGrUM library name
# AGRUM_LIBRARIES - list of qualified libraries to link against
# AGRUM_LIBRARY_DIRS - list of libraries dirs
# AGRUM_VERSION_STRING - versioni
# AGRUM_USE_FILE - include to use agrum
# AGRUM_FOUND - set to 1 if found
#
#
set (AGRUM_FOUND 1)
set (AGRUM_DEFINITIONS "")
set (AGRUM_INCLUDE_DIR "INSTALL_PATH/include")
set (AGRUM_INCLUDE_DIRS "INSTALL_PATH/include")
set (AGRUM_CXX_FLAGS "")
set (AGRUM_LIBRARY_DIRS "INSTALL_PATH/lib")
set (AGRUM_LIB_DIR "INSTALL_PATH/lib") # deprecated

set (AGRUM_LIBRARY_DEBUG "agrum-dbg")
set (AGRUM_LIBRARIES_DEBUG "agrum-dbg")
set (AGRUM_LIBRARY_RELEASE "agrum")
set (AGRUM_LIBRARIES_RELEASE "agrum")

set (AGRUM_USE_FILE "INSTALL_PATH/lib/cmake/aGrUM/aGrUMUse.cmake")
set (AGRUM_ROOTDIR "INSTALL_PATH")
set (AGRUM_VERSION_STRING "1.7.1")
set (AGRUM_VERSION_MAJOR "1")
set (AGRUM_VERSION_MINOR "7")
set (AGRUM_VERSION_PATCH "1")

# Our library dependencies (contains definitions for IMPORTED targets)
include ("INSTALL_PATH/lib/cmake/aGrUM/agrum-targets.cmake")
