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
#include <boost/unordered_map.hpp>

#include "CDPL/MolProp/ModifiedHueckelMOCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


using namespace CDPL;


namespace
{

	typedef boost::unordered_map<Base::uint64, double> ParameterMap;

	ParameterMap alphaParams;
	ParameterMap betaParams;

	struct Init
	{

		Init() {

			alphaParams.insert(ParameterMap::value_type(5000 , -0.45));
			alphaParams.insert(ParameterMap::value_type(6000 ,  0.00));
			alphaParams.insert(ParameterMap::value_type(7010 ,  0.33));
			alphaParams.insert(ParameterMap::value_type(7000 ,  1.21));
			alphaParams.insert(ParameterMap::value_type(7001 ,  1.21));
			alphaParams.insert(ParameterMap::value_type(8020 ,  0.15));
			alphaParams.insert(ParameterMap::value_type(8010 ,  2.10));
			alphaParams.insert(ParameterMap::value_type(9020 ,  2.12));
			alphaParams.insert(ParameterMap::value_type(15010,  0.14));
			alphaParams.insert(ParameterMap::value_type(15020,  3.31));
			alphaParams.insert(ParameterMap::value_type(15011,  0.03));
			alphaParams.insert(ParameterMap::value_type(16010,  0.10));
			alphaParams.insert(ParameterMap::value_type(16020,  4.17));
			alphaParams.insert(ParameterMap::value_type(16011,  0.06));
			alphaParams.insert(ParameterMap::value_type(16021,  4.66));
			alphaParams.insert(ParameterMap::value_type(17020,  1.12));
			alphaParams.insert(ParameterMap::value_type(35020,  1.10));
			alphaParams.insert(ParameterMap::value_type(53020,  0.90));
			alphaParams.insert(ParameterMap::value_type(14000, -0.10));

			betaParams.insert(ParameterMap::value_type(500006000, 0.73));
			betaParams.insert(ParameterMap::value_type(500007010, 0.66));
			betaParams.insert(ParameterMap::value_type(500007000, 0.53));
			betaParams.insert(ParameterMap::value_type(500008020, 0.60));
			betaParams.insert(ParameterMap::value_type(500008010, 0.35));
			betaParams.insert(ParameterMap::value_type(500009020, 0.26));
			betaParams.insert(ParameterMap::value_type(500017020, 0.41));
			betaParams.insert(ParameterMap::value_type(500035020, 0.50));
			betaParams.insert(ParameterMap::value_type(500053020, 0.50));
			betaParams.insert(ParameterMap::value_type(500014000, 0.57));
			betaParams.insert(ParameterMap::value_type(500015010, 0.53));
			betaParams.insert(ParameterMap::value_type(500015020, 0.54));
			betaParams.insert(ParameterMap::value_type(500016010, 0.51));
			betaParams.insert(ParameterMap::value_type(500016020, 0.44));
			betaParams.insert(ParameterMap::value_type(600006000, 1.00));
			betaParams.insert(ParameterMap::value_type(600007010, 1.19));
			betaParams.insert(ParameterMap::value_type(600007000, 0.68));
			betaParams.insert(ParameterMap::value_type(600007001, 0.72));
			betaParams.insert(ParameterMap::value_type(600008020, 1.08));
			betaParams.insert(ParameterMap::value_type(600008010, 0.65));
			betaParams.insert(ParameterMap::value_type(600009020, 0.63));
			betaParams.insert(ParameterMap::value_type(701007010, 0.58));
			betaParams.insert(ParameterMap::value_type(701007000, 0.80));
			betaParams.insert(ParameterMap::value_type(700007000, 1.30));
			betaParams.insert(ParameterMap::value_type(701008010, 0.92));
			betaParams.insert(ParameterMap::value_type(700008020, 0.55));
			betaParams.insert(ParameterMap::value_type(700108020, 0.55));
			betaParams.insert(ParameterMap::value_type(700008010, 0.01));
			betaParams.insert(ParameterMap::value_type(600015010, 0.41));
			betaParams.insert(ParameterMap::value_type(600015020, 0.08));
			betaParams.insert(ParameterMap::value_type(701015010, 0.63));
			betaParams.insert(ParameterMap::value_type(600015011, 0.18));
			betaParams.insert(ParameterMap::value_type(700015011, 0.31));
			betaParams.insert(ParameterMap::value_type(802015011, 0.60));
			betaParams.insert(ParameterMap::value_type(801015011, 0.25));
			betaParams.insert(ParameterMap::value_type(600016010, 0.68));
			betaParams.insert(ParameterMap::value_type(600016020, 0.41));
			betaParams.insert(ParameterMap::value_type(600016011, 0.24));
			betaParams.insert(ParameterMap::value_type(600016021, 0.63));
			betaParams.insert(ParameterMap::value_type(700016020, 0.47));
			betaParams.insert(ParameterMap::value_type(700016021, 0.47));
			betaParams.insert(ParameterMap::value_type(802016010, 0.19));
			betaParams.insert(ParameterMap::value_type(802016011, 0.19));
			betaParams.insert(ParameterMap::value_type(802016020, 3.28));
			betaParams.insert(ParameterMap::value_type(801016020, 0.18));
			betaParams.insert(ParameterMap::value_type(802016021, 3.28));
			betaParams.insert(ParameterMap::value_type(801016021, 0.18));
			betaParams.insert(ParameterMap::value_type(600017020, 0.29));
			betaParams.insert(ParameterMap::value_type(600035020, 0.29));
			betaParams.insert(ParameterMap::value_type(600053020, 0.20));
			betaParams.insert(ParameterMap::value_type(902016020, 0.76));
			betaParams.insert(ParameterMap::value_type(902016021, 0.76));
		}

	} init;
}


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

void MolProp::ModifiedHueckelMOCalculator::initHueckelMatrix(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t num_atoms = pi_sys.getNumAtoms();
	
	hueckelMatrix.resize(num_atoms, num_atoms);
	hueckelMatrix.clear();

	for (std::size_t i = 0; i < num_atoms; i++)
		hueckelMatrix(i, i) = getAlpha(pi_sys.getAtom(0), molgraph);

	for (BondList::const_iterator it = piSysBonds.begin(), end = piSysBonds.end(); it != end; ++it) {
		const Bond* bond = *it;
		std::size_t atom1_idx = pi_sys.getAtomIndex(bond->getBegin());
		std::size_t atom2_idx = pi_sys.getAtomIndex(bond->getEnd());
		double beta = getBeta(*bond, molgraph);

		hueckelMatrix(atom1_idx, atom2_idx) = beta;
		hueckelMatrix(atom2_idx, atom1_idx) = beta;
	}
}

double MolProp::ModifiedHueckelMOCalculator::getAlpha(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const
{
	return 0.0; // TODO
}

double MolProp::ModifiedHueckelMOCalculator::getBeta(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph) const
{
	return 1.0; // TODO
}

bool MolProp::ModifiedHueckelMOCalculator::diagonalizeHueckelMatrix()
{
	std::size_t num_atoms = hueckelMatrix.getSize1();
	
	hmEigenVectors.resize(num_atoms, num_atoms);
	hmEigenValues.resize(num_atoms);
	
	return jacobiDiagonalize(hueckelMatrix, hmEigenValues, hmEigenVectors, 100);
}
