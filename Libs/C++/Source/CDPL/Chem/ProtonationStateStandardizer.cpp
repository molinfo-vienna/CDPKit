/* 
 * ProtonationStateStandardizer.cpp 
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

#include <algorithm>
#include <cmath>
#include <mutex>

#include "CDPL/Chem/ProtonationStateStandardizer.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL;


namespace
{

    struct ProtStateTransform
    {

        const char* substructSMARTS;
        long        protChanges[2 * 3 + 1];
    };

    const ProtStateTransform PROT_STATE_TRANSFORMS[] = {
      { "[Li,Na,K,Rb,Cs;X0+0:1]", { 1, 1, 1, 0 } },
      { "[Cu,Fe,Zn,Be,Mg,Ca,Sr,Ba;X0+0:1]", { 1, 1, 2, 0 } },
      { "[Bi;+0:1]", { 1, 1, 3, 0 } },
      { "[F,Cl,Br,I,At;H1+0:1]", { 1, 1, -1, -1 } },
      { "[O,S]=[S,C]-[O,S;+0X2H1:1]", { 1, 1, -1, -1 } },
      { "[O,S]=[PH1](-[+0])-[O,S;+0X2H1:1]", { 1, 1, -1, -1 } },
      { "[O,S]=[PH0](-[+0])(-[O,S;+0X2H1:1])-[O,S;+0X2H1:2]", { 2, 1, -1, -1, 2, -1, -1 } },
      { "[O,S]=[PH0](-[+0])(-[+0])-[O,S;+0X2H1:1]", { 1, 1, -1, -1 } },
      { "[N+0v3X3;H3,!$(*~[O,S,Se,P,#7,#6X3,+1]):1]", { 1, 1, 1, 1 } },
      { "[N+0v3X3;H2,!$(*~[O,S,Se,P,#6X3,+1]):1]-[N+0v3X3]", { 1, 1, 1, 1 } },
      { "[N+0v4X4:1]", { 1, 1, 1, 0 } },
      { "[N+0v3X2;H1,!$(*~[O,S,Se,P,#7,+1]):1]=[C;H2,!$(*~[O,S,Se,P,+1,#6X3])]", { 1, 1, 1, 1 } },
      { "[n+0v3X2H0:1]1[c;H1,!$(*~[#8,#16])]nc[c;H1,!$(*~[#8,#16])]1", { 1, 1, 1, 1 } }
    };

    Chem::Molecule::SharedPointer PROT_STATE_TRANSFORM_PATTERNS[sizeof(PROT_STATE_TRANSFORMS) / sizeof(ProtStateTransform)];
    
    std::once_flag initProtStateTransformsFlag;
    
    void initProtStateTransforms()
    {
        for (std::size_t i = 0; i < sizeof(PROT_STATE_TRANSFORMS) / sizeof(ProtStateTransform); i++)
            PROT_STATE_TRANSFORM_PATTERNS[i] = Chem::parseSMARTS(PROT_STATE_TRANSFORMS[i].substructSMARTS);
    }

    Chem::Molecule::SharedPointer POS_CHARGED_ATOM_PATTERN;
    Chem::Molecule::SharedPointer POS_CHARGED_NO_H_ATOM_PATTERN;
    Chem::Molecule::SharedPointer NEG_CHARGED_ATOM_PATTERN;
    Chem::Molecule::SharedPointer NEG_CHARGED_ACID_ATOM_PATTERN;

    std::once_flag initChargedAtomPatternsFlag;
    
    void initChargedAtomPatterns()
    {
        POS_CHARGED_ATOM_PATTERN = Chem::parseSMARTS("[+,+2,+3,+4;!h0;!$(*~[-]),$(*(~[-])~[-])]");
        POS_CHARGED_NO_H_ATOM_PATTERN = Chem::parseSMARTS("[+,+2,+3,+4;h0;!$(*~[-]),$(*(~[-])~[-])]");
        NEG_CHARGED_ATOM_PATTERN = Chem::parseSMARTS("[-!$(*~[+,+2,+3,+4])]");
        NEG_CHARGED_ACID_ATOM_PATTERN = Chem::parseSMARTS("[$([O,S;-][C,S;+0]=[O,S]),$([O,S;-][N,P;+](=[O,S])[O,S;-]),$([O-][Cl,Br,I;+,+2,+3][O-]),$([n-]1nnnc1),$([n-]1ncnn1)]");
    }

    // taken from the RDKit Atom.cpp source file
    const bool EARLY_ATOM_TABLE[] = {
      false,  // #0 *
      false,  // #1 H
      false,  // #2 He
      true,   // #3 Li
      true,   // #4 Be
      true,   // #5 B
      false,  // #6 C
      false,  // #7 N
      false,  // #8 O
      false,  // #9 F
      false,  // #10 Ne
      true,   // #11 Na
      true,   // #12 Mg
      true,   // #13 Al
      false,  // #14 Si
      false,  // #15 P
      false,  // #16 S
      false,  // #17 Cl
      false,  // #18 Ar
      true,   // #19 K
      true,   // #20 Ca
      true,   // #21 Sc
      true,   // #22 Ti
      false,  // #23 V
      false,  // #24 Cr
      false,  // #25 Mn
      false,  // #26 Fe
      false,  // #27 Co
      false,  // #28 Ni
      false,  // #29 Cu
      true,   // #30 Zn
      true,   // #31 Ga
      true,   // #32 Ge
      false,  // #33 As
      false,  // #34 Se
      false,  // #35 Br
      false,  // #36 Kr
      true,   // #37 Rb
      true,   // #38 Sr
      true,   // #39 Y
      true,   // #40 Zr
      true,   // #41 Nb
      false,  // #42 Mo
      false,  // #43 Tc
      false,  // #44 Ru
      false,  // #45 Rh
      false,  // #46 Pd
      false,  // #47 Ag
      true,   // #48 Cd
      true,   // #49 In
      true,   // #50 Sn
      true,   // #51 Sb
      false,  // #52 Te
      false,  // #53 I
      false,  // #54 Xe
      true,   // #55 Cs
      true,   // #56 Ba
      true,   // #57 La
      true,   // #58 Ce
      true,   // #59 Pr
      true,   // #60 Nd
      true,   // #61 Pm
      false,  // #62 Sm
      false,  // #63 Eu
      false,  // #64 Gd
      false,  // #65 Tb
      false,  // #66 Dy
      false,  // #67 Ho
      false,  // #68 Er
      false,  // #69 Tm
      false,  // #70 Yb
      false,  // #71 Lu
      true,   // #72 Hf
      true,   // #73 Ta
      false,  // #74 W
      false,  // #75 Re
      false,  // #76 Os
      false,  // #77 Ir
      false,  // #78 Pt
      false,  // #79 Au
      true,   // #80 Hg
      true,   // #81 Tl
      true,   // #82 Pb
      true,   // #83 Bi
      false,  // #84 Po
      false,  // #85 At
      false,  // #86 Rn
      true,   // #87 Fr
      true,   // #88 Ra
      true,   // #89 Ac
      true,   // #90 Th
      true,   // #91 Pa
      true,   // #92 U
      true,   // #93 Np
      false,  // #94 Pu
      false,  // #95 Am
      false,  // #96 Cm
      false,  // #97 Bk
      false,  // #98 Cf
      false,  // #99 Es
      false,  // #100 Fm
      false,  // #101 Md
      false,  // #102 No
      false,  // #103 Lr
      true,   // #104 Rf
      true,   // #105 Db
      true,   // #106 Sg
      true,   // #107 Bh
      true,   // #108 Hs
      true,   // #109 Mt
      true,   // #110 Ds
      true,   // #111 Rg
      true,   // #112 Cn
      true,   // #113 Nh
      true,   // #114 Fl
      true,   // #115 Mc
      true,   // #116 Lv
      true,   // #117 Ts
      true    // #118 Og
    };

    bool isEarlyAtom(unsigned int type)
    {
        return ((type < 119) && EARLY_ATOM_TABLE[type]);
    }
}


Chem::ProtonationStateStandardizer::ProtonationStateStandardizer()
{
    substructSearch.uniqueMappingsOnly(true);
}

Chem::ProtonationStateStandardizer::ProtonationStateStandardizer(const ProtonationStateStandardizer& standardizer)
{
    substructSearch.uniqueMappingsOnly(true);
}

bool Chem::ProtonationStateStandardizer::standardize(Molecule& mol, Flavor flavor)
{
    switch (flavor)    {

        case MIN_CHARGED_ATOM_COUNT:
            return minChargedAtomCount(mol);
            
        case PHYSIOLOGICAL_CONDITION_STATE:
            return protForPhysCond(mol);
            
        case MAX_CHARGE_COMPENSATION:
            return maxChargeComp(mol);
    }
    
    return false;
}

bool Chem::ProtonationStateStandardizer::standardize(const Molecule& mol, Molecule& std_mol, Flavor flavor)
{
    copyMolecule(mol, std_mol);
    
    return standardize(std_mol, flavor);
}

Chem::ProtonationStateStandardizer& Chem::ProtonationStateStandardizer::operator=(const ProtonationStateStandardizer& standardizer)
{
    return *this;
}
    
void Chem::ProtonationStateStandardizer::copyMolecule(const Molecule& mol, Molecule& mol_copy) const
{
    mol_copy.copy(mol);

    clearComponents(mol_copy);
}

bool Chem::ProtonationStateStandardizer::minChargedAtomCount(Molecule& mol)
{
    calcImplicitHydrogenCounts(mol, false);

    bool changes = false;
    std::size_t init_atom_cnt = mol.getNumAtoms();
    
    for (Molecule::BondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) {
        Bond& bond = *it;
        Atom& atom1 = bond.getBegin();
        Atom& atom2 = bond.getEnd();

        long charge1 = getFormalCharge(atom1);
        long charge2 = getFormalCharge(atom2);

        if ((charge1 <= 0 && charge2 <=0) || (charge1 >= 0 && charge2 >= 0))
            continue;
    
        long comp = std::min(std::abs(charge1), std::abs(charge2));
        long order = getOrder(bond);

        comp = std::min(3 - order, comp);
        comp = std::min(long(std::min(calcFreeValence(atom1), calcFreeValence(atom2))), comp);
    
        if (comp <= 0)
            continue;

        setOrder(bond, order + comp);

        if (charge1 < 0)
            setFormalCharge(atom1, charge1 + comp);
        else
            setFormalCharge(atom1, charge1 - comp);        

        if (charge2 < 0)
            setFormalCharge(atom2, charge2 + comp);
        else
            setFormalCharge(atom2, charge2 - comp);        

        changes = true;
    }
    
    atomList.clear();
    
    for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
        atomList.push_back(&*it);
        
    for (AtomList::const_iterator it = atomList.begin(), end = atomList.end(); it != end; ++it) {
        Atom& atom = **it;

        if (!mol.containsAtom(atom))
            continue;
        
        long net_charge = calcNetCharge(atom);

        if (net_charge == 0)
            continue;

        std::size_t val_xcs = calcValenceExcess(atom);

        if (val_xcs == 0) {
            setFormalCharge(atom, getFormalCharge(atom) - net_charge);
            changes = true;
            continue;
        }

        std::size_t num_rem_hs = 0;
    
        for (std::size_t i = 0; i < atom.getNumAtoms() && num_rem_hs < val_xcs; ) {
            const Atom& nbr_atom = atom.getAtom(i);

            if (!isRemovableHydrogen(nbr_atom)) {
                i++;
                continue;
            }

            mol.removeAtom(nbr_atom.getIndex());
            num_rem_hs++;
        }

        if (num_rem_hs == 0)
            continue;

        if (net_charge < 0)
            setFormalCharge(atom, getFormalCharge(atom) + num_rem_hs);
        else
            setFormalCharge(atom, getFormalCharge(atom) - num_rem_hs);

        changes = true;
    }

    if (!changes)
        return false;
    
    std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), static_cast<void (*)(Atom&)>(&clearAromaticityFlag));
    std::for_each(mol.getBondsBegin(), mol.getBondsEnd(), static_cast<void (*)(Bond&)>(&clearAromaticityFlag));
    std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), &clearHybridizationState);
    std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), &clearImplicitHydrogenCount);

    if (mol.getNumAtoms() != init_atom_cnt)
        clearComponents(mol);
    
    return true;
}

bool Chem::ProtonationStateStandardizer::protForPhysCond(Molecule& mol)
{
    std::call_once(initProtStateTransformsFlag, &initProtStateTransforms);

    bool changes = minChargedAtomCount(mol);
    std::size_t init_atom_cnt = mol.getNumAtoms();

    calcImplicitHydrogenCounts(mol, false);
    perceiveHybridizationStates(mol, false);
    perceiveSSSR(mol, false);
    setRingFlags(mol, false);
    setAromaticityFlags(mol, false);

    atomSet.clear();

    for (std::size_t i = 0; i < sizeof(PROT_STATE_TRANSFORMS) / sizeof(ProtStateTransform); i++) {
        const Molecule& ptn_mol = *PROT_STATE_TRANSFORM_PATTERNS[i];
    
        substructSearch.setQuery(ptn_mol);

        if (!substructSearch.findMappings(mol))
            continue;

        const long* prot_changes = PROT_STATE_TRANSFORMS[i].protChanges;
            
        for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(), end = substructSearch.getMappingsEnd(); it != end; ++it) {
            const AtomMapping& atom_mpg = it->getAtomMapping();

            for (std::size_t j = 1, prot_changes_end = std::size_t(prot_changes[0] * 3 + 1); j < prot_changes_end; j += 3) {
                Atom* atom = const_cast<Atom*>(atom_mpg[getAtomWithMappingID(ptn_mol, prot_changes[j])]);

                if (!atom)
                    continue;

                if (atomSet.find(atom) != atomSet.end())
                    continue;

                atomSet.insert(atom);

                setFormalCharge(*atom, prot_changes[j + 1]);
                adaptHydrogenCount(*atom, mol, prot_changes[j + 2]);
        
                changes = true;
            }
        }
    }

    if (!changes)
        return false;

    if (mol.getNumAtoms() != init_atom_cnt)
        clearComponents(mol);

    return true;
}

// Port of RDKit's Uncharger:uncharge() method
bool Chem::ProtonationStateStandardizer::maxChargeComp(Molecule& mol)
{
    using namespace std::placeholders;
    
    std::call_once(initChargedAtomPatternsFlag, &initChargedAtomPatterns);

    calcImplicitHydrogenCounts(mol, false);
    perceiveHybridizationStates(mol, false);
    perceiveSSSR(mol, false);
    perceiveHybridizationStates(mol, false);
    setAromaticityFlags(mol, false);

    std::size_t n_matched = getMatches(*NEG_CHARGED_ATOM_PATTERN, mol, negChargedAtoms);
    std::size_t a_matched = getMatches(*NEG_CHARGED_ACID_ATOM_PATTERN, mol, negChargedAcidAtoms);

    getMatches(*POS_CHARGED_ATOM_PATTERN, mol, posChargedAtoms);
    getMatches(*POS_CHARGED_NO_H_ATOM_PATTERN, mol, posChargedNoHAtoms);
    
    std::size_t q_matched = 0;

    for (AtomList::const_iterator it = posChargedNoHAtoms.begin(), end = posChargedNoHAtoms.end(); it != end; ++it)
        q_matched += getFormalCharge(**it);
    
    std::size_t num_neg_atoms = 0;

    for (Molecule::ConstAtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
        if (getFormalCharge(*it) < 0)
            num_neg_atoms++;

    bool changes = removeConnectedHydrogens(negChargedAtoms, mol);

    changes |= removeConnectedHydrogens(negChargedAcidAtoms, mol);
    changes |= removeConnectedHydrogens(posChargedAtoms, mol);

    perceiveComponents(mol, changes);
    calcImplicitHydrogenCounts(mol, changes);
    
    bool clr_arom = false;
    bool have_canon_num = false;
    
    // Neutralize negative charges
    if (q_matched > 0 && (n_matched > 0 || a_matched > 0)) {
        canonNumberingCalc.calculate(mol, canonAtomNumbering);

        have_canon_num = true;
        
        std::sort(negChargedAtoms.begin(), negChargedAtoms.end(),
                  std::bind(&ProtonationStateStandardizer::cmpCanonicalNumber, this, _1, _2));
        std::sort(negChargedAcidAtoms.begin(), negChargedAcidAtoms.end(),
                  std::bind(&ProtonationStateStandardizer::cmpCanonicalNumber, this, _1, _2));

        long neg_surplus = num_neg_atoms - q_matched;

        if (neg_surplus > 0 && n_matched > 0) { // zwitterion with more negative charges than quaternary positive centres
            atomMask.resize(mol.getNumAtoms());
            atomMask.reset();

            for (AtomList::const_iterator it = negChargedAcidAtoms.begin(), end = negChargedAcidAtoms.end(); it != end; ++it)
                atomMask.set((*it)->getIndex());
                
            for (AtomList::const_iterator it = negChargedAtoms.begin(), end = negChargedAtoms.end(); it != end; ++it) {
                Atom* atom = *it;

                if (atomMask.test(atom->getIndex()))
                    continue;
            
                if (incrementCharge(*atom, true)) {
                    if (getAromaticityFlag(*atom))
                        clr_arom = true;
                    
                    changes = true;
                        
                    if (--neg_surplus == 0)
                        break;
                }
            }
        }

        neg_surplus = a_matched - q_matched;
        
        if (neg_surplus > 0) {     // now do the other negative groups if we still have charges left:
            atomMask.resize(mol.getNumAtoms());
            atomMask.reset();

            for (AtomList::const_iterator it = negChargedAtoms.begin(), end = negChargedAtoms.end(); it != end; ++it) {
                Atom* atom = *it;

                for (Atom::ConstAtomIterator n_it = atom->getAtomsBegin(), n_end = atom->getAtomsEnd(); n_it != n_end; ++n_it) {
                    const Atom& nbr_atom = *n_it;
                
                    if (getFormalCharge(nbr_atom) > 0) {  // if the neighbor has a positive charge, neutralize only once (e.g., NO3-)
                        if (!atomMask.test(nbr_atom.getIndex()))
                            atomMask.set(nbr_atom.getIndex());
                        else
                            atomMask.set(atom->getIndex());

                        break;
                    }
                }
            }
            
            // zwitterion with more negative charges than quaternary positive centres
            for (AtomList::const_iterator it = negChargedAcidAtoms.begin(), end = negChargedAcidAtoms.end(); it != end; ++it) {
                Atom* atom = *it;
                
                if (getFormalCharge(*atom)  >= 0 || atomMask.test(atom->getIndex())) // skip ahead if we already neutralized this or if it is part of a zwitterion
                    continue;
                
                incrementCharge(*atom, false); // add hydrogen to first negative acidic atom, increase formal charge

                if (getAromaticityFlag(*atom))
                    clr_arom = true;

                changes = true;
                
                if (--neg_surplus == 0)        // until quaternary positive == negative total or no more negative atoms
                    break;
            }
        }

    } else {
        for (AtomList::const_iterator it = negChargedAtoms.begin(), end = negChargedAtoms.end(); it != end; ++it) {
            Atom* atom = *it;

            if (incrementCharge(*atom, true)) {
                if (getAromaticityFlag(*atom))
                    clr_arom = true;
                
                changes = true;
            }
        }
    }

    long net_charge = 0;

    for (Molecule::ConstAtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
        net_charge += getFormalCharge(*it);

    if (net_charge > 0) { // neutralize cations until there is no longer a net charge remaining
        if (!have_canon_num)
            canonNumberingCalc.calculate(mol, canonAtomNumbering);

        std::sort(posChargedAtoms.begin(), posChargedAtoms.end(),
                  std::bind(&ProtonationStateStandardizer::cmpCanonicalNumber, this, _1, _2));
        
        for (AtomList::const_iterator it = posChargedAtoms.begin(), end = posChargedAtoms.end(); it != end; ++it) {
            Atom* atom = *it;

            while (getFormalCharge(*atom) > 0 && net_charge > 0) {  // neutralize positive charges where H counts can be adjusted
                setFormalCharge(*atom, getFormalCharge(*atom) - 1);
                net_charge--;

                if (getAromaticityFlag(*atom))
                    clr_arom = true;

                changes = true;

                unsigned int atom_type = getType(*atom);
                std::size_t impl_h_cnt = getImplicitHydrogenCount(*atom);
                
                if (atom_type != AtomType::C && !isEarlyAtom(atom_type)) {
                    if (impl_h_cnt >= 1) {
                        setImplicitHydrogenCount(*atom, impl_h_cnt - 1);

                        if (impl_h_cnt == 1) // we just removed the last one
                            break;
                    }

                } else
                    setImplicitHydrogenCount(*atom, impl_h_cnt + 1);
            }

            if (net_charge == 0)
                break;
        }
    }
    
    if (!changes)
        return false;

    if (clr_arom) {
        std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), static_cast<void (*)(Atom&)>(&clearAromaticityFlag));
        std::for_each(mol.getBondsBegin(), mol.getBondsEnd(), static_cast<void (*)(Bond&)>(&clearAromaticityFlag));
    }

    std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), &clearHybridizationState);

    return true;
}

const Chem::Atom* Chem::ProtonationStateStandardizer::getAtomWithMappingID(const Molecule& ptn, std::size_t id) const
{
    for (Molecule::ConstAtomIterator it = ptn.getAtomsBegin(), end = ptn.getAtomsEnd(); it != end; ++it) {
        const Atom& atom = *it;

        if (getAtomMappingID(atom) == id)
            return &atom;
    }

    return 0;
}

std::size_t Chem::ProtonationStateStandardizer::adaptHydrogenCount(Atom& atom, Molecule& mol, long h_delta) const
{
    if (h_delta == 0)
        return 0;
    
    std::size_t impl_h_cnt = getImplicitHydrogenCount(atom);

    if (h_delta > 0) {
        setImplicitHydrogenCount(atom, impl_h_cnt + h_delta);
        return h_delta;
    }

    h_delta = -h_delta;
    
    if (impl_h_cnt >= std::size_t(h_delta)) {
        setImplicitHydrogenCount(atom, impl_h_cnt - h_delta);
        return h_delta;
    }

    std::size_t num_rem_hs = impl_h_cnt;

    setImplicitHydrogenCount(atom, 0);
    
    for (std::size_t i = 0; i < atom.getNumAtoms() && num_rem_hs < std::size_t(h_delta); ) {
        const Atom& nbr_atom = atom.getAtom(i);

        if (!isRemovableHydrogen(nbr_atom)) {
            i++;
            continue;
        }

        mol.removeAtom(nbr_atom.getIndex());
        num_rem_hs++;
    }
        
    return num_rem_hs;
}

std::size_t Chem::ProtonationStateStandardizer::calcFreeValence(const Atom& atom) const
{
    std::size_t heavy_val = 0;
    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) 
        if (getType(*a_it) != AtomType::H)
            heavy_val += getOrder(*b_it);
        
    const Util::STArray& val_states = AtomDictionary::getValenceStates(getType(atom));

    for (std::size_t i = 0, num_states = val_states.size(); i < num_states; i++)
        if (val_states[i] > heavy_val)
            return (val_states[i] - heavy_val);
        
    return 0;
}

long Chem::ProtonationStateStandardizer::calcNetCharge(const Atom& atom) const
{
    long net_charge = getFormalCharge(atom);

    if (net_charge == 0)
        return 0;

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end && net_charge != 0; ++a_it) {
        long nbr_charge = getFormalCharge(*a_it);

        if (net_charge > 0) {
            if (nbr_charge >= 0)
                continue;

            net_charge = std::max(net_charge + nbr_charge, long(0));

        } else {
            if (nbr_charge <= 0)
                continue;
                
            net_charge = std::min(net_charge + nbr_charge, long(0));
        }
    }

    return net_charge;
}

std::size_t Chem::ProtonationStateStandardizer::calcValenceExcess(const Atom& atom) const
{
    std::size_t exp_val = Internal::calcExplicitValence(atom, atom.getMolecule());
    const Util::STArray& val_states = AtomDictionary::getValenceStates(getType(atom));
    std::size_t max_val = 0;

    for (std::size_t i = 0, num_states = val_states.size(); i < num_states; i++)
        max_val = std::max(max_val, val_states[i]);

    if (max_val >= exp_val)
        return 0;

    return (exp_val - max_val);
}

std::size_t Chem::ProtonationStateStandardizer::getMatches(const Molecule& ptn, const Molecule& mol, AtomList& matches)
{
    matches.clear();
    substructSearch.setQuery(ptn);

    if (!substructSearch.findMappings(mol))
        return 0;

    for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(), end = substructSearch.getMappingsEnd(); it != end; ++it) {
        const AtomMapping& atom_mpg = it->getAtomMapping();

        for (AtomMapping::ConstEntryIterator e_it = atom_mpg.getEntriesBegin(), e_end = atom_mpg.getEntriesEnd(); e_it != e_end; ++e_it)
            matches.push_back(const_cast<Atom*>(e_it->second));
    }
    
    return matches.size();
}
        
bool Chem::ProtonationStateStandardizer::incrementCharge(Atom& atom, bool checked) const
{
    long h_delta = 1;
    std::size_t impl_h_cnt = getImplicitHydrogenCount(atom);
    
    if (checked && isEarlyAtom(getType(atom))) {
        if (impl_h_cnt == 0)
            return false;

        h_delta = -1;
    }

    setImplicitHydrogenCount(atom, impl_h_cnt + h_delta);
    setFormalCharge(atom, getFormalCharge(atom) + 1);
    
    return true;
}

bool Chem::ProtonationStateStandardizer::cmpCanonicalNumber(const Atom* atom1, const Atom* atom2) const
{
    return (canonAtomNumbering[atom1->getIndex()] < canonAtomNumbering[atom2->getIndex()]);
}

bool Chem::ProtonationStateStandardizer::isRemovableHydrogen(const Atom& atom) const
{
    if (atom.getNumBonds() != 1)
        return false;

    if (getType(atom) != AtomType::H)
        return false;

    if (getIsotope(atom) != 0)
        return false;

    if (getFormalCharge(atom) != 0)
        return false;

    const Atom& con_atom = atom.getAtom(0);
    unsigned int con_atom_type = getType(con_atom);

    if (con_atom_type > AtomType::MAX_ATOMIC_NO)
        return false;

    const Bond& bond = atom.getBond(0);

    switch (get2DStereoFlag(bond)) {

        case BondStereoFlag::UP:
        case BondStereoFlag::REVERSE_UP:
        case BondStereoFlag::DOWN:
        case BondStereoFlag::REVERSE_DOWN:
            if (con_atom.getNumBonds() == 3 || con_atom.getNumBonds() == 4)
                return false;

        default:
            break;
    }

    const StereoDescriptor& con_atom_sd = getStereoDescriptor(con_atom);

    if (con_atom_sd.isValid(con_atom) &&
        (con_atom_sd.getConfiguration() == AtomConfiguration::R || con_atom_sd.getConfiguration() == AtomConfiguration::S))
        return false;

    const Util::STArray& con_atom_std_vals = AtomDictionary::getValenceStates(con_atom_type);

    if (con_atom_std_vals.isEmpty())
        return false;

    std::size_t con_atom_val = Internal::calcValence(con_atom, atom.getMolecule());

    if (getFormalCharge(con_atom) == 1 && (con_atom_std_vals[0] + 1) == con_atom_val)
        return true;

    if (con_atom_val > con_atom_std_vals[0])
        return false;

    if (Internal::getRingBondCount(con_atom, atom.getMolecule()) >= 3)
        return false;

    return true;
}

bool Chem::ProtonationStateStandardizer::removeConnectedHydrogens(const AtomList& atoms, Molecule& mol) const
{
    bool changes = false;
    
    for (AtomList::const_iterator it = atoms.begin(), end = atoms.end(); it != end; ++it) {
        Atom& atom = **it;
        
        for (std::size_t i = 0; i < atom.getNumAtoms(); ) {
            const Atom& nbr_atom = atom.getAtom(i);

            if (!isRemovableHydrogen(nbr_atom)) {
                i++;
                continue;
            }

            mol.removeAtom(nbr_atom.getIndex());
            changes = true;
        }
    }

    return changes;
}
