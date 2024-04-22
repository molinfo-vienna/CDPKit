/* 
 * LogSCalculator.cpp 
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

#include <numeric>
#include <vector>
#include <mutex>

#include "CDPL/MolProp/LogSCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Math/VectorIterator.hpp"


using namespace CDPL;


namespace
{
    
    typedef std::vector<Chem::MolecularGraph::SharedPointer> PatternTable;

    PatternTable atomTypePatterns;

    std::once_flag initAtomTypePatternsFlag;

    void initAtomTypePatterns() 
    {
        using namespace Chem;

        atomTypePatterns.push_back(parseSMARTS("[CX4;H4:1]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H3:1]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H3:2][#6]")); 
        atomTypePatterns.push_back(parseSMARTS("[CX4;H3:3][CX4,c,F,Cl,Br,I]")); 
        atomTypePatterns.push_back(parseSMARTS("[CX4;H3:4][CX3,c,F,Cl,Br,I]=[#8,#7]")); 
        atomTypePatterns.push_back(parseSMARTS("[CX4;H3:5][CX4,c,F,Cl,Br,I]~[#8,#7]")); 
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:6]")); 
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:7][#6]")); 
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:8]([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:9]([#6X4,c,F,Cl,Br,I])[#6X4,c,F,Cl,Br,I]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:10][#6]=[#8,#7]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:11][CX4,c,F,Cl,Br,I]~[#8,#7]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:12]([CX4,c,F,Cl,Br,I])[CX4,c,F,Cl,Br,I]~[#8,#7]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H2:13]-[OH,NH2,NH]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H:14]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H:15]([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H:16]([#6])([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H:17]([#6X4,c,F,Cl,Br,I])([#6X4,c,F,Cl,Br,I])[#6X4,c,F,Cl,Br,I]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H1:18]-[OH,NH2,NH]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:19]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:19][#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:19]([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:20]([#6])([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:21]([#6])([#6])([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:21]([#6X4,c])([#6X4,c])([#6X4,c])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[CX4;H0:21]([#6X4,c])([#6X4,c])([#6X4,c])[#6X4,c]"));
        atomTypePatterns.push_back(parseSMARTS("[C;H2:22]=*"));
        atomTypePatterns.push_back(parseSMARTS("[C;H1:23]=*"));
        atomTypePatterns.push_back(parseSMARTS("[C;H0:24]=*"));
        atomTypePatterns.push_back(parseSMARTS("[C;H1:25]=O"));
        atomTypePatterns.push_back(parseSMARTS("[C;H0:26]=O"));
        atomTypePatterns.push_back(parseSMARTS("[C;r:27]=O"));
        atomTypePatterns.push_back(parseSMARTS("[C:28](C)C"));
        atomTypePatterns.push_back(parseSMARTS("[C:28]#*"));
        atomTypePatterns.push_back(parseSMARTS("[c;H1:29](~c)~c"));
        atomTypePatterns.push_back(parseSMARTS("[c;H1;r6:30](~c)~c"));
        atomTypePatterns.push_back(parseSMARTS("[c;H1:31](~c)~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[c;H1:32](~[a;!c])~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:33](~[a;!c])~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:34](~[!#6])(~[a;!c])~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:35](~*)(~c)~c"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:35](~C)(~c)~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:36](~[CX4,F,Cl,Br,I])(~c)~c"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:36](~[CX4,F,Cl,Br,I])(~c)~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:37](~c)(~[c])~c"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:38](~[!#6;!F;!Cl])(~c)~c"));
        atomTypePatterns.push_back(parseSMARTS("[c;H0:39](~[!#6])(~c)~[a;!c]"));
        atomTypePatterns.push_back(parseSMARTS("[#8;H1:40]"));
        atomTypePatterns.push_back(parseSMARTS("[#8;H1:41]C"));
        atomTypePatterns.push_back(parseSMARTS("[#8;H0:42]"));
        atomTypePatterns.push_back(parseSMARTS("[#8;H0:43]CO"));
        atomTypePatterns.push_back(parseSMARTS("[#8;H0:44]([#6X4])[#6X4]"));
        atomTypePatterns.push_back(parseSMARTS("[#8:45]=C"));
        atomTypePatterns.push_back(parseSMARTS("[#8:45]=c"));
        atomTypePatterns.push_back(parseSMARTS("[#8:46]=C([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[#8:46]=c([#6])[#6]"));
        atomTypePatterns.push_back(parseSMARTS("[o:47]"));
        atomTypePatterns.push_back(parseSMARTS("[OX1:48]~S"));
        atomTypePatterns.push_back(parseSMARTS("[OX1:48]~P"));
        atomTypePatterns.push_back(parseSMARTS("[OX2:49](*)[P]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H2:50]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H2:50][C]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H1:51]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H1:52]([#6X4])"));
        atomTypePatterns.push_back(parseSMARTS("[N;H1:53]([#6X4])[#6X4]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H1;r:54]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H0:55]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H0:56]([#6X4])"));
        atomTypePatterns.push_back(parseSMARTS("[N;H0:56]([#6X4])[#6X4]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H0:56]([#6X4])([#6X4])[#6X4]"));
        atomTypePatterns.push_back(parseSMARTS("[N;H0;r:57]([#6X4])([#6X4])[#6X4]"));
        atomTypePatterns.push_back(parseSMARTS("[n:58]"));
        atomTypePatterns.push_back(parseSMARTS("[n:59]~[n]"));
        atomTypePatterns.push_back(parseSMARTS("[n:59]~[*]~[n]"));
        atomTypePatterns.push_back(parseSMARTS("[nH:60]"));
        atomTypePatterns.push_back(parseSMARTS("[N:61]=*"));
        atomTypePatterns.push_back(parseSMARTS("[N:62]#*"));
        atomTypePatterns.push_back(parseSMARTS("[N:62](=*)=*"));
        atomTypePatterns.push_back(parseSMARTS("[NX3:63](O)=O"));
        atomTypePatterns.push_back(parseSMARTS("[NX3:63](O)-O"));
        atomTypePatterns.push_back(parseSMARTS("[S;H1:64]"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:65]"));
        atomTypePatterns.push_back(parseSMARTS("[s:66]"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:66]1*=**=*1"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:66]1*:**:*1"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:66]1*=**:*1"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:66]1*=*~*~*=*1"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:66]1*:*~*~*:*1"));
        atomTypePatterns.push_back(parseSMARTS("[S;H0:66]1*=*~*~*:*1"));
        atomTypePatterns.push_back(parseSMARTS("[SX3:67]=[OX1]"));
        atomTypePatterns.push_back(parseSMARTS("[SX4:67](=[OX1])=[OX1]"));
        atomTypePatterns.push_back(parseSMARTS("[SX3:67]-[OX1]"));
        atomTypePatterns.push_back(parseSMARTS("[SX4:67](-[OX1])-[OX1]"));
        atomTypePatterns.push_back(parseSMARTS("[PX3:68]"));
        atomTypePatterns.push_back(parseSMARTS("[PX4:68]"));
        atomTypePatterns.push_back(parseSMARTS("[F:69]"));
        atomTypePatterns.push_back(parseSMARTS("[Cl:70]"));
        atomTypePatterns.push_back(parseSMARTS("[Br:71]"));
        atomTypePatterns.push_back(parseSMARTS("[I:72]"));
        atomTypePatterns.push_back(parseSMARTS("[F:73]c"));
        atomTypePatterns.push_back(parseSMARTS("[Cl:74]c"));
        atomTypePatterns.push_back(parseSMARTS("[Br:75]c"));
        atomTypePatterns.push_back(parseSMARTS("[I:76]c"));
    }

    constexpr std::size_t LOGS_OFFSET_INDEX    = 0;
    constexpr std::size_t HYDROPHOBIC_C_INDEX  = 77;
    constexpr std::size_t SQUARED_MW_INDEX     = 78;

    constexpr double REGRESSION_COEFFS[] = {
          -0.332777159212,
        0.377662987239,
        0.116285697171,
        -0.159031865491,
        0.332416630985,
        0.0248726610163,
        0.0584833467075,
        0.0423932225981,
        -0.0286232594976,
        -0.195499180093,
        0.54190814936,
        0.103294500243,
        0.0977604918427,
        0.23832885944,
        -0.0470026238415,
        0.0116595769766,
        0.000686443212761,
        0.0245512162982,
        0.107234608462,
        -0.0449974908798,
        0.0596605349637,
        1.28436026878e-15,
        0.0569699129121,
        -0.140163703519,
        -0.198397807606,
        0.501205131285,
        -0.138096753706,
        -0.0254430659814,
        -0.0922907982408,
        -0.140975911062,
        -0.201312365769,
        0.0918228650665,
        -0.167414833579,
        0.602921766185,
        -0.933790231614,
        -0.464852161597,
        -0.214628837434,
        -0.654314799463,
        -0.315862179284,
        -0.639093111858,
        0.57444832397,
        0.322034022188,
        -0.188653494378,
        -0.017427980067,
        -0.00590220857807,
        0.070480596968,
        -0.0172746427733,
        -0.157684427233,
        0.0873786451599,
        -0.239482347174,
        0.354012262133,
        -0.109402898254,
        -0.134787305315,
        0.0771617526112,
        -0.00184960327857,
        0.271518842054,
        -0.333453624029,
        0.342903479296,
        0.440543958427,
        0.105012224259,
        0.0576098171935,
        -0.29235189692,
        0.206215248207,
        -0.0942662800488,
        0.68764612773,
        -0.853555026466,
        -0.592420971323,
        0.0470081048262,
        -0.0996487371312,
        -0.265768869038,
        -0.533127936882,
        -0.496173263713,
        -0.56076900185,
        -0.192434587407,
        -0.602731665751,
        -0.673484985187,
        -0.064764896147,
        -0.303534934819,
        -6.95335930774e-06
    };
}


constexpr std::size_t MolProp::LogSCalculator::FEATURE_VECTOR_SIZE;


MolProp::LogSCalculator::LogSCalculator(): featureVector(FEATURE_VECTOR_SIZE), logS(0.0) {}

MolProp::LogSCalculator::LogSCalculator(const Chem::MolecularGraph& molgraph): featureVector(FEATURE_VECTOR_SIZE)
{
    calculate(molgraph);
}

double MolProp::LogSCalculator::calculate(const Chem::MolecularGraph& molgraph) 
{
    init(molgraph);
    countHydrophicCarbons(molgraph);
    calcLogS(molgraph);

    return logS;
}

double MolProp::LogSCalculator::getResult() const
{
    return logS;
}

const Math::DVector& MolProp::LogSCalculator::getFeatureVector() const
{
    return featureVector;
}

void MolProp::LogSCalculator::init(const Chem::MolecularGraph& molgraph)
{
    if (atomTyper.getNumPatterns() == 0) {
        std::call_once(initAtomTypePatternsFlag, &initAtomTypePatterns);

        for (PatternTable::const_iterator p_it = atomTypePatterns.begin(), p_end = atomTypePatterns.end(); p_it != p_end; ++p_it)
            atomTyper.addPattern(*p_it);
    }

    double mw = calcMass(molgraph);

    featureVector.clear();
    featureVector[LOGS_OFFSET_INDEX] = 1;
    featureVector[SQUARED_MW_INDEX] = mw * mw;
}

void MolProp::LogSCalculator::countHydrophicCarbons(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
        const Atom& atom = molgraph.getAtom(i);

        if (getType(atom) != AtomType::C || getAromaticityFlag(atom))
            continue;

        switch (getHybridizationState(atom)) {

            case HybridizationState::SP2:
                if (getRingFlag(atom))
                    continue;
                    
            case HybridizationState::SP3:
                break;

            default:
                continue;
        }

        bool hydrophobic = true;

        for (std::size_t j = 0; j < num_atoms && hydrophobic; j++) {
            if (i == j)
                continue;

            switch (getType(molgraph.getAtom(j))) {

                case AtomType::C:
                case AtomType::H:
                    continue;

                default:
                    if (hasTopDistanceBelow4(atom, molgraph.getAtom(j), molgraph, atom, 0))
                        hydrophobic = false;
            }
        }

        if (hydrophobic)
            featureVector[HYDROPHOBIC_C_INDEX]++;
    }
}

bool MolProp::LogSCalculator::hasTopDistanceBelow4(const Chem::Atom& curr_atom, const Chem::Atom& tgt_atom, const Chem::MolecularGraph& molgraph,
                                                   const Chem::Atom& prev_atom, std::size_t curr_dist)
{
    using namespace Chem;
    
    Atom::ConstBondIterator b_it = curr_atom.getBondsBegin();
    
    for (Atom::ConstAtomIterator a_it = curr_atom.getAtomsBegin(), a_end = curr_atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        const Atom& atom = *a_it;

        if (&atom == &prev_atom)
            continue;
        
        if (!molgraph.containsBond(*b_it))
            continue;

        if (&atom == &tgt_atom)
            return true;

        if (!molgraph.containsAtom(atom))
            continue;

        if (curr_dist < 2)
            if (hasTopDistanceBelow4(atom, tgt_atom, molgraph, curr_atom, curr_dist + 1))
                return true;
    }
    
    return false;
}
    
void MolProp::LogSCalculator::calcLogS(const Chem::MolecularGraph& molgraph)
{
    atomTyper.execute(molgraph);

    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++)
        if (atomTyper.hasAtomLabel(i))
            featureVector[atomTyper.getAtomLabel(i)]++;

    logS = std::inner_product(Math::vectorBegin(featureVector), Math::vectorEnd(featureVector), REGRESSION_COEFFS, 0.0);
}
