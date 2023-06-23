/* 
 * Entity3DContainerGeometricalDistanceMatrixFunction.cpp 
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


using namespace CDPL; 


void Chem::calcGeometricalDistanceMatrix(const Entity3DContainer& cntnr, Math::DMatrix& mtx)
{
	std::size_t num_entities = cntnr.getNumEntities();

	mtx.resize(num_entities, num_entities, false);
	mtx.clear();

	for (std::size_t i = 0; i < num_entities; ) {
		const Entity3D& entity1 = cntnr.getEntity(i);
		const Math::Vector3D& coords1 = get3DCoordinates(entity1);

		for (std::size_t j = ++i; j < num_entities; j++) {
			const Entity3D& entity2 = cntnr.getEntity(j);
			const Math::Vector3D& coords2 = get3DCoordinates(entity2);

			double dist = norm2(coords1 - coords2);

			mtx(i, j) = dist;
			mtx(j, i) = dist;
		}
	}
}
