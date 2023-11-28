/* 
 * MoleculeFunctions.cpp 
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

#include <memory>

#include "CDPL/ConfGen/MoleculeFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"

#include "SubstituentBulkinessCalculator.hpp"


using namespace CDPL; 


namespace
{

    const Chem::Atom* getBulkiestDoubleBondSubstituent(const Chem::Atom& atom, const Chem::Atom& db_nbr_atom, 
                                                       const ConfGen::SubstituentBulkinessCalculator& subst_blks)
    {
        using namespace Chem;

        const Atom* bkst_subst = 0;
        std::size_t bkst_subst_bks = 0;
        std::size_t bond_cnt = 0;

        for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), atoms_end = atom.getAtomsEnd(); a_it != atoms_end; ++a_it) {
            const Atom& nbr_atom = *a_it;

            if (&nbr_atom == &db_nbr_atom)
                continue;

            if (++bond_cnt > 2)
                return 0;

            std::size_t nbr_bks = subst_blks[nbr_atom.getIndex()];

            if (!bkst_subst || nbr_bks > bkst_subst_bks) {
                bkst_subst = &nbr_atom;
                bkst_subst_bks = nbr_bks;

            } else if (bkst_subst_bks == nbr_bks)
                return 0;
        }

        return bkst_subst;
    }
}


void ConfGen::prepareForConformerGeneration(Chem::Molecule& mol, bool canon)
{
    using namespace Chem;

    bool added_hs = makeHydrogenComplete(mol, true);

    perceiveComponents(mol, added_hs);
    perceiveHybridizationStates(mol, false);
    perceiveSSSR(mol, false);
    setRingFlags(mol, false);
    setAromaticityFlags(mol, false);
    calcCIPPriorities(mol, added_hs);

    for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
        Atom& atom = *it;

        if (hasStereoDescriptor(atom)) {
            if (added_hs)
                setStereoDescriptor(atom, calcStereoDescriptor(atom, mol, 0));
            
            continue;
        }
        
        if (!isStereoCenter(atom, mol, true, true, false)) {
            setStereoDescriptor(atom, StereoDescriptor(AtomConfiguration::NONE));
            continue;
        }
        
        setStereoDescriptor(atom, calcStereoDescriptor(atom, mol, 1));
    }

    std::unique_ptr<SubstituentBulkinessCalculator> blks_calc;

    for (Molecule::BondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) {
        Bond& bond = *it;

        if (hasStereoDescriptor(bond)) {
            if (added_hs)
                setStereoDescriptor(bond, calcStereoDescriptor(bond, mol, 0));
            continue;
        }
        
        if (!isStereoCenter(bond, mol, true, false)) 
            setStereoDescriptor(bond, StereoDescriptor(BondConfiguration::NONE));
        
        else {
            StereoDescriptor descr = calcStereoDescriptor(bond, mol, 1);

            switch (descr.getConfiguration()) {

                case BondConfiguration::TRANS:
                case BondConfiguration::CIS:
                case BondConfiguration::NONE:
                    setStereoDescriptor(bond, descr);
                    continue;

                default:
                    break;
            }

            if (!blks_calc.get()) {
                blks_calc.reset(new SubstituentBulkinessCalculator());
                blks_calc->calculate(mol);
            }

            const Atom* ref_atom1 = getBulkiestDoubleBondSubstituent(bond.getBegin(), bond.getEnd(), *blks_calc);

            if (!ref_atom1)
                continue;

            const Atom* ref_atom2 = getBulkiestDoubleBondSubstituent(bond.getEnd(), bond.getBegin(), *blks_calc);

            if (!ref_atom2)
                continue;

            setStereoDescriptor(bond, StereoDescriptor(BondConfiguration::TRANS, *ref_atom1, bond.getBegin(),
                                                       bond.getEnd(), *ref_atom2));
        }
    }

    if (canon) {
        if (added_hs) {
            for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
                Atom& atom = *it;
                const StereoDescriptor& descr = getStereoDescriptor(atom);

                if (descr.getConfiguration() != AtomConfiguration::R && descr.getConfiguration() != AtomConfiguration::S)
                    continue;

                if (descr.getNumReferenceAtoms() == atom.getNumBonds())
                    continue;

                setStereoDescriptor(atom, calcStereoDescriptor(atom, mol, 0));
            }
        }
        
        calcCanonicalNumbering(mol, false);
        canonicalize(mol, true, true, true, true);
        perceiveSSSR(mol, true);
        perceiveComponents(mol, true);
    }

    calcTopologicalDistanceMatrix(mol, canon || added_hs);

    FragmentList& comps = *getComponents(mol);

    for (FragmentList::ElementIterator it = comps.getElementsBegin(), end = comps.getElementsEnd(); it != end; ++it) {
        Fragment& comp = *it;

        extractTopologicalDistanceSubMatrix(mol, comp, true);
        extractSSSRSubset(mol, comp, true);
    }
}
