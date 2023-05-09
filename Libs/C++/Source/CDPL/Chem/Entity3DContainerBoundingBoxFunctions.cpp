/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DContainerBoundingBoxFunction.cpp 
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


using namespace CDPL; 


void Chem::calcBoundingBox(const Entity3DContainer& cntnr, Math::Vector3D& min, Math::Vector3D& max, bool reset)
{
	for (Entity3DContainer::ConstEntityIterator it = cntnr.getEntitiesBegin(), end = cntnr.getEntitiesEnd(); it != end; ++it) {
		const Math::Vector3D& coords = get3DCoordinates(*it);

		if (reset) {
			max(0) = coords(0);
			max(1) = coords(1);
			max(2) = coords(2);

			min(0) = coords(0);
			min(1) = coords(1);
			min(2) = coords(2);

			reset = false;
			continue;
		}

		if (coords(0) > max(0))
			max(0) = coords(0);

		else if (coords(0) < min(0))
			min(0) = coords(0);

		if (coords(1) > max(1))
			max(1) = coords(1);

		else if (coords(1) < min(1))
			min(1) = coords(1);

		if (coords(2) > max(2))
			max(2) = coords(2);
			
		else if (coords(2) < min(2))
			min(2) = coords(2);
	}
}	

bool Chem::insideBoundingBox(const Entity3DContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max)
{
	for (Entity3DContainer::ConstEntityIterator it = cntnr.getEntitiesBegin(), end = cntnr.getEntitiesEnd(); it != end; ++it) {
		const Math::Vector3D& coords = get3DCoordinates(*it);

		if (coords(0) <= max(0) && coords(0) >= min(0) &&
			coords(1) <= max(1) && coords(1) >= min(1) &&
			coords(2) <= max(2) && coords(2) >= min(2))
			continue;

		return false;
	}

	return true;
}

bool Chem::intersectsBoundingBox(const Entity3DContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max)
{
	for (Entity3DContainer::ConstEntityIterator it = cntnr.getEntitiesBegin(), end = cntnr.getEntitiesEnd(); it != end; ++it) {
		const Math::Vector3D& coords = get3DCoordinates(*it);

		if (coords(0) <= max(0) && coords(0) >= min(0) &&
			coords(1) <= max(1) && coords(1) >= min(1) &&
			coords(2) <= max(2) && coords(2) >= min(2))
			return true;
	}

	return false;
}

