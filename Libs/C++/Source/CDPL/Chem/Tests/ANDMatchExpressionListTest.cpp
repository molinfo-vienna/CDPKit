/* 
 * ANDMatchExpressionListTest.cpp 
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

#include "CDPL/Chem/ANDMatchExpressionList.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Base/Any.hpp"


namespace
{

    class TestExpression1 : public CDPL::Chem::MatchExpression<int>
    {

    public:
        bool operator()(const int&, const int&, const CDPL::Base::Any&) const
        {
            return false;
        }

        bool operator()(const int&, const int&, const CDPL::Chem::AtomBondMapping&, const CDPL::Base::Any&) const
        {
            return true;
        }

        bool requiresAtomBondMapping() const
        {
            return true;
        }
    };

    class TestExpression2 : public CDPL::Chem::MatchExpression<int>
    {

    public:
        bool operator()(const int&, const int&, const CDPL::Base::Any&) const
        {
            return true;
        }

        bool operator()(const int&, const int&, const CDPL::Chem::AtomBondMapping&, const CDPL::Base::Any&) const
        {
            return false;
        }

        bool requiresAtomBondMapping() const
        {
            return true;
        }
    };
}


BOOST_AUTO_TEST_CASE(ANDMatchExpressionListTest)
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Base;

    ANDMatchExpressionList<int> lexpr1;

    BOOST_CHECK(lexpr1.getSize() == 0);
    BOOST_CHECK(lexpr1.requiresAtomBondMapping() == false);

    BOOST_CHECK(lexpr1(0, 0, 0) == true);
    BOOST_CHECK(lexpr1(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr1.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr1.getSize() == 1);
    BOOST_CHECK(lexpr1.requiresAtomBondMapping() == false);

    BOOST_CHECK(lexpr1(0, 0, 0) == true);
    BOOST_CHECK(lexpr1(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr1.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr1.getSize() == 2);
    BOOST_CHECK(lexpr1.requiresAtomBondMapping() == false);

    BOOST_CHECK(lexpr1(0, 0, 0) == true);
    BOOST_CHECK(lexpr1(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr1.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr1.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr1.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr1.getSize() == 5);
    BOOST_CHECK(lexpr1.requiresAtomBondMapping() == false);

    BOOST_CHECK(lexpr1(0, 0, 0) == true);
    BOOST_CHECK(lexpr1(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr1.addElement(MatchExpression<int>::SharedPointer(new TestExpression1()));

    BOOST_CHECK(lexpr1.getSize() == 6);
    BOOST_CHECK(lexpr1.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr1(0, 0, 0) == false);
    BOOST_CHECK(lexpr1(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr1.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr1.getSize() == 7);
    BOOST_CHECK(lexpr1.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr1(0, 0, 0) == false);
    BOOST_CHECK(lexpr1(0, 0, AtomBondMapping(), 0) == true);

//-----    

    ANDMatchExpressionList<int> lexpr2;

    lexpr2.addElement(MatchExpression<int>::SharedPointer(new TestExpression1()));

    BOOST_CHECK(lexpr2.getSize() == 1);
    BOOST_CHECK(lexpr2.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr2(0, 0, 0) == false);
    BOOST_CHECK(lexpr2(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr2.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr2.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr2.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr2.getSize() == 4);
    BOOST_CHECK(lexpr2.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr2(0, 0, 0) == false);
    BOOST_CHECK(lexpr2(0, 0, AtomBondMapping(), 0) == true);

//-----    

    ANDMatchExpressionList<int> lexpr3;

    lexpr3.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr3.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr3.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr3.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr3.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr3.getSize() == 5);
    BOOST_CHECK(lexpr3.requiresAtomBondMapping() == false);

    BOOST_CHECK(lexpr3(0, 0, 0) == true);
    BOOST_CHECK(lexpr3(0, 0, AtomBondMapping(), 0) == true);

//-----    

    lexpr3.addElement(MatchExpression<int>::SharedPointer(new TestExpression2()));

    BOOST_CHECK(lexpr3.getSize() == 6);
    BOOST_CHECK(lexpr3.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr3(0, 0, 0) == true);
    BOOST_CHECK(lexpr3(0, 0, AtomBondMapping(), 0) == false);

//-----    

    lexpr3.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr3.getSize() == 7);
    BOOST_CHECK(lexpr3.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr3(0, 0, 0) == true);
    BOOST_CHECK(lexpr3(0, 0, AtomBondMapping(), 0) == false);

//-----    

    ANDMatchExpressionList<int> lexpr4;

    lexpr4.addElement(MatchExpression<int>::SharedPointer(new TestExpression2()));

    BOOST_CHECK(lexpr4.getSize() == 1);
    BOOST_CHECK(lexpr4.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr4(0, 0, 0) == true);
    BOOST_CHECK(lexpr4(0, 0, AtomBondMapping(), 0) == false);

//-----    

    lexpr4.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr4.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));
    lexpr4.addElement(MatchExpression<int>::SharedPointer(new MatchExpression<int>()));

    BOOST_CHECK(lexpr4.getSize() == 4);
    BOOST_CHECK(lexpr4.requiresAtomBondMapping() == true);

    BOOST_CHECK(lexpr4(0, 0, 0) == true);
    BOOST_CHECK(lexpr4(0, 0, AtomBondMapping(), 0) == false);
}
