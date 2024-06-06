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

    Chem::Molecule::SharedPointer amidePattern1;
    Chem::Molecule::SharedPointer amidePattern2;
    Chem::Molecule::SharedPointer amidePattern3;
    Chem::Molecule::SharedPointer amidePattern4;
    Chem::Molecule::SharedPointer esterPattern1;
    Chem::Molecule::SharedPointer esterPattern2;
    Chem::Molecule::SharedPointer aminePattern1;
    Chem::Molecule::SharedPointer aminePattern2;
    Chem::Molecule::SharedPointer ureaPattern1;
    Chem::Molecule::SharedPointer ureaPattern2;
    Chem::Molecule::SharedPointer etherPattern;
    Chem::Molecule::SharedPointer olefinPattern1;
    Chem::Molecule::SharedPointer olefinPattern2;
    Chem::Molecule::SharedPointer olefinPattern3;
    Chem::Molecule::SharedPointer olefinPattern4;
    Chem::Molecule::SharedPointer quarternaryNPattern1;
    Chem::Molecule::SharedPointer quarternaryNPattern2;
    Chem::Molecule::SharedPointer quarternaryNPattern3;
    Chem::Molecule::SharedPointer aromaticNAliphaticCPattern;
    Chem::Molecule::SharedPointer lactamNAliphaticCPattern;
    Chem::Molecule::SharedPointer aromaticCAromaticCPattern;
    Chem::Molecule::SharedPointer sulfonamidePattern1;
    Chem::Molecule::SharedPointer sulfonamidePattern2;
    Chem::Molecule::SharedPointer sulfonamidePattern3;
    Chem::Molecule::SharedPointer sulfonamidePattern4;

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

        amidePattern1               = parseSMARTS("[#7v3X3H0:" + str(RECAPAtomLabel::AMIDE_N) + "](-[#6])(-[#6])-!@[CH0:" + str(RECAPAtomLabel::AMIDE_C) + "](=O)-[#6]");
        amidePattern2               = parseSMARTS("[#7v3X3H1:" + str(RECAPAtomLabel::AMIDE_N) + "](-[#6])-!@[CH1:" + str(RECAPAtomLabel::AMIDE_C) + "]=O");
        amidePattern3               = parseSMARTS("[#7v3X3H0:" + str(RECAPAtomLabel::AMIDE_N) + "](-[#6])(-[#6])-!@[CH0:" + str(RECAPAtomLabel::AMIDE_C) + "](=O)-[#6]");
        amidePattern4               = parseSMARTS("[#7v3X3H1:" + str(RECAPAtomLabel::AMIDE_N) + "](-[#6])-!@[CH1:" + str(RECAPAtomLabel::AMIDE_C) + "]=O");
        
        esterPattern1               = parseSMARTS("[OX2:" + str(RECAPAtomLabel::ESTER_O) + "](-[#6])-!@[CH0:" + str(RECAPAtomLabel::ESTER_C) + "](=O)-[#6]");
        esterPattern2               = parseSMARTS("[OX2:" + str(RECAPAtomLabel::ESTER_O) + "](-[#6])-!@[CH1:" + str(RECAPAtomLabel::ESTER_C) + "]=O");

        aminePattern1               = parseSMARTS("[NX3v3H0:" + str(RECAPAtomLabel::AMINE_N) + "](-[#6])(-[#6])-!@[C!R:" + str(RECAPAtomLabel::AMINE_C) + "]");
        aminePattern2               = parseSMARTS("[NX3v3H1:" + str(RECAPAtomLabel::AMINE_N) + "](-[#6])-!@[C!R:" + str(RECAPAtomLabel::AMINE_C) + "]");
        
        ureaPattern1                = parseSMARTS("[#7v3X3H0:" + str(RECAPAtomLabel::UREA_N) + "](-[#6])(-[#6])-!@[C:" + str(RECAPAtomLabel::UREA_C) + "](=O)-[#7]");
        ureaPattern2                = parseSMARTS("[#7v3X3H1:" + str(RECAPAtomLabel::UREA_N) + "](-[#6])-!@[C:" + str(RECAPAtomLabel::UREA_C) + "](=O)-[#7]");
        
        etherPattern               = parseSMARTS("[OX2:" + str(RECAPAtomLabel::ETHER_O) + "](-[#6])-!@[C!R:" + str(RECAPAtomLabel::ETHER_C) + "]");
        
        olefinPattern1              = parseSMARTS("[CX3H0:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#6])(-[#6])=!@[CX3H0:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#6])-[#6]");
        olefinPattern2              = parseSMARTS("[CX3H1:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#6])=!@[CX3H0:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#6])-[#6]");
        olefinPattern3              = parseSMARTS("[CX3H0:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#6])(-[#6])=!@[CX3H1:" + str(RECAPAtomLabel::OLEFIN_C) + "]-[#6]");
        olefinPattern4              = parseSMARTS("[CX3H1:" + str(RECAPAtomLabel::OLEFIN_C) + "](-[#6])=!@[CX3H1:" + str(RECAPAtomLabel::OLEFIN_C) + "]-[#6]");
        
        quarternaryNPattern1        = parseSMARTS("[NX4+1H0:" + str(RECAPAtomLabel::QUARTERNARY_N_N) + "](-[#6])(-[#6])(-[#6])-!@[CX4!R:" + str(RECAPAtomLabel::QUARTERNARY_N_C) + "]");
        quarternaryNPattern2        = parseSMARTS("[NX4+1H1:" + str(RECAPAtomLabel::QUARTERNARY_N_N) + "](-[#6])(-[#6])-!@[CX4!R:" + str(RECAPAtomLabel::QUARTERNARY_N_C) + "]");
        quarternaryNPattern3        = parseSMARTS("[NX4+1H2:" + str(RECAPAtomLabel::QUARTERNARY_N_N) + "](-[#6])-!@[CX4!R:" + str(RECAPAtomLabel::QUARTERNARY_N_C) + "]");
                        
        aromaticNAliphaticCPattern = parseSMARTS("[n:" + str(RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_N) + "]-!@[CX4:" + str(RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_C) + "]");
        lactamNAliphaticCPattern   = parseSMARTS("[Nv3X3R:" + str(RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_N) + "](-@[#6R])(-!@[CX4!R:" + str(RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_C) + "])-@[CR](=O)(-@[#6R])");
        aromaticCAromaticCPattern  = parseSMARTS("[c:" + str(RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C) + "]-!@[c:" + str(RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C) + "]");

        sulfonamidePattern1         = parseSMARTS("[#7v3X3H0:" + str(RECAPAtomLabel::SULFONAMIDE_N) + "](-[#6])(-[#6])-!@[SH0:" + str(RECAPAtomLabel::SULFONAMIDE_S) + "](~[OX1])(~[OX1])-[#6]");
        sulfonamidePattern2         = parseSMARTS("[#7v3X3H1:" + str(RECAPAtomLabel::SULFONAMIDE_N) + "](-[#6])-!@[SH0:" + str(RECAPAtomLabel::SULFONAMIDE_S) + "](~[OX1])(~[OX1])-[#6]");
        sulfonamidePattern3         = parseSMARTS("[#7v3X3H0:" + str(RECAPAtomLabel::SULFONAMIDE_N) + "](-[#6])(-[#6])-!@[SH1:" + str(RECAPAtomLabel::SULFONAMIDE_S) + "](~[OX1])~[OX1]");
        sulfonamidePattern4         = parseSMARTS("[#7v3X3H1:" + str(RECAPAtomLabel::SULFONAMIDE_N) + "](-[#6])-!@[SH1:" + str(RECAPAtomLabel::SULFONAMIDE_S) + "](~[OX1])~[OX1]");

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

    addFragmentationRule(aminePattern1, RECAPRuleID::AMINE);
    addFragmentationRule(aminePattern2, RECAPRuleID::AMINE);
        
    addFragmentationRule(etherPattern, RECAPRuleID::ETHER);

    addFragmentationRule(amidePattern1, RECAPRuleID::AMIDE);
    addFragmentationRule(amidePattern2, RECAPRuleID::AMIDE);
    addFragmentationRule(amidePattern3, RECAPRuleID::AMIDE);
    addFragmentationRule(amidePattern4, RECAPRuleID::AMIDE);
    
    addFragmentationRule(esterPattern1, RECAPRuleID::ESTER);
    addFragmentationRule(esterPattern2, RECAPRuleID::ESTER);
        
    addFragmentationRule(ureaPattern1, RECAPRuleID::UREA);
    addFragmentationRule(ureaPattern2, RECAPRuleID::UREA);
    
    addFragmentationRule(olefinPattern1, RECAPRuleID::OLEFIN);
    addFragmentationRule(olefinPattern2, RECAPRuleID::OLEFIN);
    addFragmentationRule(olefinPattern3, RECAPRuleID::OLEFIN);
    addFragmentationRule(olefinPattern4, RECAPRuleID::OLEFIN);
                
    addFragmentationRule(quarternaryNPattern1, RECAPRuleID::QUARTERNARY_N);
    addFragmentationRule(quarternaryNPattern2, RECAPRuleID::QUARTERNARY_N);
    addFragmentationRule(quarternaryNPattern3, RECAPRuleID::QUARTERNARY_N);
            
    addFragmentationRule(aromaticNAliphaticCPattern, RECAPRuleID::AROMATIC_N_ALIPHATIC_C);
    addFragmentationRule(lactamNAliphaticCPattern, RECAPRuleID::LACTAM_N_ALIPHATIC_C);
    addFragmentationRule(aromaticCAromaticCPattern, RECAPRuleID::AROMATIC_C_AROMATIC_C);

    addFragmentationRule(sulfonamidePattern1, RECAPRuleID::SULFONAMIDE);
    addFragmentationRule(sulfonamidePattern2, RECAPRuleID::SULFONAMIDE);
    addFragmentationRule(sulfonamidePattern3, RECAPRuleID::SULFONAMIDE);
    addFragmentationRule(sulfonamidePattern4, RECAPRuleID::SULFONAMIDE);

    addExcludePattern(methylXPattern);
    addExcludePattern(ethylXPattern);
    addExcludePattern(propylXPattern);
    addExcludePattern(butylXPattern);
}
