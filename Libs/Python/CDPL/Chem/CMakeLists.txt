INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(chem_MOD_SRCS
    Module.cpp
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
    AtomMappingExport.cpp 
    BondMappingExport.cpp 
    AtomBondMappingExport.cpp 
    FragmentListExport.cpp 
    MDLDataBlockExport.cpp
    PDBDataExport.cpp
    ElementHistogramExport.cpp
    MassCompositionExport.cpp
    StereoDescriptorExport.cpp
    MultiConfMoleculeInputProcessorExport.cpp
    DefaultMultiConfMoleculeInputProcessorExport.cpp

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
  
    CompleteRingSetExport.cpp 
    AromaticRingSetExport.cpp 
    SmallestSetOfSmallestRingsExport.cpp 
    AromaticSubstructureExport.cpp 
    CyclicSubstructureExport.cpp 
    ConnectedSubstructureSetExport.cpp 
    ComponentSetExport.cpp 
   
    Atom2DCoordinatesGeneratorExport.cpp 
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
    DaylightFingerprintGeneratorExport.cpp 
    AutoCorrelationVectorCalculatorExport.cpp 
    RDFCodeCalculatorExport.cpp 
    BurdenMatrixGeneratorExport.cpp 
    BCUTDescriptorCalculatorExport.cpp 
     
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
    JMEMoleculeInputHandlerExport.cpp 
    JMEReactionInputHandlerExport.cpp 
    JMEMolecularGraphOutputHandlerExport.cpp 
    JMEReactionOutputHandlerExport.cpp 
    PDBMoleculeInputHandlerExport.cpp 
    PDBMolecularGraphOutputHandlerExport.cpp 
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
   
    MoleculeReaderExport.cpp 
    MoleculeWriterExport.cpp 
    MolecularGraphReaderExport.cpp 
    MolecularGraphWriterExport.cpp 
    ReactionReaderExport.cpp 
    ReactionWriterExport.cpp 
    INCHIMoleculeReaderExport.cpp 
    INCHIMolecularGraphWriterExport.cpp 
    JMEMoleculeReaderExport.cpp 
    JMEMolecularGraphWriterExport.cpp 
    JMEReactionReaderExport.cpp 
    JMEReactionWriterExport.cpp 
    PDBMoleculeReaderExport.cpp 
    PDBMolecularGraphWriterExport.cpp 
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
   
    MolecularGraphPropertyExport.cpp 
    AtomPropertyExport.cpp 
    BondPropertyExport.cpp 
    ReactionPropertyExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 
    DataFormatExport.cpp 
    AtomPropertyFlagExport.cpp 
    BondPropertyFlagExport.cpp 
    ReactionRoleExport.cpp 
    AtomTypeExport.cpp 
    ResidueTypeExport.cpp 
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

    ControlParameterFunctionExport.cpp 
    UtilityFunctionExport.cpp 
    AtomContainerFunctionExport.cpp 
    BondContainerFunctionExport.cpp 
    AtomFunctionExport.cpp 
    BondFunctionExport.cpp 
    MolecularGraphFunctionExport.cpp 
    MoleculeFunctionExport.cpp 
    FragmentFunctionExport.cpp 
    ReactionFunctionExport.cpp 
    SimilarityFunctionExport.cpp 
    AtomTypeFunctionExport.cpp 
    ResidueFunctionExport.cpp 

    ToPythonConverterRegistration.cpp 
    FromPythonConverterRegistration.cpp 
   )

ADD_LIBRARY(_chem MODULE ${chem_MOD_SRCS})

TARGET_LINK_LIBRARIES(_chem cdpl-chem-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_chem PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_chem PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
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
