/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP

#include <string>
#include <cstddef>
#include <ctime>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MDLDataBlock.hpp"
#include "CDPL/Chem/PDBData.hpp"
#include "CDPL/Chem/MassComposition.hpp"
#include "CDPL/Chem/ElementHistogram.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/ControlParameterDefault.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_MOLECULAR_GRAPH_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API const std::string& getName(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setName(MolecularGraph& molgraph, const std::string& name);

		CDPL_CHEM_API void clearName(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasName(const MolecularGraph& molgraph);


		CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const MolecularGraph& molgraph);
	
		CDPL_CHEM_API void setMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr, bool overwrite = true);

		CDPL_CHEM_API void clearMatchConstraints(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasMatchConstraints(const MolecularGraph& molgraph);


		CDPL_CHEM_API const MatchExpression<MolecularGraph>::SharedPointer& getMatchExpression(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMatchExpression(MolecularGraph& molgraph, const MatchExpression<MolecularGraph>::SharedPointer& expr);

		CDPL_CHEM_API void clearMatchExpression(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasMatchExpression(const MolecularGraph& molgraph);

		CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer buildMatchExpression(const MolecularGraph& molgraph);

		CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer buildMatchExpression(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API const FragmentList::SharedPointer& getRings(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setRings(MolecularGraph& molgraph, const FragmentList::SharedPointer& rings);

		CDPL_CHEM_API void clearRings(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasRings(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API const FragmentList::SharedPointer& getSSSR(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setSSSR(MolecularGraph& molgraph, const FragmentList::SharedPointer& sssr);

		CDPL_CHEM_API void clearSSSR(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasSSSR(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API const Fragment::SharedPointer& getCyclicSubstructure(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setCyclicSubstructure(MolecularGraph& molgraph, const Fragment::SharedPointer& substruct);

		CDPL_CHEM_API void clearCyclicSubstructure(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasCyclicSubstructure(const MolecularGraph& molgraph);

		CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(const MolecularGraph& molgraph);

		CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API const FragmentList::SharedPointer& getComponents(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setComponents(MolecularGraph& molgraph, const FragmentList::SharedPointer& comps);

		CDPL_CHEM_API void clearComponents(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasComponents(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API std::size_t getComponentCount(const MolecularGraph& molgraph);


		CDPL_CHEM_API const FragmentList::SharedPointer& getComponentGroups(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setComponentGroups(MolecularGraph& molgraph, const FragmentList::SharedPointer& comp_groups);

		CDPL_CHEM_API void clearComponentGroups(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasComponentGroups(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API std::size_t getConformationIndex(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setConformationIndex(MolecularGraph& molgraph, std::size_t index);

		CDPL_CHEM_API void clearConformationIndex(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasConformationIndex(const MolecularGraph& molgraph);


		CDPL_CHEM_API void extractReactionCenter(const MolecularGraph& molgraph, Fragment& rxn_center);


		CDPL_CHEM_API double getStoichiometricNumber(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setStoichiometricNumber(MolecularGraph& molgraph, double num);

		CDPL_CHEM_API void clearStoichiometricNumber(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasStoichiometricNumber(const MolecularGraph& molgraph);


		CDPL_CHEM_API const std::string& getResidueCode(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setResidueCode(MolecularGraph& molgraph, const std::string& code);

		CDPL_CHEM_API void clearResidueCode(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasResidueCode(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getResidueSequenceNumber(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setResidueSequenceNumber(MolecularGraph& molgraph, std::size_t seq_no);

		CDPL_CHEM_API void clearResidueSequenceNumber(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasResidueSequenceNumber(const MolecularGraph& molgraph);


		CDPL_CHEM_API char getResidueInsertionCode(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setResidueInsertionCode(MolecularGraph& molgraph, char code);

		CDPL_CHEM_API void clearResidueInsertionCode(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasResidueInsertionCode(const MolecularGraph& molgraph);


		CDPL_CHEM_API char getChainID(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setChainID(MolecularGraph& molgraph, char id);

		CDPL_CHEM_API void clearChainID(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasChainID(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getModelNumber(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setModelNumber(MolecularGraph& molgraph, std::size_t model_no);

		CDPL_CHEM_API void clearModelNumber(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasModelNumber(const MolecularGraph& molgraph);
	

		CDPL_CHEM_API const PDBData::SharedPointer& getPDBData(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setPDBData(MolecularGraph& molgraph, const PDBData::SharedPointer& data);

		CDPL_CHEM_API void clearPDBData(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasPDBData(const MolecularGraph& molgraph);


		CDPL_CHEM_API const std::string& getMDLUserInitials(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLUserInitials(MolecularGraph& molgraph, const std::string& initials);

		CDPL_CHEM_API void clearMDLUserInitials(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLUserInitials(const MolecularGraph& molgraph);

	
		CDPL_CHEM_API const std::string& getMDLProgramName(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLProgramName(MolecularGraph& molgraph, const std::string& name);

		CDPL_CHEM_API void clearMDLProgramName(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLProgramName(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::time_t getMDLTimestamp(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLTimestamp(MolecularGraph& molgraph, std::time_t time);

		CDPL_CHEM_API void clearMDLTimestamp(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLTimestamp(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getMDLRegistryNumber(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLRegistryNumber(MolecularGraph& molgraph, std::size_t reg_no);

		CDPL_CHEM_API void clearMDLRegistryNumber(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLRegistryNumber(const MolecularGraph& molgraph);


		CDPL_CHEM_API const std::string& getMDLComment(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLComment(MolecularGraph& molgraph, const std::string& comment);

		CDPL_CHEM_API void clearMDLComment(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLComment(const MolecularGraph& molgraph);


		CDPL_CHEM_API unsigned int getMDLCTABVersion(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLCTABVersion(MolecularGraph& molgraph, unsigned int version);

		CDPL_CHEM_API void clearMDLCTABVersion(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLCTABVersion(const MolecularGraph& molgraph);


		CDPL_CHEM_API const MDLDataBlock::SharedPointer& getMDLStructureData(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLStructureData(MolecularGraph& molgraph, const MDLDataBlock::SharedPointer& data);

		CDPL_CHEM_API void clearMDLStructureData(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLStructureData(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getMDLDimensionality(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLDimensionality(MolecularGraph& molgraph, std::size_t dim);

		CDPL_CHEM_API void clearMDLDimensionality(MolecularGraph& CDPL);	

		CDPL_CHEM_API bool hasMDLDimensionality(const MolecularGraph& molgraph);


		CDPL_CHEM_API long getMDLScalingFactor1(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLScalingFactor1(MolecularGraph& molgraph, long factor);

		CDPL_CHEM_API void clearMDLScalingFactor1(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLScalingFactor1(const MolecularGraph& molgraph);

	
		CDPL_CHEM_API double getMDLScalingFactor2(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLScalingFactor2(MolecularGraph& molgraph, double factor);

		CDPL_CHEM_API void clearMDLScalingFactor2(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLScalingFactor2(const MolecularGraph& molgraph);

	
		CDPL_CHEM_API double getMDLEnergy(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLEnergy(MolecularGraph& molgraph, double energy);

		CDPL_CHEM_API void clearMDLEnergy(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLEnergy(const MolecularGraph& molgraph);


		CDPL_CHEM_API bool getMDLChiralFlag(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setMDLChiralFlag(MolecularGraph& molgraph, bool flag);

		CDPL_CHEM_API void clearMDLChiralFlag(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasMDLChiralFlag(const MolecularGraph& molgraph);


		CDPL_CHEM_API void buildAdjacencyMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

		CDPL_CHEM_API void buildIncidenceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

		CDPL_CHEM_API void buildBondMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

		CDPL_CHEM_API void buildBondElectronMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

	
		CDPL_CHEM_API const Math::ULMatrix::SharedPointer& getTopologicalDistanceMatrix(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setTopologicalDistanceMatrix(MolecularGraph& molgraph, const Math::ULMatrix::SharedPointer& mtx);

		CDPL_CHEM_API void clearTopologicalDistanceMatrix(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasTopologicalDistanceMatrix(const MolecularGraph& molgraph);

		CDPL_CHEM_API Math::ULMatrix::SharedPointer calcTopologicalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);


		CDPL_CHEM_API const Math::DMatrix::SharedPointer& getGeometricalDistanceMatrix(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setGeometricalDistanceMatrix(MolecularGraph& molgraph, const Math::DMatrix::SharedPointer& mtx);

		CDPL_CHEM_API void clearGeometricalDistanceMatrix(MolecularGraph& molgraph);
	
		CDPL_CHEM_API bool hasGeometricalDistanceMatrix(const MolecularGraph& molgraph);

		CDPL_CHEM_API Math::DMatrix::SharedPointer calcGeometricalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API std::size_t calcTopologicalRadius(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcTopologicalDiameter(const MolecularGraph& molgraph);


		CDPL_CHEM_API double calcRingComplexity(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcKierShape1(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcKierShape2(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcKierShape3(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcWienerIndex(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcRandicIndex(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcZagrebIndex1(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcZagrebIndex2(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcTotalWalkCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcCyclomaticNumber(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getAtomCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getAtomCount(const MolecularGraph& molgraph, unsigned int type);

		CDPL_CHEM_API std::size_t getImplicitHydrogenCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getOrdinaryHydrogenCount(const MolecularGraph& molgraph, unsigned int flags = AtomPropertyFlag::DEFAULT);

		CDPL_CHEM_API std::size_t getExplicitOrdinaryHydrogenCount(const MolecularGraph& molgraph, unsigned int flags = AtomPropertyFlag::DEFAULT);

		CDPL_CHEM_API std::size_t getChainAtomCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getHydrogenAcceptorAtomCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getHydrogenDonorAtomCount(const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getBondCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getBondCount(const MolecularGraph& molgraph, std::size_t order);

		CDPL_CHEM_API std::size_t getHydrogenBondCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getChainBondCount(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getRotatableBondCount(const MolecularGraph& molgraph);

	
		CDPL_CHEM_API double calcMass(const MolecularGraph& molgraph);

		CDPL_CHEM_API void calcMassComposition(const MolecularGraph& molgraph, MassComposition& comp);
	
		CDPL_CHEM_API void buildMassCompositionString(const MolecularGraph& molgraph, std::string& comp);

		CDPL_CHEM_API void buildMolecularFormula(const MolecularGraph& molgraph, std::string& formula);

		CDPL_CHEM_API void buildElementHistogram(const MolecularGraph& molgraph, ElementHistogram& hist);

	
		CDPL_CHEM_API const FragmentList::SharedPointer& getAromaticRings(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setAromaticRings(MolecularGraph& molgraph, const FragmentList::SharedPointer& rings);

		CDPL_CHEM_API void clearAromaticRings(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasAromaticRings(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveAromaticRings(const MolecularGraph& molgraph);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveAromaticRings(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API const Fragment::SharedPointer& getAromaticSubstructure(const MolecularGraph& molgraph);

		CDPL_CHEM_API void setAromaticSubstructure(MolecularGraph& molgraph, const Fragment::SharedPointer& substruct);

		CDPL_CHEM_API void clearAromaticSubstructure(MolecularGraph& molgraph);

		CDPL_CHEM_API bool hasAromaticSubstructure(const MolecularGraph& molgraph);

		CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(const MolecularGraph& molgraph);

		CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API std::size_t buildAtomTypeMask(const MolecularGraph& molgraph, Util::BitSet& mask, unsigned int atom_type);


		CDPL_CHEM_API bool generateSMILES(const MolecularGraph& molgraph, std::string& smiles, bool canonical = false, 
										  bool ord_h_deplete = true, unsigned int atom_flags = AtomPropertyFlag::DEFAULT, 
										  unsigned int bond_flags = BondPropertyFlag::DEFAULT);
	
		CDPL_CHEM_API int generateINCHI(const MolecularGraph& molgraph, std::string& inchi, 
										const std::string& options = ControlParameterDefault::INCHI_OUTPUT_OPTIONS,
										std::size_t dim = 0);

		CDPL_CHEM_API int generateINCHIKey(const MolecularGraph& molgraph, std::string& inchi_key);

		CDPL_CHEM_API Base::uint64 calcHashCode(const MolecularGraph& molgraph, unsigned int atom_flags = AtomPropertyFlag::DEFAULT, 
												unsigned int bond_flags = BondPropertyFlag::DEFAULT,
												bool global_stereo = true, bool ord_h_deplete = true);


		CDPL_CHEM_API double calcXLogP(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcLogS(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcTPSA(const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t calcRuleOfFiveScore(const MolecularGraph& molgraph);
		
		CDPL_CHEM_API double calcMeanPolarizability(const MolecularGraph& molgraph);

		CDPL_CHEM_API double calcMolecularComplexity(const MolecularGraph& molgraph);
		
		CDPL_CHEM_API void calcPEOECharges(MolecularGraph& molgraph, bool overwrite, std::size_t num_iter = 6, 
										   double damping = 0.5);


		CDPL_CHEM_API void generate2DCoordinates(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API void generateHydrogen3DCoordinates(MolecularGraph& molgraph, bool undef_only = true);


		CDPL_CHEM_API void generateBond2DStereoFlags(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void generateBondDirections(MolecularGraph& molgraph, bool overwrite, bool ring_bonds = true, 
												  std::size_t min_ring_size = 8);

		
		CDPL_CHEM_API void calcCIPPriorities(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void perceiveSymmetryClasses(MolecularGraph& molgraph, bool overwrite, 
												   unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
												   unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool inc_impl_h = true);

		CDPL_CHEM_API void generateCanonicalNumbering(MolecularGraph& molgraph, bool overwrite,
													  unsigned int atom_flags = AtomPropertyFlag::DEFAULT, 
													  unsigned int bond_flags = BondPropertyFlag::DEFAULT);

		CDPL_CHEM_API void generateMorganNumbering(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API void calcImplicitHydrogenCounts(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void calcFormalCharges(MolecularGraph& molgraph, bool overwrite);
	
		CDPL_CHEM_API void perceiveHybridizationStates(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void perceiveBondOrders(MolecularGraph& molgraph, bool undef_only = true);

		CDPL_CHEM_API void kekulizeBonds(MolecularGraph& molgraph);

		CDPL_CHEM_API void perceiveAtomStereoCenters(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void perceiveBondStereoCenters(MolecularGraph& molgraph, bool overwrite,
													 std::size_t min_ring_size = 8);

		CDPL_CHEM_API void calcMDLParities(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void calcAtomStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1);

		CDPL_CHEM_API void calcAtomStereoDescriptorsFromMDLParities(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void calcBondStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1, 
													 std::size_t min_ring_size = 8);

		CDPL_CHEM_API void calcAtomCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void calcBondCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void setAtomMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr, 
												   bool overwrite);

		CDPL_CHEM_API void setBondMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr, 
												   bool overwrite);
	
		CDPL_CHEM_API void buildMatchExpressions(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void buildMatchExpressionStrings(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void initSubstructureSearchQuery(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void initSubstructureSearchTarget(MolecularGraph& molgraph, bool overwrite);


		CDPL_CHEM_API void setAromaticityFlags(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void setRingFlags(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void setAtomTypesFromSymbols(MolecularGraph& molgraph, bool overwrite);

		CDPL_CHEM_API void setAtomSymbolsFromTypes(MolecularGraph& molgraph, bool overwrite);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
 
