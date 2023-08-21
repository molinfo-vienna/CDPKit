##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp
    BasicReactionTest.cpp
    BasicMoleculeTest.cpp
    BasicAtomTest.cpp
    BasicBondTest.cpp
    ReactionTest.cpp
    MoleculeTest.cpp
    AtomTest.cpp
    BondTest.cpp
    AtomContainerTest.cpp
    BondContainerTest.cpp
    FragmentTest.cpp
    AtomBondMappingTest.cpp
    DataFormatsTest.cpp
    StringDataBlockTest.cpp
    AtomDictionaryTest.cpp

    JMEMolecularGraphOutputHandlerTest.cpp
    MOLMolecularGraphOutputHandlerTest.cpp
    SDFMolecularGraphOutputHandlerTest.cpp
    SMILESMolecularGraphOutputHandlerTest.cpp
    SMARTSMolecularGraphOutputHandlerTest.cpp
    
    JMEMoleculeInputHandlerTest.cpp
    MOLMoleculeInputHandlerTest.cpp
    SDFMoleculeInputHandlerTest.cpp
    SMILESMoleculeInputHandlerTest.cpp
    SMARTSMoleculeInputHandlerTest.cpp

    JMEReactionOutputHandlerTest.cpp
    RXNReactionOutputHandlerTest.cpp
    RDFReactionOutputHandlerTest.cpp
    SMILESReactionOutputHandlerTest.cpp
    SMARTSReactionOutputHandlerTest.cpp

#    JMEReactionInputHandlerTest.cpp
#    RXNReactionInputHandlerTest.cpp
#    RDFReactionInputHandlerTest.cpp
#    SMILESReactionInputHandlerTest.cpp
#    SMARTSReactionInputHandlerTest.cpp

    MatchConstraintListTest.cpp          # TODO
    MatchExpressionTest.cpp
    MatchExpressionListTest.cpp
    #PropertyMatchExpressionTest.cpp
    ANDMatchExpressionListTest.cpp
    ORMatchExpressionListTest.cpp
    NOTMatchExpressionTest.cpp

    #HashCodeCalculatorTest.cpp 
    
    CompleteRingSetTest.cpp 
    SmallestSetOfSmallestRingsTest.cpp 
    ConnectedSubstructureSetTest.cpp 
    ComponentSetTest.cpp 

    #AtomFunctionsTest.cpp
    #BondFunctionsTest.cpp
    MoleculeHydrogenManipulationFunctionsTest.cpp
    FragmentHydrogenManipulationFunctionsTest.cpp
    #ReactionFunctionsTest.cpp

    AtomHybridizationPerceptionTest.cpp
    #AtomSymbolTest.cpp
    #AtomTypeTest.cpp

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

    #MoleculeReactionRoleTest.cpp

    #ReactionComponentCountTest.cpp
    #ReactionReactantCountTest.cpp
    #ReactionAgentCountTest.cpp
    #ReactionProductCountTest.cpp 
    )

SET(CMAKE_BUILD_TYPE "Debug")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(chem-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(chem-test-suite cdpl-chem-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Chem" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/chem-test-suite")
