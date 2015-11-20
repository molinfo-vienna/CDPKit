INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    BasicReactionTest.cpp
    BasicMoleculeTest.cpp
    BasicAtomTest.cpp
    BasicBondTest.cpp
    ReactionTest.cpp
    MoleculeTest.cpp
    AtomTest.cpp
    BondTest.cpp
    #AtomContainerTest.cpp
    #BondContainerTest.cpp
    FragmentTest.cpp
    AtomBondMappingTest.cpp
    #DataFormatsTest.cpp
    MDLDataBlockTest.cpp
    AtomTypeFunctionsTest.cpp

    #IsHydrogenTest.cpp
    #IsOrdinaryHydrogenTest.cpp

    #JMEMolecularGraphOutputHandlerTest.cpp
    #MOLMolecularGraphOutputHandlerTest.cpp
    #SDFMolecularGraphOutputHandlerTest.cpp
    #SMILESMolecularGraphOutputHandlerTest.cpp
    #SMARTSMolecularGraphOutputHandlerTest.cpp
    #JMEMoleculeInputHandlerTest.cpp
    #MOLMoleculeInputHandlerTest.cpp
    #SDFMoleculeInputHandlerTest.cpp
    #SMILESMoleculeInputHandlerTest.cpp
    #SMARTSMoleculeInputHandlerTest.cpp
    #JMEReactionOutputHandlerTest.cpp
    #RXNReactionOutputHandlerTest.cpp
    #RDFReactionOutputHandlerTest.cpp
    #SMILESReactionOutputHandlerTest.cpp
    #SMARTSReactionOutputHandlerTest.cpp
    #JMEReactionInputHandlerTest.cpp
    #RXNReactionInputHandlerTest.cpp
    #RDFReactionInputHandlerTest.cpp
    #SMILESReactionInputHandlerTest.cpp
    #SMARTSReactionInputHandlerTest.cpp

    MatchConstraintListTest.cpp          # TODO
    MatchExpressionTest.cpp
    ListMatchExpressionTest.cpp
    #PropertyMatchExpressionTest.cpp
    ANDListMatchExpressionTest.cpp
    ORListMatchExpressionTest.cpp
    NOTMatchExpressionTest.cpp

    #HashCodeCalculatorTest.cpp 
    
    #CompleteRingSetTest.cpp 
    #SmallestSetOfSmallestRingsTest.cpp 
    #ConnectedSubstructureSetTest.cpp 
    #ComponentSetTest.cpp 

    SimilarityFunctionsTest.cpp
    UtilityFunctionsTest.cpp
    #AtomFunctionsTest.cpp
    #BondFunctionsTest.cpp
    MoleculeHydrogenManipulationFunctionsTest.cpp
    FragmentHydrogenManipulationFunctionsTest.cpp
    #ReactionFunctionsTest.cpp

    #AtomContainerAtomCountTest.cpp
    #AtomContainerMassTest.cpp
    #AtomContainerHCountTest.cpp
    #AtomContainerHeavyAtomCountTest.cpp
    #AtomContainerFormalChargeTest.cpp
    #AtomContainerElementHistogramTest.cpp
    #AtomContainerMolecularFormulaTest.cpp
    #AtomContainerMassCompositionTest.cpp
    #AtomContainerMassCompositionStringTest.cpp

    #BondContainerBondCountTest.cpp
    #BondContainerSingleBondCountTest.cpp
    #BondContainerDoubleBondCountTest.cpp
    #BondContainerTripleBondCountTest.cpp
    #BondContainerHeavyBondCountTest.cpp
    #BondContainerHBondCountTest.cpp

    #MolecularGraphChainBondCountTest.cpp
    #MolecularGraphRingBondCountTest.cpp
    #MolecularGraphAromaticBondCountTest.cpp
    #MolecularGraphRotableBondCountTest.cpp
    #MolecularGraphChainAtomCountTest.cpp
    #MolecularGraphRingAtomCountTest.cpp
    #MolecularGraphAromaticAtomCountTest.cpp
    #MolecularGraphOrdinaryHCountTest.cpp
    #MolecularGraphTotalAtomCountTest.cpp
    #MolecularGraphTotalChainAtomCountTest.cpp
    #MolecularGraphTotalBondCountTest.cpp
    #MolecularGraphTotalSingleBondCountTest.cpp
    #MolecularGraphTotalChainBondCountTest.cpp
    #MolecularGraphTotalHBondCountTest.cpp
    #MolecularGraphTotalHCountTest.cpp
    #MolecularGraphTotalOrdinaryHCountTest.cpp
    #MolecularGraphImplicitHCountTest.cpp
    #MolecularGraphTotalMassTest.cpp
    #MolecularGraphTotalMassCompositionStringTest.cpp
    #MolecularGraphTotalMassCompositionTest.cpp
    #MolecularGraphTotalMolecularFormulaTest.cpp
    #MolecularGraphTotalElementHistogramTest.cpp
    #MolecularGraphSSSRTest.cpp
    #MolecularGraphRingsTest.cpp
    #MolecularGraphHashCodeTest.cpp

    #AtomIsChemElementTest.cpp
    #AtomIsMainGroupElementTest.cpp
    #AtomIsTransitionMetalTest.cpp
    #AtomIsMetalTest.cpp
    #AtomIsNonMetalTest.cpp
    #AtomIsSemiMetalTest.cpp
    #AtomIsHalogenTest.cpp
    #AtomIsNobleGasTest.cpp
    #AtomVdWRadiusTest.cpp
    #AtomIUPACGroupTest.cpp
    #AtomSymbolTest.cpp
    #AtomTypeTest.cpp

    #MoleculeReactionRoleTest.cpp

    #ReactionComponentCountTest.cpp
    #ReactionReactantCountTest.cpp
    #ReactionAgentCountTest.cpp
    #ReactionProductCountTest.cpp 
   )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(chem-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(chem-test-suite cdpl-chem-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Chem" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/chem-test-suite")
