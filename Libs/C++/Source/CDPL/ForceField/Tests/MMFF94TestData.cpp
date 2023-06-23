/* 
 * MMFF94TestData.cpp
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


#include <string>
#include <cstdlib>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MOL2MoleculeReader.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Util/FileDataReader.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"

#include "MMFF94TestData.hpp"


using namespace CDPL;
using namespace Testing;


MMFF94TestData::MoleculeList      MMFF94TestData::DYN_TEST_MOLECULES;
MMFF94TestData::MoleculeList      MMFF94TestData::STAT_TEST_MOLECULES;

OptimolLogReader MMFF94TestData::DYN_LOG_READER(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94_opti.log"));
OptimolLogReader MMFF94TestData::STAT_LOG_READER(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94s_opti.log"));


namespace
{

    void setupTestMolecule(Chem::Molecule& mol)
    {
        using namespace Chem;
        using namespace ForceField;

        for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
            Atom& atom = *it;

            if (MolProp::isMetal(atom) && !MolProp::isNonMetal(atom))
                setFormalCharge(atom, getMOL2Charge(atom));
        }

        perceiveSSSR(mol, false);
        setRingFlags(mol, false);
        setAromaticityFlags(mol, false);
        calcTopologicalDistanceMatrix(mol, false);
        perceiveMMFF94AromaticRings(mol, false);
        assignMMFF94AtomTypes(mol, true, false);
        assignMMFF94BondTypeIndices(mol, true, false);
    }

    void readTestMolecules(const std::string& fname, MMFF94TestData::MoleculeList& mol_list)
    {
        using namespace Chem;

        Util::FileDataReader<MOL2MoleculeReader> mol_reader(fname);

        while (true) {
            BasicMolecule::SharedPointer mol_ptr(new BasicMolecule());

            if (!mol_reader.read(*mol_ptr))
                return;

            setupTestMolecule(*mol_ptr);
            mol_list.push_back(mol_ptr);
        }
    }

    struct Init
    {

        Init() {
            readTestMolecules(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94_hypervalent.mol2"), MMFF94TestData::DYN_TEST_MOLECULES);
            readTestMolecules(std::getenv("CDPKIT_TEST_DATA_DIR") + std::string("/MMFF94/MMFF94s_hypervalent.mol2"), MMFF94TestData::STAT_TEST_MOLECULES);
        }

    } init;
}
