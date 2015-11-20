/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphMDLScalingFactorFunctions.cpp 
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
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"


using namespace CDPL; 


long Chem::getMDLScalingFactor1(const MolecularGraph& molgraph)
{
	static long DEF_FACTOR = 1;

	return molgraph.getPropertyOrDefault<long>(MolecularGraphProperty::MDL_SCALING_FACTOR1, DEF_FACTOR);
}

void Chem::setMDLScalingFactor1(MolecularGraph& molgraph, long factor)
{
	molgraph.setProperty(MolecularGraphProperty::MDL_SCALING_FACTOR1, factor);
}

void Chem::clearMDLScalingFactor1(MolecularGraph& molgraph)
{
	molgraph.removeProperty(MolecularGraphProperty::MDL_SCALING_FACTOR1);
}

bool Chem::hasMDLScalingFactor1(const MolecularGraph& molgraph)
{
	return molgraph.isPropertySet(MolecularGraphProperty::MDL_SCALING_FACTOR1);
}


double Chem::getMDLScalingFactor2(const MolecularGraph& molgraph)
{
	static double DEF_FACTOR = 1;

	return molgraph.getPropertyOrDefault<double>(MolecularGraphProperty::MDL_SCALING_FACTOR2, DEF_FACTOR);
}

void Chem::setMDLScalingFactor2(MolecularGraph& molgraph, double factor)
{
	molgraph.setProperty(MolecularGraphProperty::MDL_SCALING_FACTOR2, factor);
}

void Chem::clearMDLScalingFactor2(MolecularGraph& molgraph)
{
	molgraph.removeProperty(MolecularGraphProperty::MDL_SCALING_FACTOR2);
}

bool Chem::hasMDLScalingFactor2(const MolecularGraph& molgraph)
{
	return molgraph.isPropertySet(MolecularGraphProperty::MDL_SCALING_FACTOR2);
}
