/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphMMFF94AtomTypesFunction.cpp 
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
#include <functional>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Util/Array.hpp"


using namespace CDPL; 


void ForceField::assignMMFF94AtomTypes(Chem::MolecularGraph& molgraph, bool strict, bool overwrite)
{
     if (!overwrite && std::find_if(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
								   boost::bind(std::equal_to<bool>(), false,
											   boost::bind(&hasMMFF94SymbolicType, _1))) == molgraph.getAtomsEnd() &&
		 std::find_if(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
					  boost::bind(std::equal_to<bool>(), false,
								  boost::bind(&hasMMFF94NumericType, _1))) == molgraph.getAtomsEnd())
		return;

	 Util::UIArray num_types;
	 Util::SArray sym_types;

	 MMFF94AtomTyper typer(molgraph, sym_types, num_types, strict);

	 for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
		 setMMFF94SymbolicType(molgraph.getAtom(i), sym_types[i]);
		 setMMFF94NumericType(molgraph.getAtom(i), num_types[i]);
	 }
}
