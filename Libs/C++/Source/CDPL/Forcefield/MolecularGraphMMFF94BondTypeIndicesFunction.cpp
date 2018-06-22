/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphMMFF94BondTypeIndicesFunction.cpp 
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
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Forcefield/MolecularGraphFunctions.hpp"
#include "CDPL/Forcefield/BondFunctions.hpp"
#include "CDPL/Forcefield/MMFF94BondTyper.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Util/Array.hpp"


using namespace CDPL; 


void Forcefield::assignMMFF94BondTypeIndices(Chem::MolecularGraph& molgraph, bool overwrite)
{
     if (!overwrite && std::find_if(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
									boost::bind(std::equal_to<bool>(), false,
												boost::bind(&hasMMFF94TypeIndex, _1))) == molgraph.getBondsEnd())
		return;

	 Util::UIArray types;
	 MMFF94BondTyper typer(molgraph, types);

	 for (std::size_t i = 0, num_bonds = molgraph.getNumBonds(); i < num_bonds; i++) 
		 setMMFF94TypeIndex(molgraph.getBond(i), types[i]);
}
