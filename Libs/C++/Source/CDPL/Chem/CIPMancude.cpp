/* 
 * CIPMancude.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * The code in this file is a C++11 port of Java code written by John Mayfield
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


#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"

#include "CIPMancude.hpp"


using namespace CDPL;


void Chem::CIPMancude::setMolecularGraph(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;
    calculated = false;
}

const Chem::CIPMancude::Fraction& Chem::CIPMancude::operator[](const Atom& atom)
{
    if (!calculated) {
        calcFracAtomicNos();
        calculated = true;
    }

    return fractions[molGraph->getAtomIndex(atom)];
}

bool Chem::CIPMancude::seedTypes()
{
    bool result = false;
    std::size_t num_atoms = molGraph->getNumAtoms();

    types.resize(num_atoms, Other);
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        types[i] = Other;

        const Atom& atom = molGraph->getAtom(i);
        std::size_t btypes = getImplicitHydrogenCount(atom);
        bool in_ring = false;
        auto a_it = atom.getAtomsBegin();
        
        for (auto b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
            if (!molGraph->containsAtom(*a_it))
                continue;

            const Bond& bond = *b_it;

            if (!molGraph->containsBond(bond))
                continue;
            
            switch (getOrder(bond)) {
                
                case 1:
                    btypes += 0x00000001;
                    break;
                
                case 2:
                    btypes += 0x00000100;
                    break;
                
                case 3:
                    btypes += 0x00010000;
                    break;
                
                default:
                    btypes += 0x01000000;
                    break;
            }
            
            if (!in_ring && getRingFlag(bond))
                in_ring = true;
        }
                                                       
        if (in_ring) {
            long q = getFormalCharge(atom);
            
            switch (getType(atom)) {

                case AtomType::C:
                case AtomType::Si:
                case AtomType::Ge:
                    if (q == 0 && btypes == 0x0102)
                        types[i] = Cv4D4;
                    
                    else if (q == -1 && btypes == 0x0003) {
                        types[i] = Cv3D3Minus;
                        result = true;
                    }
                    break;
                    
                case AtomType::N:
                case AtomType::P:
                case AtomType::As:
                    if (q == 0 && btypes == 0x0101) {
                        types[i] = Nv3D2;
                        result = true;
                    } else if (q == -1 && btypes == 0x0002) {
                        types[i] = Nv2D2Minus;
                        result = true;
                    } else if (q == 1 && btypes == 0x0102) {
                        types[i] = Nv4D3Plus;
                        result = true;
                    }
                    break;
                    
                case AtomType::O:
                    if (q == 1 && btypes == 0x0101) {
                        types[i] = Ov3D2Plus;
                        result = true;
                    }

                default:
                    break;
            }
        }
    }
    
    return result;
}

void Chem::CIPMancude::relaxTypes()
{
    std::size_t num_atoms = molGraph->getNumAtoms();

    counts.assign(num_atoms, 0);
    atomQueue.clear();

    for (std::size_t i = 0; i < num_atoms; i++) {
        const Atom& atom = molGraph->getAtom(i);
        auto b_it = atom.getBondsBegin();
        
        for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
            if (!molGraph->containsBond(*b_it))
                continue;

            const Atom& nbr = *a_it;

            if (!molGraph->containsAtom(nbr))
                continue;
        
            if (types[molGraph->getAtomIndex(nbr)] != Other)
                counts[i]++;
        }
        
        if (counts[i] == 1)
            atomQueue.push_back(&atom);
    }
    
    while (!atomQueue.empty()) {
        const Atom* atom = atomQueue.front(); atomQueue.pop_front();
        std::size_t aidx = molGraph->getAtomIndex(*atom);

        if (types[aidx] != Other) {
            types[aidx] = Other;

            auto b_it = atom->getBondsBegin();
        
            for (auto a_it = atom->getAtomsBegin(), a_end = atom->getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
                if (!molGraph->containsBond(*b_it))
                    continue;

                const Atom& nbr = *a_it;
            
                if (!molGraph->containsAtom(nbr))
                    continue;
          
                if (--counts[molGraph->getAtomIndex(nbr)] == 1)
                    atomQueue.push_back(&nbr);
            }
        }
    }
}

void Chem::CIPMancude::visitPart(std::size_t part, const Atom* atom)
{
    do {
        const Atom* next = 0;
        auto a_it = atom->getAtomsBegin();
        
        for (auto b_it = atom->getBondsBegin(), b_end = atom->getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
            const Atom& nbr = *a_it;
            
            if (!molGraph->containsAtom(nbr))
                continue;

            const Bond& bond = *b_it;

            if (!molGraph->containsBond(bond))
                continue;
            
            if (!getRingFlag(bond))
                continue;
           
            std::size_t aidx = molGraph->getAtomIndex(nbr);
            
            if (parts[aidx] == 0 && types[aidx] != Other) {
                parts[aidx] = part;
                
                if (next)
                    visitPart(part, &nbr);
                else
                    next = &nbr;
            }
        }
        
        atom = next;
  
    } while (atom);
}

std::size_t Chem::CIPMancude::visitParts()
{
    std::size_t num_parts = 0;

    for (std::size_t i = 0, num_atoms = molGraph->getNumAtoms(); i < num_atoms; i++) {
        const Atom& atom = molGraph->getAtom(i);

        if (parts[i] == 0 && types[i] != Other) {
            parts[i] = ++num_parts;
            
            visitPart(parts[i], &atom);
        }
    }
    
    return num_parts;
}

void Chem::CIPMancude::calcFracAtomicNos()
{
    std::size_t num_atoms = molGraph->getNumAtoms();
    
    fractions.resize(num_atoms);

    for (std::size_t i = 0; i < num_atoms; i++) {
        fractions[i].first = getType(molGraph->getAtom(i));
        fractions[i].second = 1;
    }
    
    if (!seedTypes())
        return;

    relaxTypes();

    parts.assign(num_atoms, 0);

    std::size_t num_parts = visitParts();

    resParts.assign(num_parts, 0);

    std::size_t num_res = 0;

    if (num_parts > 0) {
        for (std::size_t i = 0; i < num_atoms; i++) {
            if (parts[i] == 0)
                continue;

            const Atom& atom = molGraph->getAtom(i);

            if (types[i] == Cv3D3Minus || types[i] == Nv2D2Minus) {
                std::size_t j = 0;

                for (; j < num_res; j++)
                    if (resParts[j] == parts[i])
                        break;

                if (j >= num_res)
                    resParts[num_res++] = parts[i];
            }

            fractions[i].first  = 0;
            fractions[i].second = 0;

            auto b_it = atom.getBondsBegin();

            for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
                if (!molGraph->containsBond(*b_it))
                    continue;

                const Atom& nbr = *a_it;

                if (!molGraph->containsAtom(nbr))
                    continue;

                if (parts[molGraph->getAtomIndex(nbr)] == parts[i]) {
                    fractions[i].first += getType(nbr);
                    fractions[i].second++;
                }
            }
        }
    }

    if (num_res > 0) {
        for (std::size_t j = 0; j < num_res; j++) {
            Fraction frac(0, 0);
            std::size_t part = resParts[j];

            counts.clear();
            
            for (std::size_t i = 0; i < num_atoms; i++) {
                if (parts[i] == part) {
                    counts.push_back(i);
                    frac.second++;

                    const Atom& atom = molGraph->getAtom(i);
                    auto b_it = atom.getBondsBegin();

                    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
                        const Bond& bond = *b_it;
                        
                        if (!molGraph->containsBond(bond))
                            continue;

                        const Atom& nbr = *a_it;

                        if (!molGraph->containsAtom(nbr))
                            continue;
                    
                        std::size_t order = getOrder(bond);

                        if (order > 1 && parts[molGraph->getAtomIndex(nbr)] == part)
                            frac.first += (order - 1) * getType(nbr);
                    }
                }
            }

            for (std::size_t i : counts)
                fractions[i] = frac;
        }
    }
}
