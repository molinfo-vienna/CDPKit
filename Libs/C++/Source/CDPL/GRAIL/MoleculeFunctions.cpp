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

#include "CDPL/GRAIL/MoleculeFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/ProtonationStateStandardizer.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Pharm/MoleculeFunctions.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/XLogPCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


using namespace CDPL; 


void GRAIL::prepareForGRAILDescriptorCalculation(Chem::Molecule& mol, bool std_prot_state)
{
    if (std_prot_state)
    Chem::ProtonationStateStandardizer().standardize(mol, Chem::ProtonationStateStandardizer::PHYSIOLOGICAL_CONDITION_STATE);
    
    Pharm::prepareForPharmacophoreGeneration(mol, false);

    MolProp::XLogPCalculator calculator(mol);
    const Math::DVector& logp_contribs = calculator.getAtomContributions();

    for (std::size_t i = 0, num_atoms = mol.getNumAtoms(); i < num_atoms; i++) 
    MolProp::setHydrophobicity(mol.getAtom(i), logp_contribs[i]);
    
    Chem::perceiveSybylAtomTypes(mol, true);
    ForceField::perceiveMMFF94AromaticRings(mol, true);
    ForceField::assignMMFF94AtomTypes(mol, false, true);
    ForceField::assignMMFF94BondTypeIndices(mol, false, true);
    ForceField::calcMMFF94AtomCharges(mol, false, true);
}
