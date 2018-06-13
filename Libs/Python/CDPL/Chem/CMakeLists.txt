INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(chem_MOD_SRCS
    Module.cpp
    Entity3DExport.cpp
    Entity3DContainerExport.cpp
    AtomContainerExport.cpp
    BondContainerExport.cpp
    AtomExport.cpp
    BondExport.cpp
    MolecularGraphExport.cpp
    MoleculeExport.cpp
    ReactionExport.cpp
    BasicAtomExport.cpp
    BasicBondExport.cpp
    BasicMoleculeExport.cpp
    BasicReactionExport.cpp
    FragmentExport.cpp 
    Entity3DMappingExport.cpp 
    AtomMappingExport.cpp 
    BondMappingExport.cpp 
    AtomBondMappingExport.cpp 
    FragmentListExport.cpp 
    StringDataBlockExport.cpp
    ElementHistogramExport.cpp
    MassCompositionExport.cpp
    StereoDescriptorExport.cpp
    MultiConfMoleculeInputProcessorExport.cpp
    DefaultMultiConfMoleculeInputProcessorExport.cpp
    AtomDictionaryExport.cpp

    MatchConstraintListExport.cpp 
    MatchExpressionExport.cpp 
    MatchExpressionListExport.cpp 
    ANDMatchExpressionListExport.cpp 
    ORMatchExpressionListExport.cpp 
    NOTMatchExpressionExport.cpp 
    AtomTypeMatchExpressionExport.cpp 
    AtomEnvironmentMatchExpressionExport.cpp 
    AtomConfigurationMatchExpressionExport.cpp 
    BondConfigurationMatchExpressionExport.cpp 
    BondDirectionMatchExpressionExport.cpp 
    BondSubstituentDirectionMatchExpressionExport.cpp 
    BondReactionCenterStatusMatchExpressionExport.cpp 
    MolecularGraphComponentGroupingMatchExpressionExport.cpp 
    ReactionAtomMappingMatchExpressionExport.cpp 
    ReactionComponentGroupingMatchExpressionExport.cpp 

    SubstructureSearchExport.cpp 
    ReactionSubstructureSearchExport.cpp 
    CommonConnectedSubstructureSearchExport.cpp 
    MaxCommonAtomSubstructureSearchExport.cpp 
    MaxCommonBondSubstructureSearchExport.cpp 

    ReactorExport.cpp 
  
    TopologicalEntityAlignmentExport.cpp	
    GeometricalEntityAlignmentExport.cpp
   
    CompleteRingSetExport.cpp 
    AromaticRingSetExport.cpp 
    AromaticSSSRSubsetExport.cpp 
    SmallestSetOfSmallestRingsExport.cpp 
    AromaticSubstructureExport.cpp 
    CyclicSubstructureExport.cpp 
    ConnectedSubstructureSetExport.cpp 
    ComponentSetExport.cpp 
   
    Atom2DCoordinatesGeneratorExport.cpp 
    Hydrogen3DCoordinatesGeneratorExport.cpp 
    MorganNumberingGeneratorExport.cpp 
    CanonicalNumberingGeneratorExport.cpp 
    CIPPriorityCalculatorExport.cpp 
    BondStereoFlagGeneratorExport.cpp 
    BondDirectionGeneratorExport.cpp 
    BondOrderGeneratorExport.cpp 
    KekuleStructureGeneratorExport.cpp 
    XLogPCalculatorExport.cpp 
    TPSACalculatorExport.cpp 
    HashCodeCalculatorExport.cpp 
    SymmetryClassCalculatorExport.cpp 
    LogSCalculatorExport.cpp 
    MolecularComplexityCalculatorExport.cpp 
    PEOEChargeCalculatorExport.cpp 
    AutoCorrelation2DVectorCalculatorExport.cpp 
    AtomRDFCodeCalculatorExport.cpp 
    MoleculeRDFDescriptorCalculatorExport.cpp 
    AtomAutoCorrelation3DVectorCalculatorExport.cpp 
    MoleculeAutoCorr3DDescriptorCalculatorExport.cpp 
    BurdenMatrixGeneratorExport.cpp 
    BCUTDescriptorCalculatorExport.cpp 
    SurfaceAtomExtractorExport.cpp 
    PathFingerprintGeneratorExport.cpp 
    CircularFingerprintGeneratorExport.cpp 
    PatternAtomTyperExport.cpp 
    SubstructureHistogramGeneratorExport.cpp 
    GeneralizedBellAtomDensityExport.cpp
    AtomDensityGridCalculatorExport.cpp
    AtomHydrophobicityCalculatorExport.cpp
    BuriednessScoreExport.cpp
    BuriednessGridCalculatorExport.cpp
    TautomerGeneratorExport.cpp
    DefaultTautomerGeneratorExport.cpp
    TautomerizationRuleExport.cpp 
    PatternBasedTautomerizationRuleExport.cpp 
    KetoEnolTautomerizationExport.cpp 
    ImineEnamineTautomerizationExport.cpp  
    NitrosoOximeTautomerizationExport.cpp  
    AmideImidicAcidTautomerizationExport.cpp  
    LactamLactimTautomerizationExport.cpp  
    KeteneYnolTautomerizationExport.cpp  
    NitroAciTautomerizationExport.cpp  
    PhosphinicAcidTautomerizationExport.cpp  
    SulfenicAcidTautomerizationExport.cpp  
    GenericHydrogen13ShiftTautomerizationExport.cpp  
    GenericHydrogen15ShiftTautomerizationExport.cpp  

    MoleculeIOManagerExport.cpp 
    MolecularGraphIOManagerExport.cpp 
    ReactionIOManagerExport.cpp 
    MoleculeInputHandlerExport.cpp 
    MoleculeOutputHandlerExport.cpp 
    MolecularGraphInputHandlerExport.cpp 
    MolecularGraphOutputHandlerExport.cpp 
    ReactionInputHandlerExport.cpp 
    ReactionOutputHandlerExport.cpp 
    INCHIMoleculeInputHandlerExport.cpp 
    INCHIMolecularGraphOutputHandlerExport.cpp 
    CDFMoleculeInputHandlerExport.cpp 
    CDFMolecularGraphOutputHandlerExport.cpp 
    CDFReactionInputHandlerExport.cpp 
    CDFReactionOutputHandlerExport.cpp 
    JMEMoleculeInputHandlerExport.cpp 
    JMEReactionInputHandlerExport.cpp 
    JMEMolecularGraphOutputHandlerExport.cpp 
    JMEReactionOutputHandlerExport.cpp 
    MOLMoleculeInputHandlerExport.cpp 
    MOLMolecularGraphOutputHandlerExport.cpp 
    SDFMoleculeInputHandlerExport.cpp 
    SDFMolecularGraphOutputHandlerExport.cpp 
    RXNReactionInputHandlerExport.cpp 
    RXNReactionOutputHandlerExport.cpp 
    RDFReactionInputHandlerExport.cpp 
    RDFReactionOutputHandlerExport.cpp 
    SMILESMoleculeInputHandlerExport.cpp 
    SMILESReactionInputHandlerExport.cpp 
    SMILESMolecularGraphOutputHandlerExport.cpp 
    SMILESReactionOutputHandlerExport.cpp 
    SMARTSMoleculeInputHandlerExport.cpp 
    SMARTSReactionInputHandlerExport.cpp 
    SMARTSMolecularGraphOutputHandlerExport.cpp 
    SMARTSReactionOutputHandlerExport.cpp 
    MOL2MoleculeInputHandlerExport.cpp 
    MOL2MolecularGraphOutputHandlerExport.cpp 

    MoleculeReaderExport.cpp 
    MoleculeWriterExport.cpp 
    MolecularGraphReaderExport.cpp 
    MolecularGraphWriterExport.cpp 
    ReactionReaderExport.cpp 
    ReactionWriterExport.cpp 
    INCHIMoleculeReaderExport.cpp 
    INCHIMolecularGraphWriterExport.cpp 
    CDFMoleculeReaderExport.cpp 
    CDFMolecularGraphWriterExport.cpp
    CDFReactionReaderExport.cpp 
    CDFReactionWriterExport.cpp 
    JMEMoleculeReaderExport.cpp 
    JMEMolecularGraphWriterExport.cpp 
    JMEReactionReaderExport.cpp 
    JMEReactionWriterExport.cpp 
    SMILESMoleculeReaderExport.cpp 
    SMILESReactionReaderExport.cpp 
    SMILESMolecularGraphWriterExport.cpp 
    SMILESReactionWriterExport.cpp 
    SMARTSMoleculeReaderExport.cpp 
    SMARTSReactionReaderExport.cpp 
    SMARTSMolecularGraphWriterExport.cpp 
    SMARTSReactionWriterExport.cpp 
    MOLMoleculeReaderExport.cpp 
    MOLMolecularGraphWriterExport.cpp 
    SDFMoleculeReaderExport.cpp 
    SDFMolecularGraphWriterExport.cpp 
    RXNReactionReaderExport.cpp 
    RXNReactionWriterExport.cpp 
    RDFReactionReaderExport.cpp 
    RDFReactionWriterExport.cpp 
    MOL2MoleculeReaderExport.cpp 
    MOL2MolecularGraphWriterExport.cpp

    MolecularGraphPropertyExport.cpp 
    Entity3DPropertyExport.cpp 
    AtomPropertyExport.cpp 
    BondPropertyExport.cpp 
    ReactionPropertyExport.cpp 
    AtomPropertyDefaultExport.cpp 
    BondPropertyDefaultExport.cpp 
    MolecularGraphPropertyDefaultExport.cpp 
    ReactionPropertyDefaultExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 
    DataFormatExport.cpp 
    AtomPropertyFlagExport.cpp 
    BondPropertyFlagExport.cpp 
    ReactionRoleExport.cpp 
    AtomTypeExport.cpp 
    AtomConfigurationExport.cpp 
    BondConfigurationExport.cpp 
    BondStereoFlagExport.cpp 
    HybridizationStateExport.cpp 
    ReactionCenterStatusExport.cpp 
    BondDirectionExport.cpp 
    RadicalTypeExport.cpp 
    AtomMatchConstraintExport.cpp 
    BondMatchConstraintExport.cpp 
    MolecularGraphMatchConstraintExport.cpp 
    ReactionMatchConstraintExport.cpp 
    INCHIReturnCodeExport.cpp
    MDLDataFormatVersionExport.cpp 
    MDLParityExport.cpp 
    SybylAtomTypeExport.cpp 
    SybylBondTypeExport.cpp 
    MOL2MoleculeTypeExport.cpp 
    MOL2ChargeTypeExport.cpp 
    TautomerizationTypeExport.cpp 

    ControlParameterFunctionExport.cpp 
    UtilityFunctionExport.cpp 
    AtomContainerFunctionExport.cpp 
    BondContainerFunctionExport.cpp 
    Entity3DContainerFunctionExport.cpp 
    Entity3DFunctionExport.cpp 
    AtomFunctionExport.cpp 
    BondFunctionExport.cpp 
    MolecularGraphFunctionExport.cpp 
    MoleculeFunctionExport.cpp 
    FragmentFunctionExport.cpp 
    ReactionFunctionExport.cpp 
    SimilarityFunctionExport.cpp 

    BoostFunctionWrapperExport.cpp
    Atom3DCoordinatesFunctorExport.cpp
    AtomConformer3DCoordinatesFunctorExport.cpp
    AtomArray3DCoordinatesFunctorExport.cpp

    ToPythonConverterRegistration.cpp 
    FromPythonConverterRegistration.cpp 
   )

ADD_LIBRARY(_chem MODULE ${chem_MOD_SRCS})

TARGET_LINK_LIBRARIES(_chem cdpl-chem-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_chem PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_chem PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_chem PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_chem PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_chem.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_chem PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _chem DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
