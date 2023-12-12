/* 
 * MoleculeConnectAtomsFunctions.cpp 
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
#include <algorithm>
#include <iterator>

#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


void Chem::connectAtoms(Molecule& mol, double dist_tol, std::size_t atom_idx_offs)
{
    connectAtoms(mol, &get3DCoordinates, dist_tol, atom_idx_offs);
}

void Chem::connectAtoms(Molecule& mol, const Atom3DCoordinatesFunction& coords_func,
                        double dist_tol, std::size_t atom_idx_offs)
{
    struct AtomData
    {

        AtomData(unsigned int type, double cov_rad, std::size_t free_val):
            type(type), covRadius(cov_rad), freeVal(free_val) {}

        unsigned int type;
        double       covRadius;
        std::size_t  freeVal;
    };
    
    std::vector<AtomData> atom_data;
    std::size_t num_atoms = mol.getNumAtoms() - atom_idx_offs;
    
    atom_data.reserve(num_atoms);

    for (auto it = mol.getAtomsBegin() + atom_idx_offs, end = mol.getAtomsEnd(); it != end; ++it) {
        const Atom& atom = *it;
        unsigned int type = getType(atom);
        double cov_rad = AtomDictionary::getCovalentRadius(type);

        if (cov_rad <= 0.0) {
            atom_data.emplace_back(type, 0.0, 0);
            continue;
        }

        long valence = 0;
         
        for (const auto& bond : atom.getBonds())
            valence += std::max(std::size_t(1), getOrder(bond));
    
        if (hasImplicitHydrogenCount(atom))
            valence += getImplicitHydrogenCount(atom);

        long max_val = 0;

        switch (AtomDictionary::getIUPACGroup(type)) {

            case 1:
                max_val = 1;
                break;

            case 2:
                max_val = 2;
                break;

            case 13:
            case 14:
                max_val = 4;
                break;

            case 15:
                if (type > AtomType::N)
                    max_val = 5;
                else
                    max_val = 4;
                break;

            case 16:
                if (type > AtomType::O)
                    max_val = 6;
                else
                    max_val = 3;
                break;

            case 17:
                if (type > AtomType::F)
                    max_val = 7;
                else
                    max_val = 1;
                break;

            case 18:
                if (type <= AtomType::Ne)
                    max_val = 0;
                else
                    max_val = 0;
                break;

            default:
                max_val = 8;
                break;
        }
        
        atom_data.emplace_back(type, cov_rad, std::max(long(0), max_val - valence));
    }    
   
    struct AtomPair
    {

        AtomPair(std::size_t atom1_idx, std::size_t atom2_idx, double rel_dist):
            atom1Idx(atom1_idx), atom2Idx(atom2_idx), relDist(rel_dist) {}
        
        std::size_t atom1Idx;
        std::size_t atom2Idx;
        double      relDist;
    };

    std::vector<AtomPair> atom_pairs;

    atom_pairs.reserve(num_atoms * 2);
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        if (atom_data[i].freeVal == 0)
            continue;
        
        const Math::Vector3D& pos1 = coords_func(mol.getAtom(i + atom_idx_offs));
        
        for (std::size_t j = i + 1; j < num_atoms; j++) {
             if (atom_data[i].type == AtomType::H && atom_data[j].type == AtomType::H && num_atoms != 2)
                 continue;
             
             if (atom_data[j].freeVal == 0)
                 continue;

             double dist = length(coords_func(mol.getAtom(j + atom_idx_offs)) - pos1);

             if (dist > (atom_data[i].covRadius + atom_data[j].covRadius + dist_tol))
                 continue;

             dist /= (atom_data[i].covRadius + atom_data[j].covRadius);

             if (dist < 0.5) // atom clash?
                 continue;
             
             atom_pairs.emplace_back(i, j, dist);
        }
    }

    std::sort(atom_pairs.begin(), atom_pairs.end(),
              [](const AtomPair& ap1, const AtomPair& ap2) -> bool { return (ap1.relDist < ap2.relDist); });

    for (const auto& atom_pair : atom_pairs) {
        if (atom_data[atom_pair.atom1Idx].freeVal == 0 || atom_data[atom_pair.atom2Idx].freeVal == 0)
            continue;

        mol.addBond(atom_pair.atom1Idx + atom_idx_offs, atom_pair.atom2Idx + atom_idx_offs);

        atom_data[atom_pair.atom1Idx].freeVal--;
        atom_data[atom_pair.atom2Idx].freeVal--;
    }
}
