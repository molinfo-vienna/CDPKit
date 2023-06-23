/* 
 * MolecularGraphPEOEPropertiesFunction.cpp 
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
#include "CDPL/MolProp/PEOESigmaChargeCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL; 


void MolProp::calcPEOEProperties(Chem::MolecularGraph& molgraph, bool overwrite, std::size_t num_iter, 
                                 double damping)
{
    if (!overwrite) {
        Chem::MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd();
        
        for ( ; it != end; ++it) {
            const Chem::Atom& atom = *it;

            if (!hasPEOESigmaCharge(atom) || !hasPEOESigmaElectronegativity(atom))
                break;
        }
        
        if (it == end)
            return;
    }

    PEOESigmaChargeCalculator calculator;

    calculator.setNumIterations(num_iter);
    calculator.setDampingFactor(damping);
    calculator.calculate(molgraph);
    
    std::size_t num_atoms = molgraph.getNumAtoms();

    for (std::size_t i = 0; i < num_atoms; i++) {
        Chem::Atom& atom = molgraph.getAtom(i);
        
        setPEOESigmaCharge(atom, calculator.getCharge(i));
        setPEOESigmaElectronegativity(atom, calculator.getElectronegativity(i));
    }
}
