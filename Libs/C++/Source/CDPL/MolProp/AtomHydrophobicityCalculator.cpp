/* 
 * AtomHydrophobicityCalculator.cpp 
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

#include <locale>
#include <algorithm>
#include <unordered_map>
#include <mutex>

#include "CDPL/MolProp/AtomHydrophobicityCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"

#include "AtomSurfaceAccessibilityData.hpp"


using namespace CDPL; 


namespace
{

    typedef std::unordered_map<std::string, double> AtomSurfaceAccessibilityTable;

    AtomSurfaceAccessibilityTable atomSurfAccTable;
    std::once_flag initAtomSurfAccTableFlag;

    void initAtomSurfAccTable() 
    {
        for (std::size_t i = 0; i < sizeof(ATOM_SURF_ACC_DATA) / sizeof(AtomSurfAccData); i++)
            atomSurfAccTable.insert(AtomSurfaceAccessibilityTable::value_type(ATOM_SURF_ACC_DATA[i].pattern, ATOM_SURF_ACC_DATA[i].value));
    }
    
    void appendBondSymbol(std::string& str, const Chem::Bond& bond)
    {
        if (getAromaticityFlag(bond)) {
            str.push_back(':');
            return;
        }

        switch (getOrder(bond)) {

            case 1:
                return;

            case 2:
                str.push_back('=');
                return;

            case 3:
                str.push_back('#');
                return;
        }

        str.push_back('~');
    }

    void appendAtomSymbol(std::string& str, const Chem::Atom& atom)
    {
        using namespace Chem;
        
        unsigned int type = getType(atom);

        if (type > AtomType::MAX_ATOMIC_NO)
            type = AtomType::ANY;

        const std::string& elem_sym = AtomDictionary::getSymbol(type);

        if (elem_sym.empty())
            return;
        
        if (getAromaticityFlag(atom))
            str.push_back(std::tolower(elem_sym[0], std::locale::classic()));
        else
            str.push_back(elem_sym[0]);

        if (elem_sym.size() > 1)
            str.push_back(elem_sym[1]);
    }
}


MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator()
{}

MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(const AtomHydrophobicityCalculator& calc)
{}

MolProp::AtomHydrophobicityCalculator::AtomHydrophobicityCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
    calculate(molgraph, hyd_table);
}

MolProp::AtomHydrophobicityCalculator::~AtomHydrophobicityCalculator() {}

MolProp::AtomHydrophobicityCalculator& MolProp::AtomHydrophobicityCalculator::operator=(const AtomHydrophobicityCalculator& calc)
{
    return *this;
}

void MolProp::AtomHydrophobicityCalculator::calculate(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
    calcHydrophobicities(molgraph, hyd_table);
}

void MolProp::AtomHydrophobicityCalculator::calcHydrophobicities(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table)
{
    using namespace Chem;

    std::call_once(initAtomSurfAccTableFlag, &initAtomSurfAccTable);

    std::size_t num_atoms = molgraph.getNumAtoms();
       
    hyd_table.assign(num_atoms, 0.0);
    cat9To11Counts.assign(num_atoms, 0);
    cat13Counts.assign(num_atoms, 0);
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = molgraph.getAtom(i);

        if (getFormalCharge(atom) != 0) { // category 3 atom
            getEnvironment(atom, molgraph, 2, atomEnvironment);

            for (auto& env_atom : atomEnvironment.getAtoms()) // category 3 env. atoms
                hyd_table[molgraph.getAtomIndex(env_atom)] = -3.0;
        }
        
        auto type = getType(atom);
 
        switch (type) {

            case AtomType::N:
            case AtomType::O:
                // category 1 atom
                hyd_table[i] = -1.0;
                
            case AtomType::S:
                break;

            case AtomType::H:
                // category 1 atom
                hyd_table[i] = -1.0;
                
            default:
                continue;
        }

        std::size_t num_bonds = 0;
        std::size_t valence = 0;
        std::size_t h_count = 0;
        auto unsat = false;
        auto deloc = getAromaticityFlag(atom);
        auto b_it = atom.getBondsBegin();

        for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
            auto& nbr_atom = *a_it;

            if (!molgraph.containsAtom(nbr_atom))
                continue;

            auto& nbr_bond = *b_it;

            if (!molgraph.containsBond(nbr_bond))
                continue;

            auto order = getOrder(nbr_bond);
            auto nbr_type = getType(nbr_atom);
            
            if ((order == 1) && (nbr_type == AtomType::H))
                h_count++;

            if (order > 1)
                unsat = true;

            if (!deloc && (order == 1) && getAromaticityFlag(nbr_atom))
                deloc = true;
            
            num_bonds++;
            valence += order;
        }

        auto impl_h_cnt = getImplicitHydrogenCount(atom);

        valence += impl_h_cnt;
        num_bonds += impl_h_cnt;
        h_count += impl_h_cnt;

        if (type == AtomType::S) {
            if ((valence == 2) && (num_bonds == 2) && (h_count >= 1)) { // category 2 atom
                if (!deloc) { 
                    getEnvironment(atom, molgraph, 1, atomEnvironment);

                    for (auto& env_atom : atomEnvironment.getAtoms())  // category 5 env. atoms
                        hyd_table[molgraph.getAtomIndex(env_atom)] = -5.0;
                }

                hyd_table[i] = -2.0;
                continue;
            }

            if (valence > 2) {  // category 7 atom
                getEnvironment(atom, molgraph, 1, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms()) // category 7 env. atoms
                    hyd_table[molgraph.getAtomIndex(env_atom)] = -7.0;

                getEnvironment(atom, molgraph, 2, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms()) // category 10 env. atoms
                    cat9To11Counts[molgraph.getAtomIndex(env_atom)]++;

                continue;
            }
            
            if (unsat) {  // category 8 atom
                hyd_table[i] = -8.0;

                getEnvironment(atom, molgraph, 1, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms()) // category 11 env. atom
                    cat9To11Counts[molgraph.getAtomIndex(env_atom)]++;
            }
            
            continue;
        }

        if (type == AtomType::O) {
            if (unsat) { // category 6 atom
                getEnvironment(atom, molgraph, 2, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms()) // category 6 env. atoms
                    hyd_table[molgraph.getAtomIndex(env_atom)] = -6.0;

                getEnvironment(atom, molgraph, 3, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms()) // category 9 env. atoms
                    cat9To11Counts[molgraph.getAtomIndex(env_atom)]++;
                
                continue;
            }

            if (!deloc) {
                if (h_count > 0) { // category 4 atom
                    getEnvironment(atom, molgraph, 2, atomEnvironment);

                    for (auto& env_atom : atomEnvironment.getAtoms()) // category 4 env. atoms
                        hyd_table[molgraph.getAtomIndex(env_atom)] = -4.0;
                    
                } else {
                    getEnvironment(atom, molgraph, 1, atomEnvironment);

                    for (auto& env_atom : atomEnvironment.getAtoms()) // category 13 env. atoms
                        cat13Counts[molgraph.getAtomIndex(env_atom)]++;
                }
            }
            
            continue;
        }

        if ((type == AtomType::N) && !deloc) {
            if (h_count > 0) { // category 4 atom
                getEnvironment(atom, molgraph, 2, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms())
                    hyd_table[molgraph.getAtomIndex(env_atom)] = -4.0; // category 4 env. atoms
                    
            } else {
                getEnvironment(atom, molgraph, 1, atomEnvironment);

                for (auto& env_atom : atomEnvironment.getAtoms())
                    cat13Counts[molgraph.getAtomIndex(env_atom)]++; // category 13 env. atoms
            }
        }
    }
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        if ((hyd_table[i] != 0.0) || (cat9To11Counts[i] > 1) || (cat13Counts[i] > 1)) { 
            hyd_table[i] = 0.0;
            continue;
        }
  
        auto base_hyd = (cat9To11Counts[i] > 0 ? 0.6 : 1.0);

        if (cat13Counts[i] > 0)
            base_hyd *= 0.25;
       
        hyd_table[i] = base_hyd * calcAccessibleSurfaceFactor(molgraph.getAtom(i), molgraph);
    }
}

double MolProp::AtomHydrophobicityCalculator::calcAccessibleSurfaceFactor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    atomEnvData.clear();

    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        const Atom& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;

        const Bond& nbr_bond = *b_it;

        if (!molgraph.containsBond(nbr_bond))
            continue;
        
        atomDescr.clear();

        appendBondSymbol(atomDescr, nbr_bond);
        appendAtomSymbol(atomDescr, nbr_atom);

        atomEnvData.push_back(atomDescr);
    }

    for (std::size_t i = 0, num_impl_hs = calcImplicitHydrogenCount(atom, molgraph); i < num_impl_hs; i++)
        atomEnvData.push_back("H");
    
    std::sort(atomEnvData.begin(), atomEnvData.end());
    
    atomDescr.clear();
            
    appendAtomSymbol(atomDescr, atom);

    for (StringList::const_iterator it = atomEnvData.begin(), end = atomEnvData.end(); it != end; ++it)
        atomDescr.append(*it);

    AtomSurfaceAccessibilityTable::const_iterator it = atomSurfAccTable.find(atomDescr);

    if (it != atomSurfAccTable.end())
        return it->second;

    // fallback 1
    
    atomDescr.clear();

    appendAtomSymbol(atomDescr, atom);

    atomDescr.append(std::to_string(atomEnvData.size()));
    atomDescr.push_back('.');
    atomDescr.append(std::to_string(std::count(atomEnvData.begin(), atomEnvData.end(), "H")));

    it = atomSurfAccTable.find(atomDescr);

    if (it != atomSurfAccTable.end())
        return it->second;

    // fallback 2

    double vdw_radius = MolProp::getVdWRadius(atom);

    return (vdw_radius * vdw_radius);
}
