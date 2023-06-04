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

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
ENDFOREACH(PYTHON_FILE)

SET(grail_MOD_SRCS
    Module.cpp
  
    AttributedGridPropertyExport.cpp 
    AttributedGridPropertyDefaultExport.cpp
    FeatureTypeExport.cpp 

    GeneralizedBellAtomDensityExport.cpp
    AtomDensityGridCalculatorExport.cpp
    BuriednessScoreExport.cpp
    BuriednessGridCalculatorExport.cpp
    FeatureInteractionScoreGridCalculatorExport.cpp
    GRAILDataSetGeneratorExport.cpp
    GRAILDescriptorCalculatorExport.cpp
    BindingAffinityCalculatorExport.cpp    

    FunctionWrapperExport.cpp

    AttributedGridFunctionExport.cpp
    FeatureFunctionExport.cpp
    MoleculeFunctionExport.cpp
    
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_grail MODULE ${grail_MOD_SRCS})

TARGET_LINK_LIBRARIES(_grail cdpl-grail-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_grail PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_grail PROPERTIES SUFFIX ".pyd")
  SET(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/GRAIL/_grail.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_grail PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")
  SET_TARGET_PROPERTIES(_grail PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  SET(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/GRAIL/_grail.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
	       @ONLY
	       )

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/GRAIL" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _grail DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/GRAIL" COMPONENT CDPLPythonModules)
INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
