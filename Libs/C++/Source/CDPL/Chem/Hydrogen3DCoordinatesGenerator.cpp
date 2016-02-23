/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Hydrogen3DCoordinatesGenerator.cpp 
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


#include "StaticInit.hpp"

#include <cmath>
#include <iterator>

#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomTypeFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL;


namespace
{

	const double SQRT_3 = std::sqrt(3.0);
	const double INV_SQRT_3 = 1.0 / SQRT_3;
	const double C1 = std::cos(2.0 * M_PI / 5.0);
	const double C2 = std::cos(M_PI / 5.0);
	const double S1 = std::sin(2.0 * M_PI / 5.0);
	const double S2 = std::sin(4.0 * M_PI / 5.0);

	const Math::Vector3D trigonalPlanarTemplate[] = {
	    Math::vec(0.0, -1.0, 0.0),
		Math::vec(SQRT_3 * 0.5, 0.5, 0.0),
		Math::vec(SQRT_3 * 0.5, 0.5, 0.0)
	};

	const Math::Vector3D trigonalBipyramidalTemplate[] = {
	    Math::vec(0.0, -1.0, 0.0),
	    Math::vec(0.0, 0.0, 1.0),
	    Math::vec(0.0, 0.0, -1.0),
		Math::vec(SQRT_3 * 0.5, 0.5, 0.0),
		Math::vec(SQRT_3 * 0.5, 0.5, 0.0)
	};

	const Math::Vector3D tetrahedralTemplate[] = {
	    Math::vec(INV_SQRT_3, INV_SQRT_3, INV_SQRT_3),
		Math::vec(INV_SQRT_3, -INV_SQRT_3, -INV_SQRT_3),
		Math::vec(-INV_SQRT_3, INV_SQRT_3, -INV_SQRT_3),
		Math::vec(-INV_SQRT_3, -INV_SQRT_3, INV_SQRT_3)
	};

	const Math::Vector3D squarePlanarTemplate[] = {
	    Math::vec(0.0, 1.0, 0.0),
	    Math::vec(1.0, 0.0, 0.0),
	    Math::vec(0.0, -1.0, 0.0),
	    Math::vec(-1.0, 0.0, 0.0)
	};

	const Math::Vector3D octahedralTemplate[] = {
	    Math::vec(0.0, 1.0, 0.0),
	    Math::vec(1.0, 0.0, 0.0),
	    Math::vec(0.0, -1.0, 0.0),
	    Math::vec(-1.0, 0.0, 0.0),
	    Math::vec(0.0, 0.0, 1.0),
	    Math::vec(0.0, 0.0, -1.0)
	};

	const Math::Vector3D pentagonalBipyramidalTemplate[] = {
	    Math::vec(0.0, 1.0, 0.0),
	    Math::vec(S1, C1, 0.0),
	    Math::vec(S2, -C2, 0.0),
	    Math::vec(-S2, -C2, 0.0),
	    Math::vec(-S1, C1, 0.0),
	    Math::vec(0.0, 0.0, 1.0),
	    Math::vec(0.0, 0.0, -1.0)
	};
}


Chem::Hydrogen3DCoordinatesGenerator::Hydrogen3DCoordinatesGenerator(): undefOnly(true) {}

Chem::Hydrogen3DCoordinatesGenerator::Hydrogen3DCoordinatesGenerator(const MolecularGraph& molgraph, bool undef_only): undefOnly(undef_only) 
{
	generate(molgraph);
}

void Chem::Hydrogen3DCoordinatesGenerator::undefinedOnly(bool undef_only) 
{
	undefOnly = undef_only;
}

bool Chem::Hydrogen3DCoordinatesGenerator::undefinedOnly() const
{
	return undefOnly;
}

const Math::Vector3DArray& Chem::Hydrogen3DCoordinatesGenerator::generate(const MolecularGraph& molgraph)
{
	init(molgraph);
	assignHydrogenCoords();

	return coordinates;
}

