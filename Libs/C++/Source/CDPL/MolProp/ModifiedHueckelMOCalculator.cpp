/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ModifiedHueckelMOCalculator.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/MolProp/ModifiedHueckelMOCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"


using namespace CDPL;


MolProp::ModifiedHueckelMOCalculator::ModifiedHueckelMOCalculator():
	locPiBonds(false)
{}

MolProp::ModifiedHueckelMOCalculator::ModifiedHueckelMOCalculator(const Chem::MolecularGraph& molgraph):
	locPiBonds(false)
{
	calculate(molgraph);
}

MolProp::ModifiedHueckelMOCalculator::ModifiedHueckelMOCalculator(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph):
	locPiBonds(false)
{
	calculate(pi_sys_list, molgraph);
}

void MolProp::ModifiedHueckelMOCalculator::localizedPiBonds(bool localized)
{
	locPiBonds = localized;
}

bool MolProp::ModifiedHueckelMOCalculator::localizedPiBonds() const
{
	return locPiBonds;
}
		
void MolProp::ModifiedHueckelMOCalculator::calculate(const Chem::MolecularGraph& molgraph)
{
	calculate(*getPiElectronSystems(molgraph), molgraph);
}

void MolProp::ModifiedHueckelMOCalculator::calculate(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph)
{
	getAtomPiSysCounts(pi_sys_list, molgraph);
	
	std::for_each(pi_sys_list.getElementsBegin(), pi_sys_list.getElementsEnd(),
				  boost::bind(&ModifiedHueckelMOCalculator::calcForPiSystem, this, _1, boost::ref(molgraph)));

	// TODO
}

void MolProp::ModifiedHueckelMOCalculator::getAtomPiSysCounts(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	atomPiSysCounts.assign(molgraph.getNumAtoms(), 0);

	for (ElectronSystemList::ConstElementIterator ps_it = pi_sys_list.getElementsBegin(), ps_end = pi_sys_list.getElementsEnd(); ps_it != ps_end; ++ps_it) {
		const ElectronSystem& pi_sys = *ps_it;

		for (ElectronSystem::ConstAtomIterator a_it = pi_sys.getAtomsBegin(), a_end = pi_sys.getAtomsEnd(); a_it != a_end; ++a_it) {
			const Atom& atom = *a_it;

			if (molgraph.containsAtom(atom))
				atomPiSysCounts[molgraph.getAtomIndex(atom)]++;
		}
	}
}

void MolProp::ModifiedHueckelMOCalculator::calcForPiSystem(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	if (pi_sys.getNumAtoms() < 2)
		return;

	getPiSystemBonds(pi_sys, molgraph);
	initHueckelMatrix(pi_sys, molgraph);

	if (!diagonalizeHueckelMatrix())
		throw Base::CalculationFailed("ModifiedHueckelMOCalculator: could not diagonalized Hueckel-matrix of pi-system");

	// TODO
}

void MolProp::ModifiedHueckelMOCalculator::initHueckelMatrix(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	std::size_t num_atoms = pi_sys.getNumAtoms();
	
	hueckelMatrix.resize(num_atoms, num_atoms);
	hueckelMatrix.clear();

	// TODO
}

bool MolProp::ModifiedHueckelMOCalculator::diagonalizeHueckelMatrix()
{
	std::size_t num_atoms = hueckelMatrix.getSize1();
	
	hmEigenVectors.resize(num_atoms, num_atoms);
	hmEigenValues.resize(num_atoms);
	
	return jacobiDiagonalize(hueckelMatrix, hmEigenValues, hmEigenVectors);
}

void MolProp::ModifiedHueckelMOCalculator::getPiSystemBonds(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	piSysBonds.clear();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (pi_sys.containsAtom(bond.getBegin()) && pi_sys.containsAtom(bond.getEnd()))
			piSysBonds.push_back(&bond);
	}
}
