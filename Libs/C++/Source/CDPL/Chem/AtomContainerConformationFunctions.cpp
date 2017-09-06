/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerConformationFunctions.cpp 
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

#include <algorithm>
#include <limits>

#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"


using namespace CDPL; 


std::size_t Chem::getNumConformations(const AtomContainer& cntnr)
{
	std::size_t num_confs = std::numeric_limits<std::size_t>::max();

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!has3DCoordinatesArray(atom))
			return 0;

		const Math::Vector3DArray::SharedPointer& coords_array = get3DCoordinatesArray(atom);
		
		num_confs = std::min(num_confs, coords_array->getSize());
	}

	return (num_confs == std::numeric_limits<std::size_t>::max() ? 0 : num_confs);
}

void Chem::applyConformation(AtomContainer& cntnr, std::size_t conf_idx)
{
	for (AtomContainer::AtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		set3DCoordinates(atom, (*get3DCoordinatesArray(atom))[conf_idx]);
	}
}

void Chem::getConformation(const AtomContainer& cntnr, std::size_t conf_idx, Math::Vector3DArray& coords)
{
	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		coords.addElement((*get3DCoordinatesArray(*it))[conf_idx]);
}

void Chem::setConformation(AtomContainer& cntnr, std::size_t conf_idx, const Math::Vector3DArray& coords)
{
	for (std::size_t i = 0, num_atoms = cntnr.getNumAtoms(); i < num_atoms; i++)
		(*get3DCoordinatesArray(cntnr.getAtom(i)))[conf_idx] = coords[i];
}

void Chem::addConformation(AtomContainer& cntnr, const Math::Vector3DArray& coords)
{
	std::size_t i = 0;
	
	for (AtomContainer::AtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it, i++) {
		Atom& atom = *it;
		Math::Vector3DArray::SharedPointer coords_array;

		if (!has3DCoordinatesArray(atom)) {
			coords_array.reset(new Math::Vector3DArray());

			set3DCoordinatesArray(atom, coords_array);

		} else
			coords_array = get3DCoordinatesArray(atom);
		
		coords_array->addElement(coords[i]);
	}
}

void Chem::transformConformation(AtomContainer& cntnr, std::size_t conf_idx, const Math::Matrix4D& mtx)
{
	Math::Vector4D tmp1;
	Math::Vector4D tmp2;

	tmp1[3] = 1.0;

	for (AtomContainer::AtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;
		Math::Vector3DArray& coords_array = *get3DCoordinatesArray(atom);

		tmp1[0] = coords_array[conf_idx][0];
		tmp1[1] = coords_array[conf_idx][1];
		tmp1[2] = coords_array[conf_idx][2];

		prod(mtx, tmp1, tmp2);

		coords_array[conf_idx][0] = tmp2[0];
		coords_array[conf_idx][1] = tmp2[1];
		coords_array[conf_idx][2] = tmp2[2];
	}
}

void Chem::transformConformations(AtomContainer& cntnr, const Math::Matrix4D& mtx)
{
	for (AtomContainer::AtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		transform(*get3DCoordinatesArray(*it), mtx);
}
