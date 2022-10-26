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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-molprop_LIB_SRCS
    AtomProperty.cpp

    AtomPropertyFunctions.cpp
    
    AtomContainerElementalCompositionFunctions.cpp
    AtomContainerMassCompositionFunctions.cpp
    AtomContainerAtomCountFunctions.cpp
    AtomContainerNetFormalChargeFunction.cpp

    BondContainerBondCountFunctions.cpp

    MolecularGraphAtomCountFunctions.cpp
    MolecularGraphBondCountFunctions.cpp
    MolecularGraphComponentCountFunction.cpp
    MolecularGraphCyclomaticNumberFunction.cpp
    MolecularGraphMassCompositionFunctions.cpp
    MolecularGraphElementalCompositionFunctions.cpp
    MolecularGraphMeanPolarizabilityFunction.cpp
    MolecularGraphAtomHydrophobicityFunction.cpp
    MolecularGraphPEOESigmaChargesFunction.cpp
    MolecularGraphRO5ScoreFunction.cpp
    MolecularGraphTPSAFunction.cpp
    MolecularGraphLogSFunction.cpp
    MolecularGraphXLogPFunction.cpp

    AtomPolarizabilityFunctions.cpp
    AtomBondCountFunctions.cpp
    AtomElementPropertyFunctions.cpp
    AtomRingMembershipFunctions.cpp
    AtomClassificationFunctions.cpp
    AtomValenceFunctions.cpp
    AtomValenceElectronCountFunctions.cpp
    AtomAtomCountFunctions.cpp
    AtomVSEPRGeometryFunctions.cpp
    
    BondPolarizabilityFunction.cpp
    BondClassificationFunctions.cpp
    BondRingMembershipFunctions.cpp
    
    AtomHydrophobicityCalculator.cpp
    LogSCalculator.cpp
    PEOESigmaChargeCalculator.cpp
    ModifiedHueckelMOCalculator.cpp
    TPSACalculator.cpp
    XLogPCalculator.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

ADD_LIBRARY(cdpl-molprop-static STATIC ${cdpl-molprop_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-molprop-static PROPERTIES 
                      OUTPUT_NAME cdpl-molprop
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_MOLPROP_STATIC_LINKK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_BASE_STATIC_LINK;CDPL_UTIL_STATIC_LINK"
                     )

INSTALL(TARGETS cdpl-molprop-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

TARGET_LINK_LIBRARIES(cdpl-molprop-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static)

ADD_LIBRARY(cdpl-molprop-shared SHARED ${cdpl-molprop_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-molprop-shared cdpl-chem-shared cdpl-math-shared cdpl-util-shared cdpl-base-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-molprop-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-MolProp
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-molprop-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-molprop
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(WIN32)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-molprop.dll")
  ELSE()			
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-molprop.so")
  ENDIF(WIN32)

  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-molprop-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)

