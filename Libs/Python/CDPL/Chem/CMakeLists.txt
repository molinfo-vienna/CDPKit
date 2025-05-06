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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
endforeach(PYTHON_FILE)

set(chem_MOD_SRCS
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
    ElectronSystemExport.cpp 
    Entity3DMappingExport.cpp 
    AtomMappingExport.cpp 
    BondMappingExport.cpp 
    AtomBondMappingExport.cpp 
    FragmentListExport.cpp
    ElectronSystemListExport.cpp 
    StringDataBlockExport.cpp
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
    AutomorphismGroupSearchExport.cpp 
    MultiSubstructureSearchExport.cpp
    
    ReactorExport.cpp
    SubstructureEditorExport.cpp 
  
    TopologicalEntityAlignmentExport.cpp    
    SpatialEntityAlignmentExport.cpp
   
    CompleteRingSetExport.cpp 
    AromaticRingSetExport.cpp 
    AromaticSSSRSubsetExport.cpp 
    SmallestSetOfSmallestRingsExport.cpp
    ExtendedSSSRExport.cpp 
    AromaticSubstructureExport.cpp 
    CyclicSubstructureExport.cpp 
    ConnectedSubstructureSetExport.cpp 
    ComponentSetExport.cpp 
    PiElectronSystemListExport.cpp
    
    Atom2DCoordinatesCalculatorExport.cpp 
    Hydrogen3DCoordinatesCalculatorExport.cpp 
    MorganNumberingCalculatorExport.cpp 
    CanonicalNumberingCalculatorExport.cpp 
    CIPPriorityCalculatorExport.cpp
    CIPConfigurationLabelerExport.cpp 
    BondStereoFlagCalculatorExport.cpp 
    BondOrderCalculatorExport.cpp 
    KekuleStructureCalculatorExport.cpp 
    HashCodeCalculatorExport.cpp 
    SymmetryClassCalculatorExport.cpp 
    SurfaceAtomExtractorExport.cpp 
    PatternAtomTyperExport.cpp 
    SubstructureHistogramCalculatorExport.cpp 
    TautomerScoreExport.cpp
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
    ConjugatedRingBondPatternSwitchingExport.cpp 
    FragmentGeneratorExport.cpp
    RECAPFragmentGeneratorExport.cpp
    BRICSFragmentGeneratorExport.cpp
    BemisMurckoAnalyzerExport.cpp
    ResonanceStructureGeneratorExport.cpp
    StereoisomerGeneratorExport.cpp
    ChEMBLStandardizerExport.cpp
    ProtonationStateStandardizerExport.cpp
    
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
    XYZMoleculeInputHandlerExport.cpp 
    XYZMolecularGraphOutputHandlerExport.cpp 
    CMLMoleculeInputHandlerExport.cpp 
    CMLMolecularGraphOutputHandlerExport.cpp 

    MoleculeReaderExport.cpp 
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
    XYZMoleculeReaderExport.cpp 
    XYZMolecularGraphWriterExport.cpp
    CMLMoleculeReaderExport.cpp 
    CMLMolecularGraphWriterExport.cpp
    
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
    CIPDescriptorExport.cpp 
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
    RECAPRuleIDExport.cpp 
    RECAPAtomLabelExport.cpp 
    BRICSRuleIDExport.cpp 
    BRICSAtomLabelExport.cpp 

    ControlParameterFunctionExport.cpp 
    UtilityFunctionExport.cpp 
    AtomContainerFunctionExport.cpp 
    Entity3DContainerFunctionExport.cpp 
    Entity3DFunctionExport.cpp 
    AtomFunctionExport.cpp 
    BondFunctionExport.cpp 
    MolecularGraphFunctionExport.cpp 
    MoleculeFunctionExport.cpp 
    FragmentFunctionExport.cpp 
    ReactionFunctionExport.cpp 

    FunctionWrapperExport.cpp
    Atom3DCoordinatesFunctorExport.cpp
    AtomConformer3DCoordinatesFunctorExport.cpp
    AtomArray3DCoordinatesFunctorExport.cpp

    ToPythonConverterRegistration.cpp 
    FromPythonConverterRegistration.cpp 
   )

add_library(_chem MODULE ${chem_MOD_SRCS})

target_link_libraries(_chem cdpl-chem-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_chem PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_chem PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem/_chem.pyd")
else(WIN32)
  set_target_properties(_chem PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem/_chem.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem" COMPONENT CDPLPythonModules)
install(TARGETS _chem DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
