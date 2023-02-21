/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondDonorAtomTyper.cpp 
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

#include "CDPL/MolProp/HBondDonorAtomTyper.hpp"
#include "CDPL/MolProp/HBondDonorAtomType.hpp"
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
      { "[IX1H1:1]", MolProp::HBondDonorAtomType::I_HI },
      { "[BrX1H1:1]", MolProp::HBondDonorAtomType::BR_HBR },
	  { "[ClX1H1:1]", MolProp::HBondDonorAtomType::CL_HCL },
	  { "[FX1H1:1]", MolProp::HBondDonorAtomType::F_HF },
	  { "[#1X1H1:1]", MolProp::HBondDonorAtomType::H_H2 },
	  { "[SX2H1:1]-C#N", MolProp::HBondDonorAtomType::S_HSCN },
	  { "[CX2H1:1]#N", MolProp::HBondDonorAtomType::C_HCN },
	  { "[CX2H1:1]#C", MolProp::HBondDonorAtomType::C_ETHINE },
	  { "[NX2H1:1]=N=N", MolProp::HBondDonorAtomType::N_HN3 },
	  { "[NX2H1:1]-N#N", MolProp::HBondDonorAtomType::N_HN3 },
	  { "[NX3H3:1]", MolProp::HBondDonorAtomType::N_NH3 },
	  { "[NX4H4+1:1]", MolProp::HBondDonorAtomType::N_NH4 },
	  { "[NX3;H1,H2:1]", MolProp::HBondDonorAtomType::N_AMINE },
	  { "[NX4+1;H1,H2,H3:1]", MolProp::HBondDonorAtomType::N_AMINIUM },
	  { "[NX3;H1,H2:1]-[a]", MolProp::HBondDonorAtomType::N_ANILINE },
	  { "[NX3;H1,H2:1]-c1c(-N(=O)-O)cccc1", MolProp::HBondDonorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "[NX3;H1,H2:1]-c1cc(-N(=O)-O)ccc1", MolProp::HBondDonorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "[NX3;H1,H2:1]-c1ccc(-N(=O)-O)cc1", MolProp::HBondDonorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "[NX3;H1,H2:1]-c1c(-N(=O)-O)cc(-N(=O)-O)cc1(-N(=O)-O)", MolProp::HBondDonorAtomType::N_TRI_NITRO_ANILINE },
	  { "[nX3;H1:1]", MolProp::HBondDonorAtomType::N_PYRROLE },
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


MolProp::HBondDonorAtomTyper::HBondDonorAtomTyper(const Chem::MolecularGraph& molgraph, Util::UIArray& types)
{
    perceiveTypes(molgraph, types);
}

MolProp::HBondDonorAtomTyper::HBondDonorAtomTyper() {} 

void MolProp::HBondDonorAtomTyper::perceiveTypes(const Chem::MolecularGraph& molgraph, Util::UIArray& types)
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
			types[i] = HBondDonorAtomType::NONE;
		else
			types[i] = TYPE_PATTERNS[atomTyper.getPatternIndex(i)].type;
    }
}
