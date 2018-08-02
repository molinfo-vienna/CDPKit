/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsInteractionParameterizer.cpp 
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

#include <string>

#include <boost/lexical_cast.hpp>

#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionParameterizer.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


ForceField::MMFF94VanDerWaalsInteractionParameterizer::MMFF94VanDerWaalsInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
																								 MMFF94VanDerWaalsInteractionData& ia_data):
	filterFunc(), typeFunc(&getMMFF94NumericType), distFunc(&Chem::getTopologicalDistance),
	paramTable(MMFF94VanDerWaalsParameterTable::get())
{
    parameterize(molgraph, ia_data);
}

ForceField::MMFF94VanDerWaalsInteractionParameterizer::MMFF94VanDerWaalsInteractionParameterizer() :
	filterFunc(), typeFunc(&getMMFF94NumericType), distFunc(&Chem::getTopologicalDistance),
	paramTable(MMFF94VanDerWaalsParameterTable::get())
{}

void ForceField::MMFF94VanDerWaalsInteractionParameterizer::setFilterFunction(const InteractionFilterFunction2& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94VanDerWaalsInteractionParameterizer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	typeFunc = func;
}  

void ForceField::MMFF94VanDerWaalsInteractionParameterizer::setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func)
{
	distFunc = func;
}  

void ForceField::MMFF94VanDerWaalsInteractionParameterizer::setVanDerWaalsParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94VanDerWaalsInteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, 
																		 MMFF94VanDerWaalsInteractionData& ia_data)
{
	using namespace Chem;

	typedef MMFF94VanDerWaalsParameterTable::Entry ParamEntry;

	ia_data.clear();

	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
		const Atom& atom1 = molgraph.getAtom(i);
		const ParamEntry& param_entry1 = paramTable->getEntry(typeFunc(atom1));

		if (!param_entry1)
			throw Base::ItemNotFound("MMFF94VanDerWaalsInteractionParameterizer: could not find MMFF94 van der Waals parameters for atom #" + 
									 boost::lexical_cast<std::string>(i));

		for (std::size_t j = i + 1; j < num_atoms; j++) {
			const Atom& atom2 = molgraph.getAtom(j);
			std::size_t top_dist = distFunc(atom1, atom2, molgraph);

			if (top_dist != 0 && top_dist < 3)
				continue;

			if (filterFunc && !filterFunc(atom1, atom2))
				continue;
	
			const ParamEntry& param_entry2 = paramTable->getEntry(typeFunc(atom2));

			if (!param_entry2)
				throw Base::ItemNotFound("MMFF94VanDerWaalsInteractionParameterizer: could not find MMFF94 van der Waals parameters for atom #" + 
										 boost::lexical_cast<std::string>(j));

			ia_data.addElement(MMFF94VanDerWaalsInteraction(i, j, param_entry1.getAtomicPolarizability(), param_entry1.getEffectiveElectronNumber(),
															param_entry1.getFactorA(), param_entry1.getFactorG(), param_entry1.getHDonorAcceptorType(),
															param_entry2.getAtomicPolarizability(), param_entry2.getEffectiveElectronNumber(),
															param_entry2.getFactorA(), param_entry2.getFactorG(), param_entry2.getHDonorAcceptorType(),
															paramTable->getExponent(), paramTable->getFactorB(), paramTable->getBeta(),
															paramTable->getFactorDARAD(), paramTable->getFactorDAEPS()));
		}
	}
}
