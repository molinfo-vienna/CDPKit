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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CDPKIT_EXTERNAL_DIR}")

set(cdpl-pharm_LIB_SRCS
    Feature.cpp
    BasicFeature.cpp
    FeatureContainer.cpp
    FeatureSet.cpp
    Pharmacophore.cpp
    BasicPharmacophore.cpp
  
    FeatureContainerProperty.cpp
    FeatureProperty.cpp
    FeatureContainerPropertyDefault.cpp
    FeaturePropertyDefault.cpp
    DataFormat.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp
  
    FeatureGenerator.cpp
    PatternBasedFeatureGenerator.cpp
    HydrophobicFeatureGenerator.cpp
    HydrophobicAtomFeatureGenerator.cpp
    AromaticFeatureGenerator.cpp
    HBondAcceptorFeatureGenerator.cpp
    HBondDonorFeatureGenerator.cpp
    PosIonizableFeatureGenerator.cpp
    NegIonizableFeatureGenerator.cpp
    XBondAcceptorFeatureGenerator.cpp
    XBondDonorFeatureGenerator.cpp
    PharmacophoreGenerator.cpp
    DefaultPharmacophoreGenerator.cpp
    InteractionAnalyzer.cpp
    DefaultInteractionAnalyzer.cpp
    InteractionConstraintConnector.cpp
    FeatureDistanceConstraint.cpp
    HydrophobicInteractionConstraint.cpp
    IonicInteractionConstraint.cpp
    HBondingInteractionConstraint.cpp
    XBondingInteractionConstraint.cpp
    CationPiInteractionConstraint.cpp
    OrthogonalPiPiInteractionConstraint.cpp
    ParallelPiPiInteractionConstraint.cpp
    InteractionPharmacophoreGenerator.cpp
    
    FeatureInteractionScoreCombiner.cpp
    FeatureDistanceScore.cpp
    HydrophobicInteractionScore.cpp
    IonicInteractionScore.cpp
    HBondingInteractionScore.cpp
    XBondingInteractionScore.cpp
    OrthogonalPiPiInteractionScore.cpp
    ParallelPiPiInteractionScore.cpp
    CationPiInteractionScore.cpp

    FeatureTypeMatchFunctor.cpp
    FeaturePairDistanceMatchFunctor.cpp
    FeaturePositionMatchFunctor.cpp
    FeatureGeometryMatchFunctor.cpp
    SpatialFeatureMapping.cpp
    PharmacophoreAlignment.cpp
 
    PharmacophoreFitScore.cpp

    ScreeningProcessor.cpp
    ScreeningProcessorImpl.cpp
    PharmacophoreFitScreeningScore.cpp
    FileScreeningHitCollector.cpp
    PSDPharmacophoreByteBufferReader.cpp
    PSDFeatureContainerByteBufferWriter.cpp
    PSDMoleculeByteBufferReader.cpp
    PSDMolecularGraphByteBufferWriter.cpp
    PSDScreeningDBCreator.cpp
    PSDScreeningDBCreatorImpl.cpp
    PSDScreeningDBAccessorImpl.cpp
    PSDScreeningDBAccessor.cpp
    SQLiteDataIOBase.cpp
   
    PSDPharmacophoreInputHandler.cpp
    PSDMoleculeInputHandler.cpp
    PSDMolecularGraphOutputHandler.cpp
    PSDPharmacophoreReader.cpp
    PSDMoleculeReader.cpp
    PSDMolecularGraphWriter.cpp
      
    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFPharmacophoreReader.cpp
    CDFFeatureContainerWriter.cpp
  
    PMLDataReader.cpp
    PMLDataWriter.cpp
    PMLPharmacophoreReader.cpp
    PMLFeatureContainerWriter.cpp

    FeaturePropertyFunctions.cpp

    FeatureContainerPropertyFunctions.cpp
    FeatureContainerFeatureCountFunctions.cpp
    FeatureContainerFeatureTypeHistogramFunctions.cpp
    FeatureContainerXVolumeClashTestFunction.cpp
    FeatureContainerGetFeatureAtomsFunction.cpp
    FeatureContainerTransform3DCoordinatesFunction.cpp
    FeatureContainerClearOrientationsFunction.cpp
    FeatureContainerRemovePositionalDuplicatesFunction.cpp
    FeatureContainerRemoveFeaturesWithTypeFunction.cpp

    FeatureSetGetFeaturesFunction.cpp
    FeatureSetRemovePositionalDuplicatesFunction.cpp
    FeatureSetRemoveFeaturesWithTypeFunction.cpp
    
    PharmacophoreBuildInteractionPharmFunction.cpp
    PharmacophoreCreateXVolumesFunctions.cpp
    PharmacophoreXVolumesModificationFunctions.cpp
    PharmacophoreRemovePositionalDuplicatesFunction.cpp
    PharmacophoreRemoveFeaturesWithTypeFunction.cpp
    
    ControlParameterFunctions.cpp
    MoleculeFunctions.cpp
    UtilityFunctions.cpp

    PiPiInteractionUtilities.cpp
    TwoPointPharmacophore.cpp
    QueryTwoPointPharmacophore.cpp
   )

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-pharm-static STATIC ${cdpl-pharm_LIB_SRCS} $<TARGET_OBJECTS:sqlite3> $<TARGET_OBJECTS:cdpl-internal>)

  set_target_properties(cdpl-pharm-static PROPERTIES 
    OUTPUT_NAME cdpl-pharm
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_PHARM_STATIC_LINK")

  target_link_libraries(cdpl-pharm-static cdpl-chem-static cdpl-molprop-static cdpl-biomol-static cdpl-math-static
    cdpl-util-static cdpl-base-static Boost::iostreams)

  if(CXX_FILESYSTEM_HAVE_FS)
    target_link_libraries(cdpl-pharm-static std::filesystem)
  else()
    target_link_libraries(cdpl-pharm-static Boost::filesystem)
  endif(CXX_FILESYSTEM_HAVE_FS)
  
  target_include_directories(cdpl-pharm-static
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

  install(TARGETS cdpl-pharm-static EXPORT ExportedTargets
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
    )
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-pharm-shared SHARED ${cdpl-pharm_LIB_SRCS} $<TARGET_OBJECTS:sqlite3> $<TARGET_OBJECTS:cdpl-internal>)

target_link_libraries(cdpl-pharm-shared PUBLIC cdpl-chem-shared cdpl-molprop-shared cdpl-biomol-shared cdpl-base-shared
  cdpl-math-shared cdpl-util-shared)
target_link_libraries(cdpl-pharm-shared PRIVATE Boost::iostreams)

if(CXX_FILESYSTEM_HAVE_FS)
  target_link_libraries(cdpl-pharm-shared PRIVATE std::filesystem)
else()
  target_link_libraries(cdpl-pharm-shared PRIVATE Boost::filesystem)
endif(CXX_FILESYSTEM_HAVE_FS)

target_include_directories(cdpl-pharm-shared
  PUBLIC
  "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
  "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

if(UNIX)
  target_link_libraries(cdpl-pharm-shared PRIVATE dl) # for sqlite3
endif()

set_target_properties(cdpl-pharm-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-pharm
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-pharm.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-pharm.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-pharm.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-pharm-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-pharm-shared EXPORT ExportedTargets
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)
