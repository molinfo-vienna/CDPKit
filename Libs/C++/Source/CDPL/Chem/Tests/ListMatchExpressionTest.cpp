/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatchExpressionListTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/MatchExpressionList.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	class TestExpression1 : public CDPL::Chem::MatchExpression<int>
	{

	public:
		bool requiresAtomBondMapping() const
		{
			return true;
		}
	};

	class TestExpression2 : public CDPL::Chem::MatchExpression<int>
	{

	public:

		bool requiresAtomBondMapping() const
		{
			return false;
		}
	};
}


BOOST_AUTO_TEST_CASE(MatchExpressionListTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	MatchExpressionList<int> lexpr1;

	BOOST_CHECK(lexpr1.isEmpty());

	BOOST_CHECK(lexpr1.getSize() == 0);

	BOOST_CHECK(!lexpr1.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() == 
				const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() == 
				const_cast<MatchExpressionList<int>&>(lexpr1).getElementsEnd());

	BOOST_CHECK_THROW(lexpr1.getElement(0), IndexError);
	BOOST_CHECK_THROW(lexpr1.getElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr1.getBase().getElement(0), IndexError);
	BOOST_CHECK_THROW(lexpr1.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(0), IndexError);
	BOOST_CHECK_THROW(lexpr1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin()), RangeError);
	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin() + 1), RangeError);

//-----

	MatchExpression<int>::SharedPointer sub_expr1_ptr(new TestExpression2());

	lexpr1.addElement(sub_expr1_ptr);

	BOOST_CHECK(!lexpr1.isEmpty());

	BOOST_CHECK(lexpr1.getSize() == 1);

	BOOST_CHECK(!lexpr1.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 1 ==
				const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 1 == 
				const_cast<MatchExpressionList<int>&>(lexpr1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&lexpr1.getElement(0) == sub_expr1_ptr.get());

	BOOST_CHECK_THROW(lexpr1.getElement(1), IndexError);
	BOOST_CHECK_THROW(lexpr1.getElement(2), IndexError);

	BOOST_CHECK(lexpr1.getBase().getElement(0) == sub_expr1_ptr);

	BOOST_CHECK_THROW(lexpr1.getBase().getElement(1), IndexError);
	BOOST_CHECK_THROW(lexpr1.getBase().getElement(2), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(1), IndexError);
	BOOST_CHECK_THROW(lexpr1.removeElement(2), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin() + 1), RangeError);
	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsEnd()), RangeError);

//-----

	MatchExpression<int>::SharedPointer sub_expr2_ptr(new TestExpression2());

	lexpr1.addElement(sub_expr2_ptr);

	BOOST_CHECK(!lexpr1.isEmpty());

	BOOST_CHECK(lexpr1.getSize() == 2);

	BOOST_CHECK(!lexpr1.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 2 ==
				const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 2 == 
				const_cast<MatchExpressionList<int>&>(lexpr1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 1) == sub_expr2_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 1) == sub_expr2_ptr.get());

	BOOST_CHECK(&lexpr1.getElement(0) == sub_expr1_ptr.get());
	BOOST_CHECK(&lexpr1.getElement(1) == sub_expr2_ptr.get());

	BOOST_CHECK_THROW(lexpr1.getElement(2), IndexError);
	BOOST_CHECK_THROW(lexpr1.getElement(3), IndexError);

	BOOST_CHECK(lexpr1.getBase().getElement(0) == sub_expr1_ptr);
	BOOST_CHECK(lexpr1.getBase().getElement(1) == sub_expr2_ptr);

	BOOST_CHECK_THROW(lexpr1.getBase().getElement(2), IndexError);
	BOOST_CHECK_THROW(lexpr1.getBase().getElement(3), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(2), IndexError);
	BOOST_CHECK_THROW(lexpr1.removeElement(3), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin() + 2), RangeError);
	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsEnd()), RangeError);

