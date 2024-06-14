/* 
 * MACCSFingerprintGenerator.cpp 
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

#include "CDPL/Descr/MACCSFingerprintGenerator.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

    struct Pattern
    {

        Pattern(const char* ptn_str, std::size_t cnt):
            pattern(ptn_str ? Chem::parseSMARTS(ptn_str) : Chem::MolecularGraph::SharedPointer()), countThresh(cnt) {}
        
        Chem::MolecularGraph::SharedPointer pattern;
        std::size_t                         countThresh;
    };
    
    typedef std::vector<Pattern> PatternList;

    PatternList    patterns;
    std::once_flag initFlag;

    void init()
    {
        patterns.emplace_back("[!0]", 0);                                                  // Isotope
        patterns.emplace_back("[#104,#105,#106,#107,#108,#109,#110,#111,#112]", 0);        // 103 < ATOMIC_NUM < 113
        patterns.emplace_back("[#32,#33,#34,#50,#51,#52,#82,#83,#84]", 0);                 // Group IVa,Va,VIa Periods 4-6 (Ge...)  *NOTE* incomplete
        patterns.emplace_back("[Ac,Th,Pa,U,Np,Pu,Am,Cm,Bk,Cf,Es,Fm,Md,No,Lr]", 0);         // Actinide
        patterns.emplace_back("[Sc,Ti,Y,Zr,Hf,Lu,Lr,Rf]", 0);                              // Group IIIB,IVB (Sc...)
        patterns.emplace_back("[La,Ce,Pr,Nd,Pm,Sm,Eu,Gd,Tb,Dy,Ho,Er,Tm,Yb,Lu]", 0);        // Lanthanide
        patterns.emplace_back("[V,Cr,Mn,Nb,Mo,Tc,Ta,W,Re,Db,Sg,Bh]", 0);                   // Group VB,VIB,VIIB (V...)
        patterns.emplace_back("[!#6;!#1]1~*~*~*~1", 0);                                    // QAAA@1
        patterns.emplace_back("[Fe,Co,Ni,Ru,Rh,Pd,Os,Ir,Pt,Hs,Mt,Ds]", 0);                 // Group VIII (Fe...)
        patterns.emplace_back("[Be,Mg,Ca,Sr,Ba,Ra]", 0);                                   // Group IIa (Alkaline earth)
        patterns.emplace_back("[R]1@*@*@*@1", 0);                                          // 4M Ring
        patterns.emplace_back("[Cu,Zn,Ag,Cd,Au,Hg]", 0);                                   // Group IB,IIB (Cu..)
        patterns.emplace_back("[#8]~[#7](~[#6])~[#6]", 0);                                 // ON(C)C
        patterns.emplace_back("[#16]-[#16]", 0);                                           // S-S
        patterns.emplace_back("[#8]~[#6](~[#8])~[#8]", 0);                                 // OC(O)O
        patterns.emplace_back("[R!#6!#1]1~*~*~1", 0);                                      // QAA@1
        patterns.emplace_back("[#6]#[#6]", 0);                                             // CTC
        patterns.emplace_back("[#5,#13,#31,#49,#81]", 0);                                  // Group IIIA (B...)
        patterns.emplace_back("[R]1@*@*@*@*@*@*@1", 0);                                    // 7M Ring
        patterns.emplace_back("[Si]", 0);                                                  // Si
        patterns.emplace_back("[#6]=[#6](~[!#6;!#1])~[!#6;!#1]", 0);                       // C=C(Q)Q
        patterns.emplace_back("[R]1@*@*@1", 0);                                            // 3M Ring
        patterns.emplace_back("[#7]~[#6](~[#8])~[#8]", 0);                                 // NC(O)O
        patterns.emplace_back("[#7]-[#8]", 0);                                             // N-O
        patterns.emplace_back("[#7]~[#6](~[#7])~[#7]", 0);                                 // NC(N)N
        patterns.emplace_back("[#6]=;@[#6](@*)@*", 0);                                     // C$=C($A)$A
        patterns.emplace_back("[I]", 0);                                                   // I
        patterns.emplace_back("[!#6;!#1]~[CH2]~[!#6;!#1]", 0);                             // QCH2Q
        patterns.emplace_back("[#15]", 0);                                                 // P
        patterns.emplace_back("[#6]~[!#6;!#1](~[#6])(~[#6])~*", 0);                        // CQ(C)(C)A
        patterns.emplace_back("[!#6;!#1]~[F,Cl,Br,I]", 0);                                 // QX
        patterns.emplace_back("[#6]~[#16]~[#7]", 0);                                       // CSN
        patterns.emplace_back("[#7]~[#16]", 0);                                            // NS
        patterns.emplace_back("[CH2]=*", 0);                                               // CH2=A
        patterns.emplace_back("[Li,Na,K,Rb,Cs,Fr]", 0);                                    // Group IA (Alkali Metal)
        patterns.emplace_back("[#16R]", 0);                                                // S Heterocycle
        patterns.emplace_back("[#7]~[#6](~[#8])~[#7]", 0);                                 // NC(O)N
        patterns.emplace_back("[#7]~[#6](~[#6])~[#7]", 0);                                 // NC(C)N
        patterns.emplace_back("[#8]~[#16](~[#8])~[#8]", 0);                                // OS(O)O
        patterns.emplace_back("[#16]-[#8]", 0);                                            // S-O
        patterns.emplace_back("[#6]#[#7]", 0);                                             // CTN
        patterns.emplace_back("F", 0);                                                     // F
        patterns.emplace_back("[!C;!c;!#1;!H0]~*~[!C;!c;!#1;!H0]", 0);                     // QHAQH
        patterns.emplace_back("[!#1;!#6;!#7;!#8;!#9;!#14;!#15;!#16;!#17;!#35;!#53]", 0);   // OTHER
        patterns.emplace_back("[#6]=[#6]~[#7]", 0);                                        // C=CN
        patterns.emplace_back("Br", 0);                                                    // Br
        patterns.emplace_back("[#16]~*~[#7]", 0);                                          // SAN
        patterns.emplace_back("[#8]~[!#6;!#1](~[#8])(~[#8])", 0);                          // OQ(O)O
        patterns.emplace_back("[!+0]", 0);                                                 // Charge
        patterns.emplace_back("[#6]=[#6](~[#6])~[#6]", 0);                                 // C=C(C)C
        patterns.emplace_back("[#6]~[#16]~[#8]", 0);                                       // CSO
        patterns.emplace_back("[#7]~[#7]", 0);                                             // NN
        patterns.emplace_back("[!#6;!#1;!H0]~*~*~*~[!#6;!#1;!H0]", 0);                     // QHAAAQH
        patterns.emplace_back("[!#6;!#1;!H0]~*~*~[!#6;!#1;!H0]", 0);                       // QHAAQH
        patterns.emplace_back("[#8]~[#16]~[#8]", 0);                                       // OSO
        patterns.emplace_back("[#8]~[#7](~[#8])~[#6]", 0);                                 // ON(O)C
        patterns.emplace_back("[#8R]", 0);                                                 // O Heterocycle
        patterns.emplace_back("[!#6;!#1]~[#16]~[!#6;!#1]", 0);                             // QSQ
        patterns.emplace_back("[#16]!:*:*", 0);                                            // Snot%A%A
        patterns.emplace_back("[#16]=[#8]", 0);                                            // S=O
        patterns.emplace_back("[#16](~*)(~*)~*", 0);                                       // AS(A)A
        patterns.emplace_back("[R]!@[R]", 0);                                              // A$!A$A
        patterns.emplace_back("[#7]=[#8]", 0);                                             // N=O
        patterns.emplace_back("[#16]!@*@*", 0);                                            // A$A!S
        patterns.emplace_back("n:c", 0);                                                   // C%N
        patterns.emplace_back("[#6]~[#6](~[#6])(~[#6])~*", 0);                             // CC(C)(C)A
        patterns.emplace_back("[!#6;!#1]~[#16]", 0);                                       // QS
        patterns.emplace_back("[!#6;!#1;!H0]~[!#6;!#1;!H0]", 0);                           // QHQH (&...) FIX: incomplete definition
        patterns.emplace_back("[!#6;!#1]~[!#6;!#1;!H0]", 0);                               // QQH
        patterns.emplace_back("[!#6;!#1]~[#7]~[!#6;!#1]", 0);                              // QNQ
        patterns.emplace_back("[#7]~[#8]", 0);                                             // NO
        patterns.emplace_back("[#8]~*~*~[#8]", 0);                                         // OAAO
        patterns.emplace_back("[#16]=*", 0);                                               // S=A
        patterns.emplace_back("[CH3]~*~[CH3]", 0);                                         // CH3ACH3
        patterns.emplace_back("[#7](!@*)@*", 0);                                           // A!N$A
        patterns.emplace_back("[#6]=[#6](~*)~*", 0);                                       // C=C(A)A
        patterns.emplace_back("[#7]~*~[#7]", 0);                                           // NAN
        patterns.emplace_back("[#6]=[#7]", 0);                                             // C=N
        patterns.emplace_back("[#7]~*~*~[#7]", 0);                                         // NAAN
        patterns.emplace_back("[#7]~*~*~*~[#7]", 0);                                       // NAAAN
        patterns.emplace_back("[#16]~*(~*)~*", 0);                                         // SA(A)A
        patterns.emplace_back("[CH2](~*)~[!#6;!#1;!H0]", 0);                               // ACH2QH
        patterns.emplace_back("[!#6;!#1]1~*~*~*~*~1", 0);                                  // QAAAA@1
        patterns.emplace_back("[NH2]", 0);                                                 // NH2
        patterns.emplace_back("[#6]~[#7](~[#6])~[#6]", 0);                                 // CN(C)C
        patterns.emplace_back("[C;H2,H3][!#6;!#1][C;H2,H3]", 0);                           // CH2QCH2
        patterns.emplace_back("[F,Cl,Br,I]!@*@*", 0);                                      // X!A$A
        patterns.emplace_back("[#16]", 0);                                                 // S
        patterns.emplace_back("[#8]~*~*~*~[#8]", 0);                                       // OAAAO
        patterns.emplace_back("[#6H2](~*~*~[!#6!#1!H0])~*", 0);                            // QHAACH2A
        patterns.emplace_back("[#6H2](~*~*~*~[!#6!#1!H0])~*", 0);                          // QHAAACH2A
        patterns.emplace_back("[#8]~[#6](~[#7])~[#6]", 0);                                 // OC(N)C
        patterns.emplace_back("[!#6;!#1]~[CH3]", 0);                                       // QCH3
        patterns.emplace_back("[!#6;!#1]~[#7]", 0);                                        // QN
        patterns.emplace_back("[#7]~*~*~[#8]", 0);                                         // NAAO
        patterns.emplace_back("[R]1@*@*@*@*@1", 0);                                        // 5M ring
        patterns.emplace_back("[#8]~*~*~*~[#7]", 0);                                       // NAAAO
        patterns.emplace_back("[R!#6!#1]1@*@*@*@*@*@1", 0);                                // QAAAAA@1
        patterns.emplace_back("[#6]=[#6]", 0);                                             // C=C
        patterns.emplace_back("[#7]~[CH2]~*", 0);                                          // ACH2N
        patterns.emplace_back("[R]1@*@*@*@*@*@*@*@1", 0);                                  // 8M Ring
        patterns.emplace_back("[!#6;!#1]~[#8]", 0);                                        // QO
        patterns.emplace_back("Cl", 0);                                                    // Cl
        patterns.emplace_back("[!#6;!#1;!H0]~*~[CH2]~*", 0);                               // QHACH2A
        patterns.emplace_back("[R!x2](@*)(@*)@*", 0);                                      // A$A($A)$A
        patterns.emplace_back("[!#6;!#1]~*(~[!#6;!#1])~[!#6;!#1]", 0);                     // QA(Q)Q
        patterns.emplace_back("[F,Cl,Br,I]~*(~*)~*", 0);                                   // XA(A)A
        patterns.emplace_back("[CH3]~*~*~*~[CH2]~*", 0);                                   // CH3AAACH2A
        patterns.emplace_back("[#8]~[CH2]~*", 0);                                          // ACH2O
        patterns.emplace_back("[#8]~[#6]~[#7]", 0);                                        // NCO
        patterns.emplace_back("[#7]~*~[CH2]~*", 0);                                        // NACH2A
        patterns.emplace_back("*(~*)(~*)(~*)~*", 0);                                       // AA(A)(A)A
        patterns.emplace_back("[#8]!:*:*", 0);                                             // Onot%A%A
        patterns.emplace_back("[CH3]~[CH2]~*", 0);                                         // CH3CH2A
        patterns.emplace_back("[CH3]~*~[CH2]~*", 0);                                       // CH3ACH2A
        patterns.emplace_back("[#6H3]~*~*~[#6H2]~*", 0);                                   // CH3AACH2A
        patterns.emplace_back("[#7]~*~[#8]", 0);                                           // NAO
        patterns.emplace_back("[#6H2]([#6H2]*)*", 1);                                      // ACH2CH2A > 1
        patterns.emplace_back("[#7]=*", 0);                                                // N=A
        patterns.emplace_back("[!#6;R]", 1);                                               // Heterocyclic atom > 1 (&...) FIX: incomplete definition
        patterns.emplace_back("[#7;R]", 0);                                                // N Heterocycle
        patterns.emplace_back("[#7](~*)(~*)~*", 0);                                        // AN(A)A
        patterns.emplace_back("[#8]~[#6]~[#8]", 0);                                        // OCO
        patterns.emplace_back("[!#6;!#1]~[!#6;!#1]", 0);                                   // QQ
        patterns.emplace_back(nullptr, 1);                                                 // Aromatic rings > 1, checked by dedicated code 
        patterns.emplace_back("[#8](!@*)!@*", 0);                                          // A!O!A
        patterns.emplace_back("[#8]!@[R]@*", 1);                                           // A$A!O > 1 (&...) FIX: incomplete definition
        patterns.emplace_back("[#6H2](~*~*~*~[#6H2]~*)~*", 0);                             // ACH2AAACH2A
        patterns.emplace_back("[#6H2](~*~*~[#6H2]~*)~*", 0);                               // ACH2AACH2A
        patterns.emplace_back("[!#6;!#1]~[!#6;!#1]", 1);                                   // QQ > 1 (&...)  FIX: incomplete definition
        patterns.emplace_back("[!#6;!#1;!H0]", 1);                                         // QH > 1
        patterns.emplace_back("[#8]~*~[CH2]~*", 0);                                        // OACH2A
        patterns.emplace_back("[#7]!@*@*", 0);                                             // A$A!N
        patterns.emplace_back("[F,Cl,Br,I]", 0);                                           // X (HALOGEN)
        patterns.emplace_back("[#7]!:*:*", 0);                                             // Nnot%A%A
        patterns.emplace_back("[#8]=*", 1);                                                // O=A > 1
        patterns.emplace_back("[!C;!c;R]", 0);                                             // Heterocycle
        patterns.emplace_back("[!#6;!#1]~[CH2]~*", 1);                                     // QCH2A > 1 (&...) FIX: incomplete definition
        patterns.emplace_back("[O;!H0]", 0);                                               // OH
        patterns.emplace_back("[#8]", 3);                                                  // O > 3 (&...) FIX: incomplete definition
        patterns.emplace_back("[CH3]", 2);                                                 // CH3 > 2  (&...) FIX: incomplete definition
        patterns.emplace_back("[#7]", 1);                                                  // N > 1
        patterns.emplace_back("[#8]!@[R]@*", 0);                                           // A$A!O
        patterns.emplace_back("a(!:*):a!:*", 0);                                           // Anot%A%Anot%A
        patterns.emplace_back("[R]1@*@*@*@*@*@1", 1);                                      // 6M ring > 1
        patterns.emplace_back("[#8]", 2);                                                  // O > 2
        patterns.emplace_back("[#6H2](~[#6H2]~*)~*", 0);                                   // ACH2CH2A
        patterns.emplace_back("[!#6;!#1](~*)(~*)~*", 0);                                   // AQ(A)A
        patterns.emplace_back("[C;H3,H4]", 1);                                             // CH3 > 1
        patterns.emplace_back("[R](!@*)@[R]!@*", 0);                                       // A!A$A!A
        patterns.emplace_back("[#7;!H0]", 0);                                              // NH
        patterns.emplace_back("[#8]~[#6](~[#6])~[#6]", 0);                                 // OC(C)C
        patterns.emplace_back("[!#6;!#1]~[CH2]~*", 0);                                     // QCH2A
        patterns.emplace_back("[#6]=[#8]", 0);                                             // C=O
        patterns.emplace_back("[CH2](!@*)!@*", 0);                                         // A!CH2!A
        patterns.emplace_back("[#7]~*(~*)~*", 0);                                          // NA(A)A
        patterns.emplace_back("[#6]-[#8]", 0);                                             // C-O
        patterns.emplace_back("[#6]-[#7]", 0);                                             // C-N
        patterns.emplace_back("[#8]", 1);                                                  // O > 1
        patterns.emplace_back("[C;H3,H4]", 0);                                             // CH3
        patterns.emplace_back("[#7]", 0);                                                  // N
        patterns.emplace_back("a", 0);                                                     // Aromatic
        patterns.emplace_back("[R]1@*@*@*@*@*@1", 0);                                      // 6M Ring
        patterns.emplace_back("[#8]", 0);                                                  // O
        patterns.emplace_back("[R]", 0);                                                   // Ring
        patterns.emplace_back("(*).(*)", 0);                                               // Fragments
    }
}


Descr::MACCSFingerprintGenerator::MACCSFingerprintGenerator()
{
    subSearch.uniqueMappingsOnly(true);
}

Descr::MACCSFingerprintGenerator::MACCSFingerprintGenerator(const MACCSFingerprintGenerator& gen):
    MACCSFingerprintGenerator()
{}

Descr::MACCSFingerprintGenerator::MACCSFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp):
    MACCSFingerprintGenerator()
{
    generate(molgraph, fp);
}

void Descr::MACCSFingerprintGenerator::generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp)
{
    std::call_once(initFlag, &init);
  
    fp.resize(NUM_BITS);
    fp.reset();

    for (std::size_t i = 0; i < NUM_BITS; i++) {
        if (!patterns[i].pattern) {
            aromSSSRSubset.extract(molgraph);
            fp.set(i, aromSSSRSubset.getSize() > patterns[i].countThresh);
            continue;
        }

        subSearch.setQuery(*patterns[i].pattern);
        subSearch.setMaxNumMappings(patterns[i].countThresh + 1);
        
        if (patterns[i].countThresh == 0)
            fp.set(i, subSearch.mappingExists(molgraph));
            
        else {
            subSearch.findMappings(molgraph);
            fp.set(i, subSearch.getNumMappings() > patterns[i].countThresh);
        }
    }
}
