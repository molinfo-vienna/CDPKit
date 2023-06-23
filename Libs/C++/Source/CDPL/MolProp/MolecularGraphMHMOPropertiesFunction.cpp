/* 
 * MolecularGraphMHMOPropertiesFunction.cpp 
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

#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/MHMOPiChargeCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL; 


void MolProp::calcMHMOProperties(Chem::MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
    Chem::MolecularGraph::ConstAtomIterator a_it = molgraph.getAtomsBegin(), a_end = molgraph.getAtomsEnd();
        
    for ( ; a_it != a_end; ++a_it) {
        const Chem::Atom& atom = *a_it;

        if (!hasMHMOPiCharge(atom))
        break;
    }
        
    if (a_it == a_end) {
        Chem::MolecularGraph::ConstBondIterator b_it = molgraph.getBondsBegin(), b_end = molgraph.getBondsEnd();
        
        for ( ; b_it != b_end; ++b_it) {
        const Chem::Bond& bond = *b_it;

        if (!hasMHMOPiOrder(bond))
            break;
        }

        if (b_it == b_end)
        return;
    }
    }

    MHMOPiChargeCalculator calculator;

    calculator.calculate(molgraph);
    
    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
    Chem::Atom& atom = molgraph.getAtom(i);
        
    setMHMOPiCharge(atom, calculator.getCharge(i));
    }

    for (std::size_t i = 0, num_bonds = molgraph.getNumBonds(); i < num_bonds; i++) {
    Chem::Bond& bond = molgraph.getBond(i);
        
    setMHMOPiOrder(bond, calculator.getBondOrder(i));
    }
}
