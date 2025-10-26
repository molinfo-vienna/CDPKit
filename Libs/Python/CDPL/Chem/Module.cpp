/* 
 * Module.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "Module.hpp"
#include "ClassExports.hpp"
#include "FunctionExports.hpp"
#include "NamespaceExports.hpp"
#include "ConverterRegistration.hpp"


BOOST_PYTHON_MODULE(_chem)
{
    using namespace CDPLPythonChem;

    CDPLPython::declareGILNotUsed();

    exportEntity3D();
    exportEntity3DContainer();
    exportAtomContainer();
    exportBondContainer();
    exportAtom();
    exportBond();
    exportMolecularGraph();
    exportMolecule();
    exportReaction();
    exportBasicAtom();
    exportBasicBond();
    exportBasicMolecule();
    exportBasicReaction();
    exportFragment();
    exportElectronSystem();
    exportEntity3DMapping();
    exportAtomMapping();
    exportBondMapping();
    exportAtomBondMapping();
    exportFragmentList();
    exportElectronSystemList();
    exportStringDataBlock();
    exportStereoDescriptor();
    exportMultiConfMoleculeInputProcessor();
    exportDefaultMultiConfMoleculeInputProcessor();
    exportAtomDictionary();

    exportAtom3DCoordinatesFunctor();
    exportAtomConformer3DCoordinatesFunctor();
    exportAtomArray3DCoordinatesFunctor();

    exportMatchConstraintList();
    exportMatchExpressions();
    exportMatchExpressionLists();
    exportANDMatchExpressionLists();
    exportORMatchExpressionLists();
    exportNOTMatchExpressions();
    exportAtomTypeMatchExpression();
    exportAtomEnvironmentMatchExpression();
    exportAtomConfigurationMatchExpression();
    exportBondConfigurationMatchExpression();
    exportBondDirectionMatchExpression();
    exportBondSubstituentDirectionMatchExpression();
    exportBondReactionCenterStatusMatchExpression();
    exportMolecularGraphComponentGroupingMatchExpression();
    exportReactionAtomMappingMatchExpression();
    exportReactionComponentGroupingMatchExpression();

    exportSubstructureSearch();
    exportReactionSubstructureSearch();
    exportCommonConnectedSubstructureSearch();
    exportMaxCommonAtomSubstructureSearch();
    exportMaxCommonBondSubstructureSearch();
    exportAutomorphismGroupSearch();
    exportMultiSubstructureSearch();
    
    exportReactor();
    exportSubstructureEditor();

    exportTopologicalEntityAlignments();
    exportSpatialEntityAlignments();

    exportCompleteRingSet();
    exportAromaticRingSet();
    exportAromaticSSSRSubset();
    exportSmallestSetOfSmallestRings();
    exportExtendedSSSR();
    exportAromaticSubstructure();
    exportCyclicSubstructure();
    exportConnectedSubstructureSet();
    exportComponentSet();
    exportPiElectronSystemList();
    
    exportMorganNumberingCalculator();
    exportCanonicalNumberingCalculator();
    exportCIPPriorityCalculator();
    exportCIPConfigurationLabeler();
    exportAtom2DCoordinatesCalculator();
    exportHydrogen3DCoordinatesCalculator();
    exportBondStereoFlagCalculator();
    exportBondOrderCalculator();
    exportKekuleStructureCalculator();
    exportHashCodeCalculator();
    exportSymmetryClassCalculator();
    exportSurfaceAtomExtractor();

    exportPatternAtomTyper();
    exportSubstructureHistogramCalculator();
    exportTautomerScore();
    exportTautomerGenerator();
    exportDefaultTautomerGenerator();
    exportTautomerizationRule();
    exportPatternBasedTautomerizationRule();
    exportKetoEnolTautomerization();
    exportImineEnamineTautomerization();  
    exportNitrosoOximeTautomerization();  
    exportAmideImidicAcidTautomerization();  
    exportLactamLactimTautomerization();  
    exportKeteneYnolTautomerization();  
    exportNitroAciTautomerization();  
    exportPhosphinicAcidTautomerization();  
    exportSulfenicAcidTautomerization();  
    exportGenericHydrogen13ShiftTautomerization();  
    exportGenericHydrogen15ShiftTautomerization();
    exportConjugatedRingBondPatternSwitching();
    exportFragmentGenerator();
    exportRECAPFragmentGenerator();
    exportBRICSFragmentGenerator();
    exportBemisMurckoAnalyzer();
    exportResonanceStructureGenerator();
    exportStereoisomerGenerator();
    exportChEMBLStandardizer();
    exportProtonationStateStandardizer();
    
    exportMoleculeReader();
    exportMolecularGraphWriter();
    exportReactionReader();
    exportReactionWriter();
    exportINCHIMoleculeReader();
    exportINCHIMolecularGraphWriter();
    exportJMEMoleculeReader();
    exportJMEMolecularGraphWriter();
    exportJMEReactionReader();
    exportJMEReactionWriter();
    exportSMILESMoleculeReader();
    exportSMILESReactionReader();
    exportSMILESMolecularGraphWriter();
    exportSMILESReactionWriter();
    exportSMARTSMoleculeReader();
    exportSMARTSReactionReader();
    exportSMARTSMolecularGraphWriter();
    exportSMARTSReactionWriter();
    exportMOLMoleculeReader();
    exportMOLMolecularGraphWriter();
    exportSDFMoleculeReader();
    exportSDFMolecularGraphWriter();
    exportRXNReactionReader();
    exportRXNReactionWriter();
    exportRDFReactionReader();
    exportRDFReactionWriter();
    exportCDFMoleculeReader();
    exportCDFMolecularGraphWriter();
    exportCDFReactionReader();
    exportCDFReactionWriter();
    exportMOL2MoleculeReader();
    exportMOL2MolecularGraphWriter();
    exportXYZMoleculeReader();
    exportXYZMolecularGraphWriter();
    exportCMLMoleculeReader();
    exportCMLMolecularGraphWriter();
  
    exportMoleculeIOManager();
    exportMolecularGraphIOManager();
    exportReactionIOManager();

    exportMoleculeInputHandler();
    exportMoleculeOutputHandler();
    exportMolecularGraphInputHandler();
    exportMolecularGraphOutputHandler();
    exportReactionInputHandler();
    exportReactionOutputHandler();
    exportINCHIMoleculeInputHandler();
    exportINCHIMolecularGraphOutputHandler();
    exportCDFMoleculeInputHandler();
    exportCDFMolecularGraphOutputHandler();
    exportCDFReactionInputHandler();
    exportCDFReactionOutputHandler();
    exportJMEMoleculeInputHandler();
    exportJMEReactionInputHandler();
    exportJMEMolecularGraphOutputHandler();
    exportJMEReactionOutputHandler();
    exportMOLMoleculeInputHandler();
    exportMOLMolecularGraphOutputHandler();
    exportSDFMoleculeInputHandler();
    exportSDFMolecularGraphOutputHandler();
    exportRXNReactionInputHandler();
    exportRXNReactionOutputHandler();
    exportRDFReactionInputHandler();
    exportRDFReactionOutputHandler();
    exportSMILESMoleculeInputHandler();
    exportSMILESReactionInputHandler();
    exportSMILESMolecularGraphOutputHandler();
    exportSMILESReactionOutputHandler();
    exportSMARTSMoleculeInputHandler();
    exportSMARTSReactionInputHandler();
    exportSMARTSMolecularGraphOutputHandler();
    exportSMARTSReactionOutputHandler();
    exportMOL2MoleculeInputHandler();
    exportMOL2MolecularGraphOutputHandler();
    exportXYZMoleculeInputHandler();
    exportXYZMolecularGraphOutputHandler();
    exportCMLMoleculeInputHandler();
    exportCMLMolecularGraphOutputHandler();

    exportMolecularGraphProperties();
    exportEntity3DProperties();
    exportAtomProperties();
    exportBondProperties();
    exportReactionProperties();
    exportAtomPropertyDefaults();
    exportBondPropertyDefaults();
    exportMolecularGraphPropertyDefaults();
    exportReactionPropertyDefaults();

    exportControlParameters();
    exportControlParameterDefaults();

    exportDataFormats();

    exportAtomPropertyFlags();
    exportBondPropertyFlags();
    exportReactionRoles();
    exportAtomTypes();
    exportAtomConfigurations();
    exportBondConfigurations();
    exportCIPDescriptors();
    exportBondStereoFlags();
    exportHybridizationStates();
    exportReactionCenterStates();
    exportBondDirections();
    exportRadicalTypes();
    exportAtomMatchConstraints();
    exportBondMatchConstraints();
    exportMolecularGraphMatchConstraints();
    exportReactionMatchConstraints();
    exportINCHIReturnCodes();
    exportMDLDataFormatVersions();
    exportMDLParities();
    exportSybylAtomTypes();
    exportSybylBondTypes();
    exportMOL2MoleculeTypes();
    exportMOL2ChargeTypes();
    exportTautomerizationTypes();
    exportRECAPRuleIDs();
    exportRECAPAtomLabels();
    exportBRICSRuleIDs();
    exportBRICSAtomLabels();

    exportControlParameterFunctions();
    exportUtilityFunctions();
    exportAtomContainerFunctions();
    exportEntity3DContainerFunctions();
    exportEntity3DFunctions();
    exportAtomFunctions();
    exportBondFunctions();
    exportMolecularGraphFunctions();
    exportMoleculeFunctions();
    exportFragmentFunctions();
    exportReactionFunctions();

    exportFunctionWrappers();

    registerToPythonConverters();
    registerFromPythonConverters();
}