//-----

	MatchExpression<int>::SharedPointer sub_expr3_ptr(new TestExpression1());

	lexpr1.addElement(sub_expr3_ptr);

	BOOST_CHECK(!lexpr1.isEmpty());

	BOOST_CHECK(lexpr1.getSize() == 3);

	BOOST_CHECK(lexpr1.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 3 ==
				const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 3 == 
				const_cast<MatchExpressionList<int>&>(lexpr1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 1) == sub_expr2_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 1) == sub_expr2_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 2) == sub_expr3_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() + 2) == sub_expr3_ptr.get());

	BOOST_CHECK(&lexpr1.getElement(0) == sub_expr1_ptr.get());
	BOOST_CHECK(&lexpr1.getElement(1) == sub_expr2_ptr.get());
	BOOST_CHECK(&lexpr1.getElement(2) == sub_expr3_ptr.get());

	BOOST_CHECK_THROW(lexpr1.getElement(3), IndexError);
	BOOST_CHECK_THROW(lexpr1.getElement(4), IndexError);

	BOOST_CHECK(lexpr1.getBase().getElement(0) == sub_expr1_ptr);
	BOOST_CHECK(lexpr1.getBase().getElement(1) == sub_expr2_ptr);
	BOOST_CHECK(lexpr1.getBase().getElement(2) == sub_expr3_ptr);

	BOOST_CHECK_THROW(lexpr1.getBase().getElement(3), IndexError);
	BOOST_CHECK_THROW(lexpr1.getBase().getElement(4), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(3), IndexError);
	BOOST_CHECK_THROW(lexpr1.removeElement(4), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin() + 3), RangeError);
	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsEnd()), RangeError);

//-----

	MatchExpressionList<int> lexpr2(lexpr1);

	lexpr2.addElement(sub_expr3_ptr);

	BOOST_CHECK(!lexpr2.isEmpty());

	BOOST_CHECK(lexpr2.getSize() == 4);

	BOOST_CHECK(lexpr2.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 4 ==
				const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 4 == 
				const_cast<MatchExpressionList<int>&>(lexpr2).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1) == sub_expr2_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1) == sub_expr2_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 2) == sub_expr3_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 2) == sub_expr3_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 3) == sub_expr3_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 3) == sub_expr3_ptr.get());

	BOOST_CHECK(&lexpr2.getElement(0) == sub_expr1_ptr.get());
	BOOST_CHECK(&lexpr2.getElement(1) == sub_expr2_ptr.get());
	BOOST_CHECK(&lexpr2.getElement(2) == sub_expr3_ptr.get());
	BOOST_CHECK(&lexpr2.getElement(3) == sub_expr3_ptr.get());

	BOOST_CHECK_THROW(lexpr2.getElement(4), IndexError);

	BOOST_CHECK(lexpr2.getBase().getElement(0) == sub_expr1_ptr);
	BOOST_CHECK(lexpr2.getBase().getElement(1) == sub_expr2_ptr);
	BOOST_CHECK(lexpr2.getBase().getElement(2) == sub_expr3_ptr);
	BOOST_CHECK(lexpr2.getBase().getElement(3) == sub_expr3_ptr);

	BOOST_CHECK_THROW(lexpr2.getBase().getElement(4), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(4), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(lexpr2.getElementsEnd()), RangeError);

//-----

	lexpr2.removeElement(2);

	BOOST_CHECK(!lexpr2.isEmpty());

	BOOST_CHECK(lexpr2.getSize() == 3);

	BOOST_CHECK(lexpr2.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 3 ==
				const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 3 == 
				const_cast<MatchExpressionList<int>&>(lexpr2).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1) == sub_expr2_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1) == sub_expr2_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 2) == sub_expr3_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 2) == sub_expr3_ptr.get());

	BOOST_CHECK(&lexpr2.getElement(0) == sub_expr1_ptr.get());
	BOOST_CHECK(&lexpr2.getElement(1) == sub_expr2_ptr.get());
	BOOST_CHECK(&lexpr2.getElement(2) == sub_expr3_ptr.get());

	BOOST_CHECK_THROW(lexpr2.getElement(3), IndexError);

	BOOST_CHECK(lexpr2.getBase().getElement(0) == sub_expr1_ptr);
	BOOST_CHECK(lexpr2.getBase().getElement(1) == sub_expr2_ptr);
	BOOST_CHECK(lexpr2.getBase().getElement(2) == sub_expr3_ptr);

	BOOST_CHECK_THROW(lexpr2.getBase().getElement(3), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(3), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(lexpr2.getElementsEnd()), RangeError);

//-----

	MatchExpressionList<int>::ElementIterator it = lexpr2.removeElement(--lexpr2.getElementsEnd());

	BOOST_CHECK(it == lexpr2.getElementsEnd());

	BOOST_CHECK(!lexpr2.isEmpty());

	BOOST_CHECK(lexpr2.getSize() == 2);

	BOOST_CHECK(!lexpr2.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 2 ==
				const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 2 == 
				const_cast<MatchExpressionList<int>&>(lexpr2).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&*(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1) == sub_expr2_ptr.get());
	BOOST_CHECK(&*(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1) == sub_expr2_ptr.get());

	BOOST_CHECK(&lexpr2.getElement(0) == sub_expr1_ptr.get());
	BOOST_CHECK(&lexpr2.getElement(1) == sub_expr2_ptr.get());

	BOOST_CHECK_THROW(lexpr2.getElement(2), IndexError);

	BOOST_CHECK(lexpr2.getBase().getElement(0) == sub_expr1_ptr);
	BOOST_CHECK(lexpr2.getBase().getElement(1) == sub_expr2_ptr);

	BOOST_CHECK_THROW(lexpr2.getBase().getElement(2), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(2), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(lexpr2.getElementsEnd()), RangeError);

