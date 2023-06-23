/* 
 * AtomPolarizabilityFunctions.cpp 
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

#include <cmath>

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"

#include "AtomicHybridPolarizabilities.hpp"


using namespace CDPL; 


namespace
{

    std::size_t getNumPiNeighbors(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
    {
        using namespace Chem;

        std::size_t n = 0;

        Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
        Atom::ConstBondIterator b_it = atom.getBondsBegin();

        for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
            const Bond& bond = *b_it;

            if (!molgraph.containsBond(bond))
                continue;

            const Atom& atom = *a_it;

            if (!molgraph.containsAtom(atom))
                continue;

            if (getOrder(bond) > 1) {
                n++;
                continue;
            }
        
            if (MolProp::isUnsaturated(atom, molgraph)) {
                n++;
                continue;
            }

            if (getAromaticityFlag(bond))
                n++;
        }

        return n;
    }
}


double MolProp::getHybridPolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    unsigned int atom_type = getType(atom);

    switch (atom_type) {

        case AtomType::H:
            return AtomicHybridPolarizability::H;

        case AtomType::F:
            return AtomicHybridPolarizability::F;

        case AtomType::Cl:
            return AtomicHybridPolarizability::Cl;

        case AtomType::Br:
            return AtomicHybridPolarizability::Br;

        case AtomType::I:
            return AtomicHybridPolarizability::I;

        case AtomType::C: {
            std::size_t bond_count = getBondCount(atom, molgraph);

            switch (bond_count) {
                
                case 4:
                    return AtomicHybridPolarizability::CTE;

                case 3:
                    if (getNumPiNeighbors(atom, molgraph) >= 3)
                        return AtomicHybridPolarizability::CBR;

                    return AtomicHybridPolarizability::CTR;

                case 2:
                    return AtomicHybridPolarizability::CDI;
            }

            return AtomicHybridPolarizability::C_DEFAULT;
        }

        case AtomType::N: {
            std::size_t bond_count = getBondCount(atom, molgraph);

            switch (bond_count) {
                
                case 3:
                    if (getNumPiNeighbors(atom, molgraph) > 0) 
                        return AtomicHybridPolarizability::NPI2;

                    return AtomicHybridPolarizability::NTE;

                case 2:
                    return AtomicHybridPolarizability::NTR2;

                case 1:
                    return AtomicHybridPolarizability::NDI;
            }

            return AtomicHybridPolarizability::N_DEFAULT;
        }

        case AtomType::O: {
            std::size_t bond_count = getBondCount(atom, molgraph);

            switch (bond_count) {
                
                case 2:
                    if (getNumPiNeighbors(atom, molgraph) > 1)
                        return AtomicHybridPolarizability::OPI2;

                    return AtomicHybridPolarizability::OTE;

                case 1:
                    return AtomicHybridPolarizability::OTR4;
            }

            return AtomicHybridPolarizability::O_DEFAULT;
        }

        case AtomType::S: {
            std::size_t bond_count = getBondCount(atom, molgraph);

            switch (bond_count) {
                
                case 2:
                    if (getNumPiNeighbors(atom, molgraph) > 1)
                        return AtomicHybridPolarizability::SPI2;

                    return AtomicHybridPolarizability::STE;

                case 1:
                    return AtomicHybridPolarizability::STR4;
            }

            return AtomicHybridPolarizability::S_DEFAULT;
        }

        case AtomType::P:
            return AtomicHybridPolarizability::PTE;

        default:
            return AtomicHybridPolarizability::DEFAULT;
    }
}

double MolProp::calcEffectivePolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, double damping)
{
    using namespace Chem;

    double polarizability = 0.0;

    const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);
    MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

    std::size_t atom_idx = molgraph.getAtomIndex(atom);
    std::size_t i = 0;

    for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it, i++) {
        std::size_t dist = dist_mtx(atom_idx, i);

        if (i != atom_idx && dist == 0)
            continue;

        double factor = (dist <= 1 ? 1.0 : std::pow(damping, double(dist - 1)));
        const Atom& nbr_atom = *it;

        polarizability += getHybridPolarizability(nbr_atom, molgraph) * factor;
        polarizability += getImplicitHydrogenCount(nbr_atom) * std::pow(damping, double(dist)) * 
            AtomicHybridPolarizability::H;
    }

    return polarizability;
}
