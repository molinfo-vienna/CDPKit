/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DContainerCoordinatesFunctions.cpp 
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

#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/Entity3D.hpp"
#include "CDPL/Util/SequenceFunctions.hpp"


using namespace CDPL; 


void Chem::get3DCoordinates(const Entity3DContainer& cntnr, Math::Vector3DArray& coords, bool append)
{
	if (!append)
		coords.clear();

	for (Entity3DContainer::ConstEntityIterator it = cntnr.getEntitiesBegin(), end = cntnr.getEntitiesEnd(); it != end; ++it)
		coords.addElement(get3DCoordinates(*it));
}

void Chem::set3DCoordinates(Entity3DContainer& cntnr, const Math::Vector3DArray& coords)
{
	Util::forEachPair(cntnr.getEntitiesBegin(), cntnr.getEntitiesEnd(), coords.getElementsBegin(), coords.getElementsEnd(),
				  static_cast<void (*)(Entity3D&, const Math::Vector3D&)>(&set3DCoordinates));
}

void Chem::transform3DCoordinates(Entity3DContainer& cntnr, const Math::Matrix4D& mtx)
{
	Math::Vector4D tmp1;
	Math::Vector4D tmp2;
	Math::Vector3D tmp3;

	tmp1[3] = 1.0;

	for (Entity3DContainer::EntityIterator it = cntnr.getEntitiesBegin(), end = cntnr.getEntitiesEnd(); it != end; ++it) {
		Entity3D& ent = *it;
		const Math::Vector3D& coords = get3DCoordinates(ent);

		tmp1[0] = coords[0];
		tmp1[1] = coords[1];
		tmp1[2] = coords[2];

		prod(mtx, tmp1, tmp2);

		tmp3[0] = tmp2[0];
		tmp3[1] = tmp2[1];
		tmp3[2] = tmp2[2];

		set3DCoordinates(ent, tmp3);
	}
}
