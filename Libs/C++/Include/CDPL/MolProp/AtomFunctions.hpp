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

#ifndef CDPL_MOLPROP_ATOMFUNCTIONS_HPP
#define CDPL_MOLPROP_ATOMFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class Atom;
		class MolecularGraph;
	}

	namespace MolProp
	{
		
		CDPL_MOLPROP_API double getHydrophobicity(const Chem::Atom& atom);

		CDPL_MOLPROP_API void setHydrophobicity(Chem::Atom& atom, double hyd);

		CDPL_MOLPROP_API void clearHydrophobicity(Chem::Atom& atom);	

		CDPL_MOLPROP_API bool hasHydrophobicity(const Chem::Atom& atom);


		CDPL_MOLPROP_API double getPEOESigmaCharge(const Chem::Atom& atom);

		CDPL_MOLPROP_API void setPEOESigmaCharge(Chem::Atom& atom, double charge);

		CDPL_MOLPROP_API void clearPEOESigmaCharge(Chem::Atom& atom);
	
		CDPL_MOLPROP_API bool hasPEOESigmaCharge(const Chem::Atom& atom);
	

		CDPL_MOLPROP_API double getPEOESigmaElectronegativity(const Chem::Atom& atom);

		CDPL_MOLPROP_API void setPEOESigmaElectronegativity(Chem::Atom& atom, double e_neg);

		CDPL_MOLPROP_API void clearPEOESigmaElectronegativity(Chem::Atom& atom);
	
		CDPL_MOLPROP_API bool hasPEOESigmaElectronegativity(const Chem::Atom& atom);


		CDPL_MOLPROP_API double getMHMOPiCharge(const Chem::Atom& atom);

		CDPL_MOLPROP_API void setMHMOPiCharge(Chem::Atom& atom, double charge);

		CDPL_MOLPROP_API void clearMHMOPiCharge(Chem::Atom& atom);
	
		CDPL_MOLPROP_API bool hasMHMOPiCharge(const Chem::Atom& atom);

		
		CDPL_MOLPROP_API bool isInRing(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API bool isInRingOfSize(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t size);

		CDPL_MOLPROP_API std::size_t getNumContainingSSSRRings(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		
		CDPL_MOLPROP_API double getAtomicWeight(const Chem::Atom& atom);

		CDPL_MOLPROP_API std::size_t getIUPACGroup(const Chem::Atom& atom);

		CDPL_MOLPROP_API std::size_t getPeriod(const Chem::Atom& atom);

		CDPL_MOLPROP_API double getVdWRadius(const Chem::Atom& atom);

		CDPL_MOLPROP_API double getCovalentRadius(const Chem::Atom& atom, std::size_t order);

		CDPL_MOLPROP_API double getAllredRochowElectronegativity(const Chem::Atom& atom);

		CDPL_MOLPROP_API const std::string& getElementName(const Chem::Atom& atom);

		CDPL_MOLPROP_API std::size_t getElementValenceElectronCount(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isChemicalElement(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isMainGroupElement(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isMetal(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isTransitionMetal(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isNonMetal(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isSemiMetal(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isHalogen(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isNobleGas(const Chem::Atom& atom);


		CDPL_MOLPROP_API bool isOrdinaryHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
												 unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);
		
		CDPL_MOLPROP_API bool isHeavy(const Chem::Atom& atom);

		CDPL_MOLPROP_API bool isUnsaturated(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API bool isHydrogenAcceptor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API bool isHydrogenDonor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API bool isCarbonylLikeAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

		CDPL_MOLPROP_API bool isAmideCenterAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

		CDPL_MOLPROP_API bool isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

		CDPL_MOLPROP_API bool isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API bool isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


		CDPL_MOLPROP_API std::size_t getOrdinaryHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
															  unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

		CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

		CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

		CDPL_MOLPROP_API std::size_t getExplicitChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getRingAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getAromaticAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getHeavyAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


		CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);

		CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);

		CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);

		CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);

		CDPL_MOLPROP_API std::size_t getExplicitChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getRingBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getAromaticBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getHeavyBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t getRotatableBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool inc_h_rotors, bool inc_amide_bonds);

		
		CDPL_MOLPROP_API std::size_t calcExplicitValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
	
		CDPL_MOLPROP_API std::size_t calcValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

	
		CDPL_MOLPROP_API std::size_t calcFreeValenceElectronCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API std::size_t calcValenceElectronCount(const Chem::Atom& atom);


		CDPL_MOLPROP_API std::size_t calcStericNumber(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API unsigned int getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t steric_num);

		CDPL_MOLPROP_API unsigned int getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
	

		CDPL_MOLPROP_API double getHybridPolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API double calcEffectivePolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, double damping = 0.75);

		CDPL_MOLPROP_API double calcTotalPartialCharge(const Chem::Atom& atom);

		CDPL_MOLPROP_API double calcLonePairElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API double calcPiElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API double calcInductiveEffect(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t num_bonds = 3);
	}
}

#endif // CDPL_MOLPROP_ATOMFUNCTIONS_HPP
 
