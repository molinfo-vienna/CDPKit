/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MHMOPiChargeCalculator.cpp 
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
h * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "StaticInit.hpp"

#include <algorithm>
#include <functional>

#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/MolProp/MHMOPiChargeCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	typedef boost::unordered_map<Base::uint64, double> ParameterMap;

	ParameterMap alphaParams;
	ParameterMap betaParams;

	struct Init
	{

		Init() {
			alphaParams.insert(ParameterMap::value_type(5000, -0.45)); // B0
			alphaParams.insert(ParameterMap::value_type(6000, 0.00)); // C*
			alphaParams.insert(ParameterMap::value_type(7010, 0.33)); // N*
			alphaParams.insert(ParameterMap::value_type(7000, 1.21)); // N**
			alphaParams.insert(ParameterMap::value_type(7001, 1.21)); // N** // nitro
			alphaParams.insert(ParameterMap::value_type(8020, 0.15)); // O*
			alphaParams.insert(ParameterMap::value_type(8010, 2.10)); // O**
			alphaParams.insert(ParameterMap::value_type(9020, 2.12)); // F**
			alphaParams.insert(ParameterMap::value_type(15010, 0.14)); // P*
			alphaParams.insert(ParameterMap::value_type(15020, 3.31)); // P**
			alphaParams.insert(ParameterMap::value_type(15011, 0.03)); // P*
			alphaParams.insert(ParameterMap::value_type(16010, 0.10)); // S*
			alphaParams.insert(ParameterMap::value_type(16020, 4.17)); // S**
			alphaParams.insert(ParameterMap::value_type(16011, 0.06)); // S* // hypervalent
			alphaParams.insert(ParameterMap::value_type(16021, 4.66)); // S** // hypervalent
			alphaParams.insert(ParameterMap::value_type(17020, 1.12)); // Cl**
			alphaParams.insert(ParameterMap::value_type(35020, 1.10)); // Br**
			alphaParams.insert(ParameterMap::value_type(53020, 0.90)); // I**
			alphaParams.insert(ParameterMap::value_type(14000,-0.10)); // Si*
			
			betaParams.insert(ParameterMap::value_type(500006000, 0.73)); // B0-C*
			betaParams.insert(ParameterMap::value_type(500007010, 0.66)); // B0-N*
			betaParams.insert(ParameterMap::value_type(500007000, 0.53)); // B0-N**
			betaParams.insert(ParameterMap::value_type(500008020, 0.60)); // B0-O*
			betaParams.insert(ParameterMap::value_type(500008010, 0.35)); // B0-O**
			betaParams.insert(ParameterMap::value_type(500009020, 0.26)); // B0-F**
			betaParams.insert(ParameterMap::value_type(500017020, 0.41)); // B0-Cl**
			betaParams.insert(ParameterMap::value_type(500035020, 0.50)); // B0-Br**
			betaParams.insert(ParameterMap::value_type(500053020, 0.50)); // B0-I**
			betaParams.insert(ParameterMap::value_type(500014000, 0.57)); // B0-Si*
			betaParams.insert(ParameterMap::value_type(500015010, 0.53)); // B0-P*
			betaParams.insert(ParameterMap::value_type(500015020, 0.54)); // B0-P**
			betaParams.insert(ParameterMap::value_type(500016010, 0.51)); // B0-S*	
			betaParams.insert(ParameterMap::value_type(500016020, 0.44)); // B0-S**
			betaParams.insert(ParameterMap::value_type(600006000, 1.00)); // C*-C*
			betaParams.insert(ParameterMap::value_type(600007010, 1.19)); // C*-N*
			betaParams.insert(ParameterMap::value_type(600007000, 0.68)); // C*-N**
			betaParams.insert(ParameterMap::value_type(600007001, 0.72)); // C*-Nitro
			betaParams.insert(ParameterMap::value_type(600008020, 1.08)); // C*-O*
			betaParams.insert(ParameterMap::value_type(600008010, 0.65)); // C*-O**
			betaParams.insert(ParameterMap::value_type(600009020, 0.63)); // C*-F**
			betaParams.insert(ParameterMap::value_type(701007010, 0.58)); // N*-N*
			betaParams.insert(ParameterMap::value_type(701007000, 0.80)); // N*-N**
			betaParams.insert(ParameterMap::value_type(700007000, 1.30)); // N**-N** // eg. phenylhydrazine
			betaParams.insert(ParameterMap::value_type(701008010, 0.92)); // N*-O**
			betaParams.insert(ParameterMap::value_type(700008020, 0.55)); // N**-O* // ???
			betaParams.insert(ParameterMap::value_type(700108020, 0.55)); // N**-O* // nitro
			betaParams.insert(ParameterMap::value_type(700008010, 0.01)); // N**-O**
			betaParams.insert(ParameterMap::value_type(600015010, 0.41)); // C*-P*
			betaParams.insert(ParameterMap::value_type(600015020, 0.08)); // C*-P**
			betaParams.insert(ParameterMap::value_type(701015010, 0.63)); // N*-P*
			betaParams.insert(ParameterMap::value_type(600015011, 0.18)); // C*-P*
			betaParams.insert(ParameterMap::value_type(700015011, 0.31)); // N*-P* // P(=O)(O)(O)N
			betaParams.insert(ParameterMap::value_type(802015011, 0.60)); // O*-P*
			betaParams.insert(ParameterMap::value_type(801015011, 0.25)); // O**-P*
			betaParams.insert(ParameterMap::value_type(600016010, 0.68)); // C*-S*
			betaParams.insert(ParameterMap::value_type(600016020, 0.41)); // C*-S**
			betaParams.insert(ParameterMap::value_type(600016011, 0.24)); // C*-S* // hypervalent
			betaParams.insert(ParameterMap::value_type(600016021, 0.63)); // C*-S** // hypervalent sulfur
			betaParams.insert(ParameterMap::value_type(700016020, 0.47)); // N**-S**
			betaParams.insert(ParameterMap::value_type(700016021, 0.47)); // N**-S** // S(=O)(=O)NH2
			betaParams.insert(ParameterMap::value_type(802016010, 0.19)); // O*-S* 
			betaParams.insert(ParameterMap::value_type(802016011, 0.19)); // O*-S*   // RS(=O)R'
			betaParams.insert(ParameterMap::value_type(802016020, 3.28)); // O*-S**
			betaParams.insert(ParameterMap::value_type(801016020, 0.18)); // O**-S**
			betaParams.insert(ParameterMap::value_type(802016021, 3.28)); // O*-S**  // S(=O)(=O)OH
			betaParams.insert(ParameterMap::value_type(801016021, 0.18)); // O**-S** // S(=O)(=O)OH
			betaParams.insert(ParameterMap::value_type(600017020, 0.29)); // C*-Cl**
			betaParams.insert(ParameterMap::value_type(600035020, 0.29)); // C*-Br**
			betaParams.insert(ParameterMap::value_type(600053020, 0.20)); // C*-I**
			betaParams.insert(ParameterMap::value_type(902016020, 0.76)); // F**-S** // S(=O)(=O)F
			betaParams.insert(ParameterMap::value_type(902016021, 0.76)); // F**-S** // S(=O)(=O)F
		}

	} init;

	const double ENERGY_LEVEL_COMP_TOL = 0.01;
	const double SIGMA_CORR_REF        = 7.324379833683146;
	const double SIGMA_FACTOR          = 0.029;
	const double HYPER_CONJ_FACTOR     = 0.58;
}


