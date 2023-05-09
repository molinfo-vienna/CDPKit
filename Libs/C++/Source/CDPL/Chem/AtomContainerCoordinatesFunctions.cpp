/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerCoordinatesFunctions.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Util/SequenceFunctions.hpp"


using namespace CDPL; 


bool Chem::hasCoordinates(const AtomContainer& cntnr, std::size_t dim)
{
	if (dim == 3)
		return (std::find_if(cntnr.getAtomsBegin(), cntnr.getAtomsEnd(),
							 boost::bind(std::equal_to<bool>(), false,
										 boost::bind(&has3DCoordinates, _1))) == cntnr.getAtomsEnd());

	return (std::find_if(cntnr.getAtomsBegin(), cntnr.getAtomsEnd(),
						 boost::bind(std::equal_to<bool>(), false,
									 boost::bind(&has2DCoordinates, _1))) == cntnr.getAtomsEnd());
}

void Chem::get2DCoordinates(const AtomContainer& cntnr, Math::Vector2DArray& coords, bool append)
{
	if (!append)
		coords.clear();

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		coords.addElement(get2DCoordinates(*it));
}

void Chem::set2DCoordinates(AtomContainer& cntnr, const Math::Vector2DArray& coords)
{
	Util::forEachPair(cntnr.getAtomsBegin(), cntnr.getAtomsEnd(), coords.getElementsBegin(), coords.getElementsEnd(),
					  static_cast<void (*)(Atom&, const Math::Vector2D&)>(&set2DCoordinates));
}

void Chem::transform2DCoordinates(AtomContainer& cntnr, const Math::Matrix3D& mtx)
{
	Math::Vector3D tmp1;
	Math::Vector3D tmp2;
	Math::Vector2D tmp3;

	tmp1[2] = 1.0;

	for (AtomContainer::AtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;
		const Math::Vector2D& coords = get2DCoordinates(atom);

		tmp1[0] = coords[0];
		tmp1[1] = coords[1];

		prod(mtx, tmp1, tmp2);

		tmp3[0] = tmp2[0];
		tmp3[1] = tmp2[1];

		set2DCoordinates(atom, tmp3);
	}
}

void Chem::get3DCoordinates(const AtomContainer& cntnr, Math::Vector3DArray& coords, const Atom3DCoordinatesFunction& coords_func, bool append)
{
	if (!append)
		coords.clear();

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		coords.addElement(coords_func(*it));
}
