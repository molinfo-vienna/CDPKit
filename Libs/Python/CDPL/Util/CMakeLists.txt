# -*- mode: CMake -*-

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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
ENDFOREACH(PYTHON_FILE)

SET(util_MOD_SRCS
    Module.cpp
    BitSetExport.cpp
    ArrayExport.cpp
    BronKerboschAlgorithmExport.cpp
    DGCoordinatesGeneratorExport.cpp
    CompressionStreamExport.cpp
    
    SequenceFunctionExport.cpp
    FileFunctionExport.cpp
    
    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_util MODULE ${util_MOD_SRCS})

TARGET_LINK_LIBRARIES(_util cdpl-util-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_util PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_util PROPERTIES SUFFIX ".pyd")
  SET(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Util/_util.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_util PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  SET(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Util/_util.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
	       @ONLY
	       )

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Util" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _util DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Util" COMPONENT CDPLPythonModules)
INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

IF(PYTHON_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHON_TESTS_ENABLED)