MolProp::MHMOPiChargeCalculator::MHMOPiChargeCalculator():
	locPiBonds(false)
{}

MolProp::MHMOPiChargeCalculator::MHMOPiChargeCalculator(const Chem::MolecularGraph& molgraph):
	locPiBonds(false)
{
	calculate(molgraph);
}

MolProp::MHMOPiChargeCalculator::MHMOPiChargeCalculator(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph):
	locPiBonds(false)
{
	calculate(pi_sys_list, molgraph);
}

void MolProp::MHMOPiChargeCalculator::localizedPiBonds(bool localized)
{
	locPiBonds = localized;
}

bool MolProp::MHMOPiChargeCalculator::localizedPiBonds() const
{
	return locPiBonds;
}
		
void MolProp::MHMOPiChargeCalculator::calculate(const Chem::MolecularGraph& molgraph)
{
	calculate(*getPiElectronSystems(molgraph), molgraph);
}

void MolProp::MHMOPiChargeCalculator::calculate(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	atomElecDensities.assign(num_atoms, 0.0);
	atomPiCharges.assign(num_atoms, 0.0);
	bondElecDensities.assign(molgraph.getNumBonds(), 0.0);
	energy = 0.0;
	
	initAtomPiSysCounts(pi_sys_list, molgraph);
	initAtomFreeElecCounts(pi_sys_list, molgraph);
	
	std::for_each(pi_sys_list.getElementsBegin(), pi_sys_list.getElementsEnd(),
				  boost::bind(&MHMOPiChargeCalculator::calcForPiSys, this, _1, boost::ref(molgraph)));
}

