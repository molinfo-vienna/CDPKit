/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ClassExports.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_CHEM_CLASSEXPORTS_HPP
#define CDPL_PYTHON_CHEM_CLASSEXPORTS_HPP


namespace CDPLPythonChem
{

	void exportEntity3D();
	void exportEntity3DContainer();
	void exportAtomContainer();
	void exportBondContainer();
	void exportAtom();
	void exportBond();
	void exportMolecularGraph();
	void exportMolecule();
	void exportReaction();
	void exportBasicAtom();
	void exportBasicBond();
	void exportBasicMolecule();
	void exportBasicReaction();
	void exportFragment();
	void exportEntity3DMapping();
	void exportAtomMapping();
	void exportBondMapping();
	void exportAtomBondMapping();
	void exportFragmentList();
	void exportMDLDataBlock();
	void exportMassComposition();
	void exportElementHistogram();
	void exportStereoDescriptor();
	void exportMultiConfMoleculeInputProcessor();
	void exportDefaultMultiConfMoleculeInputProcessor();
	void exportAtomDictionary();

	void exportBoostFunctionWrappers();

	void exportMatchConstraintList();
	void exportMatchExpressions();
	void exportMatchExpressionLists();
	void exportANDMatchExpressionLists();
	void exportORMatchExpressionLists();
	void exportNOTMatchExpressions();
	void exportAtomTypeMatchExpression();
	void exportAtomEnvironmentMatchExpression();
	void exportAtomConfigurationMatchExpression();
	void exportBondConfigurationMatchExpression();
	void exportBondDirectionMatchExpression();
	void exportBondSubstituentDirectionMatchExpression();
	void exportBondReactionCenterStatusMatchExpression();
	void exportMolecularGraphComponentGroupingMatchExpression();
	void exportReactionAtomMappingMatchExpression();
	void exportReactionComponentGroupingMatchExpression();

	void exportSubstructureSearch();
	void exportReactionSubstructureSearch();
	void exportCommonConnectedSubstructureSearch();
	void exportMaxCommonAtomSubstructureSearch();
	void exportMaxCommonBondSubstructureSearch();

	void exportReactor();

	void exportTopologicalEntityAlignments();
	void exportGeometricalEntityAlignments();
	
	void exportCompleteRingSet();
	void exportAromaticRingSet();
	void exportAromaticSSSRSubset();
	void exportSmallestSetOfSmallestRings();
	void exportAromaticSubstructure();
	void exportCyclicSubstructure();
	void exportConnectedSubstructureSet();
	void exportComponentSet();

	void exportMorganNumberingGenerator();
	void exportCanonicalNumberingGenerator();
	void exportCIPPriorityCalculator();
	void exportAtom2DCoordinatesGenerator();
	void exportHydrogen3DCoordinatesGenerator();
	void exportBondStereoFlagGenerator();
	void exportBondOrderGenerator();
	void exportKekuleStructureGenerator();
	void exportBondDirectionGenerator();
	void exportXLogPCalculator();
	void exportTPSACalculator();
	void exportHashCodeCalculator();
	void exportSymmetryClassCalculator();
	void exportLogSCalculator();
	void exportMolecularComplexityCalculator();
	void exportPEOEChargeCalculator();
	void exportDaylightFingerprintGenerator();
	void exportAutoCorrelationVectorCalculator();
	void exportRDFCodeCalculator();
	void exportBurdenMatrixGenerator();
	void exportBCUTDescriptorCalculator();

	void exportMoleculeReader();
	void exportMoleculeWriter();
	void exportMolecularGraphReader();
	void exportMolecularGraphWriter();
	void exportReactionReader();
	void exportReactionWriter();
	void exportINCHIMoleculeReader();
	void exportINCHIMolecularGraphWriter();
	void exportJMEMoleculeReader();
	void exportJMEMolecularGraphWriter();
	void exportJMEReactionReader();
	void exportJMEReactionWriter();
	void exportSMILESMoleculeReader();
	void exportSMILESReactionReader();
	void exportSMILESMolecularGraphWriter();
	void exportSMILESReactionWriter();
	void exportSMARTSMoleculeReader();
	void exportSMARTSReactionReader();
	void exportSMARTSMolecularGraphWriter();
	void exportSMARTSReactionWriter();
	void exportMOLMoleculeReader();
	void exportMOLMolecularGraphWriter();
	void exportSDFMoleculeReader();
	void exportSDFMolecularGraphWriter();
	void exportRXNReactionReader();
	void exportRXNReactionWriter();
	void exportRDFReactionReader();
	void exportRDFReactionWriter();
	void exportCDFMoleculeReader();
	void exportCDFMolecularGraphWriter();

	void exportMoleculeIOManager();
	void exportMolecularGraphIOManager();
	void exportReactionIOManager();

	void exportMoleculeInputHandler();
	void exportMoleculeOutputHandler();
	void exportMolecularGraphInputHandler();
	void exportMolecularGraphOutputHandler();
	void exportReactionInputHandler();
	void exportReactionOutputHandler();
	void exportINCHIMoleculeInputHandler();
	void exportINCHIMolecularGraphOutputHandler();
	void exportCDFMoleculeInputHandler();
	void exportCDFMolecularGraphOutputHandler();
	void exportJMEMoleculeInputHandler();
	void exportJMEReactionInputHandler();
	void exportJMEMolecularGraphOutputHandler();
	void exportJMEReactionOutputHandler();
	void exportMOLMoleculeInputHandler();
	void exportMOLMolecularGraphOutputHandler();
	void exportSDFMoleculeInputHandler();
	void exportSDFMolecularGraphOutputHandler();
	void exportRXNReactionInputHandler();
	void exportRXNReactionOutputHandler();
	void exportRDFReactionInputHandler();
	void exportRDFReactionOutputHandler();
	void exportSMILESMoleculeInputHandler();
	void exportSMILESReactionInputHandler();
	void exportSMILESMolecularGraphOutputHandler();
	void exportSMILESReactionOutputHandler();
	void exportSMARTSMoleculeInputHandler();
	void exportSMARTSReactionInputHandler();
	void exportSMARTSMolecularGraphOutputHandler();
	void exportSMARTSReactionOutputHandler();
}

#endif // CDPL_PYTHON_CHEM_CLASSEXPORTS_HPP