//-----

	lexpr2.removeElement(1);

	BOOST_CHECK(!lexpr2.isEmpty());

	BOOST_CHECK(lexpr2.getSize() == 1);

	BOOST_CHECK(!lexpr2.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1 ==
				const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() + 1 == 
				const_cast<MatchExpressionList<int>&>(lexpr2).getElementsEnd());

	BOOST_CHECK(&*const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());
	BOOST_CHECK(&*const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() == sub_expr1_ptr.get());

	BOOST_CHECK(&lexpr2.getElement(0) == sub_expr1_ptr.get());

	BOOST_CHECK_THROW(lexpr2.getElement(1), IndexError);

	BOOST_CHECK(lexpr2.getBase().getElement(0) == sub_expr1_ptr);

	BOOST_CHECK_THROW(lexpr2.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(lexpr2.getElementsEnd()), RangeError);

//-----

	it = lexpr2.removeElement(lexpr2.getElementsBegin());

	BOOST_CHECK(it == lexpr2.getElementsBegin());
	BOOST_CHECK(it == lexpr2.getElementsEnd());

	BOOST_CHECK(lexpr2.isEmpty());

	BOOST_CHECK(lexpr2.getSize() == 0);

	BOOST_CHECK(!lexpr2.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsBegin()  ==
				const_cast<const MatchExpressionList<int>&>(lexpr2).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr2).getElementsBegin() == 
				const_cast<MatchExpressionList<int>&>(lexpr2).getElementsEnd());

	BOOST_CHECK_THROW(lexpr2.getElement(0), IndexError);

	BOOST_CHECK_THROW(lexpr2.getBase().getElement(0), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(0), IndexError);

	BOOST_CHECK_THROW(lexpr2.removeElement(lexpr2.getElementsBegin()), RangeError);

//-----

	lexpr1.clear();

	BOOST_CHECK(lexpr1.isEmpty());

	BOOST_CHECK(lexpr1.getSize() == 0);

	BOOST_CHECK(!lexpr1.requiresAtomBondMapping());

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() == 
				const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsEnd());
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() == 
				const_cast<MatchExpressionList<int>&>(lexpr1).getElementsEnd());

	BOOST_CHECK_THROW(lexpr1.getElement(0), IndexError);
	BOOST_CHECK_THROW(lexpr1.getElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr1.getBase().getElement(0), IndexError);
	BOOST_CHECK_THROW(lexpr1.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(0), IndexError);
	BOOST_CHECK_THROW(lexpr1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin()), RangeError);
	BOOST_CHECK_THROW(lexpr1.removeElement(lexpr1.getElementsBegin() + 1), RangeError);

//-----

	BOOST_CHECK(lexpr1.getSize() == 0);

	lexpr1.addElement(sub_expr1_ptr);
	lexpr1.addElement(sub_expr1_ptr);
	lexpr1.addElement(sub_expr1_ptr);
	lexpr1.addElement(sub_expr1_ptr);

	BOOST_CHECK(lexpr1.getSize() == 4);

	BOOST_CHECK(const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsEnd() - 
				const_cast<const MatchExpressionList<int>&>(lexpr1).getElementsBegin() == 4);
	BOOST_CHECK(const_cast<MatchExpressionList<int>&>(lexpr1).getElementsEnd() - 
				const_cast<MatchExpressionList<int>&>(lexpr1).getElementsBegin() == 4);

	it = lexpr1.removeElement(lexpr1.getElementsBegin());

	BOOST_CHECK(it == lexpr1.getElementsBegin());

	it = lexpr1.removeElement(lexpr1.getElementsBegin() + 1);

	BOOST_CHECK(it == lexpr1.getElementsBegin() + 1);

	it = lexpr1.removeElement(--lexpr1.getElementsEnd());

	BOOST_CHECK(it == lexpr1.getElementsEnd());

	it = lexpr1.removeElement(lexpr1.getElementsBegin());

	BOOST_CHECK(it == lexpr1.getElementsEnd());
}

