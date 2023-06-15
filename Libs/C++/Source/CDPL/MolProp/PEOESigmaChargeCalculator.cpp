/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PEOESigmaChargeCalculator.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>
#include <functional>

#include "CDPL/MolProp/PEOESigmaChargeCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	const double  HYDROGEN_ENEGATIVITY_P1 = 20.02;
}


constexpr std::size_t MolProp::PEOESigmaChargeCalculator::DEF_NUM_ITERATIONS;
constexpr double      MolProp::PEOESigmaChargeCalculator::DEF_DAMPING_FACTOR;


MolProp::PEOESigmaChargeCalculator::PEOESigmaChargeCalculator():
	numIterations(DEF_NUM_ITERATIONS), dampingFactor(DEF_DAMPING_FACTOR) {}

MolProp::PEOESigmaChargeCalculator::PEOESigmaChargeCalculator(const Chem::MolecularGraph& molgraph):
	numIterations(DEF_NUM_ITERATIONS), dampingFactor(DEF_DAMPING_FACTOR)
{
	calculate(molgraph);
}

void MolProp::PEOESigmaChargeCalculator::setNumIterations(std::size_t num_iter)
{
	numIterations = num_iter;
}

void MolProp::PEOESigmaChargeCalculator::setDampingFactor(double factor)
{
	dampingFactor = factor;
}

std::size_t MolProp::PEOESigmaChargeCalculator::getNumIterations() const
{
	return numIterations;
}

double MolProp::PEOESigmaChargeCalculator::getDampingFactor() const
{
	return dampingFactor;
}

void MolProp::PEOESigmaChargeCalculator::calculate(const Chem::MolecularGraph& molgraph)
{
	init(molgraph);
	calcCharges();
}

double MolProp::PEOESigmaChargeCalculator::getCharge(std::size_t idx) const
{
	if (idx >= atomStates.size())
		throw Base::IndexError("PEOESigmaChargeCalculator: atom index out of bounds");

	return atomStates[idx]->getCharge();
}

double MolProp::PEOESigmaChargeCalculator::getElectronegativity(std::size_t idx) const
{
	if (idx >= atomStates.size())
		throw Base::IndexError("PEOESigmaChargeCalculator: atom index out of bounds");

	return atomStates[idx]->getElectronegativity();
}

void MolProp::PEOESigmaChargeCalculator::init(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t num_atoms = molgraph.getNumAtoms();

	atomStates.clear();
	atomStates.reserve(num_atoms);

	implHStates.clear();
	implHStates.reserve(num_atoms);

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), atoms_end = molgraph.getAtomsEnd(); it != atoms_end; ++it) {
		const Atom& atom = *it;

		AtomState::SharedPointer atom_state_ptr(new AtomState(atom, molgraph));
		atomStates.push_back(atom_state_ptr);

		AtomState* atom_state = atom_state_ptr.get();

		std::size_t impl_h_count = getImplicitHydrogenCount(atom);

		if (impl_h_count > 0) {
			AtomState::SharedPointer h_state_ptr(new AtomState());
			implHStates.push_back(h_state_ptr);

			AtomState* h_state = h_state_ptr.get();

			for (std::size_t i = 0; i < impl_h_count; i++)
				atom_state->linkTo(h_state);

			h_state->linkTo(atom_state);
		}
	}

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), bonds_end = molgraph.getBondsEnd(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		AtomState* atom_state1 = atomStates[molgraph.getAtomIndex(bond.getBegin())].get();
		AtomState* atom_state2 = atomStates[molgraph.getAtomIndex(bond.getEnd())].get();

		atom_state1->linkTo(atom_state2);
		atom_state2->linkTo(atom_state1);
	}
}

