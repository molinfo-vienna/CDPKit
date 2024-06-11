/* 
 * ExtendedSSSRTest.cpp 
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


#include <vector>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/ExtendedSSSR.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


namespace
{

    struct TestDataEntry
    {

        std::string              smiles;
        std::vector<std::size_t> ringSizes;
    };

    TestDataEntry TEST_DATA[] = {
        { "C1C2C1C2", { 3, 3, 4 } },
        { "C12C3C4C1C5C2C3C45", { 4, 4, 4, 4, 4, 4 } },
        { "C1CC2C3C2C3C1", { 3, 3, 6, 6 } },
        { "C1=CC=C2C=CC=CC2=C1", {  6, 6, 10 } },
        { "C1CCCC2CCN3CCCC(C3O2)(CCCCCCC4CCN5CCCC(C5O4)CC1)O", { 6, 6, 6, 6, 10, 10, 20, 22, 22, 24, 24 } },
        { "CN1CCC2=CC(=C3C=C2C1CC4=CC=C(C=C4)OC5=C6C(CC7=CC(=C(C=C7)O)O3)[N+](CCC6=CC(=C5O)OC)(C)C)OC", { 6, 6, 6, 6, 6, 6, 10, 10, 18, 18, 20, 20, 22, 22, 22  } },
        { "C1C=NC2=C1N=CC=C2", { 5, 6, 9  } },
        { "C1C2C(C(C(O2)NC3=C4C(=NC=N3)N(C5C(C(C(O5)COP(=O)(O1)OP(=O)(O)O)O)O)C(=N4)N)O)O", { 5, 5, 5, 6, 9, 16, 17, 17, 17, 18  } }
    };
} // namespace


BOOST_AUTO_TEST_CASE(ExtendedSSSRTest)
{
    using namespace CDPL;
    using namespace Chem;

    ExtendedSSSR esssr;
    BasicMolecule mol;
    
    for (auto& test_data : TEST_DATA) {
        BOOST_CHECK(parseSMILES(test_data.smiles, mol));

        calcBasicProperties(mol, false);

        esssr.perceive(mol);

        BOOST_CHECK(test_data.ringSizes.size() == esssr.getSize());

        for (std::size_t i = 0, num_rings = esssr.getSize(); i < num_rings; i++)
            BOOST_CHECK(test_data.ringSizes[i] == esssr[i].getNumBonds());
    }
}
