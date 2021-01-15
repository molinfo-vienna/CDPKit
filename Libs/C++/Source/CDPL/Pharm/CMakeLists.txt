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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CDPKIT_EXTERNAL_DIR}")

SET(cdpl-pharm_LIB_SRCS
    Feature.cpp
    BasicFeature.cpp
    FeatureContainer.cpp
    FeatureSet.cpp
    Pharmacophore.cpp
    BasicPharmacophore.cpp
  
    FeatureContainerProperty.cpp
    FeatureProperty.cpp
    AttributedGridProperty.cpp
    FeatureContainerPropertyDefault.cpp
    FeaturePropertyDefault.cpp
    AttributedGridPropertyDefault.cpp
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
    PharmacophoreGenerator.cpp
    DefaultPharmacophoreGenerator.cpp
    InteractionAnalyzer.cpp
    DefaultInteractionAnalyzer.cpp
    InteractionConstraintConnector.cpp
    FeatureDistanceConstraint.cpp
    HydrophobicInteractionConstraint.cpp
    IonicInteractionConstraint.cpp
    HBondingInteractionConstraint.cpp
    CationPiInteractionConstraint.cpp
    OrthogonalPiPiInteractionConstraint.cpp
    ParallelPiPiInteractionConstraint.cpp
    InteractionPharmacophoreGenerator.cpp

    InteractionScoreCombiner.cpp
    FeatureDistanceScore.cpp
    HydrophobicInteractionScore.cpp
    IonicInteractionScore.cpp
    HBondingInteractionScore.cpp
    OrthogonalPiPiInteractionScore.cpp
    ParallelPiPiInteractionScore.cpp
    CationPiInteractionScore.cpp
    InteractionScoreGridCalculator.cpp
    InteractionScoreGridSetCalculator.cpp
    DefaultInteractionScoreGridSetCalculator.cpp

    FeatureTypeMatchFunctor.cpp
    FeaturePairDistanceMatchFunctor.cpp
    FeaturePositionMatchFunctor.cpp
    FeatureGeometryMatchFunctor.cpp
    GeometricalFeatureMappingExtractor.cpp
    PharmacophoreAlignment.cpp
    FeatureRDFCodeCalculator.cpp
    FeatureAutoCorrelation3DVectorCalculator.cpp
    PharmacophoreRDFDescriptorCalculator.cpp
    PharmacophoreAutoCorr3DDescriptorCalculator.cpp

    PharmacophoreFitScore.cpp

    ScreeningProcessor.cpp
    ScreeningProcessorImpl.cpp
    PharmacophoreFitScreeningScore.cpp

    CDFAttributedGridPropertyReader.cpp
    CDFAttributedGridPropertyWriter.cpp
    CDFPharmacophoreDataReader.cpp
    CDFPharmacophoreDataWriter.cpp
    CDFPharmacophoreReader.cpp
    CDFFeatureContainerWriter.cpp
  
    PMLDataReader.cpp
    PMLDataWriter.cpp
    PMLPharmacophoreReader.cpp
    PMLFeatureContainerWriter.cpp

    FeaturePropertyFunctions.cpp

    FeatureContainerPropertyFunctions.cpp
    FeatureContainerFeatureCountFunctions.cpp
    FeatureContainerFeatureTypeHistogramFunction.cpp
    FeatureContainerXVolumeClashTestFunction.cpp
    FeatureContainerGetFeatureAtomsFunction.cpp
    FeatureContainerTransform3DCoordinatesFunction.cpp

    FeatureSetGetFeaturesFunction.cpp

    AttributedGridPropertyFunctions.cpp

    PharmacophoreBuildInteractionPharmFunction.cpp
    PharmacophoreCreateXVolumesFunctions.cpp

    ControlParameterFunctions.cpp
    MoleculeFunctions.cpp

    PiPiInteractionUtilities.cpp
    TwoPointPharmacophore.cpp
    QueryTwoPointPharmacophore.cpp
    ThreePointPharmacophore.cpp
    QueryThreePointPharmacophore.cpp
   )

LINK_LIBRARIES(${Boost_SYSTEM_LIBRARY})
 
IF(Boost_FILESYSTEM_FOUND)
  SET(cdpl-pharm_LIB_SRCS
      ${cdpl-pharm_LIB_SRCS}	
      FileScreeningHitCollector.cpp
     )

  LINK_LIBRARIES(${Boost_FILESYSTEM_LIBRARY})
ENDIF(Boost_FILESYSTEM_FOUND)

IF(SQLITE3_FOUND)
  SET(cdpl-pharm_LIB_SRCS
      ${cdpl-pharm_LIB_SRCS}
      PSDScreeningDBCreator.cpp
      PSDScreeningDBAccessor.cpp

      SQLiteDataIOBase.cpp
      PSDScreeningDBCreatorImpl.cpp
      PSDScreeningDBAccessorImpl.cpp
     )	

  LINK_LIBRARIES(${SQLITE3_LIBRARY})
  INCLUDE_DIRECTORIES("${SQLITE3_INCLUDE_DIR}")

  IF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
    SET(cdpl-pharm_LIB_SRCS
        ${cdpl-pharm_LIB_SRCS}
        PSDPharmacophoreInputHandler.cpp
        PSDMoleculeInputHandler.cpp
        PSDMolecularGraphOutputHandler.cpp
        PSDPharmacophoreReader.cpp
        PSDMoleculeReader.cpp
        PSDMolecularGraphWriter.cpp
       )	

    LINK_LIBRARIES(${Boost_FILESYSTEM_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
  ENDIF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
ENDIF(SQLITE3_FOUND)

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

ADD_LIBRARY(cdpl-pharm-static STATIC ${cdpl-pharm_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-pharm-static PROPERTIES 
                      OUTPUT_NAME cdpl-pharm
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_PHARM_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_GRID_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-pharm-static cdpl-chem-static cdpl-grid-static cdpl-biomol-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static)

INSTALL(TARGETS cdpl-pharm-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-pharm-shared SHARED ${cdpl-pharm_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-pharm-shared cdpl-chem-shared cdpl-grid-shared cdpl-biomol-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-pharm-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Biomol
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-pharm-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-pharm
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-pharm.so")
  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake"
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
ENDIF(APPLE)

INSTALL(TARGETS cdpl-pharm-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
