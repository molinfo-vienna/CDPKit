##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

set(cdpl-base_LIB_SRCS
    PropertyContainer.cpp
    ControlParameterContainer.cpp
    ControlParameterList.cpp
    LookupKey.cpp
    DataIOManager.cpp
    DataIOBase.cpp
    DataFormat.cpp
    Exceptions.cpp
   )

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-base-static STATIC ${cdpl-base_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  set_target_properties(cdpl-base-static PROPERTIES 
    OUTPUT_NAME cdpl-base
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_BASE_STATIC_LINK")

  target_include_directories(cdpl-base-static
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")
                           
  install(TARGETS cdpl-base-static EXPORT ExportedTargets
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-base-shared SHARED ${cdpl-base_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

set_target_properties(cdpl-base-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-base
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

target_include_directories(cdpl-base-shared
  PUBLIC
  "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
  "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")
  
if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-base.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-base.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-base.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-base-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-base-shared EXPORT ExportedTargets
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)