const Math::Vector3DArray& Chem::Hydrogen3DCoordinatesGenerator::getResult() const
{
	return coordinates;
}

void Chem::Hydrogen3DCoordinatesGenerator::init(const MolecularGraph& molgraph)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	molGraph = &molgraph;
	
	coordinates.resize(num_atoms);
	
	defCoordsMask.resize(num_atoms);
	defCoordsMask.set();

	centerAtoms.clear();

	for (std::size_t i = 0; i < num_atoms; i++) {
	    const Atom& atom = molgraph.getAtom(i); 

		getConnectedAtoms(atom);

		if (conctdAtoms.size() == 1 && getType(atom) == AtomType::H && has3DCoordinates(molgraph.getAtom(conctdAtoms[0]))) {
			if (undefOnly && has3DCoordinates(atom)) 
				coordinates[i] = get3DCoordinates(atom);
			else 
				defCoordsMask.reset(i);
			
		} else {
		    coordinates[i] = get3DCoordinates(atom);
			centerAtoms.push_back(i);
		}
	}
}

/*
  SP    -> linear
  SP2   -> trigonal planar
  SP3   -> tetrahedral
  DP    -> linear
  SD3   -> tetrahedral
  SP2D  -> square planar
  SP3D  -> trigonal bipyramidal
  SP3D2 -> octahedral
  SP3D3 -> pentagonal bipyramidal
*/

void Chem::Hydrogen3DCoordinatesGenerator::assignHydrogenCoords()
{
	using namespace HybridizationState;

	for (AtomIndexList::const_iterator it = centerAtoms.begin(), end = centerAtoms.end(); it != end; ++it) { 
		std::size_t atom_idx = *it;
		const Atom& atom = molGraph->getAtom(atom_idx);
		std::size_t num_def_atoms = getConnectedAtoms(atom);

		if (num_def_atoms == conctdAtoms.size())
			continue;

		if (num_def_atoms == 0 && conctdAtoms.size() == 1) {
			assignDiatomicMolNbrCoords(atom, atom_idx);
			continue;
		}
		
		switch  (getHybridizationState(atom)) {

			case SP:
			case DP:
				assignLinearGeomCoords(atom, atom_idx, num_def_atoms);
				continue;

			case SP2:

			case SP3:
			case SD3:

			case SP2D:

			case SP3D:

			case SP3D2:

			case SP3D3:

			default:
				break;
		}
	}
}

void Chem::Hydrogen3DCoordinatesGenerator::assignDiatomicMolNbrCoords(const Atom& atom, std::size_t atom_idx)
{
	double b_length = getHydrogenBondLength(atom);
	std::size_t h_index = conctdAtoms[0];

	coordinates[h_index] = coordinates[atom_idx];
	coordinates[h_index](0) += b_length;

	defCoordsMask.set(h_index);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignLinearGeomCoords(const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms)
{

}

std::size_t Chem::Hydrogen3DCoordinatesGenerator::getConnectedAtoms(const Atom& atom)
{
	conctdAtoms.clear();

	std::size_t num_def_atoms = 0;
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		if (!molGraph->containsBond(*b_it))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		std::size_t nbr_idx = molGraph->getAtomIndex(nbr_atom);

		if (defCoordsMask.test(nbr_idx)) {
			conctdAtoms.insert(conctdAtoms.begin() + num_def_atoms, nbr_idx);
			num_def_atoms++;

		} else
			conctdAtoms.push_back(nbr_idx);
	}

	return num_def_atoms;
}

double Chem::Hydrogen3DCoordinatesGenerator::getHydrogenBondLength(const Atom& atom) const
{
	static const double h_cov_rad = getCovalentRadius(AtomType::H, 1);

	double atom_cov_rad = getCovalentRadius(getType(atom), 1);

	if (atom_cov_rad == 0.0)
		return 1.0;

	return (h_cov_rad + atom_cov_rad);
}
