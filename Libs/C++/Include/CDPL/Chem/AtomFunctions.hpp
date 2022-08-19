/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctions.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_CHEM_ATOMFUNCTIONS_HPP
#define CDPL_CHEM_ATOMFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include <boost/type_traits/is_const.hpp> 
#include <boost/mpl/if.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/AtomPriorityFunction.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class StereoDescriptor;
		
	
		CDPL_CHEM_API const std::string& getName(const Atom& atom);

		CDPL_CHEM_API void setName(Atom& atom, const std::string& name);

		CDPL_CHEM_API void clearName(Atom& atom);

		CDPL_CHEM_API bool hasName(const Atom& atom);


		CDPL_CHEM_API const std::string& getSymbol(const Atom& atom);

		CDPL_CHEM_API void setSymbol(Atom& atom, const std::string& symbol);

		CDPL_CHEM_API void clearSymbol(Atom& atom);

		CDPL_CHEM_API bool hasSymbol(const Atom& atom);

		CDPL_CHEM_API const std::string& getSymbolForType(const Atom& atom);


		CDPL_CHEM_API unsigned int getType(const Atom& atom);

		CDPL_CHEM_API void setType(Atom& atom, unsigned int type);

		CDPL_CHEM_API void clearType(Atom& atom);

		CDPL_CHEM_API bool hasType(const Atom& atom);

		CDPL_CHEM_API unsigned int getTypeForSymbol(const Atom& atom);
		
		CDPL_CHEM_API unsigned int getGenericType(const Atom& atom);//move


		CDPL_CHEM_API long getFormalCharge(const Atom& atom);

		CDPL_CHEM_API void setFormalCharge(Atom& atom, long charge);

		CDPL_CHEM_API void clearFormalCharge(Atom& atom);

		CDPL_CHEM_API bool hasFormalCharge(const Atom& atom);

		CDPL_CHEM_API long calcFormalCharge(const Atom& atom, const MolecularGraph& molgraph);


		CDPL_CHEM_API std::size_t getIsotope(const Atom& atom);

		CDPL_CHEM_API void setIsotope(Atom& atom, std::size_t isotope);

		CDPL_CHEM_API void clearIsotope(Atom& atom);

		CDPL_CHEM_API bool hasIsotope(const Atom& atom);


		CDPL_CHEM_API unsigned int getRadicalType(const Atom& atom);

		CDPL_CHEM_API void setRadicalType(Atom& atom, unsigned int type);

		CDPL_CHEM_API void clearRadicalType(Atom& atom);

		CDPL_CHEM_API bool hasRadicalType(const Atom& atom);


		CDPL_CHEM_API unsigned int getHybridizationState(const Atom& atom);

		CDPL_CHEM_API void setHybridizationState(Atom& atom, unsigned int state);

		CDPL_CHEM_API void clearHybridizationState(Atom& atom);

		CDPL_CHEM_API bool hasHybridizationState(const Atom& atom);

		CDPL_CHEM_API unsigned int perceiveHybridizationState(const Atom& atom, const MolecularGraph& molgraph);


		CDPL_CHEM_API double getAtomicWeight(const Atom& atom);//move

		CDPL_CHEM_API std::size_t getIUPACGroup(const Atom& atom);//move

		CDPL_CHEM_API double getVdWRadius(const Atom& atom);//move Internal

		CDPL_CHEM_API double getCovalentRadius(const Atom& atom, std::size_t order);//move

		CDPL_CHEM_API double getAllredRochowElectronegativity(const Atom& atom);//move

		CDPL_CHEM_API const std::string& getElementName(const Atom& atom);//move

		CDPL_CHEM_API std::size_t getElementValenceElectronCount(const Atom& atom);//move

		CDPL_CHEM_API bool isChemicalElement(const Atom& atom);//move

		CDPL_CHEM_API bool isMainGroupElement(const Atom& atom);//move

		CDPL_CHEM_API bool isMetal(const Atom& atom);//move

		CDPL_CHEM_API bool isTransitionMetal(const Atom& atom);//move

		CDPL_CHEM_API bool isNonMetal(const Atom& atom);//move

		CDPL_CHEM_API bool isSemiMetal(const Atom& atom);//move

		CDPL_CHEM_API bool isHalogen(const Atom& atom);//move

		CDPL_CHEM_API bool isNobleGas(const Atom& atom);//move


		CDPL_CHEM_API bool getRingFlag(const Atom& atom);

		CDPL_CHEM_API void setRingFlag(Atom& atom, bool in_ring);

		CDPL_CHEM_API void clearRingFlag(Atom& atom);
	
		CDPL_CHEM_API bool hasRingFlag(const Atom& atom);


		CDPL_CHEM_API bool isInRing(const Atom& atom, const MolecularGraph& molgraph);

		CDPL_CHEM_API bool isInRingOfSize(const Atom& atom, const MolecularGraph& molgraph, std::size_t size);

		CDPL_CHEM_API std::size_t getNumContainingSSSRRings(const Atom& atom, const MolecularGraph& molgraph);


		CDPL_CHEM_API bool isInFragmentOfSize(const Atom& atom, const FragmentList& frag_list, std::size_t size);

		CDPL_CHEM_API std::size_t getSizeOfSmallestContainingFragment(const Atom& atom, const FragmentList& frag_list);

		CDPL_CHEM_API std::size_t getSizeOfLargestContainingFragment(const Atom& atom, const FragmentList& frag_list);

		CDPL_CHEM_API std::size_t getNumContainingFragments(const Atom& atom, const FragmentList& frag_list);

		CDPL_CHEM_API void getContainingFragments(const Atom& atom, const FragmentList& frag_list, FragmentList& cont_frag_list, bool append = false);


		CDPL_CHEM_API bool getAromaticityFlag(const Atom& atom);

		CDPL_CHEM_API void setAromaticityFlag(Atom& atom, bool aromatic);

		CDPL_CHEM_API void clearAromaticityFlag(Atom& atom);
	
		CDPL_CHEM_API bool hasAromaticityFlag(const Atom& atom);


		CDPL_CHEM_API bool isOrdinaryHydrogen(const Atom& atom, const MolecularGraph& molgraph, 
											  unsigned int flags = AtomPropertyFlag::DEFAULT);// move Internal
		

		CDPL_CHEM_API bool isHeavy(const Atom& atom);// move Internal

		CDPL_CHEM_API bool isUnsaturated(const Atom& atom, const MolecularGraph& molgraph);// move Internal

		CDPL_CHEM_API bool isHydrogenAcceptor(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API bool isHydrogenDonor(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API bool isCarbonylLikeAtom(const Atom& atom, const MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);// move

		CDPL_CHEM_API bool isAmideCenterAtom(const Atom& atom, const MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);// move

		CDPL_CHEM_API bool isAmideNitrogen(const Atom& atom, const MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);// move

		CDPL_CHEM_API bool isInvertibleNitrogen(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API bool isPlanarNitrogen(const Atom& atom, const MolecularGraph& molgraph);// move


		CDPL_CHEM_API std::size_t calcExplicitValence(const Atom& atom, const MolecularGraph& molgraph);// move
	
		CDPL_CHEM_API std::size_t calcValence(const Atom& atom, const MolecularGraph& molgraph);// move

	
		CDPL_CHEM_API std::size_t calcFreeValenceElectronCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t calcValenceElectronCount(const Atom& atom);// move


		CDPL_CHEM_API std::size_t getUnpairedElectronCount(const Atom& atom);

		CDPL_CHEM_API void setUnpairedElectronCount(Atom& atom, std::size_t count);

		CDPL_CHEM_API void clearUnpairedElectronCount(Atom& atom);

		CDPL_CHEM_API bool hasUnpairedElectronCount(const Atom& atom);


		CDPL_CHEM_API std::size_t getImplicitHydrogenCount(const Atom& atom);

		CDPL_CHEM_API void setImplicitHydrogenCount(Atom& atom, std::size_t count);

		CDPL_CHEM_API void clearImplicitHydrogenCount(Atom& atom);

		CDPL_CHEM_API bool hasImplicitHydrogenCount(const Atom& atom);

		CDPL_CHEM_API std::size_t calcImplicitHydrogenCount(const Atom& atom, const MolecularGraph& molgraph);

		CDPL_CHEM_API std::size_t getOrdinaryHydrogenCount(const Atom& atom, const MolecularGraph& molgraph, 
														   unsigned int flags = AtomPropertyFlag::DEFAULT);// move Internal


		CDPL_CHEM_API std::size_t getExplicitAtomCount(const Atom& atom, const MolecularGraph& molgraph, unsigned int type, bool strict = true);//move

		CDPL_CHEM_API std::size_t getAtomCount(const Atom& atom, const MolecularGraph& molgraph, unsigned int type, bool strict = true);//move

		CDPL_CHEM_API std::size_t getExplicitChainAtomCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getChainAtomCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getRingAtomCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getAromaticAtomCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getHeavyAtomCount(const Atom& atom, const MolecularGraph& molgraph);// move


		CDPL_CHEM_API std::size_t getExplicitBondCount(const Atom& atom, const MolecularGraph& molgraph);//move

		CDPL_CHEM_API std::size_t getExplicitBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order);//move

		CDPL_CHEM_API std::size_t getExplicitBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);//move

		CDPL_CHEM_API std::size_t getBondCount(const Atom& atom, const MolecularGraph& molgraph);//move

		CDPL_CHEM_API std::size_t getBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order);//move

		CDPL_CHEM_API std::size_t getBondCount(const Atom& atom, const MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);//move Internal

		CDPL_CHEM_API std::size_t getExplicitChainBondCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getChainBondCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getRingBondCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getAromaticBondCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getHeavyBondCount(const Atom& atom, const MolecularGraph& molgraph);// move

		CDPL_CHEM_API std::size_t getRotatableBondCount(const Atom& atom, const MolecularGraph& molgraph, bool inc_h_rotors, bool inc_amide_bonds);// move


		CDPL_CHEM_API const Math::Vector2D& get2DCoordinates(const Atom& atom);

		CDPL_CHEM_API void set2DCoordinates(Atom& atom, const Math::Vector2D& coords);

		CDPL_CHEM_API void clear2DCoordinates(Atom& atom);
	
		CDPL_CHEM_API bool has2DCoordinates(const Atom& atom);


		CDPL_CHEM_API const Math::Vector3D& getConformer3DCoordinates(const Atom& atom, std::size_t conf_idx);
	

		CDPL_CHEM_API const Math::Vector3DArray::SharedPointer& get3DCoordinatesArray(const Atom& atom);

		CDPL_CHEM_API void set3DCoordinatesArray(Atom& atom, const Math::Vector3DArray::SharedPointer& coords_array);

		CDPL_CHEM_API void clear3DCoordinatesArray(Atom& atom);
	
		CDPL_CHEM_API bool has3DCoordinatesArray(const Atom& atom);


		CDPL_CHEM_API std::size_t getMorganNumber(const Atom& atom);

		CDPL_CHEM_API void setMorganNumber(Atom& atom, std::size_t num);

		CDPL_CHEM_API void clearMorganNumber(Atom& atom);
	
		CDPL_CHEM_API bool hasMorganNumber(const Atom& atom);


		CDPL_CHEM_API std::size_t getCanonicalNumber(const Atom& atom);

		CDPL_CHEM_API void setCanonicalNumber(Atom& atom, std::size_t num);

		CDPL_CHEM_API void clearCanonicalNumber(Atom& atom);
	
		CDPL_CHEM_API bool hasCanonicalNumber(const Atom& atom);


		CDPL_CHEM_API std::size_t getCIPPriority(const Atom& atom);

		CDPL_CHEM_API void setCIPPriority(Atom& atom, std::size_t priority);

		CDPL_CHEM_API void clearCIPPriority(Atom& atom);
	
		CDPL_CHEM_API bool hasCIPPriority(const Atom& atom);


		CDPL_CHEM_API std::size_t getSymmetryClass(const Atom& atom);

		CDPL_CHEM_API void setSymmetryClass(Atom& atom, std::size_t class_id);

		CDPL_CHEM_API void clearSymmetryClass(Atom& atom);
	
		CDPL_CHEM_API bool hasSymmetryClass(const Atom& atom);


		CDPL_CHEM_API unsigned int getCIPConfiguration(const Atom& atom);

		CDPL_CHEM_API void setCIPConfiguration(Atom& atom, unsigned int config);

		CDPL_CHEM_API void clearCIPConfiguration(Atom& atom);
	
		CDPL_CHEM_API bool hasCIPConfiguration(const Atom& atom);

		CDPL_CHEM_API unsigned int calcCIPConfiguration(const Atom& atom, const MolecularGraph& molgraph);

		CDPL_CHEM_API unsigned int calcCIPConfiguration(const Atom& atom, const MolecularGraph& molgraph, const AtomPriorityFunction& cip_pri_func);
	

		CDPL_CHEM_API const StereoDescriptor& getStereoDescriptor(const Atom& atom);

		CDPL_CHEM_API void setStereoDescriptor(Atom& atom, const StereoDescriptor& descr);

		CDPL_CHEM_API void clearStereoDescriptor(Atom& atom);
	
		CDPL_CHEM_API bool hasStereoDescriptor(const Atom& atom);

		CDPL_CHEM_API StereoDescriptor calcStereoDescriptor(const Atom& atom, const MolecularGraph& molgraph, std::size_t dim = 1);

		CDPL_CHEM_API StereoDescriptor calcStereoDescriptorFromMDLParity(const Atom& atom, const MolecularGraph& molgraph);

		CDPL_CHEM_API unsigned int calcAtomConfiguration(const Atom& atom, const MolecularGraph& molgraph, const StereoDescriptor& descr,
														 const Math::Vector3DArray& coords);


		CDPL_CHEM_API bool getStereoCenterFlag(const Atom& atom);

		CDPL_CHEM_API void setStereoCenterFlag(Atom& atom, bool is_center);

		CDPL_CHEM_API void clearStereoCenterFlag(Atom& atom);
	
		CDPL_CHEM_API bool hasStereoCenterFlag(const Atom& atom);

		CDPL_CHEM_API bool isStereoCenter(const Atom& atom, const MolecularGraph& molgraph, 
										  bool check_cip_sym = true, bool check_acyclic_subst_sym_only = false);
	

		CDPL_CHEM_API unsigned int getSybylType(const Atom& atom);

		CDPL_CHEM_API void setSybylType(Atom& atom, unsigned int type);

		CDPL_CHEM_API void clearSybylType(Atom& atom);
	
		CDPL_CHEM_API bool hasSybylType(const Atom& atom);

		CDPL_CHEM_API unsigned int perceiveSybylType(const Atom& atom, const MolecularGraph& molgraph);
	

		CDPL_CHEM_API const std::string& getMOL2Name(const Atom& atom);

		CDPL_CHEM_API void setMOL2Name(Atom& atom, const std::string& name);

		CDPL_CHEM_API void clearMOL2Name(Atom& atom);
	
		CDPL_CHEM_API bool hasMOL2Name(const Atom& atom);


		CDPL_CHEM_API double getMOL2Charge(const Atom& atom);

		CDPL_CHEM_API void setMOL2Charge(Atom& atom, double charge);

		CDPL_CHEM_API void clearMOL2Charge(Atom& atom);	

		CDPL_CHEM_API bool hasMOL2Charge(const Atom& atom);


		CDPL_CHEM_API std::size_t getMOL2SubstructureID(const Atom& atom);

		CDPL_CHEM_API void setMOL2SubstructureID(Atom& atom, std::size_t id);

		CDPL_CHEM_API void clearMOL2SubstructureID(Atom& atom);
	
		CDPL_CHEM_API bool hasMOL2SubstructureID(const Atom& atom);
	

		CDPL_CHEM_API const std::string& getMOL2SubstructureName(const Atom& atom);

		CDPL_CHEM_API void setMOL2SubstructureName(Atom& atom, const std::string& id);

		CDPL_CHEM_API void clearMOL2SubstructureName(Atom& atom);
	
		CDPL_CHEM_API bool hasMOL2SubstructureName(const Atom& atom);


		CDPL_CHEM_API const std::string& getMOL2SubstructureSubtype(const Atom& atom);

		CDPL_CHEM_API void setMOL2SubstructureSubtype(Atom& atom, const std::string& subtype);

		CDPL_CHEM_API void clearMOL2SubstructureSubtype(Atom& atom);
	
		CDPL_CHEM_API bool hasMOL2SubstructureSubtype(const Atom& atom);


		CDPL_CHEM_API const std::string& getMOL2SubstructureChain(const Atom& atom);

		CDPL_CHEM_API void setMOL2SubstructureChain(Atom& atom, const std::string& chain);

		CDPL_CHEM_API void clearMOL2SubstructureChain(Atom& atom);
	
		CDPL_CHEM_API bool hasMOL2SubstructureChain(const Atom& atom);


		CDPL_CHEM_API unsigned int getMDLParity(const Atom& atom);

		CDPL_CHEM_API void setMDLParity(Atom& atom, unsigned int parity);

		CDPL_CHEM_API void clearMDLParity(Atom& atom);
	
		CDPL_CHEM_API bool hasMDLParity(const Atom& atom);

		CDPL_CHEM_API unsigned int calcMDLParity(const Atom& atom, const MolecularGraph& molgraph);
	

		CDPL_CHEM_API bool getMDLStereoCareFlag(const Atom& atom);

		CDPL_CHEM_API void setMDLStereoCareFlag(Atom& atom, bool flag);

		CDPL_CHEM_API void clearMDLStereoCareFlag(Atom& atom);
	
		CDPL_CHEM_API bool hasMDLStereoCareFlag(const Atom& atom);


		CDPL_CHEM_API unsigned int getReactionCenterStatus(const Atom& atom);

		CDPL_CHEM_API void setReactionCenterStatus(Atom& atom, unsigned int status);

		CDPL_CHEM_API void clearReactionCenterStatus(Atom& atom);
	
		CDPL_CHEM_API bool hasReactionCenterStatus(const Atom& atom);


		CDPL_CHEM_API std::size_t getAtomMappingID(const Atom& atom);

		CDPL_CHEM_API void setAtomMappingID(Atom& atom, std::size_t id);

		CDPL_CHEM_API void clearAtomMappingID(Atom& atom);
	
		CDPL_CHEM_API bool hasAtomMappingID(const Atom& atom);


		CDPL_CHEM_API std::size_t getComponentGroupID(const Atom& atom);

		CDPL_CHEM_API void setComponentGroupID(Atom& atom, std::size_t id);

		CDPL_CHEM_API void clearComponentGroupID(Atom& atom);
	
		CDPL_CHEM_API bool hasComponentGroupID(const Atom& atom);


		CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const Atom& atom);
	
		CDPL_CHEM_API void setMatchConstraints(Atom& atom, const MatchConstraintList::SharedPointer& constr);

		CDPL_CHEM_API void clearMatchConstraints(Atom& atom);

		CDPL_CHEM_API bool hasMatchConstraints(const Atom& atom);


		CDPL_CHEM_API const MatchExpression<Atom, MolecularGraph>::SharedPointer& getMatchExpression(const Atom& atom);

		CDPL_CHEM_API void setMatchExpression(Atom& atom, const MatchExpression<Atom, MolecularGraph>::SharedPointer& expr);

		CDPL_CHEM_API void clearMatchExpression(Atom& atom);

		CDPL_CHEM_API bool hasMatchExpression(const Atom& atom);

		CDPL_CHEM_API MatchExpression<Atom, MolecularGraph>::SharedPointer buildMatchExpression(const Atom& atom, const MolecularGraph& molgraph);


		CDPL_CHEM_API const std::string& getMatchExpressionString(const Atom& atom);

		CDPL_CHEM_API void setMatchExpressionString(Atom& atom, const std::string& expr_str);

		CDPL_CHEM_API void clearMatchExpressionString(Atom& atom);

		CDPL_CHEM_API bool hasMatchExpressionString(const Atom& atom);

		CDPL_CHEM_API void buildMatchExpressionString(const Atom& atom, const MolecularGraph& molgraph, std::string& expr_str);


		CDPL_CHEM_API void markReachableAtoms(const Atom& atom, const MolecularGraph& molgraph, 
											  Util::BitSet& atom_mask, bool reset = true);

		CDPL_CHEM_API std::size_t getTopologicalDistance(const Atom& atom1, const Atom& atom2, const MolecularGraph& molgraph);


		template <typename AtomType, typename OutputIterator>
		std::size_t getConnectedAtoms(AtomType& atom, const MolecularGraph& molgraph, OutputIterator it, AtomType* excl_atom = 0)
		{
			typedef typename boost::mpl::if_<boost::is_const<AtomType>, typename AtomType::ConstAtomIterator, typename AtomType::AtomIterator>::type AtomIterator;

			AtomIterator atoms_end = atom.getAtomsEnd();
			typename AtomType::ConstBondIterator b_it = atom.getBondsBegin();
			std::size_t count = 0;

			for (AtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
				if (&(*a_it) == excl_atom)
					continue;

				if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
					*it = &(*a_it);
					++it;
					count++;
				}
			}

			return count;
		}

		template <typename AtomType, typename OutputIterator>
		std::size_t getIncidentBonds(AtomType& atom, const MolecularGraph& molgraph, OutputIterator it, AtomType* excl_atom = 0)
		{
			typedef typename boost::mpl::if_<boost::is_const<AtomType>, typename AtomType::ConstBondIterator, typename AtomType::BondIterator>::type BondIterator;

			BondIterator bonds_end = atom.getBondsEnd();
			typename AtomType::ConstAtomIterator a_it = atom.getAtomsBegin();
			std::size_t count = 0;

			for (BondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++a_it, ++b_it) {
				if (&(*a_it) == excl_atom)
					continue;
				
				if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
					*it = &(*b_it);
					++it;
					count++;
				}
			}

			return count;
		}

		template <typename AtomType, typename AtomOutputIterator, typename BondOutputIterator>
		std::size_t getConnectedAtomsAndBonds(AtomType& atom, const MolecularGraph& molgraph, AtomOutputIterator ao_it, BondOutputIterator bo_it, AtomType* excl_atom = 0)
		{
			typedef typename boost::mpl::if_<boost::is_const<AtomType>, typename AtomType::ConstAtomIterator, typename AtomType::AtomIterator>::type AtomIterator;
			typedef typename boost::mpl::if_<boost::is_const<AtomType>, typename AtomType::ConstBondIterator, typename AtomType::BondIterator>::type BondIterator;

			BondIterator bonds_end = atom.getBondsEnd();
			AtomIterator a_it = atom.getAtomsBegin();
			std::size_t count = 0;

			for (BondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++a_it, ++b_it) {
				if (&(*a_it) == excl_atom)
					continue;

				if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
					*ao_it = &(*a_it);
					*bo_it = &(*b_it);
					++ao_it;
					++bo_it;
					count++;
				}
			}

			return count;
		}
	}
}

#endif // CDPL_CHEM_ATOMFUNCTIONS_HPP
 