double MolProp::MHMOPiChargeCalculator::getElectronDensity(std::size_t atom_idx) const
{
	if (atom_idx >= atomElecDensities.size())
		throw Base::IndexError("MHMOPiChargeCalculator: atom index out of bounds");
	
	return atomElecDensities[atom_idx];
}

double MolProp::MHMOPiChargeCalculator::getCharge(std::size_t atom_idx) const
{
	if (atom_idx >= atomElecDensities.size())
		throw Base::IndexError("MHMOPiChargeCalculator: atom index out of bounds");
	
	return atomPiCharges[atom_idx];
}

double MolProp::MHMOPiChargeCalculator::getBondOrder(std::size_t bond_idx) const
{
	if (bond_idx >= bondElecDensities.size())
		throw Base::IndexError("MHMOPiChargeCalculator: bond index out of bounds");

	return bondElecDensities[bond_idx];
}

double MolProp::MHMOPiChargeCalculator::getEnergy() const
{
	return energy;
}

void MolProp::MHMOPiChargeCalculator::initAtomPiSysCounts(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	atomPiSysCounts.assign(molgraph.getNumAtoms(), 0);

	for (ElectronSystemList::ConstElementIterator ps_it = pi_sys_list.getElementsBegin(), ps_end = pi_sys_list.getElementsEnd(); ps_it != ps_end; ++ps_it) {
		const ElectronSystem& pi_sys = *ps_it;

		if (pi_sys.getNumAtoms() < 2)
			continue;
		
		for (ElectronSystem::ConstAtomIterator a_it = pi_sys.getAtomsBegin(), a_end = pi_sys.getAtomsEnd(); a_it != a_end; ++a_it) {
			const Atom& atom = *a_it;

			if (molgraph.containsAtom(atom))
				atomPiSysCounts[molgraph.getAtomIndex(atom)]++;
		}
	}
}

void MolProp::MHMOPiChargeCalculator::initAtomFreeElecCounts(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	atomFreeElecCounts.assign(molgraph.getNumAtoms(), 0);

	for (ElectronSystemList::ConstElementIterator ps_it = pi_sys_list.getElementsBegin(), ps_end = pi_sys_list.getElementsEnd(); ps_it != ps_end; ++ps_it) {
		const ElectronSystem& pi_sys = *ps_it;

		if (pi_sys.getNumAtoms() == 1)
			atomFreeElecCounts[molgraph.getAtomIndex(pi_sys.getAtom(0))] += pi_sys.getNumElectrons();
	}
}

void MolProp::MHMOPiChargeCalculator::calcForPiSys(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	if (pi_sys.getNumAtoms() < 2)
		return;

	initAtomPiElecCounts(pi_sys, molgraph);
	getInvolvedBonds(pi_sys, molgraph);
	initHueckelMatrix(pi_sys, molgraph);

	if (!diagHueckelMatrix())
		throw Base::CalculationFailed("MHMOPiChargeCalculator: could not diagonalize Hueckel-matrix");

	distElectrons(pi_sys);
	
	updateEnergy();
	updateAtomElecDensitiesAndCharges(pi_sys, molgraph);
	updateBondElecDensities(pi_sys, molgraph);
}

