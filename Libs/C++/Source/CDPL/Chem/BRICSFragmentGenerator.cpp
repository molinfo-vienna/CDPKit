/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BRICSFragmentGenerator.cpp 
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

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include "CDPL/Chem/BRICSFragmentGenerator.hpp"
#include "CDPL/Chem/BRICSRuleID.hpp"
#include "CDPL/Chem/BRICSAtomLabel.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

	Chem::Molecule::SharedPointer L1_L2_Pattern;
	Chem::Molecule::SharedPointer L1_L3_Pattern;
	Chem::Molecule::SharedPointer L1_L10_Pattern;
	Chem::Molecule::SharedPointer L2_L12_Pattern;
	Chem::Molecule::SharedPointer L2_L14_Pattern;
	Chem::Molecule::SharedPointer L2_L16_Pattern;
	Chem::Molecule::SharedPointer L3_L4_Pattern;
	Chem::Molecule::SharedPointer L3_L13_Pattern;
	Chem::Molecule::SharedPointer L3_L14_Pattern;
	Chem::Molecule::SharedPointer L3_L15_Pattern;
	Chem::Molecule::SharedPointer L3_L16_Pattern;
	Chem::Molecule::SharedPointer L4_L5_Pattern;
	Chem::Molecule::SharedPointer L4_L11_Pattern;
	Chem::Molecule::SharedPointer L5_L13_Pattern;
	Chem::Molecule::SharedPointer L5_L15_Pattern;
	Chem::Molecule::SharedPointer L6_L13_Pattern;
	Chem::Molecule::SharedPointer L6_L14_Pattern;
	Chem::Molecule::SharedPointer L6_L15_Pattern;
	Chem::Molecule::SharedPointer L6_L16_Pattern;
	Chem::Molecule::SharedPointer L7_L7_Pattern;
	Chem::Molecule::SharedPointer L8_L9_Pattern;
	Chem::Molecule::SharedPointer L8_L10_Pattern;
	Chem::Molecule::SharedPointer L8_L13_Pattern;
	Chem::Molecule::SharedPointer L8_L14_Pattern;
	Chem::Molecule::SharedPointer L8_L15_Pattern;
	Chem::Molecule::SharedPointer L8_L16_Pattern;
	Chem::Molecule::SharedPointer L9_L15_Pattern;
	Chem::Molecule::SharedPointer L9_L16_Pattern;
	Chem::Molecule::SharedPointer L10_L13_Pattern;
	Chem::Molecule::SharedPointer L10_L14_Pattern;
	Chem::Molecule::SharedPointer L10_L15_Pattern;
	Chem::Molecule::SharedPointer L10_L16_Pattern;
	Chem::Molecule::SharedPointer L11_L13_Pattern;
	Chem::Molecule::SharedPointer L11_L14_Pattern;
	Chem::Molecule::SharedPointer L11_L15_Pattern;
	Chem::Molecule::SharedPointer L11_L16_Pattern;
	Chem::Molecule::SharedPointer L13_L14_Pattern;
	Chem::Molecule::SharedPointer L13_L15_Pattern;
	Chem::Molecule::SharedPointer L13_L16_Pattern;
	Chem::Molecule::SharedPointer L14_L15_Pattern;
	Chem::Molecule::SharedPointer L14_L16_Pattern;
	Chem::Molecule::SharedPointer L15_L16_Pattern;

	Chem::Molecule::SharedPointer halogenXPattern;
	Chem::Molecule::SharedPointer hydrogenXPattern;
	Chem::Molecule::SharedPointer methoxyXPattern;
	Chem::Molecule::SharedPointer nitroXPattern;
	Chem::Molecule::SharedPointer carboxyXPattern;
	Chem::Molecule::SharedPointer hydroxyXPattern;
	Chem::Molecule::SharedPointer methylXPattern;
	Chem::Molecule::SharedPointer ethylXPattern;
	Chem::Molecule::SharedPointer isopropylXPattern;
	Chem::Molecule::SharedPointer trifluormethylXPattern;
	
	boost::once_flag initPatternsFlag = BOOST_ONCE_INIT;

	inline std::string str(unsigned int label)
	{
		return boost::lexical_cast<std::string>(label);
	}
	
	void initPatterns() 
	{
		using namespace Chem;

		L1_L2_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L2) + "](-[*])(=O)-!@[N^3:" + str(BRICSAtomLabel::L1) + "](-[*])-[*,#1]");
		L1_L3_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L3) + "](-[*])(=O)-!@[O:" + str(BRICSAtomLabel::L1) + "]-[*]");
		L1_L10_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L10) + "](-[*])(=O)-!@[N:" + str(BRICSAtomLabel::L1) + "](-@[C]=O)-@[#6,#7,#8,#16]");

		L2_L12_Pattern = parseSMARTS("[N^3:" + str(BRICSAtomLabel::L12) + "](-[*])(-[*,#1])-!@[S:" + str(BRICSAtomLabel::L2) + "](=O)(=O)-[*]");
		L2_L14_Pattern = parseSMARTS("[N^3:" + str(BRICSAtomLabel::L14) + "](-[*])(-[*,#1])-!@[c:" + str(BRICSAtomLabel::L2) + "](:[c,n,o,s]):[n,o,s]");
		L2_L16_Pattern = parseSMARTS("[N^3:" + str(BRICSAtomLabel::L16) + "](-[*])(-[*,#1])-!@[c:" + str(BRICSAtomLabel::L2) + "](:[c]):[c]");

		L3_L4_Pattern = parseSMARTS("[O:" + str(BRICSAtomLabel::L4) + "](-[*])-!@[C:" + str(BRICSAtomLabel::L3) + "](-[*])-[*,#1]");
		L3_L13_Pattern = parseSMARTS("[O:" + str(BRICSAtomLabel::L13) + "](-[*])-!@[C:" + str(BRICSAtomLabel::L3) + "](-@[#6,#7,#8,#16])-@[#7,#8,#16]");
		L3_L14_Pattern = parseSMARTS("[O:" + str(BRICSAtomLabel::L14) + "](-[*])-!@[c:" + str(BRICSAtomLabel::L3) + "](:[c,n,o,s]):[n,o,s]");
		L3_L15_Pattern = parseSMARTS("[O:" + str(BRICSAtomLabel::L15) + "](-[*])-!@[C:" + str(BRICSAtomLabel::L3) + "](-@[C])-@[C]");
		L3_L16_Pattern = parseSMARTS("[O:" + str(BRICSAtomLabel::L16) + "](-[*])-!@[c:" + str(BRICSAtomLabel::L3) + "](:[c]):[c]");

		L4_L5_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L5) + "](-[*])(-[*,#1])-!@[N^3:" + str(BRICSAtomLabel::L4) + "](-[*;!$([*]=[*])])-[*,#1;!$([*]=[*])]");
		L4_L11_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L11) + "](-[*])(-[*,#1])-!@[SX2:" + str(BRICSAtomLabel::L4) + "]-[*]");

		L5_L13_Pattern = parseSMARTS("[N^3:" + str(BRICSAtomLabel::L13) + "](-[*;!$([*]=[*])])(-[*,#1;!$([*]=[*])])-!@[C:" + str(BRICSAtomLabel::L5) + "](-@[#6,#7,#8,#16])-@[#7,#8,#16]");
		L5_L15_Pattern = parseSMARTS("[N^3:" + str(BRICSAtomLabel::L15) + "](-[*;!$([*]=[*])])(-[*,#1;!$([*]=[*])])-!@[C:" + str(BRICSAtomLabel::L5) + "](-@[C])-@[C]");

		L6_L13_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L13) + "](-[*])(=O)-!@[C:" + str(BRICSAtomLabel::L6) + "](-@[#6,#7,#8,#16])-@[#7,#8,#16]");
		L6_L14_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L14) + "](-[*])(=O)-!@[c:" + str(BRICSAtomLabel::L6) + "](:[c,n,o,s]):[n,o,s]");
		L6_L15_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L15) + "](-[*])(=O)-!@[C:" + str(BRICSAtomLabel::L6) + "](-@[C])-@[C]");
		L6_L16_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L16) + "](-[*])(=O)-!@[c:" + str(BRICSAtomLabel::L6) + "](:[c]):[c]");

		L7_L7_Pattern = parseSMARTS("[CX3:" + str(BRICSAtomLabel::L7) + "](-[#6])(-[#6,#1])=!@[CX3:" + str(BRICSAtomLabel::L7) + "](-[#6])-[#6,#1]");

		L8_L9_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L9) + "](-[*])(-[*,#1])-!@[n:" + str(BRICSAtomLabel::L8) + "](:[c,n,o,s]):[c,n,o,s]");
		L8_L10_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L10) + "](-[*])(-[*,#1])-!@[N:" + str(BRICSAtomLabel::L8) + "](-@[C]=O)-@[#6,#7,#9,#16]");
		L8_L13_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L13) + "](-[*])(-[*,#1])-!@[C:" + str(BRICSAtomLabel::L8) + "](-@[#6,#7,#8,#16])-@[#7,#8,#16]");
		L8_L14_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L14) + "](-[*])(-[*,#1])-!@[c:" + str(BRICSAtomLabel::L8) + "](:[c,n,o,s]):[n,o,s]");
		L8_L15_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L15) + "](-[*])(-[*,#1])-!@[C:" + str(BRICSAtomLabel::L8) + "](-@[C])-@[C]");
		L8_L16_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L16) + "](-[*])(-[*,#1])-!@[c:" + str(BRICSAtomLabel::L8) + "](:[c]):[c]");

		L9_L15_Pattern = parseSMARTS("[n:" + str(BRICSAtomLabel::L15) + "](:[c,n,o,s])(:[c,n,o,s])-!@[C:" + str(BRICSAtomLabel::L9) + "](-@[C])-@[C]");
		L9_L16_Pattern = parseSMARTS("[n:" + str(BRICSAtomLabel::L16) + "](:[c,n,o,s])(:[c,n,o,s])-!@[c:" + str(BRICSAtomLabel::L9) + "](:[c]):[c]");

		L10_L13_Pattern = parseSMARTS("[N:" + str(BRICSAtomLabel::L13) + "](-@[C]=O)(-@[#6,#7,#8,#16])-!@[C:" + str(BRICSAtomLabel::L10) + "](-@[#6,#7,#8,#16])-@[#7,#8,#16]");
		L10_L14_Pattern = parseSMARTS("[N:" + str(BRICSAtomLabel::L14) + "](-@[C]=O)(-@[#6,#7,#8,#16])-!@[c:" + str(BRICSAtomLabel::L10) + "](:[c,n,o,s]):[n,o,s]");
		L10_L15_Pattern = parseSMARTS("[N:" + str(BRICSAtomLabel::L15) + "](-@[C]=O)(-@[#6,#7,#8,#16])-!@[C:" + str(BRICSAtomLabel::L10) + "](-@[C])-@[C]");
		L10_L16_Pattern = parseSMARTS("[N:" + str(BRICSAtomLabel::L16) + "](-@[C]=O)(-@[#6,#7,#8,#16])-!@[c:" + str(BRICSAtomLabel::L10) + "](:[c]):[c]");

		L11_L13_Pattern = parseSMARTS("[SX2:" + str(BRICSAtomLabel::L13) + "](-[*])-!@[C:" + str(BRICSAtomLabel::L11) + "](-@[#6,#7,#8,#16])-@[#7,#8,#16]");
		L11_L14_Pattern = parseSMARTS("[SX2:" + str(BRICSAtomLabel::L14) + "](-[*])-!@[c:" + str(BRICSAtomLabel::L11) + "](:[c,n,o,s]):[n,o,s]");
		L11_L15_Pattern = parseSMARTS("[SX2:" + str(BRICSAtomLabel::L15) + "](-[*])-!@[C:" + str(BRICSAtomLabel::L11) + "](-@[C])-@[C]");
		L11_L16_Pattern = parseSMARTS("[SX2:" + str(BRICSAtomLabel::L16) + "](-[*])-!@[c:" + str(BRICSAtomLabel::L11) + "](:[c]):[c]");

		L13_L14_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L14) + "](-@[#6,#7,#8,#16])(-@[#7,#8,#16])-!@[c:" + str(BRICSAtomLabel::L13) + "](:[c,n,o,s]):[n,o,s]");
		L13_L15_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L15) + "](-@[#6,#7,#8,#16])(-@[#7,#8,#16])-!@[C:" + str(BRICSAtomLabel::L13) + "](-@[C])-@[C]");
		L13_L16_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L16) + "](-@[#6,#7,#8,#16])(-@[#7,#8,#16])-!@[c:" + str(BRICSAtomLabel::L13) + "](:[c]):[c]");

		L14_L15_Pattern = parseSMARTS("[c:" + str(BRICSAtomLabel::L15) + "](:[c,n,o,s])(:[n,o,s])-!@[C:" + str(BRICSAtomLabel::L14) + "](-@[C])-@[C]");
		L14_L16_Pattern = parseSMARTS("[c:" + str(BRICSAtomLabel::L16) + "](:[c,n,o,s])(:[n,o,s])-!@[c:" + str(BRICSAtomLabel::L14) + "](:[c]):[c]");

		L15_L16_Pattern = parseSMARTS("[C:" + str(BRICSAtomLabel::L16) + "](-@[C])(-@[C])-!@[c:" + str(BRICSAtomLabel::L15) + "](:[c]):[c]");

		halogenXPattern = parseSMARTS("[*:1]-[Cl,Br,I:1]");
		hydrogenXPattern = parseSMARTS("[*:1]-[#1:1]");
		methoxyXPattern = parseSMARTS("[*:1]-[O:1]-[CH3]");
		nitroXPattern = parseSMARTS("[*:1]-[N:1](-O)=O");
		carboxyXPattern = parseSMARTS("[*:1]-[C:1](-[OX1,OH1])=O");
		hydroxyXPattern = parseSMARTS("[*:1]-[OX1,OH1:1]");
		methylXPattern = parseSMARTS("[*:1]-[CH3:1]");
		ethylXPattern = parseSMARTS("[*:1]-[CH2:1]-[CH3]");
		isopropylXPattern = parseSMARTS("[*:1]-[CH1:1](-[CH3])-[CH3]");
		trifluormethylXPattern = parseSMARTS("[*:1]-[C:1](-[F])(-[F])-[F]");
	}
};


