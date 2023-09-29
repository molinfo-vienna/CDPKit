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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-grid_LIB_SRCS
    AttributedGridProperty.cpp
    AttributedGridPropertyDefault.cpp

    ControlParameter.cpp
    ControlParameterDefault.cpp
    DataFormat.cpp  

    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFDRegularGridReader.cpp
    CDFDRegularGridWriter.cpp
    CDFDRegularGridSetReader.cpp
    CDFDRegularGridSetWriter.cpp
    CDFRegularGridDataReader.cpp
    CDFRegularGridDataWriter.cpp
    CDFRegularGridSetDataReader.cpp
    CDFRegularGridSetDataWriter.cpp

    AttributedGridPropertyFunctions.cpp
    ControlParameterFunctions.cpp
   )

IF(NOT PYPI_PACKAGE_BUILD)
  ADD_LIBRARY(cdpl-grid-static STATIC ${cdpl-grid_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  TARGET_LINK_LIBRARIES(cdpl-grid-static cdpl-base-static cdpl-util-static)

  SET_TARGET_PROPERTIES(cdpl-grid-static PROPERTIES 
    OUTPUT_NAME cdpl-grid
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_GRID_STATIC_LINK")

  INSTALL(TARGETS cdpl-grid-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
ENDIF(NOT PYPI_PACKAGE_BUILD)

ADD_LIBRARY(cdpl-grid-shared SHARED ${cdpl-grid_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

TARGET_LINK_LIBRARIES(cdpl-grid-shared cdpl-base-shared cdpl-util-shared)

SET_TARGET_PROPERTIES(cdpl-grid-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-grid
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

IF(WIN32)
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-grid.dll")
ELSEIF(APPLE)
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-grid.dylib")
ELSE()            
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-grid.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

INSTALL(TARGETS cdpl-grid-shared
  RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
  LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
  ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

IF(CDPL_CXX_UNIT_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(CDPL_CXX_UNIT_TESTS_ENABLED)
