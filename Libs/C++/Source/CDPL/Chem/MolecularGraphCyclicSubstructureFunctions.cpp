/* 
 * MolecularGraphCyclicSubstructureFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/CyclicSubstructure.hpp"


using namespace CDPL; 


Chem::Fragment::SharedPointer Chem::perceiveCyclicSubstructure(const MolecularGraph& molgraph)
{
	Fragment::SharedPointer substruct_ptr(new CyclicSubstructure(molgraph));

	return substruct_ptr;
}

Chem::Fragment::SharedPointer Chem::perceiveCyclicSubstructure(MolecularGraph& molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Any prev_substruct = molgraph.getProperty(MolecularGraphProperty::CYCLIC_SUBSTRUCTURE, false);
	
		if (!prev_substruct.isEmpty())
			return prev_substruct.getData<Fragment::SharedPointer>();
	}

	Fragment::SharedPointer substruct_ptr(new CyclicSubstructure(molgraph));

	molgraph.setProperty(MolecularGraphProperty::CYCLIC_SUBSTRUCTURE, substruct_ptr);

	return substruct_ptr;
}
