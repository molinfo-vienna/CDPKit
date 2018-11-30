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
#include <limits>
#include <algorithm>

#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Internal/Permutation.hpp"


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
		Math::vec(-SQRT_3 * 0.5, 0.5, 0.0),
		Math::vec(SQRT_3 * 0.5, 0.5, 0.0)
	};

	const Math::Vector3D trigonalBipyramidalTemplate[] = {
	    Math::vec(0.0, 0.0, 1.0),
	    Math::vec(0.0, -1.0, 0.0),
	    Math::vec(0.0, 0.0, -1.0),
		Math::vec(-SQRT_3 * 0.5, 0.5, 0.0),
		Math::vec(SQRT_3 * 0.5, 0.5, 0.0)
	};

	const std::size_t trigonalBipyramidalCoordPerms[] = {
	    0, 3, 6, 8,

	    0, 1, 2, 3, 4, 
		0, 2, 1, 3, 4, 
		2, 3, 4, 0, 1, 

		0, 1, 2, 3, 4, 
		0, 2, 3, 1, 4, 
		2, 3, 4, 0, 1,

		0, 1, 2, 3, 4, 
		0, 2, 3, 4, 1
	};

	const Math::Vector3D tetrahedralTemplate[] = {
	    Math::vec(INV_SQRT_3, INV_SQRT_3, INV_SQRT_3),
		Math::vec(INV_SQRT_3, -INV_SQRT_3, -INV_SQRT_3),
		Math::vec(-INV_SQRT_3, INV_SQRT_3, -INV_SQRT_3),
		Math::vec(-INV_SQRT_3, -INV_SQRT_3, INV_SQRT_3)
	};

	const std::size_t tetrahedralCoordPerms[] = {
	    0, 1, 2, 

		0, 1, 2, 3,

		0, 1, 2, 3
	};

	const Math::Vector3D squarePlanarTemplate[] = {
	    Math::vec(0.0, 1.0, 0.0),
	    Math::vec(1.0, 0.0, 0.0),
	    Math::vec(0.0, -1.0, 0.0),
	    Math::vec(-1.0, 0.0, 0.0)
	};

	const std::size_t squarePlanarCoordPerms[] = {
	    0, 2, 3, 

		0, 1, 2, 3,
		0, 2, 1, 3,

		0, 1, 2, 3
	};

	const Math::Vector3D octahedralTemplate[] = {
	    Math::vec(0.0, 1.0, 0.0),
	    Math::vec(1.0, 0.0, 0.0),
	    Math::vec(0.0, -1.0, 0.0),
	    Math::vec(-1.0, 0.0, 0.0),
	    Math::vec(0.0, 0.0, 1.0),
	    Math::vec(0.0, 0.0, -1.0)
	};

	const std::size_t octahedralCoordPerms[] = {
	    0, 2, 4, 6, 7,

		0, 1, 2, 3, 4, 5,
		0, 2, 1, 3, 4, 5,

		0, 1, 2, 3, 4, 5,
		0, 1, 4, 2, 3, 5,
	
		0, 1, 2, 3, 4, 5,
		0, 1, 2, 4, 3, 5,

		0, 1, 2, 3, 4, 5
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

	const std::size_t pentagonalBipyramidalCoordPerms[] = {
	    0, 4, 9, 14, 18, 20,

		0, 1, 2, 3, 4, 5, 6,
		0, 2, 1, 3, 4, 5, 6,
		0, 5, 1, 2, 3, 4, 6,
		5, 6, 0, 1, 2, 3, 4,

		0, 1, 2, 3, 4, 5, 6,
		0, 1, 3, 2, 4, 5, 6,
		0, 1, 5, 2, 4, 3, 6,
		0, 2, 5, 1, 4, 3, 6,
		0, 5, 6, 1, 2, 3, 4,

		0, 1, 2, 3, 4, 5, 6,
		0, 1, 2, 5, 3, 4, 6,
		0, 1, 3, 5, 2, 4, 6,
		5, 6, 0, 1, 2, 3, 4,
		5, 6, 0, 2, 1, 3, 4,

		0, 1, 2, 3, 4, 5, 6,
		0, 1, 2, 3, 5, 4, 6,
		0, 1, 2, 5, 6, 3, 4,
		0, 1, 3, 5, 6, 2, 4,

		0, 1, 2, 3, 4, 5, 6,
		0, 1, 2, 3, 5, 6, 4
	};

	const std::size_t MAX_TEMPLATE_SIZE = 7;
}


