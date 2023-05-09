/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentListTest.cpp 
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


#include <functional>

#include <boost/bind.hpp>
#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/AddressOf.hpp"


BOOST_AUTO_TEST_CASE(FragmentListTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	Fragment::SharedPointer fptr1(new Fragment());
	Fragment::SharedPointer fptr2(new Fragment());
	Fragment::SharedPointer fptr3(new Fragment());
	Fragment::SharedPointer fptr4(new Fragment());
	Fragment::SharedPointer fptr5(new Fragment());

	FragmentList flist1;

//-----

	BOOST_CHECK(flist1.getSize() == 0);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() == const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() == const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 0);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 0);

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(0), IndexError);

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.getBase().getElement(0), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(0), IndexError);
	BOOST_CHECK_THROW(flist1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin()), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 1), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	flist1.addElement(fptr1);

	BOOST_CHECK(flist1.getSize() == 1);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() != const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() != const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 1);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 1);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist1).getElementsBegin() == fptr1.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist1).getElementsBegin() == fptr1.get());

	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(0) == fptr1.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(0) == fptr1.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(1), IndexError);

	BOOST_CHECK(flist1.getBase().getElement(0) == fptr1);
	BOOST_CHECK_THROW(flist1.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 1), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	flist1.addElement(fptr2);
	flist1.addElement(fptr3);
	flist1.addElement(fptr4);
	flist1.addElement(fptr5);

	BOOST_CHECK(flist1.getSize() == 5);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() != const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() != const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 5);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 5);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist1).getElementsBegin() == fptr1.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist1).getElementsBegin() == fptr1.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 1) == fptr2.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 1) == fptr2.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 2) == fptr3.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 2) == fptr3.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 3) == fptr4.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 3) == fptr4.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 4) == fptr5.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 4) == fptr5.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsBegin() + 5) == const_cast<FragmentList&>(flist1).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsBegin() + 5) == const_cast<const FragmentList&>(flist1).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(0) == fptr1.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(0) == fptr1.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(1) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(1) == fptr2.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(2) == fptr3.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(2) == fptr3.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(3) == fptr4.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(3) == fptr4.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(4) == fptr5.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(4) == fptr5.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(5), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(5), IndexError);

	BOOST_CHECK(flist1.getBase().getElement(0) == fptr1);
	BOOST_CHECK(flist1.getBase().getElement(1) == fptr2);
	BOOST_CHECK(flist1.getBase().getElement(2) == fptr3);
	BOOST_CHECK(flist1.getBase().getElement(3) == fptr4);
	BOOST_CHECK(flist1.getBase().getElement(4) == fptr5);
	BOOST_CHECK_THROW(flist1.getBase().getElement(5), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(6), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 5), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	FragmentList flist2;

	flist2.addElement(fptr2);
	flist2.addElement(fptr1);
	flist2.addElement(fptr4);

	BOOST_CHECK(flist2.getSize() == 3);

	BOOST_CHECK(const_cast<FragmentList&>(flist2).getElementsEnd() != const_cast<FragmentList&>(flist2).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist2).getElementsEnd() != const_cast<const FragmentList&>(flist2).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist2).getElementsEnd() - const_cast<FragmentList&>(flist2).getElementsBegin()) == 3);
	BOOST_CHECK((const_cast<const FragmentList&>(flist2).getElementsEnd() - const_cast<const FragmentList&>(flist2).getElementsBegin()) == 3);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist2).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist2).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist2).getElementsBegin() + 1) == fptr1.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist2).getElementsBegin() + 1) == fptr1.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist2).getElementsBegin() + 2) == fptr4.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist2).getElementsBegin() + 2) == fptr4.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist2).getElementsBegin() + 3) == const_cast<FragmentList&>(flist2).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist2).getElementsBegin() + 3) == const_cast<const FragmentList&>(flist2).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist2).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist2).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist2).getElement(1) == fptr1.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist2).getElement(1) == fptr1.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist2).getElement(2) == fptr4.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist2).getElement(2) == fptr4.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist2).getElement(3), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist2).getElement(3), IndexError);

	BOOST_CHECK(flist2.getBase().getElement(0) == fptr2);
	BOOST_CHECK(flist2.getBase().getElement(1) == fptr1);
	BOOST_CHECK(flist2.getBase().getElement(2) == fptr4);
	BOOST_CHECK_THROW(flist2.getBase().getElement(3), IndexError);

