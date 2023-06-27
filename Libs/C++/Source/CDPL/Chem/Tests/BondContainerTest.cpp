/* 
 * BondContainerTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"


BOOST_AUTO_TEST_CASE(BondContainerTest)
{
    using namespace CDPL;
    using namespace Chem;

    BasicMolecule mol;
    BondContainer& cntnr = mol;
    
    mol.addAtom();
    mol.addAtom();
    mol.addAtom();

    BOOST_CHECK(cntnr.getNumBonds() == 0);

    BOOST_CHECK(cntnr.getBondsBegin() == cntnr.getBondsEnd());

    BOOST_CHECK((cntnr.getBondsEnd() - cntnr.getBondsBegin()) == 0);

//-----

    Bond& bond1 = mol.addBond(0, 1);

    BOOST_CHECK(cntnr.getNumBonds() == 1);

    BOOST_CHECK(cntnr.getBondsBegin() != cntnr.getBondsEnd());

    BOOST_CHECK((cntnr.getBondsEnd() - cntnr.getBondsBegin()) == 1);

    BOOST_CHECK((cntnr.getBondsBegin() + 1) == cntnr.getBondsEnd());

    BOOST_CHECK(&*cntnr.getBondsBegin() == &bond1);

//-----

    Bond& bond2 = mol.addBond(0, 2);

    BOOST_CHECK(cntnr.getNumBonds() == 2);

    BOOST_CHECK(cntnr.getBondsBegin() != cntnr.getBondsEnd());

    BOOST_CHECK((cntnr.getBondsEnd() - cntnr.getBondsBegin()) == 2);

    BOOST_CHECK((cntnr.getBondsBegin() + 1) != cntnr.getBondsEnd());
    BOOST_CHECK((cntnr.getBondsBegin() + 2) == cntnr.getBondsEnd());

    BOOST_CHECK(&*cntnr.getBondsBegin() == &bond1);
    BOOST_CHECK(&*(cntnr.getBondsBegin() + 1) == &bond2);
}