Chem::Hydrogen3DCoordinatesGenerator::Hydrogen3DCoordinatesGenerator(): 
	molGraph(0), undefOnly(true), coordsFunc(&get3DCoordinates), hasCoordsFunc(&has3DCoordinates)
{}

Chem::Hydrogen3DCoordinatesGenerator::Hydrogen3DCoordinatesGenerator(
	const MolecularGraph& molgraph, Math::Vector3DArray& coords, bool undef_only): 
	undefOnly(undef_only), coordsFunc(&get3DCoordinates), hasCoordsFunc(&has3DCoordinates)  
{
	generate(molgraph, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::undefinedOnly(bool undef_only) 
{
	undefOnly = undef_only;
}

bool Chem::Hydrogen3DCoordinatesGenerator::undefinedOnly() const
{
	return undefOnly;
}

void Chem::Hydrogen3DCoordinatesGenerator::setAtom3DCoordinatesCheckFunction(const AtomPredicate& func)
{
	hasCoordsFunc = func;
}

const Chem::AtomPredicate& Chem::Hydrogen3DCoordinatesGenerator::getAtom3DCoordinatesCheckFunction() const
{
	return hasCoordsFunc;
}

void Chem::Hydrogen3DCoordinatesGenerator::setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func)
{
	coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction& Chem::Hydrogen3DCoordinatesGenerator::getAtom3DCoordinatesFunction() const
{
	return coordsFunc;
}

void Chem::Hydrogen3DCoordinatesGenerator::generate(const MolecularGraph& molgraph, Math::Vector3DArray& coords, bool init_coords)
{
	setup(molgraph);
	assignCoordinates(coords, init_coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::generate(Math::Vector3DArray& coords, bool init_coords)
{
	if (!molGraph)
		return;

	assignCoordinates(coords, init_coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::setup(const MolecularGraph& molgraph)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	molGraph = &molgraph;
	
	defCoordsMask.resize(num_atoms);
	defCoordsMask.set();

	centerAtoms.clear();

	for (std::size_t i = 0; i < num_atoms; i++) {
	    const Atom& atom = molgraph.getAtom(i); 

		getConnectedAtoms(atom, conctdAtoms);

		if (conctdAtoms.size() == 1 && getType(atom) == AtomType::H) {
			if (!undefOnly || !hasCoordsFunc(atom))
				defCoordsMask.reset(i);
			
		} else 
			centerAtoms.push_back(i);
	}
}

void Chem::Hydrogen3DCoordinatesGenerator::assignCoordinates(Math::Vector3DArray& coords, bool init_coords)
{
	using namespace HybridizationState;
	
	if (init_coords) {
		coords.resize(molGraph->getNumAtoms());

		for (std::size_t i = 0, num_atoms = molGraph->getNumAtoms(); i < num_atoms; i++) 
			if (defCoordsMask.test(i))
				coords[i] = coordsFunc(molGraph->getAtom(i));
	}

	savedCoordsMask = defCoordsMask;

	for (AtomIndexList::const_iterator it = centerAtoms.begin(), end = centerAtoms.end(); it != end; ++it) { 
		std::size_t atom_idx = *it;
		const Atom& atom = molGraph->getAtom(atom_idx);
		std::size_t num_def_atoms = getConnectedAtoms(atom, conctdAtoms);

		if (num_def_atoms == conctdAtoms.size())
			continue;

		if (num_def_atoms == 0 && conctdAtoms.size() == 1) {
			assignDiatomicMolCoords(atom, atom_idx, coords);
			continue;
		}
		
		switch (getHybridizationState(atom, num_def_atoms)) {

			case SP:
			case DP:
				assignLinearCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			case SP2:
				assignTrigonalPlanarCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			case SP3:
			case SD3:
				assignTetrahedralCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			case SP2D:
				assignSquarePlanarCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			case SP3D:
				assignTrigonalBipyramidalCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			case SP3D2:
				assignOctahedralCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			case SP3D3:
				assignPentagonalBipyramidalCoords(atom, atom_idx, num_def_atoms, coords);
				continue;

			default:
				assignEvenlyDistributedCoords(atom, atom_idx, num_def_atoms, coords);
				break;
		}
	}

	savedCoordsMask.swap(defCoordsMask);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignDiatomicMolCoords(
	const Atom& atom, std::size_t atom_idx, Math::Vector3DArray& coords)
{
	double b_length = getHydrogenBondLength(atom);
	std::size_t h_index = conctdAtoms[0];

	coords[h_index].assign(coords[atom_idx]);
	coords[h_index](0) += b_length;
	defCoordsMask.set(h_index);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignLinearCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 2)
		return assignTrigonalPlanarCoords(atom, atom_idx, num_def_atoms, coords);

	double b_length = getHydrogenBondLength(atom);

	if (num_def_atoms == 0) {
		for (std::size_t i = 0; i < 2; i++) {
			std::size_t h_index = conctdAtoms[i];

			coords[h_index].assign(coords[atom_idx]);
			coords[h_index](0) += b_length * (i == 0 ? 1.0 : -1.0);
			defCoordsMask.set(h_index);
		}

		return;
	}

	std::size_t h_index = conctdAtoms[1];

	coords[h_index].assign(coords[atom_idx] - coords[conctdAtoms[0]]);
	coords[h_index] *= b_length / length(coords[h_index]); 
	coords[h_index].plusAssign(coords[atom_idx]);
	defCoordsMask.set(h_index);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignTrigonalPlanarCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 3)
		return assignTetrahedralCoords(atom, atom_idx, num_def_atoms, coords);

	assignTemplateCoords(atom, atom_idx, num_def_atoms, 3, trigonalPlanarTemplate, 0, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignTetrahedralCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 4)
		return assignTrigonalBipyramidalCoords(atom, atom_idx, num_def_atoms, coords);

	if (num_def_atoms < 3)
		assignTemplateCoords(atom, atom_idx, num_def_atoms, 4, tetrahedralTemplate, 0, coords);
	else
		assignTemplateCoords(atom, atom_idx, num_def_atoms, 4, tetrahedralTemplate, tetrahedralCoordPerms, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignSquarePlanarCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 4)
		return assignOctahedralCoords(atom, atom_idx, num_def_atoms, coords);

	assignTemplateCoords(atom, atom_idx, num_def_atoms, 4, squarePlanarTemplate, squarePlanarCoordPerms, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignTrigonalBipyramidalCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 5)
		return assignOctahedralCoords(atom, atom_idx, num_def_atoms, coords);

	assignTemplateCoords(atom, atom_idx, num_def_atoms, 5, trigonalBipyramidalTemplate, trigonalBipyramidalCoordPerms, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignOctahedralCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 6)
		return assignPentagonalBipyramidalCoords(atom, atom_idx, num_def_atoms, coords);

	assignTemplateCoords(atom, atom_idx, num_def_atoms, 6, octahedralTemplate, octahedralCoordPerms, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignPentagonalBipyramidalCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	if (conctdAtoms.size() > 7)
		return assignEvenlyDistributedCoords(atom, atom_idx, num_def_atoms, coords);

	assignTemplateCoords(atom, atom_idx, num_def_atoms, 7, pentagonalBipyramidalTemplate, pentagonalBipyramidalCoordPerms, coords);
}

void Chem::Hydrogen3DCoordinatesGenerator::assignEvenlyDistributedCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, Math::Vector3DArray& coords)
{
	std::size_t num_points = conctdAtoms.size();

	// Golden section spiral point distribution

	genPoints.resize(num_points);

	double inc = M_PI * (3.0 - std::sqrt(5.0));
	double off = 2.0 / num_points;

	for (std::size_t i = 0; i < num_points; i++) {
		double y = i * off - 1.0 + off * 0.5;
		double r = std::sqrt(1.0 - y * y);
		double phi = i * inc;
		
		genPoints[i](0) = std::cos(phi) * r;
		genPoints[i](1) = y;
		genPoints[i](2) = std::sin(phi) * r;
	}

	if (num_def_atoms < 2) {
		assignTemplateCoords(atom, atom_idx, num_def_atoms, num_points, &genPoints[0], 0, coords);
		return;
	}

	refPoints.resize(3, 3, false);
	tmpltPoints.resize(3, 3, false);

	column(refPoints, 0) = Math::ZeroVector<double>(3);
	column(tmpltPoints, 0) = Math::ZeroVector<double>(3);

	Math::Vector3D b_vec1 = coords[conctdAtoms[0]] - coords[atom_idx];
	Math::Vector3D b_vec2 = coords[conctdAtoms[1]] - coords[atom_idx];

	b_vec1 /= length(b_vec1);
	b_vec2 /= length(b_vec2);

	double ref_ang_cos = innerProd(b_vec1, b_vec2);
	double best_align_ang_diff = std::numeric_limits<double>::max();
	std::size_t best_align_pos_idx = 0;

	for (std::size_t i = 1; i < num_points; i++) {
		double ang_cos = innerProd(genPoints[i], genPoints[0]);
		double cos_diff = std::abs(ang_cos - ref_ang_cos);

		if (cos_diff < best_align_ang_diff) {
			best_align_pos_idx = cos_diff;
			best_align_pos_idx = i;
		}
	}

	column(refPoints, 1) = b_vec1;
	column(refPoints, 2) = b_vec2;
	column(tmpltPoints, 1) = genPoints[0];
	column(tmpltPoints, 2) = genPoints[best_align_pos_idx];

	if (!kabschAlgo.align(tmpltPoints, refPoints, false)) 
		return;

	usedPosMask.resize(num_points);
	usedPosMask.reset();
	usedPosMask.set(best_align_pos_idx);

	Math::Matrix3D tmplt_xform = range(kabschAlgo.getTransform(), 0, 3, 0, 3);

	for (std::size_t i = 1; i < num_points; i++) {
		b_vec1.assign(prod(tmplt_xform, genPoints[i]));
		genPoints[i].assign(b_vec1);
	}

	for (std::size_t i = 2; i < num_def_atoms; i++) {
		b_vec1.assign(coords[conctdAtoms[i]] - coords[atom_idx]);
		b_vec1 /= length(b_vec1);

		std::size_t nearest_tmplt_pos_idx = 0;
		double largest_ang_cos = -2.0;
		
		for (std::size_t j = 1; j < num_points; j++) {
			if (usedPosMask.test(j))
				continue;

			double ang_cos = innerProd(b_vec1, genPoints[j]);

			if (ang_cos > largest_ang_cos) {
				nearest_tmplt_pos_idx = j;
				largest_ang_cos = ang_cos;
			}
		}
		
		usedPosMask.set(nearest_tmplt_pos_idx);
	}

	double b_length = getHydrogenBondLength(atom);

	for (std::size_t i = num_def_atoms, j = 1; i < num_points; i++) {
		for ( ; usedPosMask.test(j); j++);

		std::size_t h_index = conctdAtoms[i];

		coords[h_index].assign(genPoints[j++] * b_length + coords[atom_idx]);
		defCoordsMask.set(h_index);
	}
}

void Chem::Hydrogen3DCoordinatesGenerator::assignTemplateCoords(
	const Atom& atom, std::size_t atom_idx, std::size_t num_def_atoms, std::size_t tmplt_size, 
	const Math::Vector3D tmplt[], const std::size_t* tmplt_perms, Math::Vector3DArray& coords)
{
	std::size_t num_cnctd_atoms = conctdAtoms.size();
	double b_length = getHydrogenBondLength(atom);

	if (num_def_atoms == 0) {
		for (std::size_t i = 0; i < num_cnctd_atoms; i++) {
			std::size_t h_index = conctdAtoms[i];

			coords[h_index].assign(tmplt[i] * b_length + coords[atom_idx]);
			defCoordsMask.set(h_index);
		}

		return;
	}

	if (num_def_atoms == 1) {
		Math::Vector3D ref_vec;	getRotationReferenceVector(atom, atom_idx, conctdAtoms[0], num_def_atoms, ref_vec, coords);
		Math::Vector3D bond_vec = coords[conctdAtoms[0]] - coords[atom_idx];
		Math::Matrix3D ctr_atom_basis; buildOrthogonalBasis(bond_vec, ref_vec, ctr_atom_basis, false);
		Math::Matrix3D tmplt_basis; buildOrthogonalBasis(tmplt[0], tmplt[1], tmplt_basis, true);
		Math::Matrix3D tmplt_xform = prod(ctr_atom_basis, tmplt_basis);

		for (std::size_t i = 1; i < num_cnctd_atoms; i++) {
			std::size_t h_index = conctdAtoms[i];

			coords[h_index].assign(prod(tmplt_xform, tmplt[i] * b_length) + coords[atom_idx]);
			defCoordsMask.set(h_index);
		}
		
		return;
	}

	std::size_t num_tmplt_perms = (tmplt_perms ? tmplt_perms[num_def_atoms - 1] - tmplt_perms[num_def_atoms - 2] : 0); 

	refPoints.resize(3, num_def_atoms + 1, false);
	tmpltPoints.resize(3, num_def_atoms + 1, false);

	column(refPoints, 0) = Math::ZeroVector<double>(3);
	column(tmpltPoints, 0) = Math::ZeroVector<double>(3);

	if (num_tmplt_perms > 0) {
		tmplt_perms += (tmplt_perms[num_def_atoms - 2] + 1) * tmplt_size - 1;

		for (std::size_t i = 0; i < num_def_atoms; i++) {
			Math::Vector3D tmp = coords[conctdAtoms[i]] - coords[atom_idx];
			tmp /= length(tmp);

			column(refPoints, i + 1).assign(tmp);
		}

		std::size_t num_def_atom_perms = Math::factorial<std::size_t>(num_def_atoms);
		std::size_t curr_tmplt_perm[MAX_TEMPLATE_SIZE];
		std::size_t best_tmplt_perm[MAX_TEMPLATE_SIZE];
		double best_rmsd = std::numeric_limits<double>::max();
		Math::Matrix3D best_tmplt_xform;
 
		for (std::size_t i = 0; i < num_tmplt_perms; i++, tmplt_perms += tmplt_size) {
			std::copy(tmplt_perms, tmplt_perms + tmplt_size, curr_tmplt_perm);
			
			for (std::size_t j = 0; j < num_def_atom_perms; j++) {
				for (std::size_t k = 0; k < num_def_atoms; k++)
					column(tmpltPoints, k + 1).assign(tmplt[curr_tmplt_perm[k]]);

				if (kabschAlgo.align(tmpltPoints, refPoints, false)) {
					Math::Matrix3D tmplt_xform = range(kabschAlgo.getTransform(), 0, 3, 0, 3);
					double rmsd = 0.0;
					
					for (std::size_t k = 0; k < num_def_atoms; k++) {
						Math::Vector3D tmp = column(refPoints, k + 1) - prod(tmplt_xform, tmplt[curr_tmplt_perm[k]]);
						rmsd += innerProd(tmp, tmp);
					}

					rmsd = std::sqrt(rmsd / num_def_atoms);

					if (rmsd < best_rmsd) {
						best_tmplt_xform.assign(tmplt_xform);
						std::copy(curr_tmplt_perm, curr_tmplt_perm + tmplt_size, best_tmplt_perm);
						best_rmsd = rmsd;
					}
				}

				Internal::nextPermutation(curr_tmplt_perm, curr_tmplt_perm + num_def_atoms);
			}
		}

		for (std::size_t i = num_def_atoms; i < num_cnctd_atoms; i++) {
			std::size_t h_index = conctdAtoms[i];

			coords[h_index].assign(prod(best_tmplt_xform, tmplt[best_tmplt_perm[i]] * b_length) + coords[atom_idx]);
			defCoordsMask.set(h_index);
		}

	} else {
		for (std::size_t i = 0; i < num_def_atoms; i++) {
			Math::Vector3D tmp = coords[conctdAtoms[i]] - coords[atom_idx];
			tmp /= length(tmp);

			column(refPoints, i + 1).assign(tmp);
			column(tmpltPoints, i + 1).assign(tmplt[i]);
		}

		if (kabschAlgo.align(tmpltPoints, refPoints, false)) {
			Math::Matrix3D tmplt_xform = range(kabschAlgo.getTransform(), 0, 3, 0, 3);

			for (std::size_t i = num_def_atoms; i < num_cnctd_atoms; i++) {
				std::size_t h_index = conctdAtoms[i];

				coords[h_index].assign(prod(tmplt_xform, tmplt[i] * b_length) + coords[atom_idx]);
				defCoordsMask.set(h_index);
			}
		}
	}
}

std::size_t Chem::Hydrogen3DCoordinatesGenerator::getConnectedAtoms(const Atom& atom, AtomIndexList& con_atoms)
{
	std::size_t num_def_atoms = 0;
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	con_atoms.clear();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		if (!molGraph->containsBond(*b_it))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		std::size_t nbr_idx = molGraph->getAtomIndex(nbr_atom);

		if (defCoordsMask.test(nbr_idx)) {
			con_atoms.insert(con_atoms.begin() + num_def_atoms, nbr_idx);
			num_def_atoms++;

		} else
			con_atoms.push_back(nbr_idx);
	}

	return num_def_atoms;
}

bool Chem::Hydrogen3DCoordinatesGenerator::getConnectedAtomWithCoords(
	std::size_t atom_idx, const Atom& excl_atom, std::size_t& con_atom_idx) const
{
	const Atom& atom = molGraph->getAtom(atom_idx);
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		if (!molGraph->containsBond(*b_it))
			continue;

		const Atom& nbr_atom = *a_it;

		if (&nbr_atom == &excl_atom)
			continue;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		std::size_t nbr_idx = molGraph->getAtomIndex(nbr_atom);

		if (defCoordsMask.test(nbr_idx)) {
			con_atom_idx = nbr_idx;
			return true;
		}
	}

	return false;
}

double Chem::Hydrogen3DCoordinatesGenerator::getHydrogenBondLength(const Atom& atom) const
{
	double atom_cov_rad = AtomDictionary::getCovalentRadius(getType(atom), 1);

	if (atom_cov_rad == 0.0)
		return 1.0;

	const double h_cov_rad = AtomDictionary::getCovalentRadius(AtomType::H, 1);

	return (h_cov_rad + atom_cov_rad);
}

unsigned int Chem::Hydrogen3DCoordinatesGenerator::getHybridizationState(
	const Atom& atom, std::size_t num_def_atoms) const
{
	unsigned int state = Chem::getHybridizationState(atom);

	if (state == HybridizationState::UNKNOWN)
		state = HybridizationState::SP3;

	if (state == HybridizationState::SP3) {
		switch (getType(atom)) {

			case AtomType::N:
			case AtomType::O:
			case AtomType::S:
			case AtomType::Se:
				if (conctdAtoms.size() > 3)
					return state;

				for (std::size_t i = 0; i < num_def_atoms; i++) {
					const Atom& nbr_atom = molGraph->getAtom(conctdAtoms[i]);
					
					if (getAromaticityFlag(nbr_atom) || getExplicitBondCount(nbr_atom, *molGraph, 2) > 0)
						return HybridizationState::SP2;
				}

			default:
				return state;
		}
	}

	return state;
}

void Chem::Hydrogen3DCoordinatesGenerator::buildOrthogonalBasis(
	const Math::Vector3D& v1, const Math::Vector3D& v2, Math::Matrix3D& basis, bool transp) const
{
	if (transp) {
		row(basis, 0) = v1 / length(v1);
		row(basis, 2) = crossProd(v1, v2);
		row(basis, 2) /= length(row(basis, 2));
		row(basis, 1) = crossProd(row(basis, 2), row(basis, 0));

		return;
	}

	column(basis, 0) = v1 / length(v1);
	column(basis, 2) = crossProd(v1, v2);
	column(basis, 2) /= length(column(basis, 2));
	column(basis, 1) = crossProd(column(basis, 2), column(basis, 0));
}

void Chem::Hydrogen3DCoordinatesGenerator::getRotationReferenceVector(
	const Atom& atom, std::size_t atom_idx, std::size_t nbr_atom_idx, 
	std::size_t num_def_atoms, Math::Vector3D& ref_vec, Math::Vector3DArray& coords) const
{
	using namespace HybridizationState;

	std::size_t ref_atom_idx;

	if (getConnectedAtomWithCoords(nbr_atom_idx, atom, ref_atom_idx)) {
		switch (getHybridizationState(atom, num_def_atoms)) {

			case SP2:
				if (Chem::getHybridizationState(molGraph->getAtom(nbr_atom_idx)) == SP2) {
					ref_vec.assign(coords[ref_atom_idx] - coords[nbr_atom_idx]);
					return;
				}

				ref_vec.assign(crossProd(coords[atom_idx] - coords[nbr_atom_idx],
										 coords[ref_atom_idx] - coords[nbr_atom_idx]));
				return;

			case SP3:
			case SD3:
				if (Chem::getHybridizationState(molGraph->getAtom(nbr_atom_idx)) == SP2) {
					ref_vec.assign(crossProd(coords[atom_idx] - coords[nbr_atom_idx],
											 coords[ref_atom_idx] - coords[nbr_atom_idx]));
					return;
				}

			default:
				ref_vec.assign(coords[nbr_atom_idx] - coords[ref_atom_idx]);
				return;
		}
	}

	Math::Vector3D tmp = coords[nbr_atom_idx] - coords[atom_idx];

	getPerpendicularVector(tmp, ref_vec);
}

void Chem::Hydrogen3DCoordinatesGenerator::getPerpendicularVector(
	const Math::Vector3D& v, Math::Vector3D& perp_vec) const
{
	if (v(0) != 0) {
		perp_vec(0) = v(1);
		perp_vec(1) = -v(0);
		perp_vec(2) = 0.0;
		return;
	}
	
	if (v(1) != 0) {
		perp_vec(0) = -v(1);
		perp_vec(1) = v(0);
		perp_vec(2) = 0.0;
		return;
	}
	
	perp_vec(0) = 0.0;
	perp_vec(1) = -v(2);
	perp_vec(2) = v(1);
}
