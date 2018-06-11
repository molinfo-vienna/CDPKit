INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(pharm_MOD_SRCS
    Module.cpp
    FeatureExport.cpp
    BasicFeatureExport.cpp
    FeatureContainerExport.cpp
    FeatureSetExport.cpp
    PharmacophoreExport.cpp
    BasicPharmacophoreExport.cpp

    FeatureMappingExport.cpp 
    FeatureTypeHistogramExport.cpp 
    FeatureRDFCodeCalculatorExport.cpp 
    PharmacophoreRDFDescriptorCalculatorExport.cpp
    FeatureAutoCorrelation3DVectorCalculatorExport.cpp 
    PharmacophoreAutoCorr3DDescriptorCalculatorExport.cpp

    FeatureContainerIOManagerExport.cpp 
    PharmacophoreIOManagerExport.cpp 
    PharmacophoreReaderExport.cpp 
    FeatureContainerWriterExport.cpp 
    PharmacophoreInputHandlerExport.cpp 
    FeatureContainerOutputHandlerExport.cpp 
 
    CDFPharmacophoreInputHandlerExport.cpp 
    CDFFeatureContainerOutputHandlerExport.cpp 
    CDFPharmacophoreReaderExport.cpp 
    CDFFeatureContainerWriterExport.cpp
   
    PMLPharmacophoreInputHandlerExport.cpp 
    PMLFeatureContainerOutputHandlerExport.cpp 
    PMLPharmacophoreReaderExport.cpp 
    PMLFeatureContainerWriterExport.cpp

    PharmacophoreFitScoreExport.cpp

    ScreeningDBCreatorExport.cpp
    ScreeningDBAccessorExport.cpp
    ScreeningProcessorExport.cpp
    PharmacophoreFitScreeningScoreExport.cpp

    BoostFunctionWrapperExport.cpp

    FeatureGeneratorExport.cpp
    PharmacophoreGeneratorExport.cpp
    DefaultPharmacophoreGeneratorExport.cpp
    PatternBasedFeatureGeneratorExport.cpp
    AromaticFeatureGeneratorExport.cpp
    HydrophobicFeatureGeneratorExport.cpp
    HydrophobicAtomFeatureGeneratorExport.cpp
    HBondAcceptorFeatureGeneratorExport.cpp
    HBondDonorFeatureGeneratorExport.cpp
    PosIonizableFeatureGeneratorExport.cpp
    NegIonizableFeatureGeneratorExport.cpp
    InteractionAnalyzerExport.cpp
    DefaultInteractionAnalyzerExport.cpp
    InteractionConstraintConnectorExport.cpp
    FeatureDistanceConstraintExport.cpp
    HydrophobicInteractionConstraintExport.cpp
    IonicInteractionConstraintExport.cpp
    OrthogonalPiPiInteractionConstraintExport.cpp
    ParallelPiPiInteractionConstraintExport.cpp
    CationPiInteractionConstraintExport.cpp
    HBondingInteractionConstraintExport.cpp

    InteractionScoreCombinerExport.cpp
    FeatureDistanceScoreExport.cpp
    HydrophobicInteractionScoreExport.cpp
    IonicInteractionScoreExport.cpp
    OrthogonalPiPiInteractionScoreExport.cpp
    ParallelPiPiInteractionScoreExport.cpp
    CationPiInteractionScoreExport.cpp
    HBondingInteractionScoreExport.cpp
    InteractionScoreGridCalculatorExport.cpp
    InteractionScoreGridSetCalculatorExport.cpp
    DefaultInteractionScoreGridSetCalculatorExport.cpp

    FeatureTypeMatchFunctorExport.cpp
    FeaturePairDistanceMatchFunctorExport.cpp
    TopologicalEntityAlignmentExport.cpp	
    GeometricalEntityAlignmentExport.cpp
    PharmacophoreAlignmentExport.cpp
    GeometricalFeatureMappingExtractorExport.cpp
    FeaturePositionMatchFunctorExport.cpp
    FeatureGeometryMatchFunctorExport.cpp
    
    AttributedGridPropertyExport.cpp 
    AttributedGridPropertyDefaultExport.cpp 

    FeatureContainerPropertyExport.cpp 
    FeaturePropertyExport.cpp 
    FeatureContainerPropertyDefaultExport.cpp 
    FeaturePropertyDefaultExport.cpp 
    DataFormatExport.cpp 
    FeatureTypeExport.cpp 
    FeatureGeometryExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 

    PharmacophoreFunctionExport.cpp 
    FeatureFunctionExport.cpp 
    FeatureContainerFunctionExport.cpp 
    FeatureSetFunctionExport.cpp 
    AttributedGridFunctionExport.cpp 
    ControlParameterFunctionExport.cpp 

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

IF(Boost_FILESYSTEM_FOUND)
  SET(pharm_MOD_SRCS
      ${pharm_MOD_SRCS}
      FileScreeningHitCollectorExport.cpp
     )	
ENDIF(Boost_FILESYSTEM_FOUND)

IF(SQLITE3_FOUND)
  SET(pharm_MOD_SRCS
      ${pharm_MOD_SRCS}
      PSDScreeningDBCreatorExport.cpp
      PSDScreeningDBAccessorExport.cpp
     )	
  IF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
    SET(pharm_MOD_SRCS
        ${pharm_MOD_SRCS}
        PSDPharmacophoreInputHandlerExport.cpp 
        PSDMoleculeInputHandlerExport.cpp 
        PSDMolecularGraphOutputHandlerExport.cpp 

        PSDPharmacophoreReaderExport.cpp 
        PSDMoleculeReaderExport.cpp 
        PSDMolecularGraphWriterExport.cpp
       )	
  ENDIF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
ENDIF(SQLITE3_FOUND)

ADD_LIBRARY(_pharm MODULE ${pharm_MOD_SRCS})

TARGET_LINK_LIBRARIES(_pharm cdpl-pharm-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_pharm PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_pharm PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_pharm PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_pharm PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_pharm.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_pharm PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Pharm" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _pharm DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Pharm" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
