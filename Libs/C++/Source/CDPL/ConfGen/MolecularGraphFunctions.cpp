/* 
 * MolecularGraphFunctions.cpp 
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
#include <utility>
#include <vector>

#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/BondFunctions.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/CommonConnectedSubstructureSearch.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"


using namespace CDPL; 


namespace
{
    
    std::size_t getNumMappedBonds(const Chem::Atom& ctr_atom, const Chem::BondMapping& bond_mpg)
    {
        std::size_t num_mpd_bonds = 0;

        for (auto& bond : ctr_atom.getBonds())
            if (bond_mpg[&bond])
                num_mpd_bonds++;

        return num_mpd_bonds;
    }

    unsigned int getAtomConfigForOrder(unsigned int config, const Chem::StereoDescriptor& descr,
                                       const Chem::Atom** atoms)
    {
        using namespace Chem;

        switch (!atoms[3] ?
                descr.getPermutationParity(*atoms[0], *atoms[1], *atoms[2]) :
                descr.getPermutationParity(*atoms[0], *atoms[1], *atoms[2], *atoms[3])) {

            case 1:
                return (config == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R);

            case 2:
                return config;

            default:
                return AtomConfiguration::UNDEF;
        }
    }

    const Chem::Atom* getNbrAtomWithMapping(const Chem::Atom& atom, const Chem::Bond& excl_bond,
                                            const Chem::BondMapping& bond_mpg)
    {
        using namespace Chem;

        for (auto& bond : atom.getBonds())
            if ((&bond != &excl_bond) && bond_mpg[&bond])
                return &bond.getNeighbor(atom);

        return 0;
    }
    
    std::size_t calcFixedSubstructMatchScore(const Chem::MolecularGraph& molgraph, const Chem::AtomBondMapping& mpg,
                                             bool regard_config)
    {
        using namespace Chem;

        auto& bond_mpg = mpg.getBondMapping();
        
        if (bond_mpg.getSize() == 0)
            return 0;
       
        std::size_t score = bond_mpg.getSize() * (molgraph.getNumAtoms() + molgraph.getNumBonds());

        if (!regard_config)
            return score;
        
        auto& atom_mpg = mpg.getAtomMapping();

        for (auto& ap : atom_mpg) {
            auto& atom2_sto_descr = getStereoDescriptor(*ap.second);
            
            if (atom2_sto_descr.getNumReferenceAtoms() < 3) {
                score++;
                continue;
            }
            
            auto atom2_config = atom2_sto_descr.getConfiguration();

            if (atom2_config != AtomConfiguration::R && atom2_config != AtomConfiguration::S) {
                score++;
                continue;
            }

            if (getNumMappedBonds(*ap.first, bond_mpg) <= 2) {
                score++;
                continue;
            }
            
            auto& atom1_sto_descr = getStereoDescriptor(*ap.first);
            auto num_ref_atoms = atom1_sto_descr.getNumReferenceAtoms();
            
            if (num_ref_atoms < 3)
                continue;
            
            auto atom1_config = atom1_sto_descr.getConfiguration();

            if (atom1_config != AtomConfiguration::R && atom1_config != AtomConfiguration::S)
                continue;
            
            auto ref_atoms = atom1_sto_descr.getReferenceAtoms();
            const Atom* mpd_ref_atoms1[4] = { 0 };
            const Atom* mpd_ref_atoms2[4] = { 0 };
            std::size_t num_mpd_ref_atoms = 0;
            
            for (std::size_t i = 0 ; i < num_ref_atoms; i++) {
                auto mpd_ref_atom = atom_mpg[ref_atoms[i]];

                if (!mpd_ref_atom)
                    continue;

                if (!bond_mpg[ap.first->findBondToAtom(*ref_atoms[i])])
                    continue;
    
                mpd_ref_atoms1[num_mpd_ref_atoms] = ref_atoms[i];
                mpd_ref_atoms2[num_mpd_ref_atoms++] = mpd_ref_atom;
            }

            if (num_mpd_ref_atoms <= 2)
                continue;

            atom1_config = getAtomConfigForOrder(atom1_config, atom1_sto_descr, mpd_ref_atoms1);

            if (atom1_config == AtomConfiguration::UNDEF)
                continue;

            atom2_config = getAtomConfigForOrder(atom2_config, atom2_sto_descr, mpd_ref_atoms2);

            if (atom2_config == AtomConfiguration::UNDEF)
                continue;

            if (atom1_config == atom2_config)
                score++;
        }

        for (auto& bp : bond_mpg) {
            auto& bond2_sto_descr = getStereoDescriptor(*bp.second);
            
            if (bond2_sto_descr.getNumReferenceAtoms() != 4) {
                score++;
                continue;
            }
            
            auto bond2_config = bond2_sto_descr.getConfiguration();

            if (bond2_config != BondConfiguration::CIS && bond2_config != BondConfiguration::TRANS) {
                score++;
                continue;
            }

            if (getNumMappedBonds(bp.first->getBegin(), bond_mpg) < 2 || getNumMappedBonds(bp.first->getEnd(), bond_mpg) < 2) {
                score++;
                continue;
            }
            
            auto& bond1_sto_descr = getStereoDescriptor(*bp.first);
        
            if (bond1_sto_descr.getNumReferenceAtoms() != 4)
                continue;
       
            auto bond1_config = bond1_sto_descr.getConfiguration();

            if (bond1_config != BondConfiguration::CIS && bond1_config != BondConfiguration::TRANS)
                continue;

            auto ref_atoms1 = bond1_sto_descr.getReferenceAtoms();
            auto nbr_atom_with_mpg1 = getNbrAtomWithMapping(*ref_atoms1[1], *bp.first, bond_mpg);

            if (!nbr_atom_with_mpg1) // should not happen
                continue;

            auto nbr_atom_with_mpg2 = getNbrAtomWithMapping(*ref_atoms1[2], *bp.first, bond_mpg);

            if (!nbr_atom_with_mpg2) // should not happen
                continue;

            if ((nbr_atom_with_mpg1 != ref_atoms1[0]) ^ (nbr_atom_with_mpg2 != ref_atoms1[3]))
                bond1_config = (bond1_config == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);

            auto ref_atoms2 = bond2_sto_descr.getReferenceAtoms();

            if (atom_mpg[ref_atoms1[1]] != ref_atoms2[1])
                std::swap(nbr_atom_with_mpg1, nbr_atom_with_mpg2);
            
            if ((atom_mpg[nbr_atom_with_mpg1] != ref_atoms2[0]) ^ (atom_mpg[nbr_atom_with_mpg2] != ref_atoms2[3]))
                bond2_config = (bond2_config == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);

            if (bond1_config == bond2_config)
                score++;
        }
        
        return score;
    }
    
    bool extendFixedSubstruct(const Chem::AtomBondMapping& mpg, Chem::MolecularGraph& molgraph,
                              Chem::Fragment& fixed_substr, Math::Vector3DArray* fixed_substr_coords)
    {
        using namespace Chem;     

        auto& atom_mpg = mpg.getAtomMapping();
   
        for (auto& ap : atom_mpg)
            if (fixed_substr.containsAtom(*ap.second))
                return false;
        
        auto& bond_mpg = mpg.getBondMapping();
        
        for (auto& ap : atom_mpg) {
            fixed_substr.addAtom(*ap.second);

            if (fixed_substr_coords)
                (*fixed_substr_coords)[molgraph.getAtomIndex(*ap.second)] = get3DCoordinates(*ap.first);
            else
                continue;

            if (getNumMappedBonds(*ap.first, bond_mpg) <= 2)
                continue;

            auto& sto_descr = getStereoDescriptor(*ap.first);
            auto num_ref_atoms = sto_descr.getNumReferenceAtoms();
            
            if (num_ref_atoms < 3) {
                clearStereoDescriptor(molgraph.getAtom(molgraph.getAtomIndex(*ap.second)));
                continue;
            }
            
            auto config = sto_descr.getConfiguration();

            if (config != AtomConfiguration::R && config != AtomConfiguration::S) {
                clearStereoDescriptor(molgraph.getAtom(molgraph.getAtomIndex(*ap.second)));
                continue;
            }

            auto ref_atoms = sto_descr.getReferenceAtoms();
            const Atom* mpd_ref_atoms1[4] = { 0 };
            const Atom* mpd_ref_atoms2[4] = { 0 };
            std::size_t num_mpd_ref_atoms = 0;
            
            for (std::size_t i = 0 ; i < num_ref_atoms; i++) {
                auto mpd_ref_atom = atom_mpg[ref_atoms[i]];

                if (!mpd_ref_atom)
                    continue;

                if (!bond_mpg[ap.first->findBondToAtom(*ref_atoms[i])])
                    continue;
                
                mpd_ref_atoms1[num_mpd_ref_atoms] = ref_atoms[i];
                mpd_ref_atoms2[num_mpd_ref_atoms++] = mpd_ref_atom;
            }

            if (num_mpd_ref_atoms <= 2) {
                clearStereoDescriptor(molgraph.getAtom(molgraph.getAtomIndex(*ap.second)));
                continue;
            }

            config = getAtomConfigForOrder(config, sto_descr, mpd_ref_atoms1);

            if (config == AtomConfiguration::UNDEF) {
                clearStereoDescriptor(molgraph.getAtom(molgraph.getAtomIndex(*ap.second)));
                continue;
            }

            setStereoDescriptor(molgraph.getAtom(molgraph.getAtomIndex(*ap.second)),
                                num_mpd_ref_atoms == 3 ?
                                StereoDescriptor(config, *mpd_ref_atoms2[0], *mpd_ref_atoms2[1], *mpd_ref_atoms2[2]) :
                                StereoDescriptor(config, *mpd_ref_atoms2[0], *mpd_ref_atoms2[1], *mpd_ref_atoms2[2], *mpd_ref_atoms2[3]));
        }
        
        for (auto& bp : bond_mpg) {
            fixed_substr.addBond(*bp.second);

            if (!fixed_substr_coords)
                continue;

            if (getNumMappedBonds(bp.first->getBegin(), bond_mpg) < 2 || getNumMappedBonds(bp.first->getEnd(), bond_mpg) < 2)
                continue;
            
            auto& sto_descr = getStereoDescriptor(*bp.first);
        
            if (sto_descr.getNumReferenceAtoms() != 4) {
                clearStereoDescriptor(molgraph.getBond(molgraph.getBondIndex(*bp.second)));
                continue;
            }
       
            auto config = sto_descr.getConfiguration();

            if (config != BondConfiguration::CIS && config != BondConfiguration::TRANS) {
                clearStereoDescriptor(molgraph.getBond(molgraph.getBondIndex(*bp.second)));
                continue;
            }

            auto ref_atoms = sto_descr.getReferenceAtoms();
            auto nbr_atom_with_mpg1 = getNbrAtomWithMapping(*ref_atoms[1], *bp.first, bond_mpg);
            auto nbr_atom_with_mpg2 = getNbrAtomWithMapping(*ref_atoms[2], *bp.first, bond_mpg);

            if (!nbr_atom_with_mpg1 || !nbr_atom_with_mpg2) { // should not happen
                clearStereoDescriptor(molgraph.getBond(molgraph.getBondIndex(*bp.second)));
                continue;
            }

            if ((nbr_atom_with_mpg1 != ref_atoms[0]) ^ (nbr_atom_with_mpg2 != ref_atoms[3]))
                config = (config == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);

            setStereoDescriptor(molgraph.getBond(molgraph.getBondIndex(*bp.second)),
                                StereoDescriptor(config, *atom_mpg[nbr_atom_with_mpg1], *atom_mpg[ref_atoms[1]],
                                                 *atom_mpg[ref_atoms[2]], *atom_mpg[nbr_atom_with_mpg2]));    
        }
              
        return true;
    }
    
    template <typename SearchAlgo>
    std::size_t setupFixedSubstructData(SearchAlgo& algo, std::size_t max_num_matches, Chem::MolecularGraph& molgraph,
                                        Chem::Fragment& fixed_substr, Math::Vector3DArray* fixed_substr_coords)
    {
        fixed_substr.clear();
        
        if (fixed_substr_coords)
            fixed_substr_coords->resize(molgraph.getNumAtoms());

        typedef std::pair<std::size_t, std::size_t> ScoreIndexPair;

        std::vector<ScoreIndexPair> ranked_matches;
         
        for (std::size_t i = 0, num_mpgs = algo.getNumMappings(); i < num_mpgs; i++)
            ranked_matches.emplace_back(calcFixedSubstructMatchScore(molgraph, algo.getMapping(i), fixed_substr_coords), i);

        std::sort(ranked_matches.begin(), ranked_matches.end(),
                  [](const ScoreIndexPair& m1, const ScoreIndexPair& m2) -> bool {
                      return (m1.first > m2.first);
                  });
        
        std::size_t num_matches = 0;

        for (auto& match : ranked_matches)
            if (extendFixedSubstruct(algo.getMapping(match.second), molgraph, fixed_substr, fixed_substr_coords)) {
                num_matches++;

                if (max_num_matches > 0 && num_matches >= max_num_matches)
                    break;
            }

        return num_matches;
    }
}


std::size_t ConfGen::createFragmentLinkBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, bool reset)
{
    using namespace Chem;

    std::size_t num_bonds = molgraph.getNumBonds();
    std::size_t num_lnk_bonds = 0;

    if (bond_mask.size() < num_bonds)
        bond_mask.resize(num_bonds);

    if (reset)
        bond_mask.reset();

    for (std::size_t i = 0; i < num_bonds; i++) {
        if (isFragmentLinkBond(molgraph.getBond(i), molgraph)) {
            bond_mask.set(i);
            num_lnk_bonds++;
        }
    }

    return num_lnk_bonds;
}

std::size_t ConfGen::createRotatableBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, 
                                            bool het_h_rotors, bool reset)
{
    using namespace Chem;

    std::size_t num_bonds = molgraph.getNumBonds();
    std::size_t num_rot_bonds = 0;

    if (bond_mask.size() < num_bonds)
        bond_mask.resize(num_bonds);

    if (reset) 
        bond_mask.reset();
    
    for (std::size_t i = 0; i < num_bonds; i++) {
        if (isRotatableBond(molgraph.getBond(i), molgraph, het_h_rotors)) {
            bond_mask.set(i);
            num_rot_bonds++;
        }
    } 

    return num_rot_bonds;
}

std::size_t ConfGen::createRotatableBondMask(const Chem::MolecularGraph& molgraph, const Util::BitSet& excl_bond_mask, 
                                            Util::BitSet& bond_mask, bool het_h_rotors, bool reset)
{
    using namespace Chem;

    std::size_t num_bonds = molgraph.getNumBonds();
    std::size_t num_rot_bonds = 0;

    if (bond_mask.size() < num_bonds)
        bond_mask.resize(num_bonds);
    
    if (reset)
        bond_mask.reset();

    for (std::size_t i = 0; i < num_bonds; i++) {
        if (excl_bond_mask.test(i))
            continue;

        if (isRotatableBond(molgraph.getBond(i), molgraph, het_h_rotors)) {
            bond_mask.set(i);
            num_rot_bonds++;
        }
    } 

    return num_rot_bonds;
}

std::size_t ConfGen::getRotatableBondCount(const Chem::MolecularGraph& molgraph, bool het_h_rotors)
{
    using namespace Chem;

    std::size_t num_bonds = molgraph.getNumBonds();
    std::size_t num_rot_bonds = 0;

    for (std::size_t i = 0; i < num_bonds; i++) 
        if (isRotatableBond(molgraph.getBond(i), molgraph, het_h_rotors)) 
            num_rot_bonds++;

    return num_rot_bonds;
}

unsigned int ConfGen::perceiveFragmentType(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    bool has_rigid_ring_bonds = false;

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
        const Bond& bond = *it;

        if (getRingFlag(bond)) {
            if (getOrder(bond) > 1 || getAromaticityFlag(bond))
                has_rigid_ring_bonds = true;
            else
                return FragmentType::FLEXIBLE_RING_SYSTEM;
        }
    }

    if (has_rigid_ring_bonds)
        return FragmentType::RIGID_RING_SYSTEM;
    
    return FragmentType::CHAIN;
}

void ConfGen::setConformers(Chem::MolecularGraph& molgraph, const ConformerDataArray& conf_array)
{
    using namespace Chem;

    std::size_t num_confs = conf_array.size();

    if (num_confs == 0) {
        clearConformations(molgraph);
        clearConformerEnergies(molgraph);
        return;
    }

    Util::DArray::SharedPointer conf_energies(new Util::DArray());
    std::size_t num_atoms = molgraph.getNumAtoms();

    for (std::size_t i = 0; i < num_confs; i++) {
        const ConformerData& conf_data = *conf_array[i];

        for (std::size_t j = 0; j < num_atoms; j++) {
            Atom& atom = molgraph.getAtom(j);
            Math::Vector3DArray::SharedPointer coords_array;
            
            if (i == 0) {
                coords_array.reset(new Math::Vector3DArray());
                set3DCoordinatesArray(atom, coords_array);

            } else 
                coords_array = get3DCoordinatesArray(atom);

            coords_array->addElement(conf_data[j]);
        }
        
        conf_energies->addElement(conf_data.getEnergy());
    }

    setConformerEnergies(molgraph, conf_energies);
}

unsigned int ConfGen::parameterizeMMFF94Interactions(const Chem::MolecularGraph& molgraph, ForceField::MMFF94InteractionParameterizer& parameterizer,
                                                     ForceField::MMFF94InteractionData& param_data, unsigned int ff_type, bool strict, 
                                                     double estat_de_const, double estat_dist_expo)
{
    using namespace ForceField;

    unsigned int int_types = InteractionType::ALL;

    switch (ff_type) {

        case ForceFieldType::MMFF94:
            parameterizer.setParameterSet(MMFF94ParameterSet::DYNAMIC);
            break;

        case ForceFieldType::MMFF94S:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC);
            break;

        case ForceFieldType::MMFF94S_XOOP:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC_XOOP);
            break;

        case ForceFieldType::MMFF94S_RTOR:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC_RTOR);
            break;

        case ForceFieldType::MMFF94S_RTOR_XOOP:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC_RTOR_XOOP);
            break;

        case ForceFieldType::MMFF94_NO_ESTAT:
            parameterizer.setParameterSet(MMFF94ParameterSet::DYNAMIC);
            int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
            break;

        case ForceFieldType::MMFF94S_NO_ESTAT:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC);
            int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
            break;

        case ForceFieldType::MMFF94S_XOOP_NO_ESTAT:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC_XOOP);
            int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
            break;

        case ForceFieldType::MMFF94S_RTOR_NO_ESTAT:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC_RTOR);
            int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
            break;

        case ForceFieldType::MMFF94S_RTOR_XOOP_NO_ESTAT:
            parameterizer.setParameterSet(MMFF94ParameterSet::STATIC_RTOR_XOOP);
            int_types = InteractionType::ALL ^ InteractionType::ELECTROSTATIC;
            break;

        default:
            return ReturnCode::FORCEFIELD_SETUP_FAILED;
            
    }    

    param_data.clear();

    parameterizer.setDielectricConstant(estat_de_const);
    parameterizer.setDistanceExponent(estat_dist_expo);
    parameterizer.parameterize(molgraph, param_data, int_types, strict);

    return ReturnCode::SUCCESS;
} 

std::size_t ConfGen::setupFixedSubstructureData(const Chem::SubstructureSearch& sub_search, std::size_t max_num_matches, Chem::MolecularGraph& molgraph,
                                                Chem::Fragment& fixed_substr, Math::Vector3DArray* fixed_substr_coords)
{
    return setupFixedSubstructData(sub_search, max_num_matches, molgraph, fixed_substr, fixed_substr_coords);
}

std::size_t ConfGen::setupFixedSubstructureData(const Chem::CommonConnectedSubstructureSearch& sub_search, std::size_t max_num_matches, Chem::MolecularGraph& molgraph,
                                                Chem::Fragment& fixed_substr, Math::Vector3DArray* fixed_substr_coords)
{
    return setupFixedSubstructData(sub_search, max_num_matches, molgraph, fixed_substr, fixed_substr_coords);
}
