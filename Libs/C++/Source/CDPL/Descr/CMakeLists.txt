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

SET(cdpl-descr_LIB_SRCS
    BCUTDescriptorCalculator.cpp
    BurdenMatrixGenerator.cpp
    MolecularComplexityCalculator.cpp

    CircularFingerprintGenerator.cpp 
    PathFingerprintGenerator.cpp 

    AtomRDFCodeCalculator.cpp
    MoleculeRDFDescriptorCalculator.cpp

    AutoCorrelation2DVectorCalculator.cpp
    AtomAutoCorrelation3DVectorCalculator.cpp
    MoleculeAutoCorr2DDescriptorCalculator.cpp
    MoleculeAutoCorr3DDescriptorCalculator.cpp

    FeatureRDFCodeCalculator.cpp
    FeatureAutoCorrelation3DVectorCalculator.cpp
    PharmacophoreRDFDescriptorCalculator.cpp
    PharmacophoreAutoCorr3DDescriptorCalculator.cpp

    Entity3DContainerGeomDiameterAndRadiusFunctions.cpp

    AtomContainerGeomDiameterAndRadiusFunctions.cpp
    
    MolecularGraphComplexityFunction.cpp
    MolecularGraphKierShapeFunctions.cpp
    MolecularGraphRandicIndexFunction.cpp
    MolecularGraphRingComplexityFunction.cpp
    MolecularGraphTotalWalkCountFunction.cpp
    MolecularGraphWienerIndexFunction.cpp
    MolecularGraphZagrebIndexFunctions.cpp
    MolecularGraphTopDiameterAndRadiusFunctions.cpp
    
    SimilarityFunctions.cpp
   )

IF(NOT PYPI_PACKAGE_BUILD)
  ADD_LIBRARY(cdpl-descr-static STATIC ${cdpl-descr_LIB_SRCS})

  SET_TARGET_PROPERTIES(cdpl-descr-static PROPERTIES 
    OUTPUT_NAME cdpl-descr
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_DESCR_STATIC_LINK")

  TARGET_LINK_LIBRARIES(cdpl-descr-static cdpl-pharm-static cdpl-chem-static cdpl-molprop-static
    cdpl-math-static cdpl-util-static cdpl-base-static)

  INSTALL(TARGETS cdpl-descr-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
ENDIF(NOT PYPI_PACKAGE_BUILD)

ADD_LIBRARY(cdpl-descr-shared SHARED ${cdpl-descr_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-descr-shared cdpl-pharm-shared cdpl-chem-shared cdpl-molprop-shared cdpl-base-shared
  cdpl-math-shared cdpl-util-shared)

SET_TARGET_PROPERTIES(cdpl-descr-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-descr
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

IF(WIN32)
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-descr.dll")
ELSEIF(APPLE)
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-descr.dylib")
ELSE()            
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-descr.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

IF(WIN32 AND PYPI_PACKAGE_BUILD)
   INSTALL(TARGETS cdpl-descr-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
ELSE()
  INSTALL(TARGETS cdpl-descr-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
ENDIF(WIN32 AND PYPI_PACKAGE_BUILD)

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

IF(CDPL_CXX_UNIT_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(CDPL_CXX_UNIT_TESTS_ENABLED)

