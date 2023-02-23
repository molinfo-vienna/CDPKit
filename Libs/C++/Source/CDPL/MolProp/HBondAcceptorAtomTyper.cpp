/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondAcceptorAtomTyper.cpp 
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

#include <vector>

#include <boost/thread.hpp>

#include "CDPL/MolProp/HBondAcceptorAtomTyper.hpp"
#include "CDPL/MolProp/HBondAcceptorAtomType.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL; 


namespace
{

    struct TypePattern
    {

		const char*  ptnSMARTS;
		unsigned int type;
    };
    
    TypePattern TYPE_PATTERNS[] = {
	  { "", MolProp::HBondAcceptorAtomType::O_H2O },
	  { "", MolProp::HBondAcceptorAtomType::O_UREA },
	  { "", MolProp::HBondAcceptorAtomType::O_BARBITURIC_ACID },
	  { "", MolProp::HBondAcceptorAtomType::O_URIC_ACID },
	  { "", MolProp::HBondAcceptorAtomType::O_ETHER },
	  { "", MolProp::HBondAcceptorAtomType::O_AMIDE },
	  { "", MolProp::HBondAcceptorAtomType::O_N_OXIDE },
	  { "", MolProp::HBondAcceptorAtomType::O_ACID },
	  { "", MolProp::HBondAcceptorAtomType::O_ESTER },
	  { "", MolProp::HBondAcceptorAtomType::O_SULFOXIDE },
	  { "", MolProp::HBondAcceptorAtomType::O_NITRO },
	  { "", MolProp::HBondAcceptorAtomType::O_SELEN_OXIDE },
	  { "", MolProp::HBondAcceptorAtomType::O_ALDEHYD },
	  { "", MolProp::HBondAcceptorAtomType::O_KETONE },
	  { "", MolProp::HBondAcceptorAtomType::O_ALCOHOL },
	  { "", MolProp::HBondAcceptorAtomType::N_NH3 },
	  { "", MolProp::HBondAcceptorAtomType::N_DIAMINE },
	  { "", MolProp::HBondAcceptorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "", MolProp::HBondAcceptorAtomType::N_TRI_NITRO_ANILINE },
	  { "", MolProp::HBondAcceptorAtomType::N_HALOGENO_ANILINE },
	  { "", MolProp::HBondAcceptorAtomType::N_ANILINE },
	  { "", MolProp::HBondAcceptorAtomType::N_NITRILE },
	  { "", MolProp::HBondAcceptorAtomType::N_AZOLE },
	  { "", MolProp::HBondAcceptorAtomType::N_AMINE },
	  { "", MolProp::HBondAcceptorAtomType::N_AMIDINE },
	  { "", MolProp::HBondAcceptorAtomType::N_AZO },
	  { "", MolProp::HBondAcceptorAtomType::N_AZINE },
	  { "", MolProp::HBondAcceptorAtomType::N_DIAZINE },
	  { "", MolProp::HBondAcceptorAtomType::N_IMINE },
	  { "", MolProp::HBondAcceptorAtomType::S_SULFIDE },
	  { "", MolProp::HBondAcceptorAtomType::S_THIOUREA },
	  { "", MolProp::HBondAcceptorAtomType::P_MONO_DI_PHOSPHINE },
	  { "", MolProp::HBondAcceptorAtomType::P_TRI_PHOSPHINE }
    };
    
    typedef std::vector<Chem::MolecularGraph::SharedPointer> AtomTyperPatternList;

    AtomTyperPatternList atomTyperPatterns;
    boost::once_flag initAtomTyperPatternsFlag = BOOST_ONCE_INIT;

    void initAtomTyperPatterns()
    {
		for (std::size_t i = 0; i < sizeof(TYPE_PATTERNS) / sizeof(TypePattern); i++)
			atomTyperPatterns.push_back(Chem::parseSMARTS(TYPE_PATTERNS[i].ptnSMARTS));
    }
}


MolProp::HBondAcceptorAtomTyper::HBondAcceptorAtomTyper(const Chem::MolecularGraph& molgraph, Util::UIArray& types)
{
    perceiveTypes(molgraph, types);
}

MolProp::HBondAcceptorAtomTyper::HBondAcceptorAtomTyper() {} 

void MolProp::HBondAcceptorAtomTyper::perceiveTypes(const Chem::MolecularGraph& molgraph, Util::UIArray& types)
{
    std::size_t num_atoms = molgraph.getNumAtoms();

    types.resize(num_atoms);

    if (atomTyper.getNumPatterns() == 0) {
		boost::call_once(&initAtomTyperPatterns, initAtomTyperPatternsFlag);

		for (AtomTyperPatternList::const_iterator it = atomTyperPatterns.begin(), end = atomTyperPatterns.end(); it != end; ++it)
			atomTyper.addPattern(*it);
    }

    atomTyper.execute(molgraph);
    
    for (std::size_t i = 0; i < num_atoms; i++) {
		if (!atomTyper.hasAtomLabel(i))
			types[i] = HBondAcceptorAtomType::NONE;
		else
			types[i] = TYPE_PATTERNS[atomTyper.getPatternIndex(i)].type;
    }
}
