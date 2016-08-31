INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-pharm_LIB_SRCS
    Pharmacophore.cpp
    Feature.cpp
    BasicPharmacophore.cpp
    BasicFeature.cpp
  
    PharmacophoreProperty.cpp
    FeatureProperty.cpp
    DataFormat.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp
  
    PatternBasedFeatureGenerator.cpp
    HydrophobicFeatureGenerator.cpp
    AromaticFeatureGenerator.cpp
    HBondAcceptorFeatureGenerator.cpp
    HBondDonorFeatureGenerator.cpp
    PosIonizableFeatureGenerator.cpp
    NegIonizableFeatureGenerator.cpp
    SurfaceXVolumeCoatGenerator.cpp
    PharmacophoreGenerator.cpp
    DefaultPharmacophoreGenerator.cpp
    FeatureInteractionAnalyzer.cpp
    DefaultFeatureInteractionAnalyzer.cpp
    FeatureInteractionConstraintConnector.cpp
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
    TopologicalQueryPharmAlignmentFilter.cpp
    GeometricalQueryPharmAlignmentFilter.cpp
    GeometricalFeatureMappingExtractor.cpp
    PharmacophoreAlignment.cpp

    CDFPharmacophoreInputHandler.cpp
    CDFPharmacophoreOutputHandler.cpp

    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFPharmacophoreReader.cpp
    CDFPharmacophoreWriter.cpp

    FeatureTypeFunctions.cpp
    FeatureGeometryFunctions.cpp
    FeatureOrientationFunctions.cpp
    FeatureLengthFunctions.cpp
    FeatureToleranceFunctions.cpp
    FeatureSubstructureFunctions.cpp
    FeatureDisabledFlagFunctions.cpp
    FeatureOptionalFlagFunctions.cpp

    PharmacophoreFeatureCountFunctions.cpp
    InteractionPharmacophoreFunction.cpp
    ExclusionVolumeClashTestFunction.cpp

    ControlParameterFunctions.cpp

    PiPiInteractionUtilities.cpp
   )

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
