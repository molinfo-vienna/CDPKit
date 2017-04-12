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
    DataFormat.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp
  
    FeatureGenerator.cpp
    PatternBasedFeatureGenerator.cpp
    HydrophobicFeatureGenerator.cpp
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

    FeatureTypeMatchFunctor.cpp
    FeaturePairDistanceMatchFunctor.cpp
    FeaturePositionMatchFunctor.cpp
    FeatureGeometryMatchFunctor.cpp
    GeometricalFeatureMappingExtractor.cpp
    PharmacophoreAlignment.cpp

    PharmacophoreFitScore.cpp

    ScreeningProcessor.cpp
    ScreeningProcessorImpl.cpp
    PharmacophoreFitScreeningScore.cpp

    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFPharmacophoreReader.cpp
    CDFFeatureContainerWriter.cpp
 
    PMLDataReader.cpp
    PMLDataWriter.cpp
    PMLPharmacophoreReader.cpp
    PMLFeatureContainerWriter.cpp

    FeatureTypeFunctions.cpp
    FeatureGeometryFunctions.cpp
    FeatureOrientationFunctions.cpp
    FeatureLengthFunctions.cpp
    FeatureToleranceFunctions.cpp
    FeatureSubstructureFunctions.cpp
    FeatureDisabledFlagFunctions.cpp
    FeatureOptionalFlagFunctions.cpp

    FeatureContainerNameFunctions.cpp
    FeatureContainerFeatureCountFunctions.cpp
    FeatureContainerFeatureTypeHistogramFunction.cpp
    FeatureContainerXVolumeClashTestFunction.cpp
    FeatureContainerGetFeatureAtomsFunction.cpp

    FeatureSetGetFeaturesFunction.cpp

    PharmacophoreBuildInteractionPharmFunction.cpp
    PharmacophoreCreateXVolumesFunctions.cpp

    ControlParameterFunctions.cpp

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

    LINK_LIBRARIES(${Boost_IOSTREAMS_LIBRARY})
  ENDIF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
ENDIF(SQLITE3_FOUND)

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

ADD_LIBRARY(cdpl-pharm-static STATIC ${cdpl-pharm_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-pharm-static PROPERTIES 
                      OUTPUT_NAME cdpl-pharm
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_PHARM_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-pharm-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static)

INSTALL(TARGETS cdpl-pharm-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-pharm-shared SHARED ${cdpl-pharm_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-pharm-shared cdpl-chem-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared)

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

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-pharm.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake"
                    @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-pharm-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