//-----

	flist1.removeElement(0);

	BOOST_CHECK(flist1.getSize() == 4);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() != const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() != const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 4);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 4);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 1) == fptr3.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 1) == fptr3.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 2) == fptr4.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 2) == fptr4.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 3) == fptr5.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 3) == fptr5.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsBegin() + 4) == const_cast<FragmentList&>(flist1).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsBegin() + 4) == const_cast<const FragmentList&>(flist1).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(1) == fptr3.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(1) == fptr3.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(2) == fptr4.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(2) == fptr4.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(3) == fptr5.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(3) == fptr5.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(4), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(4), IndexError);

	BOOST_CHECK(flist1.getBase().getElement(0) == fptr2);
	BOOST_CHECK(flist1.getBase().getElement(1) == fptr3);
	BOOST_CHECK(flist1.getBase().getElement(2) == fptr4);
	BOOST_CHECK(flist1.getBase().getElement(3) == fptr5);
	BOOST_CHECK_THROW(flist1.getBase().getElement(4), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(5), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(4), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 4), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	flist1.removeElement(3);

	BOOST_CHECK(flist1.getSize() == 3);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() != const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() != const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 3);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 3);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 1) == fptr3.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 1) == fptr3.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 2) == fptr4.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 2) == fptr4.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsBegin() + 3) == const_cast<FragmentList&>(flist1).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsBegin() + 3) == const_cast<const FragmentList&>(flist1).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(1) == fptr3.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(1) == fptr3.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(2) == fptr4.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(2) == fptr4.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(3), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(3), IndexError);

	BOOST_CHECK(flist1.getBase().getElement(0) == fptr2);
	BOOST_CHECK(flist1.getBase().getElement(1) == fptr3);
	BOOST_CHECK(flist1.getBase().getElement(2) == fptr4);
	BOOST_CHECK_THROW(flist1.getBase().getElement(3), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(4), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(5), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(3), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 3), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	flist1.removeElement(1);

	BOOST_CHECK(flist1.getSize() == 2);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() != const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() != const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 2);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 2);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist1).getElementsBegin() + 1) == fptr4.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist1).getElementsBegin() + 1) == fptr4.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsBegin() + 2) == const_cast<FragmentList&>(flist1).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsBegin() + 2) == const_cast<const FragmentList&>(flist1).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(1) == fptr4.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(1) == fptr4.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(2), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(2), IndexError);

	BOOST_CHECK(flist1.getBase().getElement(0) == fptr2);
	BOOST_CHECK(flist1.getBase().getElement(1) == fptr4);
	BOOST_CHECK_THROW(flist1.getBase().getElement(2), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(3), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(4), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(5), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(2), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 2), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	FragmentList::ElementIterator it = flist1.removeElement(flist1.getElementsEnd() - 1);

	BOOST_CHECK(it == flist1.getElementsEnd());

	BOOST_CHECK(flist1.getSize() == 1);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() != const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() != const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 1);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 1);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist1).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist1).getElementsBegin() == fptr2.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsBegin() + 1) == const_cast<FragmentList&>(flist1).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsBegin() + 1) == const_cast<const FragmentList&>(flist1).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist1).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist1).getElement(0) == fptr2.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(1), IndexError);

	BOOST_CHECK(flist1.getBase().getElement(0) == fptr2);
	BOOST_CHECK_THROW(flist1.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 1), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	it = flist1.removeElement(flist1.getElementsBegin());

	BOOST_CHECK(it == flist1.getElementsBegin());
	BOOST_CHECK(it == flist1.getElementsEnd());

	BOOST_CHECK(flist1.getSize() == 0);

	BOOST_CHECK(const_cast<FragmentList&>(flist1).getElementsEnd() == const_cast<FragmentList&>(flist1).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist1).getElementsEnd() == const_cast<const FragmentList&>(flist1).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist1).getElementsEnd() - const_cast<FragmentList&>(flist1).getElementsBegin()) == 0);
	BOOST_CHECK((const_cast<const FragmentList&>(flist1).getElementsEnd() - const_cast<const FragmentList&>(flist1).getElementsBegin()) == 0);

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(0), IndexError);

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist1).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist1).getElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.getBase().getElement(0), IndexError);
	BOOST_CHECK_THROW(flist1.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(0), IndexError);
	BOOST_CHECK_THROW(flist1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin()), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsBegin() + 1), RangeError);
	BOOST_CHECK_THROW(flist1.removeElement(flist1.getElementsEnd()), RangeError);

