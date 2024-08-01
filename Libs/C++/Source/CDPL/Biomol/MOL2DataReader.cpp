/* 
 * MOL2DataReader.cpp 
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

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MOL2DataReader.hpp"


using namespace CDPL;


namespace
{

    Chem::MOL2DataReader* newMOL2DataReaderInstance(const Base::DataIOBase& io_base)
    {
        return new Biomol::MOL2DataReader(io_base);
    }
}


void Biomol::MOL2DataReader::registerFactoryFunction()
{
    Chem::MOL2DataReader::factoryFunction() = &newMOL2DataReaderInstance;
}

bool Biomol::MOL2DataReader::readMolecule(std::istream& is, Chem::Molecule& mol)
{
    std::size_t prev_num_atoms = mol.getNumAtoms();
    
    if (!Chem::MOL2DataReader::readMolecule(is, mol))
        return false;

    convertMOL2ToPDBResidueInfo(mol, prev_num_atoms);
    
    return true;
}

void Biomol::MOL2DataReader::convertMOL2ToPDBResidueInfo(Chem::Molecule& mol, std::size_t atom_idx_offs) const
{
    using namespace Chem;

    long atom_serial = 1;

    for (auto it = mol.getAtomsBegin() + atom_idx_offs, end = mol.getAtomsEnd(); it != end; ++it) {
        auto& atom = *it;
        
        if (hasMOL2SubstructureName(atom)) {
            auto& ss_name = getMOL2SubstructureName(atom);

            setResidueCode(atom, ss_name.size() > 3 ? ss_name.substr(0, 3) : ss_name);
            setHeteroAtomFlag(atom, !ResidueDictionary::isStdResidue(ss_name.size() > 3 ? ss_name.substr(0, 3) : ss_name));
        }

        if (hasMOL2SubstructureID(atom))
            setResidueSequenceNumber(atom, getMOL2SubstructureID(atom));

        if (hasMOL2SubstructureChain(atom))
            setChainID(atom, getMOL2SubstructureChain(atom));

        if (hasMOL2Name(atom))
            setResidueAtomName(atom, getMOL2Name(atom));

        setSerialNumber(atom, atom_serial++);
    }
}
