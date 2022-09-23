# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
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

    ReactorExport.cpp 
  
    TopologicalEntityAlignmentExport.cpp	
    SpatialEntityAlignmentExport.cpp
   
    CompleteRingSetExport.cpp 
    AromaticRingSetExport.cpp 
    AromaticSSSRSubsetExport.cpp 
    SmallestSetOfSmallestRingsExport.cpp 
    AromaticSubstructureExport.cpp 
    CyclicSubstructureExport.cpp 
    ConnectedSubstructureSetExport.cpp 
    ComponentSetExport.cpp 
   
    Atom2DCoordinatesCalculatorExport.cpp 
    Hydrogen3DCoordinatesCalculatorExport.cpp 
    MorganNumberingCalculatorExport.cpp 
    CanonicalNumberingCalculatorExport.cpp 
    CIPPriorityCalculatorExport.cpp 
    BondStereoFlagCalculatorExport.cpp 
    BondDirectionCalculatorExport.cpp 
    BondOrderCalculatorExport.cpp 
    KekuleStructureCalculatorExport.cpp 
    HashCodeCalculatorExport.cpp 
    SymmetryClassCalculatorExport.cpp 
    SurfaceAtomExtractorExport.cpp 
    PatternAtomTyperExport.cpp 
    SubstructureHistogramCalculatorExport.cpp 
    GeneralizedBellAtomDensityExport.cpp
    AtomDensityGridCalculatorExport.cpp
    BuriednessScoreExport.cpp
    BuriednessGridCalculatorExport.cpp
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
    FragmentGeneratorExport.cpp
    RECAPFragmentGeneratorExport.cpp
    BRICSFragmentGeneratorExport.cpp
    ResonanceStructureGeneratorExport.cpp
    
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
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_chem.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_chem PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_chem PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_chem.so")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_chem PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

IF(NOT APPLE)
  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)
ENDIF(NOT APPLE)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _chem DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Chem" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
