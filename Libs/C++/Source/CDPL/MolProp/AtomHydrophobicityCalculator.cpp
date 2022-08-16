/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomHydrophobicityCalculator.cpp 
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

#include <boost/thread.hpp>

#include "CDPL/MolProp/AtomHydrophobicityCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Math/Matrix.hpp"


using namespace CDPL; 


namespace
{

    const double spherePoints[] = { -0.3090169944, -0.5,
									0.8090169944, -0.5877852523, -0.4253254042, 0.6881909602,
									-0.4253254042, -0.6881909602, 0.5877852523, 0.3090169944, 0.5,
									-0.8090169944, 0.4253254042, 0.6881909602, -0.5877852523,
									0.1606220356, 0.7020464448, -0.6937804776, 0.259891913,
									-0.8626684804, 0.4338885646, 0, -0.9619383578, 0.2732665289, 0,
									-0.8506508084, 0.5257311121, -0.5257311121, 0.8506508084, 0,
									-0.2628655561, 0.9510565163, 0.1624598481, -0.5, 0.8090169944,
									0.3090169944, -0.8090169944, 0.3090169944, -0.5, -0.8626684804,
									0.4338885646, -0.259891913, -0.6881909602, 0.5877852523,
									-0.4253254042, -0.4253254042, 0.6881909602, 0.5877852523,
									-0.259891913, 0.8626684804, 0.4338885646, -0.4338885646,
									0.259891913, 0.8626684804, -0.2732665289, 0, 0.9619383578,
									-0.1624598481, 0.2628655561, 0.9510565163, 1, 0, 0, 0.9619383578,
									-0.2732665289, 0, 0.9510565163, -0.1624598481, 0.2628655561, -1,
									0, 0, -0.9619383578, -0.2732665289, 0, -0.9510565163,
									-0.1624598481, -0.2628655561, -0.9510565163, 0.1624598481,
									0.2628655561, -0.8626684804, 0.4338885646, 0.259891913,
									-0.8090169944, 0.3090169944, 0.5, 0.5257311121, 0, 0.8506508084,
									0.6937804776, -0.1606220356, 0.7020464448, 0.4338885646,
									-0.259891913, 0.8626684804, 0.2732665289, 0, 0.9619383578,
									0.5257311121, 0, -0.8506508084, 0.2732665289, 0, -0.9619383578,
									0.4338885646, -0.259891913, -0.8626684804, -0.4338885646,
									-0.259891913, -0.8626684804, -0.5877852523, -0.4253254042,
									-0.6881909602, -0.3090169944, -0.5, -0.8090169944, 0.2628655561,
									-0.9510565163, 0.1624598481, 0.2628655561, -0.9510565163,
									-0.1624598481, 0.5257311121, -0.8506508084, 0, 0, -0.9619383578,
									-0.2732665289, 0, -1, 0, 0.1624598481, -0.2628655561,
									0.9510565163, 0.6881909602, 0.5877852523, 0.4253254042,
									0.8626684804, 0.4338885646, 0.259891913, 0.7020464448, 0.6937804776,
									0.1606220356, -0.6881909602, -0.5877852523, 0.4253254042, -0.5,
									-0.8090169944, -0.3090169944, -0.7020464448, -0.6937804776,
									-0.1606220356, -0.5257311121, -0.8506508084, 0, -0.5257311121, 0,
									0.8506508084, 0.3090169944, 0.5, 0.8090169944, 0, 0.5257311121,
									0.8506508084, 0.1606220356, 0.7020464448, 0.6937804776,
									0.8090169944, 0.3090169944, -0.5, 0.9510565163, 0.1624598481,
									-0.2628655561, 0.8506508084, 0, -0.5257311121, -0.2628655561,
									0.9510565163, -0.1624598481, 0, 1, 0, 0.2628655561, 0.9510565163,
									0.1624598481, 0, 0.9619383578, 0.2732665289, -0.9510565163,
									0.1624598481, -0.2628655561, 0, 0, 1, -0.1624598481,
									-0.2628655561, 0.9510565163, -0.4338885646, -0.259891913,
									0.8626684804, 0.5, -0.8090169944, -0.3090169944, 0.8506508084,
									-0.5257311121, 0, 0.7020464448, -0.6937804776, -0.1606220356,
									0.7020464448, -0.6937804776, 0.1606220356, 0.259891913,
									0.8626684804, -0.4338885646, 0.259891913, -0.8626684804,
									-0.4338885646, 0.1606220356, -0.7020464448, -0.6937804776, 0,
									-0.8506508084, -0.5257311121, 0.1624598481, -0.2628655561,
									-0.9510565163, 0, -0.5257311121, -0.8506508084, 0.3090169944, -0.5,
									-0.8090169944, -0.3090169944, 0.5, -0.8090169944, -0.5877852523,
									0.4253254042, -0.6881909602, -0.4253254042, 0.6881909602,
									-0.5877852523, 0.8090169944, -0.3090169944, -0.5, 0.6937804776,
									-0.1606220356, -0.7020464448, 0.8506508084, 0, 0.5257311121,
									0.9510565163, 0.1624598481, 0.2628655561, -0.8506508084,
									0.5257311121, 0, -0.7020464448, 0.6937804776, 0.1606220356,
									0.7020464448, 0.6937804776, -0.1606220356, 0.5257311121,
									0.8506508084, 0, 0.5, 0.8090169944, -0.3090169944, 0.2628655561,
									0.9510565163, -0.1624598481, -0.6937804776, 0.1606220356,
									-0.7020464448, -0.6937804776, -0.1606220356, -0.7020464448,
									-0.5257311121, 0, -0.8506508084, -0.259891913, -0.8626684804,
									0.4338885646, -0.1606220356, -0.7020464448, 0.6937804776,
									0.9619383578, 0.2732665289, 0, -0.6937804776, 0.1606220356,
									0.7020464448, -0.5877852523, 0.4253254042, 0.6881909602,
									-0.8506508084, 0, 0.5257311121, -0.8090169944, -0.3090169944, -0.5,
									-0.6881909602, -0.5877852523, -0.4253254042, 0.1624598481,
									0.2628655561, 0.9510565163, -0.5, -0.8090169944, 0.3090169944,
									-0.2628655561, -0.9510565163, 0.1624598481, -0.8506508084,
									-0.5257311121, 0, -0.8626684804, -0.4338885646, -0.259891913,
									0.8626684804, -0.4338885646, -0.259891913, 0, 0, -1, 0.1624598481,
									0.2628655561, -0.9510565163, -0.1624598481, 0.2628655561,
									-0.9510565163, -0.8090169944, -0.3090169944, 0.5, -0.6937804776,
									-0.1606220356, 0.7020464448, 0.6881909602, -0.5877852523,
									-0.4253254042, 0.5877852523, 0.4253254042, 0.6881909602,
									0.4338885646, 0.259891913, 0.8626684804, -0.9510565163,
									-0.1624598481, 0.2628655561, -0.8626684804, -0.4338885646,
									0.259891913, -0.1606220356, -0.7020464448, -0.6937804776,
									0.259891913, 0.8626684804, 0.4338885646, 0, 0.8506508084,
									0.5257311121, 0.4253254042, 0.6881909602, 0.5877852523, 0.5,
									0.8090169944, 0.3090169944, -0.7020464448, -0.6937804776,
									0.1606220356, 0.8506508084, 0.5257311121, 0, 0.8626684804,
									0.4338885646, -0.259891913, 0.5877852523, -0.4253254042,
									-0.6881909602, 0, 0.8506508084, -0.5257311121, -0.9619383578,
									0.2732665289, 0, 0.5877852523, -0.4253254042, 0.6881909602,
									0.4253254042, -0.6881909602, 0.5877852523, 0.3090169944, -0.5,
									0.8090169944, -0.7020464448, 0.6937804776, -0.1606220356,
									-0.3090169944, 0.5, 0.8090169944, -0.1606220356, 0.7020464448,
									0.6937804776, 0.8626684804, -0.4338885646, 0.259891913,
									0.8090169944, -0.3090169944, 0.5, 0, -0.5257311121, 0.8506508084,
									0.1606220356, -0.7020464448, 0.6937804776, 0.4338885646,
									0.259891913, -0.8626684804, -0.5, 0.8090169944, -0.3090169944,
									-0.259891913, 0.8626684804, -0.4338885646, 0.9510565163,
									-0.1624598481, -0.2628655561, -0.4253254042, -0.6881909602,
									-0.5877852523, -0.8506508084, 0, -0.5257311121, 0.5, -0.8090169944,
									0.3090169944, 0.6881909602, 0.5877852523, -0.4253254042,
									0.6937804776, 0.1606220356, -0.7020464448, -0.6881909602,
									0.5877852523, 0.4253254042, -0.259891913, -0.8626684804,
									-0.4338885646, -0.2732665289, 0, -0.9619383578, -0.2628655561,
									-0.9510565163, -0.1624598481, 0.8090169944, 0.3090169944, 0.5, 0,
									0.5257311121, -0.8506508084, 0.4253254042, -0.6881909602,
									-0.5877852523, 0.5877852523, 0.4253254042, -0.6881909602,
									-0.4338885646, 0.259891913, -0.8626684804, 0, 0.9619383578,
									-0.2732665289, -0.1606220356, 0.7020464448, -0.6937804776,
									0.6937804776, 0.1606220356, 0.7020464448, 0.6881909602,
									-0.5877852523, 0.4253254042, -0.1624598481, -0.2628655561,
									-0.9510565163 };

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
}


MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(): 
	coordsFunc(&Chem::get3DCoordinates) 
{}

MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(const AtomHydrophobicityCalculator& calc): 
	coordsFunc(&Chem::get3DCoordinates) 
{}

MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table): 
	coordsFunc(&Chem::get3DCoordinates)
{
    calculate(molgraph, hyd_table);
}

MolProp::AtomHydrophobicityCalculator::~AtomHydrophobicityCalculator() {}

MolProp::AtomHydrophobicityCalculator& MolProp::AtomHydrophobicityCalculator::operator=(const AtomHydrophobicityCalculator& calc)
{
    return *this;
}

void MolProp::AtomHydrophobicityCalculator::setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func)
{
    coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction& MolProp::AtomHydrophobicityCalculator::getAtom3DCoordinatesFunction() const
{
    return coordsFunc;
}

void MolProp::AtomHydrophobicityCalculator::calculate(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
    init(molgraph);

    calcHydrophobicities(hyd_table);
}

void MolProp::AtomHydrophobicityCalculator::init(const Chem::MolecularGraph& molgraph)
{
	molGraph = &molgraph;

    boost::call_once(&initHydCategoryPatterns, initHydCategoryPatternsFlag);

    if (hydSubSearchTable.empty()) {
		for (PatternTable::const_iterator p_it = atomHydCategoryPatterns.begin(), p_end = atomHydCategoryPatterns.end(); p_it != p_end; ++p_it) {
			const Chem::MolecularGraph& ptn = **p_it;
			Chem::SubstructureSearch::SharedPointer ss_ptr(new Chem::SubstructureSearch(ptn));

			hydSubSearchTable.push_back(ss_ptr);
		}
    }
}

void MolProp::AtomHydrophobicityCalculator::calcHydrophobicities(Util::DArray& hyd_table)
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

    hyd_table.assign(num_atoms, 1.0);

    for (HydPatternSubSearchTable::const_iterator ss_it = hydSubSearchTable.begin(), ss_end = hydSubSearchTable.end(); 
		 ss_it != ss_end; ++ss_it) {

		SubstructureSearch& sub_search = **ss_it;

		sub_search.findMappings(*molGraph);

		for (SubstructureSearch::ConstMappingIterator m_it = sub_search.getMappingsBegin(),
				 m_end = sub_search.getMappingsEnd(); m_it != m_end; ++m_it) {

			const AtomMapping& mapping = m_it->getAtomMapping();

			for (AtomMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it) {
				std::size_t hyd_cat = getAtomMappingID(*it->first);

				if (hyd_cat == 0)
					continue;

				hyd_table[molGraph->getAtomIndex(*it->second)] *= atomHydCategoryFactors[hyd_cat];
			}
		}
    }

    for (std::size_t i = 0; i < num_atoms; i++) {
		if (hyd_table[i] == 0.0)
			continue;

		hyd_table[i] *= calcAccessibleSurfaceFactor(molGraph->getAtom(i));
    }
}


