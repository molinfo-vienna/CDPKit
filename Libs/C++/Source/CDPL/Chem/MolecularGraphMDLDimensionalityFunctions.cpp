/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphMDLDimensionalityFunctions.cpp 
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
#include "CDPL/Chem/MolecularGraphProperty.hpp"


using namespace CDPL; 


std::size_t Chem::getMDLDimensionality(const MolecularGraph& molgraph)
{
	static std::size_t DEF_DIM = 0;

	return molgraph.getPropertyOrDefault<std::size_t>(MolecularGraphProperty::MDL_DIMENSIONALITY, DEF_DIM);
}

void Chem::setMDLDimensionality(MolecularGraph& molgraph, std::size_t dim)
{
	molgraph.setProperty(MolecularGraphProperty::MDL_DIMENSIONALITY, dim);
}

void Chem::clearMDLDimensionality(MolecularGraph& molgraph)
{
	molgraph.removeProperty(MolecularGraphProperty::MDL_DIMENSIONALITY);
}

bool Chem::hasMDLDimensionality(const MolecularGraph& molgraph)
{
	return molgraph.isPropertySet(MolecularGraphProperty::MDL_DIMENSIONALITY);
}
