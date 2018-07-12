/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsInteractionAnalyzer.cpp 
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

#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionAnalyzer.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


ForceField::MMFF94VanDerWaalsInteractionAnalyzer::MMFF94VanDerWaalsInteractionAnalyzer(const Chem::MolecularGraph& molgraph, 
																					   MMFF94VanDerWaalsInteractionList& iactions):
	filterFunc(), typeFunc(&getMMFF94NumericType), distFunc(&Chem::getTopologicalDistance),
	paramTable(MMFF94VanDerWaalsParameterTable::get())
{
    analyze(molgraph, iactions);
}

ForceField::MMFF94VanDerWaalsInteractionAnalyzer::MMFF94VanDerWaalsInteractionAnalyzer() :
	filterFunc(), typeFunc(&getMMFF94NumericType), distFunc(&Chem::getTopologicalDistance),
	paramTable(MMFF94VanDerWaalsParameterTable::get())
{}

void ForceField::MMFF94VanDerWaalsInteractionAnalyzer::setFilterFunction(const InteractionFilterFunction2& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94VanDerWaalsInteractionAnalyzer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	typeFunc = func;
}  

void ForceField::MMFF94VanDerWaalsInteractionAnalyzer::setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func)
{
	distFunc = func;
}  

void ForceField::MMFF94VanDerWaalsInteractionAnalyzer::setParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94VanDerWaalsInteractionAnalyzer::analyze(const Chem::MolecularGraph& molgraph, 
															   MMFF94VanDerWaalsInteractionList& iactions)
{
	using namespace Chem;

	typedef MMFF94VanDerWaalsParameterTable::Entry ParamEntry;

	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; ) {
		const Atom& atom1 = molgraph.getAtom(i);
		const ParamEntry& params_entry1 = paramTable->getEntry(typeFunc(atom1));

		if (!params_entry1)
			throw Base::ItemNotFound("MMFF94VanDerWaalsInteractionAnalyzerr: could not find MMFF94 van der Waals parameters for atom #" + 
									 boost::lexical_cast<std::string>(i));

		for (std::size_t j = i + 1; j < num_atoms; j++) {
			const Atom& atom2 = molgraph.getAtom(j);
			std::size_t top_dist = distFunc(atom1, atom2, molgraph);

			if (top_dist != 0 && top_dist < 3)
				continue;

			if (filterFunc && !filterFunc(atom1, atom2))
				continue;
	
			const ParamEntry& params_entry2 = paramTable->getEntry(typeFunc(atom2));

			if (!params_entry2)
				throw Base::ItemNotFound("MMFF94VanDerWaalsInteractionAnalyzerr: could not find MMFF94 van der Waals parameters for atom #" + 
										 boost::lexical_cast<std::string>(j));

			iactions.addElement(MMFF94VanDerWaalsInteraction(i, j, params_entry1.getAtomicPolarizability(), params_entry1.getEffectiveElectronNumber(),
															 params_entry1.getFactorA(), params_entry1.getFactorG(), params_entry1.getHDonorAcceptorType(),
															 params_entry2.getAtomicPolarizability(), params_entry2.getEffectiveElectronNumber(),
															 params_entry2.getFactorA(), params_entry2.getFactorG(), params_entry2.getHDonorAcceptorType(),
															 paramTable->getExponent(), paramTable->getFactorB(), paramTable->getBeta(),
															 paramTable->getFactorDARAD(), paramTable->getFactorDAEPS()));
		}
	}
}
