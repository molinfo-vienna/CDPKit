/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomHydrophobicityCalculator.cpp 
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

#include <locale>
#include <algorithm>

#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/MolProp/AtomHydrophobicityCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "AtomSurfaceAccessibilityData.hpp"


using namespace CDPL; 


namespace
{

    double atomHydCategoryFactors[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.6, 0.6, 0.6, 0, 0.25, 0 };

    typedef std::vector<Chem::MolecularGraph::SharedPointer> PatternTable;
	
    PatternTable atomHydCategoryPatterns;
    boost::once_flag initHydCategoryPatternsFlag = BOOST_ONCE_INIT;

    void initHydCategoryPatterns() 
    {
		using namespace Chem;
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[#1,#7,#8:1]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[S;!H0:2]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:3]~*~[!+0]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:3]~[!+0]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[!+0:3]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:4]~*~[O,N;!H0;!$(*-*=,:*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:4]~[O,N;!H0;!$(*-*=,:*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O,N;!H0;!$(*-*=,:*):4]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:5]~[S;!H0;!$(*-*=,:*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[S;!H0;!$(*-*=,:*):5]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:6]~*=[O]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:6]=[O]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O:6]=*"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:7]~[#16;v3,v4,v5,v6]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;v3,v4,v5,v6:7]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16:8]=*"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:9]~*~*=[O]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:10]~*~[#16;v3,v4,v5,v6]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:11]~[#16;$(*=*)]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[O]=*~*~[*:12]~*~*=[O]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O]=*~*~[*:12]~*~[#16;v3,v4,v5,v6]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O]=*~*~[*:12]~[#16;$(*=*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;v3,v4,v5,v6]~*~[*:12]~*~[#16;v3,v4,v5,v6]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;v3,v4,v5,v6]~*~[*:12]~[#16;$(*=*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;$(*=*)]~[*:12]~[#16;$(*=*)]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:13]~[N,O;!$(*-*=,:*)]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[N,O;!$(*-*=,:*)]~[*:14]~[N,O;!$(*-*=,:*)]"));
    }

    typedef boost::unordered_map<std::string, double> AtomSurfaceAccessibilityTable;

	AtomSurfaceAccessibilityTable atomSurfAccTable;
    boost::once_flag initAtomSurfAccTableFlag = BOOST_ONCE_INIT;

    void initAtomSurfAccTable() 
    {
		for (std::size_t i = 0; i < sizeof(ATOM_SURF_ACC_DATA) / sizeof(AtomSurfAccData); i++)
			atomSurfAccTable.insert(AtomSurfaceAccessibilityTable::value_type(ATOM_SURF_ACC_DATA[i].pattern, ATOM_SURF_ACC_DATA[i].value));
	}
	
	void appendBondSymbol(std::string& str, const Chem::Bond& bond)
	{
		if (getAromaticityFlag(bond)) {
			str.push_back(':');
			return;
		}

		switch (getOrder(bond)) {

			case 1:
				return;

			case 2:
				str.push_back('=');
				return;

			case 3:
				str.push_back('#');
				return;
		}

		str.push_back('~');
	}

	void appendAtomSymbol(std::string& str, const Chem::Atom& atom)
	{
		using namespace Chem;
		
		unsigned int type = getType(atom);

		if (type > AtomType::MAX_ATOMIC_NO)
			type = AtomType::ANY;

		const std::string& elem_sym = AtomDictionary::getSymbol(type);

		if (elem_sym.empty())
			return;
		
		if (getAromaticityFlag(atom))
			str.push_back(std::tolower(elem_sym[0], std::locale::classic()));
		else
			str.push_back(elem_sym[0]);

		if (elem_sym.size() > 1)
			str.push_back(elem_sym[1]);
	}
}


MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator()
{
	substructSearch.uniqueMappingsOnly(true);
}

MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(const AtomHydrophobicityCalculator& calc)
{
	substructSearch.uniqueMappingsOnly(true);
}

MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
	substructSearch.uniqueMappingsOnly(true);

