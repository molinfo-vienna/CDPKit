/* 
 * SMILESMoleculeInputHandlerTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/SMILESMolecularGraphWriter.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Base/DataIOManager.hpp"


BOOST_AUTO_TEST_CASE(SMILESMoleculeInputHandlerTest)
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Base;

    BasicMolecule mol1;
    BasicMolecule mol2;

    const DataInputHandler<Molecule>::SharedPointer handler = DataIOManager<Molecule>::getInputHandlerByFormat(Chem::DataFormat::SMILES);

    BOOST_CHECK(handler);

    BOOST_CHECK(handler->getDataFormat() == Chem::DataFormat::SMILES);

    BOOST_CHECK(DataIOManager<Molecule>::getInputHandlerByName("smiles") == handler);
    BOOST_CHECK(DataIOManager<Molecule>::getInputHandlerByFileExtension("smi") == handler);
    BOOST_CHECK(DataIOManager<Molecule>::getInputHandlerByMimeType("chemical/x-daylight-smiles") == handler);

    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

    BOOST_CHECK(ifs);

    BOOST_CHECK(JMEMoleculeReader(ifs).read(mol1));

    std::ostringstream oss;

    BOOST_CHECK(oss);

    SMILESMolecularGraphWriter writer(oss);

    setSMILESOutputAtomStereoParameter(writer, true);
    setSMILESOutputBondStereoParameter(writer, true);
    setSMILESOutputRingBondStereoParameter(writer, true);
    setSMILESMinStereoBondRingSizeParameter(writer, std::size_t(3));

    makeHydrogenDeplete(mol1);
    perceiveComponents(mol1, true);
    calcImplicitHydrogenCounts(mol1, true);
    perceiveHybridizationStates(mol1, true);
    perceiveSSSR(mol1, true);
    setRingFlags(mol1, true);
    setAromaticityFlags(mol1, true);
    calcCIPPriorities(mol1, true);
    calcAtomCIPConfigurations(mol1, true);
    calcBondCIPConfigurations(mol1, true);
    
    BOOST_CHECK(writer.write(mol1));

    std::istringstream iss(oss.str());

    BOOST_CHECK(iss);

    DataReader<Molecule>::SharedPointer reader_ptr(handler->createReader(iss));

    BOOST_CHECK(reader_ptr);
    BOOST_CHECK(reader_ptr->read(mol2));
    
    perceiveComponents(mol2, false);
    calcImplicitHydrogenCounts(mol2, false);
    perceiveHybridizationStates(mol2, false);
    perceiveSSSR(mol2, false);
    setRingFlags(mol2, false);
    setAromaticityFlags(mol2, false);
    calcCIPPriorities(mol2, false);
    calcAtomCIPConfigurations(mol2, false);
    calcBondCIPConfigurations(mol2, false);
 
    unsigned int atom_flags = AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT
        | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::AROMATICITY;

    unsigned int bond_flags = BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | BondPropertyFlag::AROMATICITY 
        | BondPropertyFlag::CONFIGURATION;

    BOOST_CHECK(calcHashCode(mol1, atom_flags, bond_flags) == calcHashCode(mol2, atom_flags, bond_flags));
}