void MolProp::MHMOPiChargeCalculator::initAtomPiElecCounts(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t num_atoms = pi_sys.getNumAtoms();

	atomPiElecCounts.assign(num_atoms, 0);
	specialAtomTypes.resize(num_atoms);
	specialAtomTypes.reset();
	
	for (std::size_t i = 0; i < num_atoms; i++)
		atomPiElecCounts[i] = pi_sys.getElectronContrib(pi_sys.getAtom(i));
	
	for (std::size_t i = 0; i < num_atoms; i++)	{
		const Atom& atom = pi_sys.getAtom(i);
		unsigned int atom_type = getType(atom);
		std::size_t num_bonds = getNumBonds(atom, pi_sys, molgraph);
			
		if( (atom_type == AtomType::S && num_bonds > 2) || (atom_type == AtomType::P && num_bonds > 3)) {
			atomPiElecCounts[i] = atom_type - 10 - getBondCount(atom, molgraph) - atomFreeElecCounts[molgraph.getAtomIndex(atom)];
			specialAtomTypes.set(i);

			Atom::ConstBondIterator b_it = atom.getBondsBegin();
	
			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
				const Atom& nbr_atom = *a_it;
				
				if (!pi_sys.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
					continue;

				if (getType(nbr_atom) != AtomType::O)
					continue;

				switch (getBondCount(nbr_atom, molgraph)) {

					case 1:
						atomPiElecCounts[pi_sys.getAtomIndex(nbr_atom)] = 1;
						continue;

					case 2:
						atomPiElecCounts[pi_sys.getAtomIndex(nbr_atom)] = 2;
				}
			}
				
		} else if (atom_type == AtomType::N && num_bonds == 3) {
			std::size_t num_o_nbrs = 0;
			Atom::ConstBondIterator b_it = atom.getBondsBegin();
				
			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
				const Atom& nbr_atom = *a_it;
				
				if (!pi_sys.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
					continue;

				if (getType(nbr_atom) == AtomType::O && getBondCount(nbr_atom, molgraph) == 1)
					num_o_nbrs++;
			}

			if (num_o_nbrs != 2)
				continue;
			
			atomPiElecCounts[i] = 2;
			specialAtomTypes.set(i);

			b_it = atom.getBondsBegin();
	
			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
				const Atom& nbr_atom = *a_it;
				
				if (!pi_sys.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
					continue;

				if (getType(nbr_atom) != AtomType::O)
					continue;

				atomPiElecCounts[pi_sys.getAtomIndex(nbr_atom)] = 1;
			}
		}
	}
}

std::size_t MolProp::MHMOPiChargeCalculator::getNumBonds(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys,
															  const Chem::MolecularGraph& molgraph) const
{
	using namespace Chem;

	std::size_t count = 0;
	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		if (pi_sys.containsAtom(*a_it) && molgraph.containsBond(*b_it))
			count++;
	}

	return count;
}

void MolProp::MHMOPiChargeCalculator::getInvolvedBonds(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	piSysBonds.clear();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (pi_sys.containsAtom(bond.getBegin()) && pi_sys.containsAtom(bond.getEnd()))
			piSysBonds.push_back(&bond);
	}
}

void MolProp::MHMOPiChargeCalculator::initHueckelMatrix(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t num_atoms = pi_sys.getNumAtoms();
	
	hueckelMatrix.resize(num_atoms, num_atoms);
	hueckelMatrix.clear();

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = pi_sys.getAtom(i);
		
		hueckelMatrix(i, i) = getAlpha(atom, pi_sys, molgraph) + getAlphaCorrection(atom, pi_sys, molgraph);
	}
	
	for (BondList::const_iterator it = piSysBonds.begin(), end = piSysBonds.end(); it != end; ++it) {
		const Bond* bond = *it;

		if (locPiBonds && getOrder(*bond) < 2)
			continue;
		
		std::size_t atom1_idx = pi_sys.getAtomIndex(bond->getBegin());
		std::size_t atom2_idx = pi_sys.getAtomIndex(bond->getEnd());
		double beta = getBeta(*bond, pi_sys, molgraph);

		hueckelMatrix(atom1_idx, atom2_idx) = beta;
		hueckelMatrix(atom2_idx, atom1_idx) = beta;
	}
}

