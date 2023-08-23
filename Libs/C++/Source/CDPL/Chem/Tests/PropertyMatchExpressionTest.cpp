/* 
 * PropertyMatchExpressionTest.cpp 
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
#include <functional>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/PropertyMatchExpression.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Base/PropertyManager.hpp"
#include "CDPL/Base/PropertyKey.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(PropertyMatchExpressionTest)
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Base;
    using namespace std::placeholders;
    
    PropertyKey key1 = PropertyManager::allocPropertyKey("key1");

    Molecule mol1, mol2;

//-----

    PropertyMatchExpression<std::string, std::equal_to<std::string>, Molecule, int> expr1("test", key1);

    BOOST_CHECK(!expr1.requiresAtomBondMapping());

    BOOST_CHECK_THROW(expr1(mol1, 0, mol2, 0, 0), CalculationFailed);
    BOOST_CHECK_THROW((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol1, 0, mol2, 0, AtomBondMapping(), 0)), CalculationFailed);

    mol1.setProperty(key1, std::string("test"));
    mol2.setProperty(key1, std::string("te434st"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 0, 0) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 1, mol1, 0, AtomBondMapping(), 0) == true));

    mol1.setProperty(key1, std::string("test2"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 1, Any()) == false);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 10, AtomBondMapping(), 0) == false));

//-----

    expr1 = PropertyMatchExpression<std::string, std::equal_to<std::string>, Molecule, int>(key1);

    mol2.setProperty(key1, std::string("test"));
    mol1.removeProperty(key1);

    BOOST_CHECK(!expr1.requiresAtomBondMapping());

    BOOST_CHECK_THROW(expr1(mol1, 0, mol2, 0, 0), CalculationFailed);
    BOOST_CHECK_THROW((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol1, 0, mol2, 0, AtomBondMapping(), 0)), CalculationFailed);

    mol1.setProperty(key1, std::string("test"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 0, 0) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 1, mol1, 0, AtomBondMapping(), 0) == true));

    BOOST_CHECK(expr1(mol1, 0, mol2, 0, 0) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol1, 1, mol2, 0, AtomBondMapping(), 0) == true));

    mol1.setProperty(key1, std::string("test2"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 1, Any()) == false);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 10, AtomBondMapping(), 0) == false));

    mol2.setProperty(key1, std::string("test2"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 1, Any()) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 10, AtomBondMapping(), 0) == true));

//-----

    expr1 =    PropertyMatchExpression<std::string, std::equal_to<std::string>, Molecule, int>("test", 
                                                                                             std::bind(std::bind(&MolecularGraph::getProperty<std::string>, 
                                                                                                                 _1, std::ref(key1), true), _1, _2));
    mol1.removeProperty(key1);
    mol2.removeProperty(key1);

    BOOST_CHECK(!expr1.requiresAtomBondMapping());

    BOOST_CHECK_THROW(expr1(mol1, 0, mol2, 0, 0), CalculationFailed);
    BOOST_CHECK_THROW((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol1, 0, mol2, 0, AtomBondMapping(), 0)), CalculationFailed);

    BOOST_CHECK_THROW(expr1(mol2, 0, mol1, 0, 0), CalculationFailed);
    BOOST_CHECK_THROW((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 0, AtomBondMapping(), 0)), CalculationFailed);

    mol1.setProperty(key1, std::string("test"));
    mol2.setProperty(key1, std::string("te12st"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 0, 0) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 1, mol1, 0, AtomBondMapping(), 0) == true));

    mol1.setProperty(key1, std::string("test2"));
    mol2.setProperty(key1, std::string("tet"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 1, Any()) == false);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 10, AtomBondMapping(), 0) == false));

//-----

    expr1 = PropertyMatchExpression<std::string, std::equal_to<std::string>, Molecule, int>(std::bind(std::bind(&MolecularGraph::getProperty<std::string>, 
                                                                                                                _1, std::ref(key1), true), _1, _2));

    mol2.setProperty(key1, std::string("testx"));
    mol1.removeProperty(key1);

    BOOST_CHECK(!expr1.requiresAtomBondMapping());

    BOOST_CHECK_THROW(expr1(mol1, 0, mol2, 0, 0), CalculationFailed);
    BOOST_CHECK_THROW((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol1, 0, mol2, 0, AtomBondMapping(), 0)), CalculationFailed);

    mol1.setProperty(key1, std::string("testx"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 0, 0) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 1, mol1, 0, AtomBondMapping(), 0) == true));

    BOOST_CHECK(expr1(mol1, 0, mol2, 0, 0) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol1, 1, mol2, 0, AtomBondMapping(), 0) == true));

    mol1.setProperty(key1, std::string("test2"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 1, Any()) == false);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 10, AtomBondMapping(), 0) == false));

    mol2.setProperty(key1, std::string("test2"));

    BOOST_CHECK(expr1(mol2, 0, mol1, 1, Any()) == true);
    BOOST_CHECK((static_cast<const MatchExpression<Molecule, int>&>(expr1)(mol2, 0, mol1, 10, AtomBondMapping(), 0) == true));

//-----------------------

    PropertyMatchExpression<std::size_t, std::less<std::size_t>, Molecule> expr2(5, key1);

    BOOST_CHECK_THROW(expr2(mol2, mol1, 0), BadCast);
    BOOST_CHECK_THROW(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0), BadCast);

    mol1.setProperty(key1, std::size_t(5));
    mol2.setProperty(key1, std::size_t(2));

    BOOST_CHECK(expr2(mol2, mol1, 0) == false);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), Any()) == false);

    mol1.setProperty(key1, std::size_t(4));
    mol2.setProperty(key1, std::size_t(17));

    BOOST_CHECK(expr2(mol2, mol1, 0) == true);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0) == true);

//-----

    expr2 = PropertyMatchExpression<std::size_t, std::less<std::size_t>, Molecule>(5, std::bind(std::bind(&MolecularGraph::getProperty<std::size_t>, 
                                                                                                          _1, std::ref(key1), true), _1));

    mol1.removeProperty(key1);
    mol2.removeProperty(key1);

    BOOST_CHECK_THROW(expr2(mol2, mol1, 0), CalculationFailed);
    BOOST_CHECK_THROW(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0), CalculationFailed);

    BOOST_CHECK_THROW(expr2(mol1, mol2, 0), CalculationFailed);
    BOOST_CHECK_THROW(static_cast<const MatchExpression<Molecule>&>(expr2)(mol1, mol2, AtomBondMapping(), 0), CalculationFailed);

    mol1.setProperty(key1, std::size_t(5));
    mol2.setProperty(key1, std::size_t(17));

    BOOST_CHECK(expr2(mol2, mol1, 0) == false);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), Any()) == false);

    mol1.setProperty(key1, std::size_t(4));
    mol2.setProperty(key1, std::size_t(7));

    BOOST_CHECK(expr2(mol2, mol1, 0) == true);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0) == true);

//-----

    expr2 = PropertyMatchExpression<std::size_t, std::less<std::size_t>, Molecule>(key1);

    mol1.removeProperty(key1);
    mol2.setProperty(key1, std::size_t(5));

    BOOST_CHECK_THROW(expr2(mol2, mol1, 0), CalculationFailed);
    BOOST_CHECK_THROW(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0), CalculationFailed);

    mol1.setProperty(key1, std::size_t(5));

    BOOST_CHECK(expr2(mol2, mol1, 0) == false);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), Any()) == false);

    mol1.setProperty(key1, std::size_t(4));

    BOOST_CHECK(expr2(mol2, mol1, 0) == true);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), Any()) == true);

    mol1.setProperty(key1, std::size_t(6));

    BOOST_CHECK(expr2(mol2, mol1, 0) == false);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0) == false);

    mol1.setProperty(key1, std::size_t(4));

    BOOST_CHECK(expr2(mol1, mol2, 0) == false);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol1, mol2, AtomBondMapping(), 0) == false);

//-----

    expr2 = PropertyMatchExpression<std::size_t, std::less<std::size_t>, Molecule>(std::bind(std::bind(&MolecularGraph::getProperty<std::size_t>, 
                                                                                                       _1, std::ref(key1), true), _1));

    mol1.removeProperty(key1);
    mol2.setProperty(key1, std::size_t(6));

    BOOST_CHECK_THROW(expr2(mol2, mol1, 0), CalculationFailed);
    BOOST_CHECK_THROW(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0), CalculationFailed);

    mol1.setProperty(key1, std::size_t(5));

    BOOST_CHECK(expr2(mol2, mol1, 0) == true);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), Any()) == true);

    mol1.setProperty(key1, std::size_t(4));

    BOOST_CHECK(expr2(mol2, mol1, 0) == true);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), Any()) == true);

    mol1.setProperty(key1, std::size_t(7));

    BOOST_CHECK(expr2(mol2, mol1, 0) == false);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol2, mol1, AtomBondMapping(), 0) == false);

    mol1.setProperty(key1, std::size_t(4));
    mol2.setProperty(key1, std::size_t(3));

    BOOST_CHECK(expr2(mol1, mol2, 0) == true);
    BOOST_CHECK(static_cast<const MatchExpression<Molecule>&>(expr2)(mol1, mol2, AtomBondMapping(), 0) == true);
}
