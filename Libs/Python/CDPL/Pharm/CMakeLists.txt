INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(pharm_MOD_SRCS
    Module.cpp
    PharmacophoreExport.cpp
    FeatureExport.cpp
    BasicPharmacophoreExport.cpp
    BasicFeatureExport.cpp

    FeatureMappingExport.cpp 
    FeatureTypeHistogramExport.cpp 

    PharmacophoreIOManagerExport.cpp 
    PharmacophoreReaderExport.cpp 
    PharmacophoreWriterExport.cpp 
    PharmacophoreInputHandlerExport.cpp 
    PharmacophoreOutputHandlerExport.cpp 

    CDFPharmacophoreInputHandlerExport.cpp 
    CDFPharmacophoreOutputHandlerExport.cpp 
    CDFPharmacophoreReaderExport.cpp 
    CDFPharmacophoreWriterExport.cpp

    ScreeningDBCreatorExport.cpp
    ScreeningDBAccessorExport.cpp

    BoostFunctionWrapperExport.cpp

    FeatureGeneratorExport.cpp
    PharmacophoreGeneratorExport.cpp
    DefaultPharmacophoreGeneratorExport.cpp
    PatternBasedFeatureGeneratorExport.cpp
    AromaticFeatureGeneratorExport.cpp
    HydrophobicFeatureGeneratorExport.cpp
    HBondAcceptorFeatureGeneratorExport.cpp
    HBondDonorFeatureGeneratorExport.cpp
    PosIonizableFeatureGeneratorExport.cpp
    NegIonizableFeatureGeneratorExport.cpp
    SurfaceXVolumeCoatGeneratorExport.cpp
    FeatureInteractionAnalyzerExport.cpp
    DefaultFeatureInteractionAnalyzerExport.cpp
    FeatureInteractionConstraintConnectorExport.cpp
    FeatureDistanceConstraintExport.cpp
    HydrophobicInteractionConstraintExport.cpp
    IonicInteractionConstraintExport.cpp
    OrthogonalPiPiInteractionConstraintExport.cpp
    ParallelPiPiInteractionConstraintExport.cpp
    CationPiInteractionConstraintExport.cpp
    HBondingInteractionConstraintExport.cpp

    FeatureTypeMatchFunctorExport.cpp
    FeaturePairDistanceMatchFunctorExport.cpp
    TopologicalEntityAlignmentExport.cpp	
    GeometricalEntityAlignmentExport.cpp
    PharmacophoreAlignmentExport.cpp
    TopologicalQueryPharmAlignmentFilterExport.cpp
    GeometricalQueryPharmAlignmentFilterExport.cpp
    GeometricalFeatureMappingExtractorExport.cpp
    FeaturePositionMatchFunctorExport.cpp
    FeatureGeometryMatchFunctorExport.cpp

    PharmacophorePropertyExport.cpp 
    FeaturePropertyExport.cpp 
    DataFormatExport.cpp 
    FeatureTypeExport.cpp 
    FeatureGeometryExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 

    PharmacophoreFunctionExport.cpp 
    FeatureFunctionExport.cpp 
    ControlParameterFunctionExport.cpp 

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

IF(SQLITE3_FOUND)
  SET(pharm_MOD_SRCS
      ${pharm_MOD_SRCS}
      SQLiteScreeningDBCreatorExport.cpp
      SQLiteScreeningDBAccessorExport.cpp
     )	
ENDIF(SQLITE3_FOUND)

ADD_LIBRARY(_pharm MODULE ${pharm_MOD_SRCS})

TARGET_LINK_LIBRARIES(_pharm cdpl-pharm-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_pharm PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_pharm PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
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