void MolProp::PEOESigmaChargeCalculator::calcCharges()
{
	using namespace std::placeholders;
	
	AtomStateList::iterator atom_states_beg = atomStates.begin();
	AtomStateList::iterator atom_states_end = atomStates.end();

	AtomStateList::iterator impl_h_states_beg = implHStates.begin();
	AtomStateList::iterator impl_h_states_end = implHStates.end();

	double attenuation_fact = 1.0;

	for (std::size_t i = 0; i < numIterations; i++) {
		attenuation_fact *= dampingFactor;

		std::for_each(atom_states_beg, atom_states_end,
					  std::bind(&AtomState::shiftCharges, _1, attenuation_fact));
		std::for_each(impl_h_states_beg, impl_h_states_end,
					  std::bind(&AtomState::shiftCharges, _1, attenuation_fact));

		std::for_each(atom_states_beg, atom_states_end,
					  std::bind(&AtomState::updateElectronegativity, _1));
		std::for_each(impl_h_states_beg, impl_h_states_end,
					  std::bind(&AtomState::updateElectronegativity, _1));
	}
}

double MolProp::PEOESigmaChargeCalculator::getNbrElectronegativityAvg(std::size_t idx) const
{
	return atomStates[idx]->getNbrElectronegativityAvg();
}

MolProp::PEOESigmaChargeCalculator::AtomState::AtomState(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph): 
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

		case AtomType::Li:
			a = 3.1;
			b = 4.44;
			c = 1.75;
			break;

		case AtomType::Na:
			a = 2.8;
			b = 12.99;
			c = 10.42;
			break;

		case AtomType::Mg:
			a = 3.3;
			b = 5.58;
			c = 2.44;
			break;

		case AtomType::Al:
			a = 5.38;
			b = 4.95;
			c = 0.87;
			break;

		case AtomType::Be:
			a = 3.84;
			b = 6.75;
			c = 3.17;
			break;

		case AtomType::B:
			a = 5.98;
			b = 6.82;
			c = 1.60;
			break;

		case AtomType::Si:
			a = 7.30;
			b = 6.57;
			c = 0.66;
			break;

		case AtomType::P:
			a = 8.91;
			b = 8.24;
			c = 1.76;
			break;

		case AtomType::Ti:
			a = 2.48;
			b = 5.10;
			c = 2.16;
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

MolProp::PEOESigmaChargeCalculator::AtomState::AtomState(): // Implicit H
	a(7.17), b(6.24), c(-0.56), enegativity(7.17), enegativityP1(HYDROGEN_ENEGATIVITY_P1), charge(0.0) 
{}

void MolProp::PEOESigmaChargeCalculator::AtomState::linkTo(AtomState* nbr_state)
{
	nbrAtomStates.push_back(nbr_state);
}

double MolProp::PEOESigmaChargeCalculator::AtomState::getCharge() const
{
	return charge;
}

double MolProp::PEOESigmaChargeCalculator::AtomState::getElectronegativity() const
{
	return enegativity;
}

void MolProp::PEOESigmaChargeCalculator::AtomState::shiftCharges(double att_fact)
{
	double q_i = 0.0;

	AtomStateList::const_iterator nbrs_end = nbrAtomStates.end();

	for (AtomStateList::const_iterator it = nbrAtomStates.begin(); it != nbrs_end; ++it) {
		const AtomState& nbr_desc = **it;

		if (enegativity < nbr_desc.enegativity)
			q_i += (nbr_desc.enegativity - enegativity) / enegativityP1;
		else
			q_i += (nbr_desc.enegativity - enegativity) / nbr_desc.enegativityP1;
	}

	charge += q_i * att_fact;
}

void MolProp::PEOESigmaChargeCalculator::AtomState::updateElectronegativity()
{
	enegativity = a + b * charge + c * charge * charge;
}

double MolProp::PEOESigmaChargeCalculator::AtomState::getNbrElectronegativityAvg() const
{
	double sum = 0.0;

	for (AtomStateList::const_iterator it = nbrAtomStates.begin(), nbrs_end = nbrAtomStates.end(); it != nbrs_end; ++it)
		sum += (*it)->enegativity;

	if (nbrAtomStates.size() > 1)
		sum /= nbrAtomStates.size();
	
	return sum;
}
