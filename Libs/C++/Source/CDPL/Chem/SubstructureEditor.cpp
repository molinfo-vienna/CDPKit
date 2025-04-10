/* 
 * SubstructureEditor.cpp 
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

#include <utility>

#include "CDPL/Chem/SubstructureEditor.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Chem/BondProperty.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    constexpr std::size_t MAX_BIT_SET_CACHE_SIZE = 500;
}


using namespace CDPL;


Chem::SubstructureEditor::SubstructureEditor():
    bitSetCache(MAX_BIT_SET_CACHE_SIZE)
{}

Chem::SubstructureEditor::SubstructureEditor(const SubstructureEditor& editor):
    bitSetCache(MAX_BIT_SET_CACHE_SIZE)
{
    for (auto &ptn : editor.searchPatterns)
        searchPatterns.emplace_back(ptn.molGraph);

    for (auto &ptn : editor.excludePatterns)
        excludePatterns.emplace_back(ptn.molGraph);
}

Chem::SubstructureEditor::~SubstructureEditor() {}

void Chem::SubstructureEditor::addSearchPattern(const MolecularGraph::SharedPointer& molgraph)
{
    searchPatterns.emplace_back(molgraph);
}

std::size_t Chem::SubstructureEditor::getNumSearchPatterns() const
{
    return searchPatterns.size();
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getSearchPattern(std::size_t idx) const
{
    if (idx >= searchPatterns.size())
        throw Base::IndexError("SubstructureEditor: search pattern index out of bounds");

    return searchPatterns[idx].molGraph;
}

void Chem::SubstructureEditor::removeSearchPattern(std::size_t idx)
{
    if (idx >= searchPatterns.size())
        throw Base::IndexError("SubstructureEditor: search pattern index out of bounds");

    searchPatterns.erase(searchPatterns.begin() + idx);
}

void Chem::SubstructureEditor::removeSearchPattern(const PatternIterator& it)
{
    const auto& base = it.base();

    if (base < searchPatterns.begin() || base >= searchPatterns.end())
        throw Base::RangeError("SubstructureEditor: search pattern iterator out of valid range");

    searchPatterns.erase(base);
}

void Chem::SubstructureEditor::clearSearchPatterns()
{
    searchPatterns.clear();
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getSearchPatternsBegin()
{
    return {searchPatterns.begin(), &getMolGraph};
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getSearchPatternsEnd()
{
    return {searchPatterns.end(), &getMolGraph};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getSearchPatternsBegin() const
{
    return {searchPatterns.begin(), &getMolGraph};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getSearchPatternsEnd() const
{
    return {searchPatterns.end(), &getMolGraph};
}

void Chem::SubstructureEditor::addExcludePattern(const MolecularGraph::SharedPointer& molgraph)
{
    excludePatterns.emplace_back(molgraph);
}

std::size_t Chem::SubstructureEditor::getNumExcludePatterns() const
{
    return excludePatterns.size();
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getExcludePattern(std::size_t idx) const
{
    if (idx >= excludePatterns.size())
        throw Base::IndexError("SubstructureEditor: exclude pattern index out of bounds");

    return excludePatterns[idx].molGraph;
}

void Chem::SubstructureEditor::removeExcludePattern(std::size_t idx)
{
    if (idx >= excludePatterns.size())
        throw Base::IndexError("SubstructureEditor: exclude pattern index out of bounds");

    excludePatterns.erase(excludePatterns.begin() + idx);
}

void Chem::SubstructureEditor::removeExcludePattern(const PatternIterator& it)
{
    const auto& base = it.base();

    if (base < excludePatterns.begin() || base >= excludePatterns.end())
        throw Base::RangeError("SubstructureEditor: exclude pattern iterator out of valid range");

    excludePatterns.erase(base);
}

void Chem::SubstructureEditor::clearExcludePatterns()
{
    excludePatterns.clear();
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getExcludePatternsBegin()
{
    return {excludePatterns.begin(), &getMolGraph};
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getExcludePatternsEnd()
{
    return {excludePatterns.end(), &getMolGraph};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getExcludePatternsBegin() const
{
    return {excludePatterns.begin(), &getMolGraph};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getExcludePatternsEnd() const
{
    return {excludePatterns.end(), &getMolGraph};
}

void Chem::SubstructureEditor::setResultPattern(const MolecularGraph::SharedPointer& molgraph)
{
    resultPattern = molgraph;
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getResultPattern() const
{
    return resultPattern;
}

std::size_t Chem::SubstructureEditor::edit(Molecule& mol)
{
    if (!resultPattern || searchPatterns.empty())
        return 0;

    initSubstructureSearchTarget(mol, false);
    
    std::size_t num_edits = 0;

    for (bool changes = true; changes; ) {
        Util::BitSet* mtd_substr_mask = nullptr;

        getExcludeMatches(mol);

        changes = false;
        
        for (auto& ptn : searchPatterns) {
            ptn.subSearch->findMappings(mol);

            for (auto& mpg : *ptn.subSearch) {
                if (!excludeMatches.empty()) {
                    if (!mtd_substr_mask)
                        mtd_substr_mask = bitSetCache.get();

                    createMatchedAtomAndBondMask(mol, mpg, *mtd_substr_mask, true, true);

                    auto excluded = false;
                
                    for (auto mask : excludeMatches)
                        if (mtd_substr_mask->is_subset_of(*mask)) {
                            excluded = true;
                            break;
                        }

                    if (excluded)
                        continue;
                }

                if (edit(mol, mpg.getAtomMapping())) {
                    num_edits++;
                    changes = true;
                    break;
                }
            }

            if (changes)
                break;
        }
    }
    
    return num_edits;
}

std::size_t Chem::SubstructureEditor::edit(const MolecularGraph& molgraph, Molecule& res_mol)
{
    res_mol.copy(molgraph);
    
    return edit(res_mol);
}

Chem::SubstructureEditor& Chem::SubstructureEditor::operator=(const SubstructureEditor& editor)
{
    if (this == &editor)
        return *this;

    searchPatterns.clear();

    for (auto &ptn : editor.searchPatterns)
        searchPatterns.emplace_back(ptn.molGraph);

    excludePatterns.clear();

    for (auto &ptn : editor.excludePatterns)
        excludePatterns.emplace_back(ptn.molGraph);
 
    return *this;
}

bool Chem::SubstructureEditor::edit(Molecule& mol, const AtomMapping& mapping)
{
    auto changes = false;
    auto clr_comps = false;
    auto update_arom = false;
    auto update_rings = false;
    auto& res_ptn = *resultPattern;
    auto num_res_ptn_atoms = res_ptn.getNumAtoms();

    if (resPtnAtomMapping.size() < num_res_ptn_atoms)
        resPtnAtomMapping.resize(num_res_ptn_atoms);

    hybStateUpdateAtoms.clear();
    configUpdateAtoms.clear();
    configUpdateBonds.clear();
    
    for (std::size_t i = 0; i < num_res_ptn_atoms; i++) {
        auto& res_ptn_atom = res_ptn.getAtom(i);
        auto id = getAtomMappingID(res_ptn_atom);
        Atom* mpd_atom = nullptr;
        
        if (id > 0)
            getMappedAtomForID(mapping, id);
        
        if ((id == 0) || !mpd_atom) {
            mpd_atom = &mol.addAtom();

            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::SYMBOL);
            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::NAME);
            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::FORMAL_CHARGE);
            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::TYPE);
            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::RADICAL_TYPE);
            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::ISOTOPE);
            copyProperty(res_ptn_atom, *mpd_atom, AtomProperty::UNPAIRED_ELECTRON_COUNT);

            configUpdateAtoms.insert(mpd_atom);
            
            resPtnAtomMapping[i] = mpd_atom;
            changes = true;
            clr_comps = true;
            continue;
        }

        if (hasType(res_ptn_atom) && (getType(res_ptn_atom) == 0)) {
            for (auto& atom : mpd_atom->getAtoms())
                configUpdateAtoms.insert(&atom);

            mol.removeAtom(mol.getAtomIndex(*mpd_atom));
            
            resPtnAtomMapping[i] = nullptr;
            changes = true;
            clr_comps = true;
            update_rings = true;
            update_arom = true;
            continue;
        }

        changes |= copyPropertyWithChangeCheck<std::string>(res_ptn_atom, *mpd_atom, AtomProperty::NAME);
        changes |= copyPropertyWithChangeCheck<unsigned int>(res_ptn_atom, *mpd_atom, AtomProperty::RADICAL_TYPE);
        changes |= copyPropertyWithChangeCheck<std::size_t>(res_ptn_atom, *mpd_atom, AtomProperty::ISOTOPE);

        if (copyPropertyWithChangeCheck<std::string>(res_ptn_atom, *mpd_atom, AtomProperty::SYMBOL) |
            copyPropertyWithChangeCheck<unsigned int>(res_ptn_atom, *mpd_atom, AtomProperty::TYPE) |
            copyPropertyWithChangeCheck<long>(res_ptn_atom, *mpd_atom, AtomProperty::FORMAL_CHARGE) |
            copyPropertyWithChangeCheck<std::size_t>(res_ptn_atom, *mpd_atom, AtomProperty::UNPAIRED_ELECTRON_COUNT)) {

            configUpdateAtoms.insert(mpd_atom);
            
            changes = true;
            update_arom = true;
        }

        resPtnAtomMapping[i] = mpd_atom;
    }

    for (auto& res_ptn_bond : res_ptn.getBonds()) {
        auto& res_atom1 = res_ptn_bond.getBegin();

        if (!res_ptn.containsAtom(res_atom1))
            continue;

        auto& res_atom2 = res_ptn_bond.getEnd();

        if (!res_ptn.containsAtom(res_atom2))
            continue;

        auto mpd_atom1 = resPtnAtomMapping[res_ptn.getAtomIndex(res_atom1)];

        if (!mpd_atom1)
            continue;
        
        auto mpd_atom2 = resPtnAtomMapping[res_ptn.getAtomIndex(res_atom2)];

        if (!mpd_atom2)
            continue;

        auto mpd_bond = mpd_atom1->findBondToAtom(*mpd_atom2);

        if (!mpd_bond) {
            mpd_bond = &mol.addBond(mol.getAtomIndex(*mpd_atom1), mol.getAtomIndex(*mpd_atom2));

            copyProperty(res_ptn_bond, *mpd_bond, BondProperty::ORDER);
            copyProperty(res_ptn_bond, *mpd_bond, BondProperty::STEREO_2D_FLAG);

            configUpdateBonds.insert(mpd_bond);
            configUpdateAtoms.insert(mpd_atom1);
            configUpdateAtoms.insert(mpd_atom2);

            changes = true;
            clr_comps = true;
            update_rings = true;
            update_arom = true;
            continue;
        }

        if (hasOrder(res_ptn_bond) && (getOrder(res_ptn_bond) == 0)) {
            mol.removeBond(mol.getBondIndex(*mpd_bond));

            configUpdateAtoms.insert(mpd_atom1);
            configUpdateAtoms.insert(mpd_atom2);
            
            changes = true;
            clr_comps = true;
            update_rings = true;
            update_arom = true;
            continue;
        }

        if (copyPropertyWithChangeCheck<std::size_t>(res_ptn_bond, *mpd_bond, BondProperty::ORDER)) {
            configUpdateBonds.insert(mpd_bond);
            configUpdateAtoms.insert(mpd_atom1);
            configUpdateAtoms.insert(mpd_atom2);
            
            changes = true;
            update_arom = true;
        }
    }

    if (clr_comps)
        clearComponents(mol);

    if (update_rings) {
        perceiveSSSR(mol, true);
        setRingFlags(mol, true);
    }

    for (auto atom : configUpdateAtoms) {
        setImplicitHydrogenCount(*atom, calcImplicitHydrogenCount(*atom, mol));
        setHybridizationState(*atom, perceiveHybridizationState(*atom, mol));
    }
    
    if (update_arom)
        setAromaticityFlags(mol, true);

    for (auto atom : configUpdateAtoms)
        setStereoDescriptor(*atom, calcStereoDescriptor(*atom, mol, 0));

    for (auto bond : configUpdateBonds)
        setStereoDescriptor(*bond, calcStereoDescriptor(*bond, mol, 0));
    
    changes |= editAtomStereoDescriptors(mol);
    changes |= editBondStereoDescriptors(mol);
 
    return changes;
}

bool Chem::SubstructureEditor::editAtomStereoDescriptors(Molecule& mol) const
{
    auto changes = false;
    auto& res_ptn = *resultPattern;
    
    for (std::size_t i = 0, num_res_ptn_atoms = res_ptn.getNumAtoms(); i < num_res_ptn_atoms; i++) {
        if (!resPtnAtomMapping[i])
            continue;
            
        auto& res_ptn_atom = res_ptn.getAtom(i);

        if (!hasStereoDescriptor(res_ptn_atom))
            continue;
        
        auto& res_stereo_desc = getStereoDescriptor(res_ptn_atom);
        auto res_config = res_stereo_desc.getConfiguration();
        
        if (res_config == AtomConfiguration::R || res_config == AtomConfiguration::S) {
            auto num_res_ref_atoms = res_stereo_desc.getNumReferenceAtoms();

            if (num_res_ref_atoms < 3 || num_res_ref_atoms > 4 || !res_stereo_desc.isValid(res_ptn_atom))
                continue;

            auto res_ref_atoms = res_stereo_desc.getReferenceAtoms();
            std::size_t num_mpd_ref_atoms = 0;
            const Atom* mpd_ref_atoms[4];
            const Atom* valid_res_ref_atoms[4];

            for (std::size_t j = 0; j < num_res_ref_atoms; j++) {
                auto mpd_atom = resPtnAtomMapping[res_ptn.getAtomIndex(*res_ref_atoms[j])];

                if (mpd_atom && mpd_atom->findBondToAtom(*resPtnAtomMapping[i])) {
                    mpd_ref_atoms[num_mpd_ref_atoms] = mpd_atom;
                    valid_res_ref_atoms[num_mpd_ref_atoms++] = res_ref_atoms[j];
                }
            }

            if (num_mpd_ref_atoms < 3)
                continue;

            if ((num_mpd_ref_atoms < num_res_ref_atoms) && 
                (res_stereo_desc.getPermutationParity(*valid_res_ref_atoms[0], *valid_res_ref_atoms[1], *valid_res_ref_atoms[2]) == 1))
                res_config = (res_config == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R);
            
            if (num_mpd_ref_atoms == 3)
                setStereoDescriptor(*resPtnAtomMapping[i],
                                    StereoDescriptor(res_config, *mpd_ref_atoms[0], *mpd_ref_atoms[1], *mpd_ref_atoms[2]));
            else
                setStereoDescriptor(*resPtnAtomMapping[i],
                                    StereoDescriptor(res_config, *mpd_ref_atoms[0], *mpd_ref_atoms[1], *mpd_ref_atoms[2], *mpd_ref_atoms[3]));
        } else {
            auto stereo_desc = getStereoDescriptor(*resPtnAtomMapping[i]);

            stereo_desc.setConfiguration(res_config);

            setStereoDescriptor(*resPtnAtomMapping[i], stereo_desc);
        }

        changes = true;
    }

    return changes;
}

bool Chem::SubstructureEditor::editBondStereoDescriptors(Molecule& mol) const
{
    auto changes = false;
    auto& res_ptn = *resultPattern;
    
    for (auto& res_ptn_bond : res_ptn.getBonds()) {
        if (!hasStereoDescriptor(res_ptn_bond))
            continue;
      
        auto& res_atom1 = res_ptn_bond.getBegin();

        if (!res_ptn.containsAtom(res_atom1))
            continue;

        auto& res_atom2 = res_ptn_bond.getEnd();

        if (!res_ptn.containsAtom(res_atom2))
            continue;

        auto mpd_atom1 = resPtnAtomMapping[res_ptn.getAtomIndex(res_atom1)];

        if (!mpd_atom1)
            continue;
        
        auto mpd_atom2 = resPtnAtomMapping[res_ptn.getAtomIndex(res_atom2)];

        if (!mpd_atom2)
            continue;

        auto mpd_bond = mpd_atom1->findBondToAtom(*mpd_atom2);

        if (!mpd_bond)
            continue;

        auto& res_stereo_desc = getStereoDescriptor(res_ptn_bond);
        auto res_config = res_stereo_desc.getConfiguration();
        
        if (res_config == BondConfiguration::CIS || res_config == BondConfiguration::TRANS) {
            if (!res_stereo_desc.isValid(res_ptn_bond))
                continue;

            auto res_ref_atoms = res_stereo_desc.getReferenceAtoms();

            if (res_ref_atoms[1] != &res_atom1)
                std::swap(mpd_atom1, mpd_atom2);

            auto mpd_ref_atom1 = resPtnAtomMapping[res_ptn.getAtomIndex(*res_ref_atoms[0])];

            if (!mpd_ref_atom1)
                continue;

            auto mpd_ref_atom2 = resPtnAtomMapping[res_ptn.getAtomIndex(*res_ref_atoms[3])];

            if (!mpd_ref_atom2)
                continue;

            if (!mpd_atom1->findBondToAtom(*mpd_ref_atom1))
                continue;

            if (!mpd_atom2->findBondToAtom(*mpd_ref_atom2))
                continue;

            setStereoDescriptor(*mpd_bond,
                                StereoDescriptor(res_config, *mpd_ref_atom1, *mpd_atom1, *mpd_atom2, *mpd_ref_atom2));
        } else {
            auto stereo_desc = getStereoDescriptor(*mpd_bond);

            stereo_desc.setConfiguration(res_config);

            setStereoDescriptor(*mpd_bond, stereo_desc);
        }

        changes = true;
    }
            
    return changes;
}

void Chem::SubstructureEditor::getExcludeMatches(const MolecularGraph& molgraph)
{
    excludeMatches.clear();
    bitSetCache.putAll();
    
    for (auto& ptn : excludePatterns) {
        ptn.subSearch->findMappings(molgraph);

        for (auto& mpg : *ptn.subSearch) {
            auto mask = bitSetCache.get();

            if (!createMatchedAtomAndBondMask(molgraph, mpg, *mask, true, true))
                createMatchedAtomAndBondMask(molgraph, mpg, *mask, false, false);

            excludeMatches.push_back(mask);
        }
    }
}

bool Chem::SubstructureEditor::createMatchedAtomAndBondMask(const MolecularGraph& molgraph, const AtomBondMapping& mapping,
                                                            Util::BitSet& mask, bool lbld_only, bool init) const
{
    auto num_atoms = molgraph.getNumAtoms();

    if (init) {
        mask.resize(num_atoms + molgraph.getNumAtoms());
        mask.reset();
    }

    auto any = false;
    
    for (auto [qa, ma] : mapping.getAtomMapping()) {
        if (lbld_only && (getAtomMappingID(*qa) == 0))
            continue;

        mask.set(molgraph.getAtomIndex(*ma));
        any = true;
    }

    if (!any)
        return false;

    for (auto [qb, mb] : mapping.getBondMapping()) {
        if (lbld_only && (!mask.test(molgraph.getAtomIndex(mb->getBegin())) ||
                          !mask.test(molgraph.getAtomIndex(mb->getEnd()))))
            continue;

        mask.set(num_atoms + molgraph.getBondIndex(*mb));
    }
  
    return true;
}

const Chem::Atom* Chem::SubstructureEditor::getMappedAtomForID(const AtomMapping& mapping, std::size_t id) const
{
    for (auto [qa, ma] : mapping)
        if (getAtomMappingID(*qa) == id)
            return ma;

    return nullptr;
}

template <typename T>
void Chem::SubstructureEditor::copyProperty(const T& src_cntnr, T& tgt_cntnr, const Base::LookupKey& key) const
{
    auto& prop_val = src_cntnr.getProperty(key, false);

    if (prop_val.isEmpty())
        return;

    tgt_cntnr.setProperty(key, prop_val);
}

template <typename VT, typename T>
bool Chem::SubstructureEditor::copyPropertyWithChangeCheck(const T& src_cntnr, T& tgt_cntnr, const Base::LookupKey& key) const
{
    auto& src_prop_val = src_cntnr.getProperty(key, false);

    if (src_prop_val.isEmpty())
        return false;

    auto& tgt_prop_val = tgt_cntnr.getProperty(key, false);

    if (!tgt_prop_val.isEmpty() && (tgt_prop_val.template getData<VT>() == src_prop_val.template getData<VT>()))
        return false;
    
    tgt_cntnr.setProperty(key, src_prop_val);
    return true;
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getMolGraph(const Pattern& ptn)
{
    return ptn.molGraph;
}
