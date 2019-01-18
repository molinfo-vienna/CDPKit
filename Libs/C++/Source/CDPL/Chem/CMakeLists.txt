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
    Entity3DMapping.cpp	
    AtomBondMapping.cpp

    Entity3DProperty.cpp
    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp
    ReactionProperty.cpp
    AtomPropertyDefault.cpp
    BondPropertyDefault.cpp
    MolecularGraphPropertyDefault.cpp
    ReactionPropertyDefault.cpp

    ControlParameter.cpp
    ControlParameterDefault.cpp
    DataFormat.cpp
    INCHIReturnCode.cpp

    StringDataBlock.cpp
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
    CDFReactionReader.cpp
    CDFReactionWriter.cpp
    MOL2DataReader.cpp
    MOL2DataWriter.cpp
    MOL2MoleculeReader.cpp
    MOL2MolecularGraphWriter.cpp

    SubstructureSearch.cpp
    ReactionSubstructureSearch.cpp
    CommonConnectedSubstructureSearch.cpp
    MaxCommonAtomSubstructureSearch.cpp
    MaxCommonBondSubstructureSearch.cpp
    AutomorphismGroupSearch.cpp
    Reactor.cpp
    TautomerGenerator.cpp
    DefaultTautomerGenerator.cpp
    PatternBasedTautomerizationRule.cpp 
    KetoEnolTautomerization.cpp 
    ImineEnamineTautomerization.cpp  
    NitrosoOximeTautomerization.cpp  
    AmideImidicAcidTautomerization.cpp  
    LactamLactimTautomerization.cpp  
    KeteneYnolTautomerization.cpp  
    NitroAciTautomerization.cpp  
    PhosphinicAcidTautomerization.cpp  
    SulfenicAcidTautomerization.cpp  
    GenericHydrogen13ShiftTautomerization.cpp  
    GenericHydrogen15ShiftTautomerization.cpp  

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
    AutoCorrelation2DVectorCalculator.cpp
    AtomAutoCorrelation3DVectorCalculator.cpp
    AtomRDFCodeCalculator.cpp
    MoleculeRDFDescriptorCalculator.cpp
    MoleculeAutoCorr3DDescriptorCalculator.cpp
    MoleculeAutoCorr2DDescriptorCalculator.cpp
    BurdenMatrixGenerator.cpp
    BCUTDescriptorCalculator.cpp
    SurfaceAtomExtractor.cpp
    PathFingerprintGenerator.cpp
    CircularFingerprintGenerator.cpp
    PatternAtomTyper.cpp
    SubstructureHistogramGenerator.cpp
    GeneralizedBellAtomDensity.cpp
    AtomDensityGridCalculator.cpp
    AtomHydrophobicityCalculator.cpp
    BuriednessScore.cpp
    BuriednessGridCalculator.cpp

    Entity3DPropertyFunctions.cpp

    Entity3DContainerCoordinatesFunctions.cpp
    Entity3DContainerGeometricalDistanceMatrixFunction.cpp
    Entity3DContainerGeometricalDistanceFunctions.cpp
    Entity3DContainerCentroidFunction.cpp
    Entity3DContainerBoundingBoxFunctions.cpp

    AtomContainerAtomCountFunctions.cpp
    AtomContainerFormalChargeFunction.cpp
    AtomContainerElementalCompositionFunctions.cpp
    AtomContainerMassCompositionFunctions.cpp
    AtomContainerCoordinatesFunctions.cpp
    AtomContainerMaxAtomMappingIDFunction.cpp
    AtomContainerMaxComponentGroupIDFunction.cpp
    AtomContainerConformationFunctions.cpp
    AtomContainerAtomTypeMaskFunction.cpp
    AtomContainerCopyAtomsFunctions.cpp
    AtomContainerBoundingBoxFunctions.cpp

    BondContainerBondCountFunctions.cpp
 
    AtomPropertyFunctions.cpp
    AtomTypeFunctions.cpp
    AtomFormalChargeFunction.cpp
    AtomHybridizationPerceptionFunction.cpp
    AtomElementPropertyFunctions.cpp
    AtomRingMembershipFunctions.cpp
    AtomFragmentMembershipFunctions.cpp
    AtomClassificationFunctions.cpp
    AtomValenceFunctions.cpp
    AtomValenceElectronCountFunctions.cpp
    AtomHydrogenCountFunctions.cpp
    AtomAtomCountFunctions.cpp
    AtomBondCountFunctions.cpp
    AtomConformerCoordinatesFunction.cpp
    AtomStereoDescriptorFunctions.cpp
    AtomCIPConfigurationFunction.cpp
    AtomMDLParityFunction.cpp
    AtomStereoCenterFlagFunction.cpp
    AtomPolarizabilityFunctions.cpp
    AtomMatchExpressionStringFunction.cpp
    AtomMatchExpressionFunction.cpp
    AtomSybylTypeFunctions.cpp
    AtomTopologicalDistanceFunction.cpp
    AtomMarkReachableAtomsFunction.cpp 

    BondPropertyFunctions.cpp
    BondRingMembershipFunctions.cpp
    BondFragmentMembershipFunctions.cpp
    BondStereoCenterFlagFunction.cpp
    BondClassificationFunctions.cpp
    BondPolarizabilityFunction.cpp
    BondStereoDescriptorFunction.cpp
    BondCIPConfigurationFunction.cpp
    BondMatchExpressionStringFunction.cpp
    BondMatchExpressionFunction.cpp
    BondSybylTypePerception.cpp

    MolecularGraphPropertyFunctions.cpp
    MolecularGraphMatchConstraintsFunctions.cpp
    MolecularGraphComponentFunctions.cpp
    MolecularGraphRingSetFunctions.cpp
    MolecularGraphSSSRFunctions.cpp
    MolecularGraphCyclicSubstructureFunctions.cpp
    MolecularGraphGeometricalDistanceMatrixFunction.cpp
    MolecularGraphTopologicalDistanceFunctions.cpp
    MolecularGraphAdjacencyMatrixFunction.cpp
    MolecularGraphIncidenceMatrixFunction.cpp
    MolecularGraphBondMatrixFunction.cpp
    MolecularGraphBondElectronMatrixFunction.cpp
    MolecularGraphBondAtomTypeMatrixFunction.cpp
    MolecularGraphKierShapeFunctions.cpp
    MolecularGraphZagrebIndexFunctions.cpp
    MolecularGraphRingComplexityFunction.cpp
    MolecularGraphTotalWalkCountFunction.cpp
    MolecularGraphRandicIndexFunction.cpp
    MolecularGraphWienerIndexFunction.cpp
    MolecularGraphCyclomaticNumberFunction.cpp
    MolecularGraphComponentGroupsFunctions.cpp
    MolecularGraphExtractReactionCenterFunction.cpp
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
    MolecularGraphSybylAtomTypesFunction.cpp
    MolecularGraphAtomHydrophobicityFunction.cpp 
    MolecularGraphCanonicalizationFunctions.cpp 

    ReactionPropertyFunctions.cpp
    ReactionMatchConstraintsFunctions.cpp
    ReactionMatchExpressionFunctions.cpp
    ReactionComponentGroupsFunctions.cpp
    ReactionAtomMappingFunctions.cpp
    ReactionHashCodeFunction.cpp
    ReactionSMILESFunction.cpp
    ReactionSubstructSearchInitializationFunctions.cpp
    ReactionMaxAtomMappingIDFunction.cpp
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
   )

IF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
   LINK_LIBRARIES(${Boost_FILESYSTEM_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
ENDIF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY})

ADD_LIBRARY(cdpl-chem-static STATIC ${cdpl-chem_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-chem-static PROPERTIES 
                      OUTPUT_NAME cdpl-chem
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_CHEM_STATIC_LINK;CDPL_GRID_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-chem-static cdpl-grid-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static inchi-static)

INSTALL(TARGETS cdpl-chem-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-chem-shared SHARED ${cdpl-chem_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-chem-shared cdpl-grid-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-internal-static inchi-static)

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

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CMAKE_BUILD_TYPE EQUAL "DEBUG")
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CMAKE_BUILD_TYPE EQUAL "DEBUG")
