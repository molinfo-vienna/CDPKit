/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TPSACalculator.cpp 
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

#include "CDPL/MolProp/TPSACalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

	typedef std::vector<Chem::MolecularGraph::SharedPointer> PatternTable;

	PatternTable atomTypePatterns;

	std::once_flag initAtomTypePatternsFlag;

	void initAtomTypePatterns() 
	{
		using namespace Chem;

		atomTypePatterns.push_back(parseSMARTS("[N:1](-*)(-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[N:2](-*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[N:3]#*"));
		atomTypePatterns.push_back(parseSMARTS("[N:4](-*)(=*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[N:5](=*)#*"));
		atomTypePatterns.push_back(parseSMARTS("[N:6]1(-*)-*-*-1"));
		atomTypePatterns.push_back(parseSMARTS("[NH:7](-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[NH:8]1-*-*-1"));
		atomTypePatterns.push_back(parseSMARTS("[NH:9]=*"));
		atomTypePatterns.push_back(parseSMARTS("[NH2:10]-*"));
		atomTypePatterns.push_back(parseSMARTS("[N+:11](-*)(-*)(-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[N+:12](-*)(-*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[N+:13](-*)#*"));
		atomTypePatterns.push_back(parseSMARTS("[NH+:14](-*)(-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[NH+:15](-*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[NH2+:16](-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[NH2+:17]=*"));
		atomTypePatterns.push_back(parseSMARTS("[NH3+:18]-*"));
		atomTypePatterns.push_back(parseSMARTS("[n:19](:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[n:20](:*)(:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[n:21](-*)(:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[n:22](=*)(:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[nH:23](:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[n+:24](:*)(:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[n+:25](-*)(:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[nH+:26](:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[O:27](-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[O:28]1-*-*-1"));
		atomTypePatterns.push_back(parseSMARTS("[O:29]=*"));
		atomTypePatterns.push_back(parseSMARTS("[OH:30]-*"));
		atomTypePatterns.push_back(parseSMARTS("[O-:31]-*"));
		atomTypePatterns.push_back(parseSMARTS("[o:32](:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[S:33](-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[S:34]=*"));
		atomTypePatterns.push_back(parseSMARTS("[S:35](-*)(-*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[S:36](-*)(-*)(=*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[SH:37]-*"));
		atomTypePatterns.push_back(parseSMARTS("[s:38](:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[s:39](=*)(:*):*"));
		atomTypePatterns.push_back(parseSMARTS("[P:40](-*)(-*)-*"));
		atomTypePatterns.push_back(parseSMARTS("[P:41](-*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[P:42](-*)(-*)(-*)=*"));
		atomTypePatterns.push_back(parseSMARTS("[PH:43](-*)(-*)=*"));
	}

	double atomTypeIncrements[] = {
	    3.24,
		12.36,
		23.79,
		11.68,
		13.60,
		3.01,
		12.03,
		21.94,
		23.85,
		26.02,
		0.00,
		3.01,
		4.36,
		4.44,
		13.97,
		16.61,
		25.59,
		27.64,
		12.89,
		4.41,
		4.93,
		8.39,
		15.79,
		4.10,
		3.88,
		14.14,
		9.23,
		12.53,
		17.07,
		20.23,
		23.06,
		13.14,
		25.30,
		32.09,
		19.21,
		8.38,
		38.80,
		28.24,
		21.70,
		13.59,
		34.14,
		9.81,
		23.47
 	};
}

MolProp::TPSACalculator::TPSACalculator(): area(0) {}

MolProp::TPSACalculator::TPSACalculator(const Chem::MolecularGraph& molgraph)
{
	calculate(molgraph);
}

double MolProp::TPSACalculator::calculate(const Chem::MolecularGraph& molgraph)
{
	init();

	atomTyper.execute(molgraph);
	area = 0.0;

	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++)
		if (atomTyper.hasAtomLabel(i))
			area += atomTypeIncrements[atomTyper.getAtomLabel(i) - 1];

	return area;
}

double MolProp::TPSACalculator::getResult() const
{
	return area;
}

void MolProp::TPSACalculator::init()
{
	if (atomTyper.getNumPatterns() == 0) {
		std::call_once(initAtomTypePatternsFlag, &initAtomTypePatterns);
	
		for (PatternTable::const_iterator p_it = atomTypePatterns.begin(), p_end = atomTypePatterns.end(); p_it != p_end; ++p_it)
			atomTyper.addPattern(*p_it);
	}
}
