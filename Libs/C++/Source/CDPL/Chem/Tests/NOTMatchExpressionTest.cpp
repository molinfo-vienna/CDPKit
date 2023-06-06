/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * NOTMatchExpressionTest.cpp 
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

#include "CDPL/Chem/NOTMatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Base/Any.hpp"


namespace
{

	class TestExpression : public CDPL::Chem::MatchExpression<int>
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
}


BOOST_AUTO_TEST_CASE(NOTMatchExpressionTest)
{
	using namespace CDPL;
	using namespace Chem;

	MatchExpression<int>::SharedPointer expr1_ptr(new TestExpression());

	BOOST_CHECK((*expr1_ptr)(1, 2, 3) == false);
	BOOST_CHECK((*expr1_ptr)(3, 4, AtomBondMapping(), 0) == true);
	BOOST_CHECK(expr1_ptr->requiresAtomBondMapping() == true);

	MatchExpression<int>::SharedPointer not_expr1_ptr(new NOTMatchExpression<int>(expr1_ptr));

	BOOST_CHECK((*not_expr1_ptr)(0, 0, 3) == true);
	BOOST_CHECK((*not_expr1_ptr)(12, 0, AtomBondMapping(), 3) == false);
	BOOST_CHECK(not_expr1_ptr->requiresAtomBondMapping() == true);

	NOTMatchExpression<int> not_expr2(not_expr1_ptr);

	BOOST_CHECK(not_expr2(4, 3, 0) == false);
	BOOST_CHECK(not_expr2(10, 2, AtomBondMapping(), 13) == true);
	BOOST_CHECK(not_expr2.requiresAtomBondMapping() == true);

//-----

	MatchExpression<int>::SharedPointer expr2_ptr(new MatchExpression<int>());

	BOOST_CHECK((*expr2_ptr)(0, 0, 0) == true);
	BOOST_CHECK((*expr2_ptr)(0, 0, AtomBondMapping(), 0) == true);
	BOOST_CHECK(expr2_ptr->requiresAtomBondMapping() == false);

	NOTMatchExpression<int> not_expr3(expr2_ptr);

	BOOST_CHECK(not_expr3(7, 6, 5) == false);
	BOOST_CHECK(not_expr3(10, 9, AtomBondMapping(), 8) == false);
	BOOST_CHECK(not_expr3.requiresAtomBondMapping() == false);
}
