/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphAromaticityFlagsFunction.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


void Chem::setAromaticityFlags(MolecularGraph& molgraph, bool overwrite)
{
	using namespace std::placeholders;
	
	if (!overwrite && std::find_if(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
								   std::bind(std::equal_to<bool>(), false,
											 std::bind(static_cast<bool (*)(const Atom&)>(&hasAromaticityFlag), _1))) == molgraph.getAtomsEnd() &&
		std::find_if(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
					 std::bind(std::equal_to<bool>(), false,
							   std::bind(static_cast<bool (*)(const Bond&)>(&hasAromaticityFlag), _1))) == molgraph.getBondsEnd())
		return;

	const Fragment::SharedPointer& arom_substruct = perceiveAromaticSubstructure(molgraph);

	setAromaticSubstructure(molgraph, arom_substruct);

	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
				  std::bind(static_cast<void (*)(Atom&, bool)>(&setAromaticityFlag), _1, 
							std::bind(&Fragment::containsAtom, std::ref(*arom_substruct), _1)));

	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
				  std::bind(static_cast<void (*)(Bond&, bool)>(&setAromaticityFlag), _1, 
							std::bind(&Fragment::containsBond, std::ref(*arom_substruct), _1)));
}