Chem::BRICSFragmentGenerator::BRICSFragmentGenerator(): FragmentGenerator()
{
	boost::call_once(&initPatterns, initPatternsFlag);

	addFragmentationRule(L1_L2_Pattern, BRICSRuleID::L1_L2);
	addFragmentationRule(L1_L3_Pattern, BRICSRuleID::L1_L3);
	addFragmentationRule(L1_L10_Pattern, BRICSRuleID::L1_L10);
	addFragmentationRule(L2_L12_Pattern, BRICSRuleID::L2_L12);
	addFragmentationRule(L2_L14_Pattern, BRICSRuleID::L2_L14);
	addFragmentationRule(L2_L16_Pattern, BRICSRuleID::L2_L16);
	addFragmentationRule(L3_L4_Pattern, BRICSRuleID::L3_L4);
	addFragmentationRule(L3_L13_Pattern, BRICSRuleID::L3_L13);
	addFragmentationRule(L3_L14_Pattern, BRICSRuleID::L3_L14);
	addFragmentationRule(L3_L15_Pattern, BRICSRuleID::L3_L15);
	addFragmentationRule(L3_L16_Pattern, BRICSRuleID::L3_L16);
	addFragmentationRule(L4_L5_Pattern, BRICSRuleID::L4_L5);
	addFragmentationRule(L4_L11_Pattern, BRICSRuleID::L4_L11);
	addFragmentationRule(L5_L13_Pattern, BRICSRuleID::L5_L13);
	addFragmentationRule(L5_L15_Pattern, BRICSRuleID::L5_L15);
	addFragmentationRule(L6_L13_Pattern, BRICSRuleID::L6_L13);
	addFragmentationRule(L6_L14_Pattern, BRICSRuleID::L6_L14);
	addFragmentationRule(L6_L15_Pattern, BRICSRuleID::L6_L15);
	addFragmentationRule(L6_L16_Pattern, BRICSRuleID::L6_L16);
	addFragmentationRule(L7_L7_Pattern, BRICSRuleID::L7_L7);
	addFragmentationRule(L8_L9_Pattern, BRICSRuleID::L8_L9);
	addFragmentationRule(L8_L10_Pattern, BRICSRuleID::L8_L10);
	addFragmentationRule(L8_L13_Pattern, BRICSRuleID::L8_L13);
	addFragmentationRule(L8_L14_Pattern, BRICSRuleID::L8_L14);
	addFragmentationRule(L8_L15_Pattern, BRICSRuleID::L8_L15);
	addFragmentationRule(L8_L16_Pattern, BRICSRuleID::L8_L16);
	addFragmentationRule(L9_L15_Pattern, BRICSRuleID::L9_L15);
	addFragmentationRule(L9_L16_Pattern, BRICSRuleID::L9_L16);
	addFragmentationRule(L10_L13_Pattern, BRICSRuleID::L10_L13);
	addFragmentationRule(L10_L14_Pattern, BRICSRuleID::L10_L14);
	addFragmentationRule(L10_L15_Pattern, BRICSRuleID::L10_L15);
	addFragmentationRule(L10_L16_Pattern, BRICSRuleID::L10_L16);
	addFragmentationRule(L11_L13_Pattern, BRICSRuleID::L11_L13);
	addFragmentationRule(L11_L14_Pattern, BRICSRuleID::L11_L14);
	addFragmentationRule(L11_L15_Pattern, BRICSRuleID::L11_L15);
	addFragmentationRule(L11_L16_Pattern, BRICSRuleID::L11_L16);
	addFragmentationRule(L13_L14_Pattern, BRICSRuleID::L13_L14);
	addFragmentationRule(L13_L15_Pattern, BRICSRuleID::L13_L15);
	addFragmentationRule(L13_L16_Pattern, BRICSRuleID::L13_L16);
	addFragmentationRule(L14_L15_Pattern, BRICSRuleID::L14_L15);
	addFragmentationRule(L14_L16_Pattern, BRICSRuleID::L14_L16);
	addFragmentationRule(L15_L16_Pattern, BRICSRuleID::L15_L16);

	addExcludePattern(halogenXPattern);
	addExcludePattern(hydrogenXPattern);
	addExcludePattern(methoxyXPattern);
	addExcludePattern(nitroXPattern);
	addExcludePattern(carboxyXPattern);
	addExcludePattern(hydroxyXPattern);
	addExcludePattern(methylXPattern);
	addExcludePattern(ethylXPattern);
	addExcludePattern(isopropylXPattern);
	addExcludePattern(trifluormethylXPattern);
}
