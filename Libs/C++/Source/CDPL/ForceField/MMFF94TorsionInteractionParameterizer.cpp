/* 
 * MMFF94TorsionInteractionParameterizer.cpp 
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

#include <iterator>
#include <cstddef>
#include <cmath>
#include <algorithm>

#include "CDPL/ForceField/MMFF94TorsionInteractionParameterizer.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{
    
    double empRuleUParamTable[Chem::AtomType::MAX_TYPE + 1];
    double empRuleVParamTable[Chem::AtomType::MAX_TYPE + 1];

    double getEmpiricalRuleUParameter(unsigned int atomic_no)
    {
        if (atomic_no > Chem::AtomType::MAX_TYPE)
            return empRuleUParamTable[Chem::AtomType::C];

        return empRuleUParamTable[atomic_no];
    }

    double getEmpiricalRuleVParameter(unsigned int atomic_no)
    {
        if (atomic_no > Chem::AtomType::MAX_TYPE)
            return empRuleVParamTable[Chem::AtomType::C];

        return empRuleVParamTable[atomic_no];
    }

    struct Init
    {
        
        Init() {
            for (std::size_t i = 0; i < Chem::AtomType::MAX_TYPE + 1; i++)
                empRuleUParamTable[i] = 2.0;

            //empRuleUParamTable[Chem::AtomType::C]  = 2.0;
            empRuleUParamTable[Chem::AtomType::N]  = 2.0;
            empRuleUParamTable[Chem::AtomType::O]  = 2.0;
            empRuleUParamTable[Chem::AtomType::Si] = 1.25;
            empRuleUParamTable[Chem::AtomType::P]  = 1.25;
            empRuleUParamTable[Chem::AtomType::S]  = 1.25;

            for (std::size_t i = 0; i < Chem::AtomType::MAX_TYPE + 1; i++)
                empRuleVParamTable[i] = 2.12;

            //empRuleVParamTable[Chem::AtomType::C]  = 2.12;
            empRuleVParamTable[Chem::AtomType::N]  = 1.50;
            empRuleVParamTable[Chem::AtomType::O]  = 0.2;
            empRuleVParamTable[Chem::AtomType::Si] = 1.22;
            empRuleVParamTable[Chem::AtomType::P]  = 2.40;
            empRuleVParamTable[Chem::AtomType::S]  = 0.48; // The paper says 0.49 - but that value gives wrong results in empirical rule h2)!
        }

    } init;

    const unsigned int FALLBACK_ATOM_TYPE = 1;
}


ForceField::MMFF94TorsionInteractionParameterizer::MMFF94TorsionInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
                                                                                         MMFF94TorsionInteractionData& ia_data,
                                                                                         bool strict):
    filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), 
    aromRingSetFunc(&getMMFF94AromaticRings), paramTable(MMFF94TorsionParameterTable::get(true)),
    typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get())
{
    parameterize(molgraph, ia_data, strict);
}

ForceField::MMFF94TorsionInteractionParameterizer::MMFF94TorsionInteractionParameterizer():
    filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), 
    aromRingSetFunc(&getMMFF94AromaticRings), paramTable(MMFF94TorsionParameterTable::get(true)),
    typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get())
{}

void ForceField::MMFF94TorsionInteractionParameterizer::setFilterFunction(const InteractionFilterFunction4& func)
{
    filterFunc = func;
} 

void ForceField::MMFF94TorsionInteractionParameterizer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
    atomTypeFunc = func;
}  

void ForceField::MMFF94TorsionInteractionParameterizer::setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func)
{
    bondTypeIdxFunc = func;
}  

void ForceField::MMFF94TorsionInteractionParameterizer::setAromaticRingSetFunction(const MMFF94RingSetFunction& func)
{
    aromRingSetFunc = func;
}

void ForceField::MMFF94TorsionInteractionParameterizer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
    typePropTable = table;
}

void ForceField::MMFF94TorsionInteractionParameterizer::setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table)
{
    paramTable = table;
}

void ForceField::MMFF94TorsionInteractionParameterizer::setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map)
{
    paramTypeMap = map;
}

void ForceField::MMFF94TorsionInteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, 
                                                                     MMFF94TorsionInteractionData& ia_data, bool strict)
{
    using namespace Chem;

    ia_data.clear();

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
        const Bond& ctr_bond = *it;
        const Atom& ctr_atom1 = ctr_bond.getBegin();
        const Atom& ctr_atom2 = ctr_bond.getEnd();

        if (!molgraph.containsAtom(ctr_atom1) || !molgraph.containsAtom(ctr_atom2))  // sanity check
            continue;

        std::size_t ctr_atom1_idx = molgraph.getAtomIndex(ctr_atom1);
        unsigned int ctr_atom1_type = atomTypeFunc(ctr_atom1);

        if (!strict && ctr_atom1_type == 0)
            ctr_atom1_type = FALLBACK_ATOM_TYPE;

        const AtomTypePropEntry* ctr_atom1_prop_entry = &typePropTable->getEntry(ctr_atom1_type);

        if (!(*ctr_atom1_prop_entry) && !strict) {
            ctr_atom1_type = FALLBACK_ATOM_TYPE;
            ctr_atom1_prop_entry = &typePropTable->getEntry(ctr_atom1_type);
        } 

        if (!(*ctr_atom1_prop_entry)) 
            throw ParameterizationFailed("MMFF94TorsionInteractionParameterizer: could not find MMFF94 atom type properties for atom #" + 
                                         std::to_string(ctr_atom1_idx));

        if (ctr_atom1_prop_entry->formsLinearBondAngle()) // Empirical rule a)
            continue;

        std::size_t ctr_atom2_idx = molgraph.getAtomIndex(ctr_atom2);
        unsigned int ctr_atom2_type = atomTypeFunc(ctr_atom2);

        if (!strict && ctr_atom2_type == 0)
            ctr_atom2_type = FALLBACK_ATOM_TYPE;

        const AtomTypePropEntry* ctr_atom2_prop_entry = &typePropTable->getEntry(ctr_atom2_type);

        if (!(*ctr_atom2_prop_entry) && !strict) {
            ctr_atom2_type = FALLBACK_ATOM_TYPE;
            ctr_atom2_prop_entry = &typePropTable->getEntry(ctr_atom2_type);
        } 

        if (!(*ctr_atom2_prop_entry))
            throw ParameterizationFailed("MMFF94TorsionInteractionParameterizer: could not find MMFF94 atom type properties for atom #" + 
                                         std::to_string(ctr_atom2_idx));

        if (ctr_atom2_prop_entry->formsLinearBondAngle()) // Empirical rule a)
            continue;

        nbrAtoms1.clear();
        nbrBonds1.clear();

        getConnectedAtomsAndBonds(ctr_atom1, molgraph, std::back_inserter(nbrAtoms1), std::back_inserter(nbrBonds1));

        std::size_t num_nbrs1 = nbrAtoms1.size();

        if (num_nbrs1 <= 1)
            continue;

        nbrAtoms2.clear();
        nbrBonds2.clear();

        getConnectedAtomsAndBonds(ctr_atom2, molgraph, std::back_inserter(nbrAtoms2), std::back_inserter(nbrBonds2));

        std::size_t num_nbrs2 = nbrAtoms2.size();

        if (num_nbrs2 <= 1)
            continue;

        unsigned int ctr_bond_type_idx = bondTypeIdxFunc(ctr_bond);

        for (std::size_t i = 0; i < num_nbrs1; i++) {
            if (nbrAtoms1[i] == &ctr_atom2)
                continue;

            std::size_t term_atom1_idx = molgraph.getAtomIndex(*nbrAtoms1[i]);
            unsigned int term_atom1_type = atomTypeFunc(*nbrAtoms1[i]);
            unsigned int term_bond1_type_idx = bondTypeIdxFunc(*nbrBonds1[i]);

            if (!strict && term_atom1_type == 0)
                term_atom1_type = FALLBACK_ATOM_TYPE;

            for (std::size_t j = 0; j < num_nbrs2; j++) {
                if (nbrAtoms2[j] == &ctr_atom1)
                    continue;
                
                if (nbrAtoms1[i] == nbrAtoms2[j]) // 3-membered ring!
                    continue;

                std::size_t term_atom2_idx = molgraph.getAtomIndex(*nbrAtoms2[j]);
                unsigned int term_atom2_type = atomTypeFunc(*nbrAtoms2[j]);
                unsigned int term_bond2_type_idx = bondTypeIdxFunc(*nbrBonds2[j]);

                if (!strict && term_atom2_type == 0)
                    term_atom2_type = FALLBACK_ATOM_TYPE;

                unsigned int tor_type_idx = getTorsionTypeIndex(molgraph, *nbrAtoms1[i], ctr_atom1, ctr_atom2, *nbrAtoms2[j], ctr_bond,
                                                                term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type,
                                                                term_bond1_type_idx, ctr_bond_type_idx, term_bond2_type_idx);
                double tor_param1 = 0.0;
                double tor_param2 = 0.0;
                double tor_param3 = 0.0;
                            
                try {
                    if (!getParameters(molgraph, *nbrAtoms1[i], ctr_atom1, ctr_atom2, *nbrAtoms2[j], ctr_bond, term_atom1_type, ctr_atom1_type, 
                                       ctr_atom2_type, term_atom2_type, tor_type_idx, *ctr_atom1_prop_entry, *ctr_atom2_prop_entry, tor_param1,
                                       tor_param2, tor_param3))
                        continue;

                } catch (const ParameterizationFailed& e) {
                    if (strict) 
                        throw e;

                    if (!getParameters(molgraph, *nbrAtoms1[i], ctr_atom1, ctr_atom2, *nbrAtoms2[j], ctr_bond, FALLBACK_ATOM_TYPE, ctr_atom1_type, 
                                       ctr_atom2_type, FALLBACK_ATOM_TYPE, tor_type_idx, *ctr_atom1_prop_entry, *ctr_atom2_prop_entry, tor_param1,
                                       tor_param2, tor_param3))
                        continue;
                }

                ia_data.addElement(MMFF94TorsionInteraction(term_atom1_idx, ctr_atom1_idx, ctr_atom2_idx, term_atom2_idx, tor_type_idx,
                                                            tor_param1, tor_param2, tor_param3));
            }
        }
    }
}

bool ForceField::MMFF94TorsionInteractionParameterizer::getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1, 
                                                                      const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
                                                                      unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                                                                      unsigned int term_atom2_type, unsigned int tor_type_idx, const AtomTypePropEntry& ctr_atom1_prop_entry, 
                                                                      const AtomTypePropEntry& ctr_atom2_prop_entry, double& tor_param1, double& tor_param2,
                                                                      double& tor_param3) const
{
    using namespace Chem;

    typedef MMFF94TorsionParameterTable::Entry ParamEntry;

    const unsigned int* term_atom1_param_types = paramTypeMap->getEntry(term_atom1_type).getParameterTypes();

    if (!term_atom1_param_types)
        throw ParameterizationFailed("MMFF94TorsionInteractionParameterizer: could not find MMFF94 parameter atom type equivalence list for atom #" + 
                                     std::to_string(molgraph.getAtomIndex(term_atom1)));

    const unsigned int* term_atom2_param_types = paramTypeMap->getEntry(term_atom2_type).getParameterTypes();

    if (!term_atom2_param_types)
        throw ParameterizationFailed("MMFF94TorsionInteractionParameterizer: could not find MMFF94 parameter atom type equivalence list for atom #" + 
                                     std::to_string(molgraph.getAtomIndex(term_atom2)));

    const ParamEntry* param_entry = &paramTable->getEntry(tor_type_idx, term_atom1_param_types[0], ctr_atom1_type, ctr_atom2_type, term_atom2_param_types[0]);

    if (!(*param_entry)) {
        param_entry = &paramTable->getEntry(tor_type_idx, term_atom1_param_types[1], ctr_atom1_type, ctr_atom2_type, term_atom2_param_types[3]);

        if (!(*param_entry)) {
            param_entry = &paramTable->getEntry(tor_type_idx, term_atom1_param_types[3], ctr_atom1_type, ctr_atom2_type, term_atom2_param_types[1]);

            if (!(*param_entry)) {
                param_entry = &paramTable->getEntry(tor_type_idx, term_atom1_param_types[3], ctr_atom1_type, ctr_atom2_type, term_atom2_param_types[3]);
            }
        }
    }
    
    if (*param_entry) {
        tor_param1 = param_entry->getTorsionParameter1();
        tor_param2 = param_entry->getTorsionParameter2();
        tor_param3 = param_entry->getTorsionParameter3();

        return true;
    }

    // Empirical rule fallback

    unsigned int ctr_atomic_no1 = ctr_atom1_prop_entry.getAtomicNumber();
    unsigned int ctr_atomic_no2 = ctr_atom2_prop_entry.getAtomicNumber();

    if (ctr_atom1_prop_entry.isAromaticAtomType() && ctr_atom2_prop_entry.isAromaticAtomType() &&
        containsFragmentWithBond(*aromRingSetFunc(molgraph), ctr_bond)) {
        // Rule b)

        double pi_bnd_order = 0.3;

        if (!ctr_atom1_prop_entry.hasPiLonePair() && !ctr_atom2_prop_entry.hasPiLonePair())
            pi_bnd_order = 0.5;
            
        double beta = 6.0;

        if ((ctr_atom1_prop_entry.getValence() == 3 && ctr_atom2_prop_entry.getValence() == 4)
            || (ctr_atom1_prop_entry.getValence() == 4 && ctr_atom2_prop_entry.getValence() == 3))
            beta = 3.0;
        
        tor_param2 = beta * pi_bnd_order * std::sqrt(getEmpiricalRuleUParameter(ctr_atomic_no1) * getEmpiricalRuleUParameter(ctr_atomic_no2));
        return true;
    }
    
    unsigned int ctr_atom1_mb_desig = ctr_atom1_prop_entry.getMultiBondDesignator();
    unsigned int ctr_atom2_mb_desig = ctr_atom2_prop_entry.getMultiBondDesignator();

    if (getOrder(ctr_bond) == 2) { 
        // Rule c)

        double pi_bnd_order = 0.4;

        if (ctr_atom1_mb_desig == 2 && ctr_atom2_mb_desig == 2)
            pi_bnd_order = 1.0;
        
        tor_param2 = 6.0 * pi_bnd_order * std::sqrt(getEmpiricalRuleUParameter(ctr_atomic_no1) * getEmpiricalRuleUParameter(ctr_atomic_no2));
        return true;
    }

    if (ctr_atom1_prop_entry.getNumNeighbors() == 4 && ctr_atom2_prop_entry.getNumNeighbors() == 4) {
        // Rule d)

        tor_param3 = std::sqrt(getEmpiricalRuleVParameter(ctr_atomic_no1) * getEmpiricalRuleVParameter(ctr_atomic_no2)) / 9.0;
        return true;
    }

    if (ctr_atom1_prop_entry.getNumNeighbors() == 4 || ctr_atom2_prop_entry.getNumNeighbors() == 4) {
        // Rules e) and f)

        const AtomTypePropEntry& non_tetra_coord_ctr_atom_props = (ctr_atom1_prop_entry.getNumNeighbors() == 4 ? ctr_atom2_prop_entry : ctr_atom1_prop_entry);

        switch (non_tetra_coord_ctr_atom_props.getNumNeighbors()) {

            case 3:
                if (non_tetra_coord_ctr_atom_props.getValence() == 4 || non_tetra_coord_ctr_atom_props.getValence() == 34 ||
                    non_tetra_coord_ctr_atom_props.getMultiBondDesignator() != 0) 
                    return false;
                
                break;

            case 2:
                //if (non_tetra_coord_ctr_atom_props.getValence() == 3 || non_tetra_coord_ctr_atom_props.getMultiBondDesignator() != 0)
                //  return false;
    
            case 1:
                return false;

            default:
                break;
        }

        tor_param3 = std::sqrt(getEmpiricalRuleVParameter(ctr_atomic_no1) * getEmpiricalRuleVParameter(ctr_atomic_no2)) / 
            (3.0 * (non_tetra_coord_ctr_atom_props.getNumNeighbors() - 1));

        return true;
    }
            
    if (getOrder(ctr_bond) == 1 && ctr_atom1_mb_desig != 0 && ctr_atom2_mb_desig != 0) {
        // Rule g)

        bool ctr_atom1_has_pi_lp = ctr_atom1_prop_entry.hasPiLonePair();
        bool ctr_atom2_has_pi_lp = ctr_atom2_prop_entry.hasPiLonePair();

        if (ctr_atom1_has_pi_lp && ctr_atom2_has_pi_lp) {
            // Rule g1)

            return false;
        }
        
        if (ctr_atom1_has_pi_lp && ctr_atom2_mb_desig != 0) {
            // Rule g2)

            double pi_bnd_order = 0.15;

            if (ctr_atom1_mb_desig != 0)
                pi_bnd_order = 0.5;
                
            else if (isInSecondPTERow(ctr_atomic_no1) && isInSecondPTERow(ctr_atomic_no2))
                pi_bnd_order = 0.3;
                
            tor_param2 = 6.0 * pi_bnd_order * std::sqrt(getEmpiricalRuleUParameter(ctr_atomic_no1) * getEmpiricalRuleUParameter(ctr_atomic_no2));
            return true;
        }

        if (ctr_atom2_has_pi_lp && ctr_atom1_mb_desig != 0) {
            // Rule g3)

            double pi_bnd_order = 0.15;

            if (ctr_atom2_mb_desig != 0)
                pi_bnd_order = 0.5;
                    
            else if (isInSecondPTERow(ctr_atomic_no1) && isInSecondPTERow(ctr_atomic_no2))
                pi_bnd_order = 0.3;
                    
            tor_param2 = 6.0 * pi_bnd_order * std::sqrt(getEmpiricalRuleUParameter(ctr_atomic_no1) * getEmpiricalRuleUParameter(ctr_atomic_no2));
            return true;
        }

        if ((ctr_atom1_mb_desig != 0 || ctr_atom2_mb_desig != 0) && (ctr_atomic_no1 != AtomType::C || ctr_atomic_no2 != AtomType::C)) {
            // Rule g4)

            tor_param2 = 6.0 * 0.4 * std::sqrt(getEmpiricalRuleUParameter(ctr_atomic_no1) * getEmpiricalRuleUParameter(ctr_atomic_no2));
            return true;
        }

        // Rule g5)

        tor_param2 = 6.0 * 0.15 * std::sqrt(getEmpiricalRuleUParameter(ctr_atomic_no1) * getEmpiricalRuleUParameter(ctr_atomic_no2));
        return true;
    }

    if ((ctr_atomic_no1 == AtomType::O || ctr_atomic_no1 == AtomType::S) && (ctr_atomic_no2 == AtomType::O || ctr_atomic_no2 == AtomType::S)) {
        // Rule h1)

        double wj = (ctr_atomic_no1 == AtomType::O ? 2.0 : 8.0);
        double wk = (ctr_atomic_no2 == AtomType::O ? 2.0 : 8.0);

        tor_param2 = -std::sqrt(wj * wk);
        return true;
    }

    // Rule h2)
 
    std::size_t num_ctr_atom1_nbrs = std::max(ctr_atom1_prop_entry.getNumNeighbors(), MolProp::getBondCount(ctr_atom1, molgraph));
    std::size_t num_ctr_atom2_nbrs = std::max(ctr_atom2_prop_entry.getNumNeighbors(), MolProp::getBondCount(ctr_atom2, molgraph));

    if (num_ctr_atom1_nbrs <= 1 || num_ctr_atom2_nbrs <= 1)
        return false;

    tor_param3 = std::sqrt(getEmpiricalRuleVParameter(ctr_atomic_no1) * getEmpiricalRuleVParameter(ctr_atomic_no2)) /
        ((num_ctr_atom1_nbrs - 1) * (num_ctr_atom2_nbrs - 1));

    return true;
}

unsigned int ForceField::MMFF94TorsionInteractionParameterizer::getTorsionTypeIndex(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1, 
                                                                                    const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
                                                                                    unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type, 
                                                                                    unsigned int term_atom2_type, unsigned int term_bond1_type_idx, unsigned int ctr_bond_type_idx,
                                                                                    unsigned int term_bond2_type_idx) const
{
    using namespace Chem;

    bool in_3_ring = false;
    const Bond* bond = term_atom1.findBondToAtom(ctr_atom2);

    if (bond && molgraph.containsBond(*bond))
        in_3_ring = true;

    else {
        bond = term_atom2.findBondToAtom(ctr_atom1);

        if (bond && molgraph.containsBond(*bond))
            in_3_ring = true;
    }

    if (!in_3_ring) {
        bond = term_atom2.findBondToAtom(term_atom1);

        if (bond && molgraph.containsBond(*bond))
            return 4;
    }
  
    if (ctr_bond_type_idx == 1) 
        return 1;

    if ((term_bond1_type_idx == 1 || term_bond2_type_idx == 1) && getOrder(ctr_bond) == 1 && 
        !containsFragmentWithBond(*aromRingSetFunc(molgraph), ctr_bond))
        return 2;

    if (!in_3_ring && (term_atom1_type == 1 || ctr_atom1_type == 1 || ctr_atom2_type == 1 || term_atom2_type == 1)) { // have sp3 carbon?
        Atom::ConstBondIterator b_it = term_atom1.getBondsBegin();

        for (Atom::ConstAtomIterator a_it = term_atom1.getAtomsBegin(), a_end = term_atom1.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
            const Atom& nbr_atom = *a_it;

            if (&nbr_atom == &ctr_atom1)
                continue;

            if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
                continue;

            bond = nbr_atom.findBondToAtom(term_atom2);

            if (bond && molgraph.containsBond(*bond))
                return 5;
        }
    }

    return 0;
}

bool ForceField::MMFF94TorsionInteractionParameterizer::isInSecondPTERow(unsigned int atomic_no) const
{
    return (atomic_no >= Chem::AtomType::Li && atomic_no <= Chem::AtomType::Ne);
}
