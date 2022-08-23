/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerGeomDiameterAndRadiusFunctions.cpp 
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
#include <limits>

#include "CDPL/Descr/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


double Descr::calcGeometricalRadius(const Chem::AtomContainer& cntnr, const Chem::Atom3DCoordinatesFunction& coords_func)
{
	using namespace Chem;
	
	if (cntnr.getNumAtoms() <= 1)
		return 0.0;

	double radius = std::numeric_limits<double>::max();

	AtomContainer::ConstAtomIterator atoms_end = cntnr.getAtomsEnd();
	AtomContainer::ConstAtomIterator atoms_beg = cntnr.getAtomsBegin();

	for (AtomContainer::ConstAtomIterator it1 = atoms_beg; it1 != atoms_end; ++it1) {
		const Atom& atom1 = *it1;
		const Math::Vector3D& coords1 = coords_func(atom1);

		double max_atom_dist = 0.0;

		for (AtomContainer::ConstAtomIterator it2 = atoms_beg; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;

			if (&atom1 == &atom2)
				continue;

			const Math::Vector3D& coords2 = coords_func(atom2);

			max_atom_dist = std::max(max_atom_dist, norm2(coords1 - coords2));
		}

		radius = std::min(max_atom_dist, radius);
	}

	return radius;
}

double Descr::calcGeometricalDiameter(const Chem::AtomContainer& cntnr, const Chem::Atom3DCoordinatesFunction& coords_func)
{
	using namespace Chem;

	double diameter = 0.0;

	AtomContainer::ConstAtomIterator atoms_end = cntnr.getAtomsEnd();

	for (AtomContainer::ConstAtomIterator it1 = cntnr.getAtomsBegin(); it1 != atoms_end; ) {
		const Atom& atom1 = *it1;
		const Math::Vector3D& coords1 = coords_func(atom1);

		for (AtomContainer::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;
			const Math::Vector3D& coords2 = coords_func(atom2);

			diameter = std::max(diameter, norm2(coords1 - coords2));
		}
	}

	return diameter;
}