    calculate(molgraph, hyd_table);
}

MolProp::AtomHydrophobicityCalculator::~AtomHydrophobicityCalculator() {}

MolProp::AtomHydrophobicityCalculator& MolProp::AtomHydrophobicityCalculator::operator=(const AtomHydrophobicityCalculator& calc)
{
    return *this;
}

void MolProp::AtomHydrophobicityCalculator::calculate(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
    calcHydrophobicities(molgraph, hyd_table);
}

void MolProp::AtomHydrophobicityCalculator::calcHydrophobicities(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
	using namespace Chem;

    boost::call_once(&initHydCategoryPatterns, initHydCategoryPatternsFlag);
    boost::call_once(&initAtomSurfAccTable, initAtomSurfAccTableFlag);

	std::size_t num_atoms = molgraph.getNumAtoms();

    hyd_table.assign(num_atoms, 1.0);

    for (PatternTable::const_iterator p_it = atomHydCategoryPatterns.begin(), p_end = atomHydCategoryPatterns.end(); 
		 p_it != p_end; ++p_it) {

		substructSearch.setQuery(**p_it);
		substructSearch.findMappings(molgraph);

		for (SubstructureSearch::ConstMappingIterator m_it = substructSearch.getMappingsBegin(),
				 m_end = substructSearch.getMappingsEnd(); m_it != m_end; ++m_it) {

			const AtomMapping& mapping = m_it->getAtomMapping();

			for (AtomMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it) {
				std::size_t hyd_cat = getAtomMappingID(*it->first);

				if (hyd_cat == 0)
					continue;

				hyd_table[molgraph.getAtomIndex(*it->second)] *= atomHydCategoryFactors[hyd_cat];
			}
		}
    }

	for (std::size_t i = 0; i < num_atoms; i++) {
		if (hyd_table[i] == 0.0)
			continue;
		
		hyd_table[i] *= calcAccessibleSurfaceFactor(molgraph.getAtom(i), molgraph);
	}
}

double MolProp::AtomHydrophobicityCalculator::calcAccessibleSurfaceFactor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	atomEnvData.clear();

	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom))
			continue;

		const Bond& nbr_bond = *b_it;

		if (!molgraph.containsBond(nbr_bond))
			continue;
		
		atomDescr.clear();

		appendBondSymbol(atomDescr, nbr_bond);
		appendAtomSymbol(atomDescr, nbr_atom);

		atomEnvData.push_back(atomDescr);
	}

	for (std::size_t i = 0, num_impl_hs = calcImplicitHydrogenCount(atom, molgraph); i < num_impl_hs; i++)
		atomEnvData.push_back("H");
	
	std::sort(atomEnvData.begin(), atomEnvData.end());
	
	atomDescr.clear();
			
	appendAtomSymbol(atomDescr, atom);

	for (StringList::const_iterator it = atomEnvData.begin(), end = atomEnvData.end(); it != end; ++it)
		atomDescr.append(*it);

	AtomSurfaceAccessibilityTable::const_iterator it = atomSurfAccTable.find(atomDescr);

	if (it != atomSurfAccTable.end())
		return it->second;

	// fallback 1
	
	atomDescr.clear();

	appendAtomSymbol(atomDescr, atom);

	atomDescr.append(boost::lexical_cast<std::string>(atomEnvData.size()));
	atomDescr.push_back('.');
	atomDescr.append(boost::lexical_cast<std::string>(std::count(atomEnvData.begin(), atomEnvData.end(), "H")));

	it = atomSurfAccTable.find(atomDescr);

	if (it != atomSurfAccTable.end())
		return it->second;

	// fallback 2

	double vdw_radius = MolProp::getVdWRadius(atom);

	return (vdw_radius * vdw_radius);
}
