/* 
 * RECAPFragmentGenerator.cpp 
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

#include <mutex>

#include "CDPL/Chem/RECAPFragmentGenerator.hpp"
#include "CDPL/Chem/RECAPRuleID.hpp"
#include "CDPL/Chem/RECAPAtomLabel.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

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

    std::once_flag initPatternsFlag;

    inline std::string str(unsigned int label)
    {
        return std::to_string(label);
    }

    void initPatterns()
    {
        using namespace Chem;

        amidePattern               = parseSMARTS("[#7v3X3:" + str(RECAPAtomLabel::AMIDE_N) + "](-[#1,#6])(-[#6])-!@[C:" + str(RECAPAtomLabel::AMIDE_C) + "](=O)-[#6,#1]");
        esterPattern               = parseSMARTS("[OX2:" + str(RECAPAtomLabel::ESTER_O) + "](-[#6])-!@[C:" + str(RECAPAtomLabel::ESTER_C) + "](=O)-[#6,#1]");
        aminePattern               = parseSMARTS("[NX3v3:" + str(RECAPAtomLabel::AMINE_N) + "](-[#1,#6])(-[#6])-!@[C!R:" + str(RECAPAtomLabel::AMINE_C) + "]");
        ureaPattern                = parseSMARTS("[#7v3X3:" + str(RECAPAtomLabel::UREA_N) + "](-[#1,#6])(-[#6])-!@[C:" + str(RECAPAtomLabel::UREA_C) + "](=O)-[#7]");
        etherPattern               = parseSMARTS("[OX2:" + str(RECAPAtomLabel::ETHER_O) + "](-[#6])-!@[C!R:" + str(RECAPAtomLabel::ETHER_C) + "]");
        olefinPattern              = parseSMARTS("[CX3:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#1,#6])(-[#6])=!@[CX3:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#1,#6])(-[#6])");
        quarternaryNPattern        = parseSMARTS("[NX4+1:" + str(RECAPAtomLabel::QUARTERNARY_N_N) + "](-[#1,#6])(-[#1,#6])(-[#6])-!@[CX4!R:" + str(RECAPAtomLabel::QUARTERNARY_N_C) + "]");
        aromaticNAliphaticCPattern = parseSMARTS("[n:" + str(RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_N) + "]-!@[CX4:" + str(RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_C) + "]");
        lactamNAliphaticCPattern   = parseSMARTS("[Nv3X3R:" + str(RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_N) + "](-@[#6R])(-!@[CX4!R:" + str(RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_C) + "])-@[CR](=O)(-@[#6R])");
        aromaticCAromaticCPattern  = parseSMARTS("[c:" + str(RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C) + "]-!@[c:" + str(RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C) + "]");
        sulfonamidePattern         = parseSMARTS("[#7v3X3:" + str(RECAPAtomLabel::SULFONAMIDE_N) + "](-[#1,#6])(-[#6])-!@[S:" + str(RECAPAtomLabel::SULFONAMIDE_S) + "](=O)(=O)-[#6,#1]");

        methylXPattern = parseSMARTS("[*:1]-[CH3:1]");
        ethylXPattern  = parseSMARTS("[*:1]-[CH2:1]-[CH3]");
        propylXPattern = parseSMARTS("[*:1]-[CH2:1]-[CH2]-[CH3]");
        butylXPattern  = parseSMARTS("[*:1]-[CH2:1]-[CH2]-[CH2]-[CH3]");
    }
}; // namespace


Chem::RECAPFragmentGenerator::RECAPFragmentGenerator():
    FragmentGenerator()
{
    std::call_once(initPatternsFlag, &initPatterns);

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
