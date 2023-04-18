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

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
ENDFOREACH(PYTHON_FILE)

SET(grails_MOD_SRCS
    Module.cpp
  
    AttributedGridPropertyExport.cpp 
    AttributedGridPropertyDefaultExport.cpp 

    GeneralizedBellAtomDensityExport.cpp
    AtomDensityGridCalculatorExport.cpp
    BuriednessScoreExport.cpp
    BuriednessGridCalculatorExport.cpp
    InteractionScoreGridCalculatorExport.cpp
    InteractionScoreGridSetCalculatorExport.cpp
    DefaultInteractionScoreGridSetCalculatorExport.cpp

    BoostFunctionWrapperExport.cpp

    AttributedGridFunctionExport.cpp
    
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_grails MODULE ${grails_MOD_SRCS})

TARGET_LINK_LIBRARIES(_grails cdpl-grails-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_grails PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_grails PROPERTIES SUFFIX ".pyd")
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_grails.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_grails PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")
  SET_TARGET_PROPERTIES(_grails PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_grails.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
	       @ONLY
	       )

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)
INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/grails" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _grails DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/grails" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
