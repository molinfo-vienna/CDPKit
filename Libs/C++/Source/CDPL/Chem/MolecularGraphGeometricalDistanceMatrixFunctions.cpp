/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphGeometricalDistanceMatrixFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"


using namespace CDPL; 


const Math::DMatrix::SharedPointer& Chem::getGeometricalDistanceMatrix(const MolecularGraph& molgraph)
{
	return molgraph.getProperty<Math::DMatrix::SharedPointer>(MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX);
}

void Chem::setGeometricalDistanceMatrix(MolecularGraph& molgraph, const Math::DMatrix::SharedPointer& mtx)
{
	molgraph.setProperty(MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX, mtx);
}

void Chem::clearGeometricalDistanceMatrix(MolecularGraph& molgraph)
{
	molgraph.removeProperty(MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX);
}

bool Chem::hasGeometricalDistanceMatrix(const MolecularGraph& molgraph)
{
	return molgraph.isPropertySet(MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX);
}

Math::DMatrix::SharedPointer Chem::calcGeometricalDistanceMatrix(MolecularGraph& molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Variant mtx_prop = molgraph.getProperty(MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX);

		if (!mtx_prop.isEmpty())
			return mtx_prop.getData<Math::DMatrix::SharedPointer>();
	}

	Math::DMatrix::SharedPointer mtx_ptr(new Math::DMatrix());

	calcGeometricalDistanceMatrix(molgraph, *mtx_ptr);

	molgraph.setProperty(MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX, mtx_ptr);

	return mtx_ptr;
}
