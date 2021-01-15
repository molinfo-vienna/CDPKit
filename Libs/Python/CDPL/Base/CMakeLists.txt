# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
ENDFOREACH(PYTHON_FILE)

SET(base_MOD_SRCS
    Module.cpp
    PropertyContainerExport.cpp
    LookupKeyExport.cpp
    ControlParameterContainerExport.cpp
    ControlParameterListExport.cpp
    DataFormatExport.cpp
    DataIOBaseExport.cpp
    IOStreamExport.cpp
    BoostFunctionWrapperExport.cpp
    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
    ExceptionTranslatorRegistration.cpp
   )

ADD_LIBRARY(_base MODULE ${base_MOD_SRCS})

TARGET_LINK_LIBRARIES(_base cdpl-base-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_base PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_base PROPERTIES SUFFIX ".pyd")
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_base.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_base PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_base PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_base.so")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_base PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

IF(NOT APPLE)
  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)
ENDIF(NOT APPLE)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Base" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _base DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Base" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
