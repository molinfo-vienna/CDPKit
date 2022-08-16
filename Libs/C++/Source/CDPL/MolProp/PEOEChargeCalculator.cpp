/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PEOEChargeCalculator.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/MolProp/PEOEChargeCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"


using namespace CDPL;


namespace
{

	const double  HYDROGEN_ENEGATIVITY_P1 = 20.02;
}


const std::size_t MolProp::PEOEChargeCalculator::DEF_NUM_ITERATIONS;
const double      MolProp::PEOEChargeCalculator::DEF_DAMPING_FACTOR = 0.5;


MolProp::PEOEChargeCalculator::PEOEChargeCalculator():
	numIterations(DEF_NUM_ITERATIONS), dampingFactor(DEF_DAMPING_FACTOR) {}

MolProp::PEOEChargeCalculator::PEOEChargeCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& charges):
	numIterations(DEF_NUM_ITERATIONS), dampingFactor(DEF_DAMPING_FACTOR)
{
	calculate(molgraph, charges);
}

void MolProp::PEOEChargeCalculator::setNumIterations(std::size_t num_iter)
{
	numIterations = num_iter;
}

void MolProp::PEOEChargeCalculator::setDampingFactor(double factor)
{
	dampingFactor = factor;
}

std::size_t MolProp::PEOEChargeCalculator::getNumIterations() const
{
	return numIterations;
}

double MolProp::PEOEChargeCalculator::getDampingFactor() const
{
	return dampingFactor;
}

void MolProp::PEOEChargeCalculator::calculate(const Chem::MolecularGraph& molgraph, Util::DArray& charges)
{
	init(molgraph, charges);
	calcCharges(charges);
}

void MolProp::PEOEChargeCalculator::getElectronegativities(Util::DArray& elnegs) const
{
	elnegs.clear();
	elnegs.reserve(atomStates.size());
	
	std::for_each(atomStates.begin(), atomStates.end(), 
				  boost::bind(&Util::DArray::addElement, 
							  boost::ref(elnegs),
							  boost::bind(&PEOEAtomState::getElectronegativity, _1)));
}

void MolProp::PEOEChargeCalculator::init(const Chem::MolecularGraph& molgraph, Util::DArray& charges)
{
	using namespace Chem;
	
	std::size_t num_atoms = molgraph.getNumAtoms();

	atomStates.clear();
	atomStates.reserve(num_atoms);

	implHStates.clear();
	implHStates.reserve(num_atoms);

	charges.clear();
	charges.reserve(num_atoms);

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), atoms_end = molgraph.getAtomsEnd(); it != atoms_end; ++it) {
		const Atom& atom = *it;

		PEOEAtomState::SharedPointer atom_state_ptr(new PEOEAtomState(atom, molgraph));
		atomStates.push_back(atom_state_ptr);

		PEOEAtomState* atom_state = atom_state_ptr.get();

		std::size_t impl_h_count = getImplicitHydrogenCount(atom);

		if (impl_h_count > 0) {
			PEOEAtomState::SharedPointer h_state_ptr(new PEOEAtomState());
			implHStates.push_back(h_state_ptr);

			PEOEAtomState* h_state = h_state_ptr.get();

			for (std::size_t i = 0; i < impl_h_count; i++)
				atom_state->linkTo(h_state);

			h_state->linkTo(atom_state);
		}
	}

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), bonds_end = molgraph.getBondsEnd(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		PEOEAtomState* atom_state1 = atomStates[molgraph.getAtomIndex(bond.getBegin())].get();
		PEOEAtomState* atom_state2 = atomStates[molgraph.getAtomIndex(bond.getEnd())].get();

		atom_state1->linkTo(atom_state2);
		atom_state2->linkTo(atom_state1);
	}
}

void MolProp::PEOEChargeCalculator::calcCharges(Util::DArray& charges)
{
	PEOEAtomStateList::iterator atom_states_beg = atomStates.begin();
	PEOEAtomStateList::iterator atom_states_end = atomStates.end();

	PEOEAtomStateList::iterator impl_h_states_beg = implHStates.begin();
	PEOEAtomStateList::iterator impl_h_states_end = implHStates.end();

	double attenuation_fact = 1.0;

	for (std::size_t i = 0; i < numIterations; i++) {
		attenuation_fact *= dampingFactor;

		std::for_each(atom_states_beg, atom_states_end,
					  boost::bind(&PEOEAtomState::shiftCharges, _1, attenuation_fact));
		std::for_each(impl_h_states_beg, impl_h_states_end,
					  boost::bind(&PEOEAtomState::shiftCharges, _1, attenuation_fact));

		std::for_each(atom_states_beg, atom_states_end,
					  boost::bind(&PEOEAtomState::updateElectronegativity, _1));
		std::for_each(impl_h_states_beg, impl_h_states_end,
					  boost::bind(&PEOEAtomState::updateElectronegativity, _1));
	}

	std::for_each(atom_states_beg, atom_states_end, boost::bind(&Util::DArray::addElement, 
																boost::ref(charges),
																boost::bind(&PEOEAtomState::getCharge, _1)));
}


