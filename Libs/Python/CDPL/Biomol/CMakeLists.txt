# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

SET(biomol_MOD_SRCS
    Module.cpp

    PDBDataExport.cpp
    ResidueListExport.cpp
    ResidueDictionaryExport.cpp
 
    PDBMoleculeReaderExport.cpp
    PDBMolecularGraphWriterExport.cpp
    MMTFMoleculeReaderExport.cpp
    MMTFMolecularGraphWriterExport.cpp
    
    PDBMoleculeInputHandlerExport.cpp
    PDBMolecularGraphOutputHandlerExport.cpp
    MMTFMoleculeInputHandlerExport.cpp
    MMTFMolecularGraphOutputHandlerExport.cpp
    
    HierarchyViewNodeExport.cpp
    HierarchyViewModelExport.cpp
    HierarchyViewChainExport.cpp
    HierarchyViewFragmentExport.cpp
    HierarchyViewExport.cpp

    AtomPropertyExport.cpp
    MolecularGraphPropertyExport.cpp
    AtomPropertyDefaultExport.cpp
    MolecularGraphPropertyDefaultExport.cpp
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 
    AtomPropertyFlagExport.cpp
    ResidueTypeExport.cpp
    PDBFormatVersionExport.cpp
    DataFormatExport.cpp

    AtomFunctionExport.cpp
    MolecularGraphFunctionExport.cpp
    ControlParameterFunctionExport.cpp 
    UtilityFunctionExport.cpp 

    BoostFunctionWrapperExport.cpp

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_biomol MODULE ${biomol_MOD_SRCS})

TARGET_LINK_LIBRARIES(_biomol cdpl-biomol-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_biomol PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_biomol PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_biomol PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_biomol PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_biomol.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_biomol PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Biomol" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _biomol DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Biomol" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