double MolProp::MHMOPiChargeCalculator::getAlpha(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys,
													  const Chem::MolecularGraph& molgraph) const
{
	ParameterMap::const_iterator it = alphaParams.find(getAtomID(atom, pi_sys, molgraph));

	if (it == alphaParams.end())
		return 0.0; // == Csp2

	return it->second;
}

double MolProp::MHMOPiChargeCalculator::getAlphaCorrection(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys,
																const Chem::MolecularGraph& molgraph) const
{
	using namespace Chem;
		
	std::size_t nbr_count = 0;
	double sigma_corr = 0.0;

	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		if (!molgraph.containsBond(*b_it))
			continue;

		sigma_corr += getPEOESigmaElectronegativity(*a_it);
		nbr_count++;
	}

	if (nbr_count > 1)
		sigma_corr /= nbr_count;
	
	sigma_corr = SIGMA_FACTOR * (sigma_corr - SIGMA_CORR_REF);
	
	double hyp_conj_corr = 0.0;

	if (atomPiElecCounts[pi_sys.getAtomIndex(atom)] == 1) {
		b_it = atom.getBondsBegin();
	
		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			if (!molgraph.containsBond(*b_it))
				continue;

			const Atom& nbr_atom = *a_it;

			if (getType(nbr_atom) != AtomType::C)
				continue;

			if (getBondCount(nbr_atom, molgraph) != 4)
				continue;

			if (getBondCount(nbr_atom, molgraph, 1, AtomType::H) == 0)
				continue;

			double sig_charge = getPEOESigmaCharge(nbr_atom);

			if(sig_charge < 0.0)
				hyp_conj_corr += sig_charge;
		}
	}

	hyp_conj_corr *= HYPER_CONJ_FACTOR;

	std::size_t num_pi_sys = atomPiSysCounts[molgraph.getAtomIndex(atom)];

	if (num_pi_sys > 1)
		return ((sigma_corr + hyp_conj_corr) / num_pi_sys);

	return (sigma_corr + hyp_conj_corr);
}

double MolProp::MHMOPiChargeCalculator::getBeta(const Chem::Bond& bond, const Chem::ElectronSystem& pi_sys,
													 const Chem::MolecularGraph& molgraph) const
{
	ParameterMap::const_iterator it = betaParams.find(getBondID(bond, pi_sys, molgraph));

	if (it == betaParams.end())
		return 1.0; // == Csp2-Csp2

	return it->second;
}

Base::uint64 MolProp::MHMOPiChargeCalculator::getAtomID(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys,
															 const Chem::MolecularGraph& molgraph) const
{
	using namespace Chem;

	unsigned int atom_type = getType(atom);
	std::size_t atom_idx = pi_sys.getAtomIndex(atom);
	std::size_t num_pi_elec = atomFreeElecCounts[molgraph.getAtomIndex(atom)] / 2;
	
	if (atom_type == AtomType::S || atom_type == AtomType::P)
		num_pi_elec = atomPiElecCounts[atom_idx];
	
	return (atom_type * 1000 + num_pi_elec * 10 + specialAtomTypes.test(atom_idx));
}

Base::uint64 MolProp::MHMOPiChargeCalculator::getBondID(const Chem::Bond& bond, const Chem::ElectronSystem& pi_sys,
															 const Chem::MolecularGraph& molgraph) const
{
	Base::uint64 atom1_id = getAtomID(bond.getBegin(), pi_sys, molgraph);
	Base::uint64 atom2_id = getAtomID(bond.getEnd(), pi_sys, molgraph);

	if (atom1_id > atom2_id)
		std::swap(atom1_id, atom2_id);

	return (atom1_id * 100000 + atom2_id);
}

