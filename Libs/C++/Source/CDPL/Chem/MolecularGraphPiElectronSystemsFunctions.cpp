/* 
 * MolecularGraphPiElectronSystemsFunctions.cpp 
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
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/PiElectronSystemList.hpp"


using namespace CDPL; 


Chem::ElectronSystemList::SharedPointer Chem::perceivePiElectronSystems(const MolecularGraph& molgraph)
{
    ElectronSystemList::SharedPointer pi_systems_ptr(new PiElectronSystemList(molgraph));

    return pi_systems_ptr;
}

Chem::ElectronSystemList::SharedPointer Chem::perceivePiElectronSystems(MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
		Base::Any prev_pi_systems = molgraph.getProperty(MolecularGraphProperty::PI_ELECTRON_SYSTEMS, false);
	
		if (!prev_pi_systems.isEmpty())
			return prev_pi_systems.getData<ElectronSystemList::SharedPointer>();
    }

    PiElectronSystemList pi_systems(molgraph);
    ElectronSystemList::SharedPointer pi_systems_ptr(new ElectronSystemList());

    pi_systems_ptr->swap(pi_systems);
	
    setPiElectronSystems(molgraph, pi_systems_ptr);

    return pi_systems_ptr;
}
