/* 
 * BemisMurckoAnalyzer.cpp 
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

#include "CDPL/Chem/BemisMurckoAnalyzer.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL;


Chem::BemisMurckoAnalyzer::BemisMurckoAnalyzer(): hDeplete(true)
{}

void Chem::BemisMurckoAnalyzer::stripHydrogens(bool strip)
{
    hDeplete = strip;
}

bool Chem::BemisMurckoAnalyzer::hydrogensStripped() const
{
    return hDeplete;
}

void Chem::BemisMurckoAnalyzer::analyze(const MolecularGraph& molgraph)
{
    extractSideChains(molgraph);
    extractFrameworks(molgraph);
    splitFrameworks();
}

const Chem::FragmentList& Chem::BemisMurckoAnalyzer::getRingSystems() const
{
    return ringSystems;
}

const Chem::FragmentList& Chem::BemisMurckoAnalyzer::getSideChains() const
{
    return sideChains;
}

const Chem::FragmentList& Chem::BemisMurckoAnalyzer::getLinkers() const
{
    return linkers;
}

const Chem::FragmentList& Chem::BemisMurckoAnalyzer::getFrameworks() const
{
    return frameworks;
}

void Chem::BemisMurckoAnalyzer::extractSideChains(const MolecularGraph& molgraph)
{
    std::size_t num_atoms = molgraph.getNumAtoms();
    
    bondCounts.assign(num_atoms, 1);
    
    if (hDeplete) {
        for (std::size_t i = 0; i < num_atoms; i++) {
            const Atom& atom = molgraph.getAtom(i);

            if (getType(atom) == AtomType::H)
                bondCounts[i] = 0;
        }
    }
  
    for (const Bond& bond : molgraph.getBonds()) {
        if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
            continue;

        std::size_t atom1_idx = molgraph.getAtomIndex(bond.getBegin());

        if (bondCounts[atom1_idx] == 0)
            continue;

        std::size_t atom2_idx = molgraph.getAtomIndex(bond.getEnd());

        if (bondCounts[atom2_idx] == 0)
            continue;

        bondCounts[atom1_idx]++;
        bondCounts[atom2_idx]++;
    }

    workingFrag.clear();
    
    for (bool changes = true; changes; ) {
        changes = false;

        for (std::size_t i = 0; i < num_atoms; i++) {
            switch (bondCounts[i]) {

                case 1:
                    bondCounts[i] = 0;
                    workingFrag.addAtom(molgraph.getAtom(i));
                    continue;

                case 2:
                    break;

                default:
                    continue;
            }

            const Atom& atom = molgraph.getAtom(i);
            Atom::ConstBondIterator b_it = atom.getBondsBegin();
        
            for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
                if (!molgraph.containsBond(*b_it) || !molgraph.containsAtom(*a_it))
                    continue;

                std::size_t& nbr_bond_cnt = bondCounts[molgraph.getAtomIndex(*a_it)];
                
                if (nbr_bond_cnt < 2)
                    continue;

                nbr_bond_cnt--;
                bondCounts[i] = 0;
                changes = true;
                workingFrag.addAtom(atom);
                break;
            }
        }
    }

    for (const Bond& bond : molgraph.getBonds())
        if (workingFrag.containsAtom(bond.getBegin()) && workingFrag.containsAtom(bond.getEnd()))
            workingFrag.addBond(bond);
    
    compSet.perceive(workingFrag);
    sideChains.swap(compSet);
}

void Chem::BemisMurckoAnalyzer::extractFrameworks(const MolecularGraph& molgraph)
{
    workingFrag.clear();

    for (std::size_t i = 0, num_atoms = bondCounts.size(); i < num_atoms; i++)
        if (bondCounts[i] > 0)
            workingFrag.addAtom(molgraph.getAtom(i));

    for (const Bond& bond : molgraph.getBonds())
        if (workingFrag.containsAtom(bond.getBegin()) && workingFrag.containsAtom(bond.getEnd()))
            workingFrag.addBond(bond);

    compSet.perceive(workingFrag);
    frameworks.swap(compSet);
}

void Chem::BemisMurckoAnalyzer::splitFrameworks()
{
    ringSystems.clear();
    linkers.clear();

    for (const auto& framework : frameworks) {
        workingFrag = framework;

        for (std::size_t i = 0, num_bonds = workingFrag.getNumBonds(); i < num_bonds; ) {
            const Bond& bond = workingFrag.getBond(i);
            
            if (getRingFlag(bond.getBegin()) != getRingFlag(bond.getEnd())) {
                workingFrag.removeBond(i);
                num_bonds--;
                continue;
            }

            i++;
        }

        compSet.perceive(workingFrag);

        for (const auto& frag : static_cast<const FragmentList::BaseType&>(compSet)) {
            if (getRingFlag(frag->getAtom(0)))
                ringSystems.addElement(frag);
            else
                linkers.addElement(frag);
        }
    }
}