bool MolProp::MHMOPiChargeCalculator::diagHueckelMatrix()
{
	std::size_t num_atoms = hueckelMatrix.getSize1();
	
	hmEigenVectors.resize(num_atoms, num_atoms);
	hmEigenValues.resize(num_atoms);
	
	return jacobiDiagonalize(hueckelMatrix, hmEigenValues, hmEigenVectors, 100);
}

void MolProp::MHMOPiChargeCalculator::distElectrons(const Chem::ElectronSystem& pi_sys)
{
	std::size_t num_mos = hmEigenValues.getSize();
	
	moDescriptors.resize(num_mos);
	moDescriptorPtrs.clear();

	for (std::size_t i = 0; i < num_mos; i++) {
		moDescriptors[i].coeffVecIndex = i;
		moDescriptors[i].energy = -hmEigenValues(i);
		moDescriptors[i].elecCount = 0.0;

		moDescriptorPtrs.push_back(&moDescriptors[i]);
	}

	std::sort(moDescriptorPtrs.begin(), moDescriptorPtrs.end(),
			  boost::bind(std::less<double>(), boost::bind(&MODescr::energy, _1),  boost::bind(&MODescr::energy, _2)));

	for (std::size_t i = 0, num_pi_elec = pi_sys.getNumElectrons(); i < num_mos; ) {
		double energy = moDescriptorPtrs[i]->energy;
		std::size_t num_eq_mos = 1;
		
		for (std::size_t j = i + 1; j < num_mos; j++) {
			if ((moDescriptorPtrs[j]->energy - energy) <= ENERGY_LEVEL_COMP_TOL)
				num_eq_mos++;
			else
				break;
		}
		
		if (num_pi_elec <= (2 * num_eq_mos)) {
			double num_elec_per_mo = num_pi_elec / num_eq_mos;
	
			for (std::size_t j = 0; j < num_eq_mos; j++, i++)
				moDescriptorPtrs[i]->elecCount = num_elec_per_mo;

			break;
		}

		for (std::size_t j = 0; j < num_eq_mos; j++, i++)
			moDescriptorPtrs[i]->elecCount = 2.0;

		num_pi_elec -= 2 * num_eq_mos;
	}
}

void MolProp::MHMOPiChargeCalculator::updateEnergy()
{
	for (MODescrPtrArray::const_iterator it = moDescriptorPtrs.begin(), end = moDescriptorPtrs.end(); it != end; ++it) {
		double num_el = (*it)->elecCount;

		if (num_el == 0.0)
			return;

		energy += num_el * (*it)->energy;
	}
}

void MolProp::MHMOPiChargeCalculator::updateAtomElecDensitiesAndCharges(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	for (std::size_t i = 0, num_atoms = pi_sys.getNumAtoms(); i < num_atoms; i++) { 
		double el_density = calcElecDensity(i, i);
		std::size_t atom_idx = molgraph.getAtomIndex(pi_sys.getAtom(i));

		atomElecDensities[atom_idx] += el_density;
		atomPiCharges[atom_idx] += atomPiElecCounts[i] - el_density; 
	}
}

void MolProp::MHMOPiChargeCalculator::updateBondElecDensities(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	for (BondList::const_iterator it = piSysBonds.begin(), end = piSysBonds.end(); it != end; ++it) {
		const Bond& bond = **it;

		bondElecDensities[molgraph.getBondIndex(bond)] += calcElecDensity(pi_sys.getAtomIndex(bond.getBegin()), pi_sys.getAtomIndex(bond.getEnd()));
	}
}

double MolProp::MHMOPiChargeCalculator::calcElecDensity(std::size_t i, std::size_t j) const
{
	double density = 0.0;

	for (std::size_t k = 0, num_mos = hmEigenValues.getSize(); k < num_mos; k++)
		density += moDescriptors[k].elecCount * hmEigenVectors(i, k) * hmEigenVectors(j, k);

	return density;
}
