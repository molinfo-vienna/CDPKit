/* 
 * MatchExpressionTest.cpp 
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

#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
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
            return false;
        }

        bool operator()(const int&, const int&, const CDPL::Chem::AtomBondMapping&,
                        const CDPL::Base::Any&) const
        {
            return true;
        }

        bool requiresAtomBondMapping() const
        {
            return true;
        }
    };
} // namespace


BOOST_AUTO_TEST_CASE(MatchExpressionTest)
{
    using namespace CDPL;
    using namespace Chem;

    MatchExpression<int> expr1;

    BOOST_CHECK(expr1.requiresAtomBondMapping() == false);

    BOOST_CHECK(expr1(1, 2, 0) == true);
    BOOST_CHECK(expr1(3, 4, Base::Any()) == true);
    BOOST_CHECK(expr1(5, 6, AtomBondMapping(), 0) == true);
    BOOST_CHECK(expr1(7, 8, AtomBondMapping(), Base::Any()) == true);

//-----

    TestExpression1 test_expr1;
    MatchExpression<int>& expr2 = test_expr1;

    BOOST_CHECK(expr2.requiresAtomBondMapping() == true);

    BOOST_CHECK(expr2(0, 0, 0) == false);
    BOOST_CHECK(expr2(0, 0, Base::Any()) == false);
    BOOST_CHECK(expr2(0, 0, AtomBondMapping(), 0) == false);
    BOOST_CHECK(expr2(0, 0, AtomBondMapping(), Base::Any()) == false);

//-----

    TestExpression2 test_expr2;
    MatchExpression<int>& expr3 = test_expr2;

    BOOST_CHECK(expr3.requiresAtomBondMapping() == true);

    BOOST_CHECK(expr3(1, 1, 0) == false);
    BOOST_CHECK(expr3(0, 0, Base::Any()) == false);
    BOOST_CHECK(expr3(2, 3, AtomBondMapping(), 4) == true);
    BOOST_CHECK(expr3(0, 1, AtomBondMapping(), Base::Any()) == true);

}