// Simplified implementation without probe-sphere

double MolProp::AtomHydrophobicityCalculator::calcAccessibleSurfaceFactor(const Chem::Atom& atom)
{
	using namespace Chem;

	double vdw_radius = getVdWRadius(atom);

    if (coordsFunc.empty())
		return vdw_radius * vdw_radius;

    const Math::Vector3D& atom_pos = coordsFunc(atom);

    nbrAtomVdWRadii.clear();
    nbrAtomPositions.clear();

    Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

    for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		if (!molGraph->containsBond(*b_it))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		nbrAtomPositions.push_back(coordsFunc(nbr_atom) - atom_pos);
		nbrAtomVdWRadii.push_back(getVdWRadius(nbr_atom));
    }

    std::size_t num_nbrs = nbrAtomPositions.size();

    if (num_nbrs == 0)
		return vdw_radius * vdw_radius;

    Math::Vector3D ref_vec1(nbrAtomPositions[0] - atom_pos);
    Math::Vector3D ref_vec2;

    if (num_nbrs > 1) {
		ref_vec2.assign(nbrAtomPositions[1] - atom_pos);

    } else {
		if (ref_vec1(0) != 0) {
			ref_vec2(0) = ref_vec1(1);
			ref_vec2(1) = -ref_vec1(0);
			ref_vec2(2) = 0.0;

		} else if (ref_vec1(1) != 0) {
			ref_vec2(0) = -ref_vec1(1);
			ref_vec2(1) = ref_vec1(0);
			ref_vec2(2) = 0.0;

		} else {
			ref_vec2(0) = 0.0;
			ref_vec2(1) = -ref_vec1(2);
			ref_vec2(2) = ref_vec1(1);
		}
    }

    ref_vec1 /= length(ref_vec1);

    Math::Matrix3D xform;

    column(xform, 0) = ref_vec1;
    column(xform, 1) = crossProd(ref_vec1, ref_vec2);
    column(xform, 1) /= length(column(xform, 1));
    column(xform, 2) = crossProd(ref_vec1, column(xform, 1));

    Math::Vector3D trans_sp;
    std::size_t inacc_cnt = 0;

    for (std::size_t i = 0; i < sizeof(spherePoints) / sizeof(double); i += 3) {
		double sp_x = spherePoints[i] * vdw_radius;
		double sp_y = spherePoints[i + 1] * vdw_radius;
		double sp_z = spherePoints[i + 2] * vdw_radius;

		trans_sp(0) = xform(0, 0) * sp_x + xform(0, 1) * sp_y +  xform(0, 2) * sp_z;
		trans_sp(1) = xform(1, 0) * sp_x + xform(1, 1) * sp_y +  xform(1, 2) * sp_z;
		trans_sp(2) = xform(2, 0) * sp_x + xform(2, 1) * sp_y +  xform(2, 2) * sp_z;

		for (std::size_t j = 0; j < num_nbrs; j++) {
			if (length(trans_sp - nbrAtomPositions[j]) < nbrAtomVdWRadii[j]) {
				inacc_cnt++;
				break;
			}
		}
    } 

    std::size_t num_spts = sizeof(spherePoints) / sizeof(double) / 3;

    return double(num_spts - inacc_cnt) * vdw_radius * vdw_radius / num_spts;
}
