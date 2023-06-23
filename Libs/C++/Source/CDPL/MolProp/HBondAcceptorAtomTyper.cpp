/* 
 * HBondAcceptorAtomTyper.cpp 
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

#include <vector>
#include <mutex>

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
	  { "[O:1]=C", MolProp::HBondAcceptorAtomType::O_KETONE },
	  { "[O:1]=[C;H1,H2]", MolProp::HBondAcceptorAtomType::O_ALDEHYD },
	  { "[OX2:1]", MolProp::HBondAcceptorAtomType::O_ETHER },
	  { "[OX2H1:1]", MolProp::HBondAcceptorAtomType::O_ALCOHOL },
	  { "[OX2H2:1]", MolProp::HBondAcceptorAtomType::O_H2O },
	  { "[O:1]=C(-N)-N", MolProp::HBondAcceptorAtomType::O_UREA },
	  { "C1C(=[O:1])NC(=[O:1])NC1=[O:1]", MolProp::HBondAcceptorAtomType::O_BARBITURIC_ACID },
	  { "C12=C(NC(=[O:1])N1)NC(=[O:1])NC2=[O:1]", MolProp::HBondAcceptorAtomType::O_URIC_ACID },
	  { "N-*=[O:1]", MolProp::HBondAcceptorAtomType::O_AMIDE },
	  { "N=*-[O:1]", MolProp::HBondAcceptorAtomType::O_AMIDE },
	  { "[O:1]-N", MolProp::HBondAcceptorAtomType::O_N_OXIDE },
	  { "[O:1]-*=[O:1]", MolProp::HBondAcceptorAtomType::O_ACID },
	  { "[O:1](-[#6])-*=O", MolProp::HBondAcceptorAtomType::O_ESTER },
	  { "[O:1]=S", MolProp::HBondAcceptorAtomType::O_SULFOXIDE },
	  { "[O:1]-N=[O:1]", MolProp::HBondAcceptorAtomType::O_NITRO },
	  { "[O:1]=[Se]", MolProp::HBondAcceptorAtomType::O_SELEN_OXIDE },
	  { "[NX3H3:1]", MolProp::HBondAcceptorAtomType::N_NH3 },
	  { "[Nv3X3;!$(*-*=O):1]", MolProp::HBondAcceptorAtomType::N_AMINE },
	  { "[Nv3X3;!$(*-*=O):1]-CC-[Nv3X3;!$(*-*=O)]", MolProp::HBondAcceptorAtomType::N_DIAMINE },
	  { "[Nv3X3;!$(*-*=O):1]-a", MolProp::HBondAcceptorAtomType::N_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1c(-N(=O)-O)cccc1", MolProp::HBondAcceptorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1cc(-N(=O)-O)ccc1", MolProp::HBondAcceptorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1ccc(-N(=O)-O)cc1", MolProp::HBondAcceptorAtomType::N_MONO_DI_NITRO_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1c(-N(=O)-O)cc(-N(=O)-O)cc1(-N(=O)-O)", MolProp::HBondAcceptorAtomType::N_TRI_NITRO_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1c(-[Cl,Br,I,F])cccc1", MolProp::HBondAcceptorAtomType::N_HALOGENO_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1cc(-[Cl,Br,I,F])ccc1", MolProp::HBondAcceptorAtomType::N_HALOGENO_ANILINE },
	  { "[Nv3X3;!$(*-*=O):1]-c1ccc(-[Cl,Br,I,F])cc1", MolProp::HBondAcceptorAtomType::N_HALOGENO_ANILINE },
	  { "[NX1:1]#C", MolProp::HBondAcceptorAtomType::N_NITRILE },
	  { "[n+0:1]1aaaa1", MolProp::HBondAcceptorAtomType::N_AZOLE },
	  { "[Nv3X2;!$(*-*=O):1]=C-[Nv3X3]", MolProp::HBondAcceptorAtomType::N_AMIDINE },
	  { "[Nv3X2]=C-[Nv3X3;!$(*-*=O):1]", MolProp::HBondAcceptorAtomType::N_AMIDINE },
	  { "[Nv3x2:1]=[Nv3x2]", MolProp::HBondAcceptorAtomType::N_AZO },
	  { "[nX2v3+0:1]1[a;!n][a;!n][a;!n][a;!n][a;!n]1", MolProp::HBondAcceptorAtomType::N_AZINE },
	  { "[nX2v3+0:1]1ncccc1", MolProp::HBondAcceptorAtomType::N_DIAZINE },
	  { "[nX2v3+0:1]1cnccc1", MolProp::HBondAcceptorAtomType::N_DIAZINE },
	  { "[nX2v3+0:1]1ccncc1", MolProp::HBondAcceptorAtomType::N_DIAZINE },
	  { "[Nv3X2;!$(*-*=O):1]=C", MolProp::HBondAcceptorAtomType::N_IMINE },
	  { "[Sv2X2:1]", MolProp::HBondAcceptorAtomType::S_SULFIDE },
	  { "[Sv2:1]=C(-N)-N", MolProp::HBondAcceptorAtomType::S_THIOUREA },
	  { "[Pv3X3;H1,H2:1]", MolProp::HBondAcceptorAtomType::P_MONO_DI_PHOSPHINE },
	  { "[Pv3X3;H0:1]", MolProp::HBondAcceptorAtomType::P_TRI_PHOSPHINE }
    };
    
    typedef std::vector<Chem::MolecularGraph::SharedPointer> AtomTyperPatternList;

    AtomTyperPatternList atomTyperPatterns;
    std::once_flag initAtomTyperPatternsFlag;

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
		std::call_once(initAtomTyperPatternsFlag, &initAtomTyperPatterns);

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
