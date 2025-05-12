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

set(cdpl-molprop_LIB_SRCS
    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp
    AtomPropertyDefault.cpp
    
    AtomPropertyFunctions.cpp
    BondPropertyFunctions.cpp
    MolecularGraphPropertyFunctions.cpp
    
    AtomContainerElementalCompositionFunctions.cpp
    AtomContainerMassCompositionFunctions.cpp
    AtomContainerAtomCountFunctions.cpp
    AtomContainerNetFormalChargeFunction.cpp
    AtomContainerDipoleMomentFunctions.cpp

    BondContainerBondCountFunctions.cpp

    MolecularGraphAtomCountFunctions.cpp
    MolecularGraphBondCountFunctions.cpp
    MolecularGraphComponentCountFunction.cpp
    MolecularGraphCyclomaticNumberFunction.cpp
    MolecularGraphMassCompositionFunctions.cpp
    MolecularGraphElementalCompositionFunctions.cpp
    MolecularGraphMeanPolarizabilityFunction.cpp
    MolecularGraphAtomHydrophobicityFunction.cpp
    MolecularGraphPEOEPropertiesFunction.cpp
    MolecularGraphMHMOPropertiesFunction.cpp
    MolecularGraphRO5ScoreFunction.cpp
    MolecularGraphTPSAFunction.cpp
    MolecularGraphLogSFunction.cpp
    MolecularGraphXLogPFunction.cpp
    MolecularGraphHBDHBAAtomTypeFunctions.cpp
    MolecularGraphFunctionalGroupsFunctions.cpp
    
    AtomPolarizabilityFunctions.cpp
    AtomBondCountFunctions.cpp
    AtomElementPropertyFunctions.cpp
    AtomRingMembershipFunctions.cpp
    AtomClassificationFunctions.cpp
    AtomValenceFunctions.cpp
    AtomValenceElectronCountFunctions.cpp
    AtomAtomCountFunctions.cpp
    AtomVSEPRGeometryFunctions.cpp
    AtomTotalPartialChargeFunction.cpp
    AtomElectronegativityFunctions.cpp
    AtomInductiveEffectFunction.cpp
    
    BondPolarizabilityFunction.cpp
    BondClassificationFunctions.cpp
    BondRingMembershipFunctions.cpp
    
    AtomHydrophobicityCalculator.cpp
    LogSCalculator.cpp
    PEOESigmaChargeCalculator.cpp
    MHMOPiChargeCalculator.cpp
    TPSACalculator.cpp
    XLogPCalculator.cpp
    HBondDonorAtomTyper.cpp
    HBondAcceptorAtomTyper.cpp
    FunctionalGroupList.cpp
   )
 
if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-molprop-static STATIC ${cdpl-molprop_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  set_target_properties(cdpl-molprop-static PROPERTIES 
    OUTPUT_NAME cdpl-molprop
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_MOLPROP_STATIC_LINK")
  target_include_directories(cdpl-molprop-static
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

  install(TARGETS cdpl-molprop-static EXPORT ExportedTargets
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)

  target_link_libraries(cdpl-molprop-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-molprop-shared SHARED ${cdpl-molprop_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

target_link_libraries(cdpl-molprop-shared cdpl-chem-shared cdpl-math-shared cdpl-util-shared cdpl-base-shared)
target_include_directories(cdpl-molprop-shared
  PUBLIC
  "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
  "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

set_target_properties(cdpl-molprop-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-molprop
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-molprop.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-molprop.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-molprop.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-molprop-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-molprop-shared EXPORT ExportedTargets
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)

