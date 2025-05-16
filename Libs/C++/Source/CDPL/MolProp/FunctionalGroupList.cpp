/* 
 * FunctionalGroupList.cpp 
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

#include "CDPL/MolProp/FunctionalGroupList.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


MolProp::FunctionalGroupList::FunctionalGroupList():
    smilesWriter(strStream)
{}

MolProp::FunctionalGroupList::FunctionalGroupList(const FunctionalGroupList& fg_list):
    FragmentList(fg_list), smilesWriter(strStream)
{}

MolProp::FunctionalGroupList::FunctionalGroupList(const Chem::MolecularGraph& molgraph):
    smilesWriter(strStream)
{
    extract(molgraph);
}

MolProp::FunctionalGroupList& MolProp::FunctionalGroupList::operator=(FunctionalGroupList& fg_list)
{
    if (&fg_list == this)
        return *this;

    FragmentList::operator=(fg_list);
    
    return *this;
}

void MolProp::FunctionalGroupList::extract(const Chem::MolecularGraph& molgraph)
{
    init();
    markAtoms(molgraph);
    combineMarkedAtoms(molgraph);
}

void MolProp::FunctionalGroupList::init()
{
    using namespace Chem;

    if (funcGroupMolComps)
        return;

    setSMILESOutputCanonicalFormParameter(smilesWriter, true);
    setSMILESOutputAtomStereoParameter(smilesWriter, false);
    setSMILESOutputBondStereoParameter(smilesWriter, false);
    setSMILESOutputIsotopeParameter(smilesWriter, false);
    setSMILESMolOutputAtomMappingIDParameter(smilesWriter, false);
    setSMILESOutputAromaticBondsParameter(smilesWriter, false);
    setSMILESOutputSingleBondsParameter(smilesWriter, false);
    setSMILESOutputKekuleFormParameter(smilesWriter, false);
    setSMILESNoOrganicSubsetParameter(smilesWriter, false);
    setSMILESRecordFormatParameter(smilesWriter, "S");
    setOrdinaryHydrogenDepleteParameter(smilesWriter, false);

    funcGroupMolComps.reset(new FragmentList());
    funcGroupMolComps->addElement(Fragment::SharedPointer(new Fragment()));
}

void MolProp::FunctionalGroupList::markAtoms(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    auto num_atoms = molgraph.getNumAtoms();

    markedAtoms.resize(num_atoms);
    markedAtoms.reset();

    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = molgraph.getAtom(i);
        auto atom_type = getType(atom);

        if ((atom_type <= AtomType::H) || (atom_type > AtomType::MAX_ATOMIC_NO) || !AtomDictionary::isNonMetal(atom_type))
            continue;

        if (atom_type == AtomType::C) {
            if (getHybridizationState(atom) != HybridizationState::SP3)
                continue;
            
            std::size_t nos_nbr_cnt = 0;
            auto b_it = atom.getBondsBegin();

            for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
                auto& bond = *b_it;

                if (!molgraph.containsBond(bond))
                    continue;

                auto& nbr_atom = *a_it;

                if (!molgraph.containsAtom(nbr_atom))
                    continue;

                switch (getType(nbr_atom)) {

                    case AtomType::N:
                    case AtomType::O:
                    case AtomType::S:
                        if ((getOrder(bond) == 1) &&
                            (Internal::getExplicitBondCount(nbr_atom, molgraph, 1) == Internal::calcExplicitValence(nbr_atom, molgraph)))
                            nos_nbr_cnt++;
                }
            }

            if (nos_nbr_cnt < 2)
                continue;
        }

        markedAtoms.set(i);
    }

    auto sssr = getSSSR(molgraph);

    for (auto& ring : *sssr) {
        if (ring.getNumBonds() != 3)
            continue;

        if ((getOrder(ring.getBond(0)) != 1) || (getOrder(ring.getBond(1)) != 1) || (getOrder(ring.getBond(2)) != 1))
            continue;

        std::size_t c_cnt = 0;
        std::size_t nos_cnt = 0;

        for (std::size_t i = 0; (i < 3) && (nos_cnt <= 1) && (c_cnt <= 2); i++) {
            switch (getType(ring.getAtom(i))) {

                case AtomType::C:
                    c_cnt++;
                    continue;

                case AtomType::N:
                case AtomType::O:
                case AtomType::S:
                    nos_cnt++;
                    continue;

                default:
                    c_cnt = 3;
            }
        }

        if ((c_cnt != 2) || (nos_cnt != 1))
            continue;

        for (std::size_t i = 0; i < 3; i++)
            markedAtoms.set(molgraph.getAtomIndex(ring.getAtom(i)));
    }
    
    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();
        
        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;
        
        if (getAromaticityFlag(bond))
            continue;

        auto order = getOrder(bond);

        if ((order < 2) || (order > 3))
            continue;

        auto atom1_type = getType(atom1);
        auto atom2_type = getType(atom2);

        if ((atom1_type > AtomType::H) && (atom1_type <= AtomType::MAX_ATOMIC_NO) && AtomDictionary::isNonMetal(atom1_type) &&
            (atom2_type > AtomType::H) && (atom2_type <= AtomType::MAX_ATOMIC_NO) && AtomDictionary::isNonMetal(atom2_type)) {

            markedAtoms.set(molgraph.getAtomIndex(atom1));
            markedAtoms.set(molgraph.getAtomIndex(atom2));
        }
    }
}

void MolProp::FunctionalGroupList::combineMarkedAtoms(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    clear();

    for (Util::BitSet::size_type i = markedAtoms.find_first(); i != Util::BitSet::npos; i = markedAtoms.find_next(i)) {
        Fragment::SharedPointer fg_ptr(new Fragment());
        auto& atom = molgraph.getAtom(i);

        fg_ptr->addAtom(atom);
        markedAtoms.reset(i);
        
        combineMarkedAtoms(atom, molgraph, *fg_ptr);
        generateAndSetName(*fg_ptr, molgraph);
        addElement(fg_ptr);
    }
}

void MolProp::FunctionalGroupList::combineMarkedAtoms(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& func_grp)
{
    auto b_it = atom.getBondsBegin();

    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& bond = *b_it;

        if (!molgraph.containsBond(bond))
            continue;

        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;

        auto nbr_atom_idx = molgraph.getAtomIndex(nbr_atom);

        if (!markedAtoms.test(nbr_atom_idx)) {
            if (func_grp.containsAtom(nbr_atom))
                func_grp.addBond(bond);

            continue;
        }

        func_grp.addAtom(nbr_atom);
        markedAtoms.reset(nbr_atom_idx);
        
        combineMarkedAtoms(nbr_atom, molgraph, func_grp);
    }
}

void MolProp::FunctionalGroupList::generateAndSetName(Chem::Fragment& func_grp, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    funcGroupMol.clear();

    for (auto& atom : func_grp.getAtoms()) {
        auto& atom_copy = funcGroupMol.addAtom();
        auto atom_type = getType(atom);

        setType(atom_copy, atom_type);
        setFormalCharge(atom_copy, getFormalCharge(atom));
    }

    for (auto& bond : func_grp.getBonds()) {
        auto& bond_copy = funcGroupMol.addBond(func_grp.getAtomIndex(bond.getBegin()), func_grp.getAtomIndex(bond.getEnd()));

        setOrder(bond_copy, getOrder(bond));
        setAromaticityFlag(bond_copy, false);
    }

    chargeStandardizer.standardize(funcGroupMol, ProtonationStateStandardizer::MIN_CHARGED_ATOM_COUNT);

    for (std::size_t i = 0, num_atoms = func_grp.getNumAtoms(); i < num_atoms; i++) {
        auto& atom = func_grp.getAtom(i);
        auto atom_type = getType(atom);
        auto& atom_copy = funcGroupMol.getAtom(i);
        
        setImplicitHydrogenCount(atom_copy, 0);
        setAromaticityFlag(atom_copy, getAromaticityFlag(atom));

        switch (atom_type) {

            case AtomType::C:
                if (!Internal::isCarbonylLike(atom, func_grp, true, true))
                    continue;

                createEnvironmentBonds(i, getEnvironmentCarbons(atom, func_grp, molgraph), AtomType::R, false);
                continue;

            case AtomType::N:
            case AtomType::O:
                if (num_atoms == 1) {
                    if (getEnvironmentCarbons(atom, func_grp, molgraph) == 1)
                        createEnvironmentBonds(i, 1, AtomType::C, getAromaticityFlag(*envCarbons.front()));
                    else
                        createEnvironmentBonds(i, envCarbons.size(), AtomType::R, false);

                    createEnvironmentBonds(i, calcImplicitHydrogenCount(atom_copy, funcGroupMol), AtomType::H, false);
                    
                } else {
                    if (atom_type == AtomType::O) {
                        createEnvironmentBonds(i, getEnvironmentCarbons(atom, func_grp, molgraph), AtomType::R, false);
                        createEnvironmentBonds(i, calcImplicitHydrogenCount(atom_copy, funcGroupMol), AtomType::H, false);

                    } else {
                        createEnvironmentBonds(i, getEnvironmentCarbons(atom, func_grp, molgraph), AtomType::R, false);
                        createEnvironmentBonds(i, calcImplicitHydrogenCount(atom_copy, funcGroupMol), AtomType::R, false);
                    }
                }
                
                continue;
                    
            case AtomType::S:
                 if (num_atoms == 1) {
                     createEnvironmentBonds(i, getEnvironmentCarbons(atom, func_grp, molgraph), AtomType::R, false);
                     createEnvironmentBonds(i, calcImplicitHydrogenCount(atom_copy, funcGroupMol), AtomType::H, false);
                     continue;
                 }

            default:
                createEnvironmentBonds(i, getEnvironmentCarbons(atom, func_grp, molgraph), AtomType::R, false);
                createEnvironmentBonds(i, calcImplicitHydrogenCount(atom_copy, funcGroupMol), AtomType::R, false);
        }
    }
    
    setComponents(funcGroupMol, funcGroupMolComps);

    funcGroupMolComps->getElement(0) = funcGroupMol;
    strStream.str(std::string());

    if (!smilesWriter.write(funcGroupMol))
        throw Base::OperationFailed("FunctionalGroupList: could not generate functional group SMILES representation");
    
    setName(func_grp, strStream.str());
}

std::size_t MolProp::FunctionalGroupList::getEnvironmentCarbons(const Chem::Atom& atom, const Chem::Fragment& func_grp, const Chem::MolecularGraph& molgraph)
{
    envCarbons.clear();

    auto b_it = atom.getBondsBegin();

    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& bond = *b_it;

        if (!molgraph.containsBond(bond))
            continue;

        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;

        if (func_grp.containsAtom(nbr_atom))
            continue;

        if (getType(nbr_atom) == Chem::AtomType::C)
            envCarbons.push_back(&nbr_atom);
    }

    return envCarbons.size();
}

void MolProp::FunctionalGroupList::createEnvironmentBonds(std::size_t atom_idx, std::size_t num_bonds, unsigned int atom_type, bool aromatic)
{
    for (std::size_t i = 0; i < num_bonds; i++) {
        auto& atom = funcGroupMol.addAtom();

        setType(atom, atom_type);
        setAromaticityFlag(atom, aromatic);
        setImplicitHydrogenCount(atom, 0);

        auto& bond = funcGroupMol.addBond(atom_idx, funcGroupMol.getNumAtoms() - 1);

        setOrder(bond, 1);
        setAromaticityFlag(bond, false);
    }
}
