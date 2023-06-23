/* 
 * MolecularGraphTotalMassCompositionStringTest.cpp 
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
#include <locale>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/AtomProperties.hpp"
#include "CDPL/Chem/AtomTypes.hpp"

#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MolecularGraphTotalMassCompositionStringTest)
{
    using namespace CDPL;
    using namespace Chem;

    std::locale::global(std::locale::classic());

    Molecule mol;

//-----

    BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == "");

    BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

    BOOST_CHECK(ifs);

    BOOST_CHECK(JMEMoleculeReader(ifs).read(mol));

    BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == 
                "H: 6.712% C: 71.558% N: 4.909% O: 16.822%");

    BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

    mol.getAtom(0).setProperty(AtomProperty::TYPE, AtomType::N);

    BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == 
                "H: 6.665% C: 66.881% N: 9.749% O: 16.705%");

    BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

    mol.getAtom(1).setProperty(AtomProperty::TYPE, AtomType::MAX_ATOMIC_NO + 1);

    BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == 
                "?: 0.000% H: 6.956% C: 65.436% N: 10.175% O: 17.433%");

    BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

    mol.getAtom(2).setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

    BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == 
                "?: 0.000% H: 6.917% C: 64.105% N: 10.680% O: 18.299%");

    BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

    for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it)
        it->setProperty(AtomProperty::TYPE, AtomType::UNKNOWN);

    BOOST_CHECK(mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

    BOOST_CHECK(mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == 
                "?: nan%" ||
                mol.getProperty<std::string>(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING) == 
                "?: -nan%");

    BOOST_CHECK(!mol.getProperty(MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, false, false).isEmpty());

//-----

    TestUtils::checkDependency(mol, MolecularGraphProperty::TOTAL_MASS_COMPOSITION_STRING, mol,
                               MolecularGraphProperty::TOTAL_MASS_COMPOSITION);
}
