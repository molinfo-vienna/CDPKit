INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CDPKIT_EXTERNAL_DIR}")

SET(cdpl-chem_LIB_SRCS
    Entity3D.cpp
    Entity3DContainer.cpp
    AtomContainer.cpp
    BondContainer.cpp
    MolecularGraph.cpp
    Molecule.cpp
    Atom.cpp
    Bond.cpp
    Reaction.cpp
    BasicReaction.cpp
    BasicMolecule.cpp
    BasicAtom.cpp
    BasicBond.cpp
    Fragment.cpp
    AtomBondMapping.cpp

    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp
    ReactionProperty.cpp
    Entity3DProperty.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp
    DataFormat.cpp
    INCHIReturnCode.cpp

    MDLDataBlock.cpp
    StereoDescriptor.cpp
    AtomDictionary.cpp

    DefaultMultiConfMoleculeInputProcessor.cpp

    INCHIMoleculeReader.cpp
    INCHIMolecularGraphWriter.cpp
    JMEDataReader.cpp
    JMEDataWriter.cpp
    JMEMoleculeReader.cpp
    JMEMolecularGraphWriter.cpp
    JMEReactionReader.cpp
    JMEReactionWriter.cpp
    SMILESDataReader.cpp
    SMILESDataWriter.cpp
    SMILESMoleculeReader.cpp
    SMILESReactionReader.cpp
    SMILESMolecularGraphWriter.cpp
    SMILESReactionWriter.cpp
    SMARTSDataReader.cpp
    SMARTSDataWriter.cpp
    SMARTSMoleculeReader.cpp
    SMARTSReactionReader.cpp
    SMARTSMolecularGraphWriter.cpp
    SMARTSReactionWriter.cpp
    MDLDataReader.cpp
    MDLDataWriter.cpp
    MOLMoleculeReader.cpp
    MOLMolecularGraphWriter.cpp
    SDFMoleculeReader.cpp
    SDFMolecularGraphWriter.cpp
    RXNReactionReader.cpp
    RXNReactionWriter.cpp
    RDFReactionReader.cpp
    RDFReactionWriter.cpp
    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFMoleculeReader.cpp
    CDFMolecularGraphWriter.cpp

    SubstructureSearch.cpp
    ReactionSubstructureSearch.cpp
    CommonConnectedSubstructureSearch.cpp
    MaxCommonAtomSubstructureSearch.cpp
    MaxCommonBondSubstructureSearch.cpp
    Reactor.cpp

    CompleteRingSet.cpp
    AromaticRingSet.cpp
    AromaticSSSRSubset.cpp
    SmallestSetOfSmallestRings.cpp
    AromaticSubstructure.cpp
    CyclicSubstructure.cpp
    ConnectedSubstructureSet.cpp
    ComponentSet.cpp

    MorganNumberingGenerator.cpp
    CIPPriorityCalculator.cpp
    CanonicalNumberingGenerator.cpp
    Atom2DCoordinatesGenerator.cpp
    Hydrogen3DCoordinatesGenerator.cpp
    BondStereoFlagGenerator.cpp
    BondDirectionGenerator.cpp
    BondOrderGenerator.cpp
    KekuleStructureGenerator.cpp
    XLogPCalculator.cpp
    TPSACalculator.cpp
    HashCodeCalculator.cpp
    SymmetryClassCalculator.cpp
    LogSCalculator.cpp
    MolecularComplexityCalculator.cpp
    PEOEChargeCalculator.cpp
    DaylightFingerprintGenerator.cpp
    AutoCorrelationVectorCalculator.cpp
    RDFCodeCalculator.cpp
    BurdenMatrixGenerator.cpp
    BCUTDescriptorCalculator.cpp
    SurfaceAtomExtractor.cpp

    Entity3DCoordinatesFunctions.cpp

    Entity3DContainerCoordinatesFunctions.cpp
    Entity3DContainerGeometricalDistanceMatrixFunction.cpp
    Entity3DContainerGeometricalDistanceFunctions.cpp
    Entity3DContainerCentroidFunction.cpp

    AtomContainerAtomCountFunctions.cpp
    AtomContainerFormalChargeFunction.cpp
    AtomContainerElementalCompositionFunctions.cpp
    AtomContainerMassCompositionFunctions.cpp
    AtomContainerCoordinatesFunctions.cpp
    AtomContainerMaxReactionAtomMappingIDFunction.cpp
    AtomContainerMaxComponentGroupIDFunction.cpp
    AtomContainerConformationFunctions.cpp
    AtomContainerAtomTypeMaskFunction.cpp
    AtomContainerCopyAtomsFunctions.cpp

    BondContainerBondCountFunctions.cpp
 
    AtomNameFunctions.cpp
    AtomSymbolFunctions.cpp
    AtomAtomTypeFunctions.cpp
    AtomFormalChargeFunctions.cpp
    AtomIsotopeFunctions.cpp
    AtomRadicalTypeFunctions.cpp
    AtomHybridizationStateFunctions.cpp
    AtomElementPropertyFunctions.cpp
    AtomRingFlagFunctions.cpp
    AtomRingMembershipFunctions.cpp
    AtomFragmentMembershipFunctions.cpp
    AtomUnpairedElectronCountFunctions.cpp
    AtomAromaticityFlagFunctions.cpp
    AtomClassificationFunctions.cpp
    AtomValenceFunctions.cpp
    AtomValenceElectronCountFunctions.cpp
    AtomHydrogenCountFunctions.cpp
    AtomAtomCountFunctions.cpp
    AtomBondCountFunctions.cpp
    AtomCoordinatesFunctions.cpp
    AtomMorganNumberFunctions.cpp
    AtomCanonicalNumberFunctions.cpp
    AtomCIPPriorityFunctions.cpp
    AtomStereoDescriptorFunctions.cpp
    AtomCIPConfigurationFunctions.cpp
    AtomMDLParityFunctions.cpp
    AtomSymmetryClassFunctions.cpp
    AtomStereoCenterFlagFunctions.cpp
    AtomMDLStereoCareFlagFunctions.cpp
    AtomPEOEChargeFunctions.cpp
    AtomPolarizabilityFunctions.cpp
    AtomReactionCenterStatusFunctions.cpp
    AtomReactionAtomMappingIDFunctions.cpp
    AtomComponentGroupIDFunctions.cpp
    AtomMatchConstraintsFunctions.cpp
    AtomMatchExpressionStringFunctions.cpp
    AtomMatchExpressionFunctions.cpp
 
    BondOrderFunctions.cpp
    BondRingFlagFunctions.cpp
    BondRingMembershipFunctions.cpp
    BondFragmentMembershipFunctions.cpp
    BondAromaticityFlagFunctions.cpp
    Bond2DStereoFlagFunctions.cpp
    BondDirectionFunctions.cpp
    BondReactionCenterStatusFunctions.cpp
    BondMatchConstraintsFunctions.cpp
    BondStereoCenterFlagFunctions.cpp
    BondClassificationFunctions.cpp
    BondPolarizabilityFunction.cpp
    BondStereoDescriptorFunctions.cpp
    BondCIPConfigurationFunctions.cpp
    BondMatchExpressionStringFunctions.cpp
    BondMatchExpressionFunctions.cpp

    MolecularGraphNameFunctions.cpp
    MolecularGraphMatchConstraintsFunctions.cpp
    MolecularGraphComponentFunctions.cpp
    MolecularGraphRingSetFunctions.cpp
    MolecularGraphSSSRFunctions.cpp
    MolecularGraphCyclicSubstructureFunctions.cpp
    MolecularGraphTopologicalDistanceMatrixFunctions.cpp
    MolecularGraphGeometricalDistanceMatrixFunctions.cpp
    MolecularGraphTopologicalDistanceFunctions.cpp
    MolecularGraphAdjacencyMatrixFunction.cpp
    MolecularGraphIncidenceMatrixFunction.cpp
    MolecularGraphBondMatrixFunction.cpp
    MolecularGraphBondElectronMatrixFunction.cpp
    MolecularGraphKierShapeFunctions.cpp
    MolecularGraphZagrebIndexFunctions.cpp
    MolecularGraphRingComplexityFunction.cpp
    MolecularGraphTotalWalkCountFunction.cpp
    MolecularGraphRandicIndexFunction.cpp
    MolecularGraphWienerIndexFunction.cpp
    MolecularGraphCyclomaticNumberFunction.cpp
    MolecularGraphComponentGroupsFunctions.cpp
    MolecularGraphExtractReactionCenterFunction.cpp
    MolecularGraphStoichiometricNumberFunctions.cpp
    MolecularGraphConformationIndexFunctions.cpp
    MolecularGraphMDLUserInitialsFunctions.cpp
    MolecularGraphMDLProgramNameFunctions.cpp
    MolecularGraphMDLTimestampFunctions.cpp
    MolecularGraphMDLRegistryNumberFunctions.cpp
    MolecularGraphMDLCommentFunctions.cpp
    MolecularGraphMDLCTABVersionFunctions.cpp
    MolecularGraphMDLStructureDataFunctions.cpp
    MolecularGraphMDLDimensionalityFunctions.cpp
    MolecularGraphMDLScalingFactorFunctions.cpp
    MolecularGraphMDLEnergyFunctions.cpp
    MolecularGraphMDLChiralFlagFunctions.cpp
    MolecularGraphAtomCountFunctions.cpp
    MolecularGraphBondCountFunctions.cpp
    MolecularGraphMassCompositionFunctions.cpp
    MolecularGraphElementalCompositionFunctions.cpp	
    MolecularGraphAromaticRingSetFunctions.cpp
    MolecularGraphAromaticSubstructureFunctions.cpp
    MolecularGraphKekulizeBondsFunction.cpp
    MolecularGraphBondOrdersFunction.cpp
    MolecularGraphMatchExpressionFunctions.cpp
    MolecularGraphMatchExpressionStringsFunction.cpp
    MolecularGraphSMILESFunction.cpp
    MolecularGraphINCHIFunctions.cpp
    MolecularGraphHashCodeFunction.cpp
    MolecularGraphXLogPFunction.cpp
    MolecularGraphLogSFunction.cpp
    MolecularGraphTPSAFunction.cpp
    MolecularGraphRO5ScoreFunction.cpp
    MolecularGraphMeanPolarizabilityFunction.cpp
    MolecularGraphComplexityFunction.cpp
    MolecularGraphPEOEChargesFunction.cpp
    MolecularGraphSubstructSearchInitializationFunctions.cpp
    MolecularGraphBond2DStereoFlagsFunction.cpp 
    MolecularGraphBondDirectionsFunction.cpp 
    MolecularGraphCIPPrioritiesFunction.cpp 
    MolecularGraphSymmetryClassesFunction.cpp 
    MolecularGraphCanonicalNumberingFunction.cpp 
    MolecularGraphMorganNumberingFunction.cpp 
    MolecularGraphAtomStereoFunctions.cpp 
    MolecularGraphBondStereoFunctions.cpp 
    MolecularGraphImplicitHydrogenCountsFunction.cpp 
    MolecularGraphFormalChargesFunction.cpp 
    MolecularGraphHybridizationStatesFunction.cpp 
    MolecularGraphAromaticityFlagsFunction.cpp 
    MolecularGraphRingFlagsFunction.cpp 
    MolecularGraphAtomTypesFromSymbolFunction.cpp
    MolecularGraphAtomSymbolsFromTypeFunction.cpp
    MolecularGraph2DCoordinatesFunction.cpp
    MolecularGraph3DCoordinatesFunctions.cpp

    ReactionNameFunctions.cpp
    ReactionMatchConstraintsFunctions.cpp
    ReactionMatchExpressionFunctions.cpp
    ReactionComponentGroupsFunctions.cpp
    ReactionAtomMappingFunctions.cpp
    ReactionHashCodeFunction.cpp
    ReactionSMILESFunction.cpp
    ReactionMDLUserInitialsFunctions.cpp
    ReactionMDLProgramNameFunctions.cpp
    ReactionMDLTimestampFunctions.cpp
    ReactionMDLRegistryNumberFunctions.cpp
    ReactionMDLCommentFunctions.cpp
    ReactionMDLReactionDataFunctions.cpp
    ReactionMDLMoleculeRecordFunctions.cpp
    ReactionMDLRXNFileVersionFunctions.cpp
    ReactionSubstructSearchInitializationFunctions.cpp
    ReactionMaxReactionAtomMappingIDFunction.cpp
    ReactionMaxComponentGroupIDFunction.cpp

    MoleculeHydrogenManipulationFunctions.cpp
    MoleculeReplaceStereoRefAtomsFunctions.cpp  
    MoleculeRemoveAtomsFunctions.cpp

    FragmentHydrogenManipulationFunctions.cpp
    FragmentRemoveAtomsFunctions.cpp

    Atom3DCoordinatesFunctor.cpp
    AtomConformer3DCoordinatesFunctor.cpp
    AtomArray3DCoordinatesFunctor.cpp

    ControlParameterFunctions.cpp

    SimilarityFunctions.cpp
    UtilityFunctions.cpp

    MatchConstraintList.cpp
    AtomTypeMatchExpression.cpp
    AtomEnvironmentMatchExpression.cpp
    AtomConfigurationMatchExpression.cpp
    BondConfigurationMatchExpression.cpp
    BondDirectionMatchExpression.cpp
    BondSubstituentDirectionMatchExpression.cpp
    BondReactionCenterStatusMatchExpression.cpp
    MolecularGraphComponentGroupingMatchExpression.cpp
    ReactionAtomMappingMatchExpression.cpp
    ReactionComponentGroupingMatchExpression.cpp

    AromaticityPerception.cpp
   )

ADD_LIBRARY(cdpl-chem-static STATIC ${cdpl-chem_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-chem-static PROPERTIES 
                      OUTPUT_NAME cdpl-chem
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static inchi-static ${Boost_DATE_TIME_LIBRARY})

INSTALL(TARGETS cdpl-chem-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-chem-shared SHARED ${cdpl-chem_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-chem-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-internal-static inchi-static ${Boost_DATE_TIME_LIBRARY})

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-chem-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Chem
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-chem-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-chem
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-chem.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake"
                    @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-chem-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