MolProp::PEOEChargeCalculator::PEOEAtomState::PEOEAtomState(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph): 
	charge(0.0) 
{
	using namespace Chem;
	
	switch (getType(atom)) {

		case AtomType::H:
			a = 7.17;
			b = 6.24;
			c = -0.56;

			enegativityP1 = HYDROGEN_ENEGATIVITY_P1;
			enegativity = a;
			return;

		case AtomType::N:
			switch (getHybridizationState(atom)) {

				case HybridizationState::SP1:
					a = 15.68;
					b = 11.70;
					c = -0.27;
					break;

				case HybridizationState::SP2:
					a = 12.87;
					b = 11.15;
					c = 0.85;
					break;

				case HybridizationState::SP3:
				default:
					a = 11.54;
					b = 10.82;
					c = 1.36;
					break;
			}

			break;

		case AtomType::O:
			switch (getHybridizationState(atom)) {

				case HybridizationState::SP2:
					a = 17.07;
					b = 13.79;
					c = 0.47;
					break;

				case HybridizationState::SP3:
				default:
					a = 14.18;
					b = 12.92;
					c = 1.39;
					break;
			}

			break;

		case AtomType::F:
			a = 14.66;
			b = 13.85;
			c = 2.31;
			break;

		case AtomType::Cl:
			a = 11.00;
			b = 9.69;
			c = 1.35;
			break;

		case AtomType::Br:
			a = 10.08;
			b = 8.47;
			c = 1.16;
			break;

		case AtomType::I:
			a = 9.90;
			b = 7.96;
			c = 0.96;
			break;

		case AtomType::S:
			a = 10.14;
			b = 9.13;
			c = 1.38;
			break;

		case AtomType::C:
		default:
			switch (getHybridizationState(atom)) {

				case HybridizationState::SP1:
					a = 10.39;
					b = 9.45;
					c = 0.73;
					break;

				case HybridizationState::SP2:
					a = 8.79;
					b = 9.32;
					c = 1.51;
					break;

				case HybridizationState::SP3:
				default:
					a = 7.98;
					b = 9.18;
					c = 1.88;
					break;
			}

			break;
	}

	enegativityP1 = a + b + c;
	enegativity = a;
}

MolProp::PEOEChargeCalculator::PEOEAtomState::PEOEAtomState(): // Implicit H
	a(7.17), b(6.24), c(-0.56), enegativity(7.17), enegativityP1(HYDROGEN_ENEGATIVITY_P1), charge(0.0) 
{}

void MolProp::PEOEChargeCalculator::PEOEAtomState::linkTo(PEOEAtomState* nbr_state)
{
	nbrAtomStates.push_back(nbr_state);
}

double MolProp::PEOEChargeCalculator::PEOEAtomState::getCharge() const
{
	return charge;
}

double MolProp::PEOEChargeCalculator::PEOEAtomState::getElectronegativity() const
{
	return enegativity;
}

void MolProp::PEOEChargeCalculator::PEOEAtomState::shiftCharges(double attenuation_fact)
{
	double q_i = 0.0;

	PEOEAtomStateList::const_iterator nbrs_end = nbrAtomStates.end();

	for (PEOEAtomStateList::const_iterator it = nbrAtomStates.begin(); it != nbrs_end; ++it) {
		const PEOEAtomState& nbr_desc = **it;

		if (enegativity < nbr_desc.enegativity)
			q_i += (nbr_desc.enegativity - enegativity) / enegativityP1;
		else
			q_i += (nbr_desc.enegativity - enegativity) / nbr_desc.enegativityP1;
	}

	charge += q_i * attenuation_fact;
}

void MolProp::PEOEChargeCalculator::PEOEAtomState::updateElectronegativity()
{
	enegativity = a + b * charge + c * charge * charge;
}