//-----

	FragmentList flist3;

	flist3 = flist2;

	BOOST_CHECK(flist3.getSize() == 3);

	BOOST_CHECK(const_cast<FragmentList&>(flist3).getElementsEnd() != const_cast<FragmentList&>(flist3).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist3).getElementsEnd() != const_cast<const FragmentList&>(flist3).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist3).getElementsEnd() - const_cast<FragmentList&>(flist3).getElementsBegin()) == 3);
	BOOST_CHECK((const_cast<const FragmentList&>(flist3).getElementsEnd() - const_cast<const FragmentList&>(flist3).getElementsBegin()) == 3);

	BOOST_CHECK(&*const_cast<FragmentList&>(flist3).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*const_cast<const FragmentList&>(flist3).getElementsBegin() == fptr2.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist3).getElementsBegin() + 1) == fptr1.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist3).getElementsBegin() + 1) == fptr1.get());
	BOOST_CHECK(&*(const_cast<FragmentList&>(flist3).getElementsBegin() + 2) == fptr4.get());
	BOOST_CHECK(&*(const_cast<const FragmentList&>(flist3).getElementsBegin() + 2) == fptr4.get());

	BOOST_CHECK((const_cast<FragmentList&>(flist3).getElementsBegin() + 3) == const_cast<FragmentList&>(flist3).getElementsEnd());
	BOOST_CHECK((const_cast<const FragmentList&>(flist3).getElementsBegin() + 3) == const_cast<const FragmentList&>(flist3).getElementsEnd());

	BOOST_CHECK(&const_cast<FragmentList&>(flist3).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist3).getElement(0) == fptr2.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist3).getElement(1) == fptr1.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist3).getElement(1) == fptr1.get());
	BOOST_CHECK(&const_cast<FragmentList&>(flist3).getElement(2) == fptr4.get());
	BOOST_CHECK(&const_cast<const FragmentList&>(flist3).getElement(2) == fptr4.get());

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist3).getElement(3), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist3).getElement(3), IndexError);

	BOOST_CHECK(flist3.getBase().getElement(0) == fptr2);
	BOOST_CHECK(flist3.getBase().getElement(1) == fptr1);
	BOOST_CHECK(flist3.getBase().getElement(2) == fptr4);
	BOOST_CHECK_THROW(flist3.getBase().getElement(3), IndexError);

//-----

	flist2.clear();

	BOOST_CHECK(flist2.getSize() == 0);

	BOOST_CHECK(const_cast<FragmentList&>(flist2).getElementsEnd() == const_cast<FragmentList&>(flist2).getElementsBegin());
	BOOST_CHECK(const_cast<const FragmentList&>(flist2).getElementsEnd() == const_cast<const FragmentList&>(flist2).getElementsBegin());

	BOOST_CHECK((const_cast<FragmentList&>(flist2).getElementsEnd() - const_cast<FragmentList&>(flist2).getElementsBegin()) == 0);
	BOOST_CHECK((const_cast<const FragmentList&>(flist2).getElementsEnd() - const_cast<const FragmentList&>(flist2).getElementsBegin()) == 0);

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist2).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist2).getElement(0), IndexError);

	BOOST_CHECK_THROW(const_cast<FragmentList&>(flist2).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<const FragmentList&>(flist2).getElement(1), IndexError);

	BOOST_CHECK_THROW(flist2.getBase().getElement(0), IndexError);
	BOOST_CHECK_THROW(flist2.getBase().getElement(1), IndexError);

	BOOST_CHECK_THROW(flist2.removeElement(0), IndexError);
	BOOST_CHECK_THROW(flist2.removeElement(1), IndexError);

	BOOST_CHECK_THROW(flist2.removeElement(flist2.getElementsBegin()), RangeError);
	BOOST_CHECK_THROW(flist2.removeElement(flist2.getElementsBegin() + 1), RangeError);
	BOOST_CHECK_THROW(flist2.removeElement(flist2.getElementsEnd()), RangeError);

//-----

	BOOST_CHECK(flist2.getSize() == 0);

	flist2.addElement(fptr2);
	flist2.addElement(fptr2);
	flist2.addElement(fptr2);
	flist2.addElement(fptr2);

	BOOST_CHECK(flist2.getSize() == 4);

	BOOST_CHECK(const_cast<const FragmentList&>(flist2).getElementsEnd() - 
				const_cast<const FragmentList&>(flist2).getElementsBegin() == 4);
	BOOST_CHECK(const_cast<FragmentList&>(flist2).getElementsEnd() - 
				const_cast<FragmentList&>(flist2).getElementsBegin() == 4);

	it = flist2.removeElement(flist2.getElementsBegin());

	BOOST_CHECK(it == flist2.getElementsBegin());

	it = flist2.removeElement(flist2.getElementsBegin() + 1);

	BOOST_CHECK(it == flist2.getElementsBegin() + 1);

	it = flist2.removeElement(--flist2.getElementsEnd());

	BOOST_CHECK(it == flist2.getElementsEnd());

	it = flist2.removeElement(flist2.getElementsBegin());

	BOOST_CHECK(it == flist2.getElementsEnd());
}
