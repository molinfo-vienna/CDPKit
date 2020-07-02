/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RECAPFragmentGenerator.cpp 
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

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include "CDPL/Chem/RECAPFragmentGenerator.hpp"
#include "CDPL/Chem/RECAPRuleID.hpp"
#include "CDPL/Chem/RECAPAtomLabel.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

	const std::string AMIDE_PATTERN_STR                  = "[#7v3X3:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AMIDE_N) + 
		                                                   "](-[#1,#6])(-[#6])-!@[C:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AMIDE_C) + "](=O)-[#6,#1]";
	const std::string ESTER_PATTERN_STR                  = "[OX2:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::ESTER_O) + 
		                                                   "](-[#6])-!@[C:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::ESTER_C) + "](=O)-[#6,#1]";
	const std::string AMINE_PATTERN_STR                  = "[NX3v3:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AMINE_N) + 
		                                                   "](-[#1,#6])(-[#6])-!@[C!R:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AMINE_C) + "]";
	const std::string UREA_PATTERN_STR                   = "[#7v3X3:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::UREA_N) + 
		                                                   "](-[#1,#6])(-[#6])-!@[C:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::UREA_C) + "](=O)-[#7]";
	const std::string ETHER_PATTERN_STR                  = "[OX2:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::ETHER_O) + 
		                                                   "](-[#6])-!@[C!R:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::ETHER_C) + "]";
	const std::string OLEFIN_PATTERN_STR                 = "[CX3:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::OLEFIN_C) + 
		                                                   "](-[#1,#6])(-[#6])=!@[CX3:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::OLEFIN_C) + "](-[#1,#6])(-[#6])";
	const std::string QUARTERNARY_N_PATTERN_STR          = "[NX4+1:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::QUARTERNARY_N_N) + 
		                                                   "](-[#1,#6])(-[#1,#6])(-[#6])-!@[CX4!R:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::QUARTERNARY_N_C) + "]";
	const std::string AROMATIC_N_ALIPHATIC_C_PATTERN_STR = "[n:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_N) +
		                                                   "]-!@[CX4:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_C) + "]";
	const std::string LACTAM_N_ALIPHATIC_C_PATTERN_STR   = "[Nv3X3R:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_N) + 
                                                           "](-@[#6R])(-!@[CX4!R:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_C) + "])-@[CR](=O)(-@[#6R])";
	const std::string AROMATIC_C_AROMATIC_C_PATTERN_STR  = "[c:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C) +
		                                                   "]-!@[c:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C) + "]";
	const std::string SULFONAMIDE_PATTERN_STR            = "[#7v3X3:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::SULFONAMIDE_N) + 
		                                                   "](-[#1,#6])(-[#6])-!@[S:" + boost::lexical_cast<std::string>(Chem::RECAPAtomLabel::SULFONAMIDE_S) + "](=O)(=O)-[#6,#1]";

	const std::string METHYL_X_PATTERN_STR               = "[*:1]-[CH3:1]";
	const std::string ETHYL_X_PATTERN_STR                = "[*:1]-[CH2:1]-[CH3]";
	const std::string PROPYL_X_PATTERN_STR               = "[*:1]-[CH2:1]-[CH2]-[CH3]";
	const std::string BUTYL_X_PATTERN_STR                = "[*:1]-[CH2:1]-[CH2]-[CH2]-[CH3]";

	Chem::Molecule::SharedPointer amidePattern;
	Chem::Molecule::SharedPointer esterPattern;
	Chem::Molecule::SharedPointer aminePattern;
	Chem::Molecule::SharedPointer ureaPattern;
	Chem::Molecule::SharedPointer etherPattern;
	Chem::Molecule::SharedPointer olefinPattern;
	Chem::Molecule::SharedPointer quarternaryNPattern;
	Chem::Molecule::SharedPointer aromaticNAliphaticCPattern;
	Chem::Molecule::SharedPointer lactamNAliphaticCPattern;
	Chem::Molecule::SharedPointer aromaticCAromaticCPattern;
	Chem::Molecule::SharedPointer sulfonamidePattern;

	Chem::Molecule::SharedPointer methylXPattern;
	Chem::Molecule::SharedPointer ethylXPattern;
	Chem::Molecule::SharedPointer propylXPattern;
	Chem::Molecule::SharedPointer butylXPattern;

	boost::once_flag initPatternsFlag = BOOST_ONCE_INIT;

	void initPatterns() 
	{
		amidePattern = Chem::parseSMARTS(AMIDE_PATTERN_STR);
		esterPattern = Chem::parseSMARTS(ESTER_PATTERN_STR);
		aminePattern = Chem::parseSMARTS(AMINE_PATTERN_STR);
		ureaPattern = Chem::parseSMARTS(UREA_PATTERN_STR);
		etherPattern = Chem::parseSMARTS(ETHER_PATTERN_STR);
		olefinPattern = Chem::parseSMARTS(OLEFIN_PATTERN_STR);
		quarternaryNPattern = Chem::parseSMARTS(QUARTERNARY_N_PATTERN_STR);
		aromaticNAliphaticCPattern = Chem::parseSMARTS(AROMATIC_N_ALIPHATIC_C_PATTERN_STR);
		lactamNAliphaticCPattern = Chem::parseSMARTS(LACTAM_N_ALIPHATIC_C_PATTERN_STR);
		aromaticCAromaticCPattern = Chem::parseSMARTS(AROMATIC_C_AROMATIC_C_PATTERN_STR);
		sulfonamidePattern = Chem::parseSMARTS(SULFONAMIDE_PATTERN_STR);

		methylXPattern = Chem::parseSMARTS(METHYL_X_PATTERN_STR);
		ethylXPattern = Chem::parseSMARTS(ETHYL_X_PATTERN_STR);
		propylXPattern = Chem::parseSMARTS(PROPYL_X_PATTERN_STR);
		butylXPattern = Chem::parseSMARTS(BUTYL_X_PATTERN_STR);
	}
};


Chem::RECAPFragmentGenerator::RECAPFragmentGenerator(): FragmentGenerator()
{
	boost::call_once(&initPatterns, initPatternsFlag);

	addFragmentationRule(aminePattern, RECAPRuleID::AMINE);
	addFragmentationRule(etherPattern, RECAPRuleID::ETHER);
	addFragmentationRule(amidePattern, RECAPRuleID::AMIDE);
	addFragmentationRule(esterPattern, RECAPRuleID::ESTER);
	addFragmentationRule(ureaPattern, RECAPRuleID::UREA);
	addFragmentationRule(olefinPattern, RECAPRuleID::OLEFIN);
	addFragmentationRule(quarternaryNPattern, RECAPRuleID::QUARTERNARY_N);
	addFragmentationRule(aromaticNAliphaticCPattern, RECAPRuleID::AROMATIC_N_ALIPHATIC_C);
	addFragmentationRule(lactamNAliphaticCPattern, RECAPRuleID::LACTAM_N_ALIPHATIC_C);
	addFragmentationRule(aromaticCAromaticCPattern, RECAPRuleID::AROMATIC_C_AROMATIC_C);
	addFragmentationRule(sulfonamidePattern, RECAPRuleID::SULFONAMIDE);

	addExcludePattern(methylXPattern);
	addExcludePattern(ethylXPattern);
	addExcludePattern(propylXPattern);
	addExcludePattern(butylXPattern);
}
