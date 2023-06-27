/* 
 * IndirectArrayTest.cpp 
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


#include <memory>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Util/IndirectArray.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    struct TestElement
    {

        typedef std::shared_ptr<TestElement> SharedPointer;
    };
}


BOOST_AUTO_TEST_CASE(IndirectArrayTest)
{
    using namespace CDPL;
    using namespace Util;
    using namespace Base;

    typedef Util::IndirectArray<TestElement, TestElement::SharedPointer> ArrayType;
    
    TestElement::SharedPointer fptr1(new TestElement());
    TestElement::SharedPointer fptr2(new TestElement());
    TestElement::SharedPointer fptr3(new TestElement());
    TestElement::SharedPointer fptr4(new TestElement());
    TestElement::SharedPointer fptr5(new TestElement());

    ArrayType array1;

//-----

    BOOST_CHECK(array1.getSize() == 0);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() == const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() == const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 0);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 0);

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(0), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(0), IndexError);

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(1), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(1), IndexError);

    BOOST_CHECK_THROW(array1.getBase().getElement(0), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(0), IndexError);
    BOOST_CHECK_THROW(array1.removeElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin()), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 1), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    array1.addElement(fptr1);

    BOOST_CHECK(array1.getSize() == 1);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() != const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() != const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 1);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 1);

    BOOST_CHECK(&*const_cast<ArrayType&>(array1).getElementsBegin() == fptr1.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array1).getElementsBegin() == fptr1.get());

    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(0) == fptr1.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(0) == fptr1.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(1), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(1), IndexError);

    BOOST_CHECK(array1.getBase().getElement(0) == fptr1);
    BOOST_CHECK_THROW(array1.getBase().getElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 1), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    array1.addElement(fptr2);
    array1.addElement(fptr3);
    array1.addElement(fptr4);
    array1.addElement(fptr5);

    BOOST_CHECK(array1.getSize() == 5);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() != const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() != const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 5);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 5);

    BOOST_CHECK(&*const_cast<ArrayType&>(array1).getElementsBegin() == fptr1.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array1).getElementsBegin() == fptr1.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 1) == fptr2.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 1) == fptr2.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 2) == fptr3.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 2) == fptr3.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 3) == fptr4.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 3) == fptr4.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 4) == fptr5.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 4) == fptr5.get());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsBegin() + 5) == const_cast<ArrayType&>(array1).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsBegin() + 5) == const_cast<const ArrayType&>(array1).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(0) == fptr1.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(0) == fptr1.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(1) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(1) == fptr2.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(2) == fptr3.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(2) == fptr3.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(3) == fptr4.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(3) == fptr4.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(4) == fptr5.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(4) == fptr5.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(5), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(5), IndexError);

    BOOST_CHECK(array1.getBase().getElement(0) == fptr1);
    BOOST_CHECK(array1.getBase().getElement(1) == fptr2);
    BOOST_CHECK(array1.getBase().getElement(2) == fptr3);
    BOOST_CHECK(array1.getBase().getElement(3) == fptr4);
    BOOST_CHECK(array1.getBase().getElement(4) == fptr5);
    BOOST_CHECK_THROW(array1.getBase().getElement(5), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(6), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 5), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    ArrayType array2;

    array2.addElement(fptr2);
    array2.addElement(fptr1);
    array2.addElement(fptr4);

    BOOST_CHECK(array2.getSize() == 3);

    BOOST_CHECK(const_cast<ArrayType&>(array2).getElementsEnd() != const_cast<ArrayType&>(array2).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array2).getElementsEnd() != const_cast<const ArrayType&>(array2).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array2).getElementsEnd() - const_cast<ArrayType&>(array2).getElementsBegin()) == 3);
    BOOST_CHECK((const_cast<const ArrayType&>(array2).getElementsEnd() - const_cast<const ArrayType&>(array2).getElementsBegin()) == 3);

    BOOST_CHECK(&*const_cast<ArrayType&>(array2).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array2).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array2).getElementsBegin() + 1) == fptr1.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array2).getElementsBegin() + 1) == fptr1.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array2).getElementsBegin() + 2) == fptr4.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array2).getElementsBegin() + 2) == fptr4.get());

    BOOST_CHECK((const_cast<ArrayType&>(array2).getElementsBegin() + 3) == const_cast<ArrayType&>(array2).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array2).getElementsBegin() + 3) == const_cast<const ArrayType&>(array2).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array2).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array2).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array2).getElement(1) == fptr1.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array2).getElement(1) == fptr1.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array2).getElement(2) == fptr4.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array2).getElement(2) == fptr4.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array2).getElement(3), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array2).getElement(3), IndexError);

    BOOST_CHECK(array2.getBase().getElement(0) == fptr2);
    BOOST_CHECK(array2.getBase().getElement(1) == fptr1);
    BOOST_CHECK(array2.getBase().getElement(2) == fptr4);
    BOOST_CHECK_THROW(array2.getBase().getElement(3), IndexError);

//-----

    array1.removeElement(0);

    BOOST_CHECK(array1.getSize() == 4);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() != const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() != const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 4);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 4);

    BOOST_CHECK(&*const_cast<ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 1) == fptr3.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 1) == fptr3.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 2) == fptr4.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 2) == fptr4.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 3) == fptr5.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 3) == fptr5.get());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsBegin() + 4) == const_cast<ArrayType&>(array1).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsBegin() + 4) == const_cast<const ArrayType&>(array1).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(1) == fptr3.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(1) == fptr3.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(2) == fptr4.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(2) == fptr4.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(3) == fptr5.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(3) == fptr5.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(4), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(4), IndexError);

    BOOST_CHECK(array1.getBase().getElement(0) == fptr2);
    BOOST_CHECK(array1.getBase().getElement(1) == fptr3);
    BOOST_CHECK(array1.getBase().getElement(2) == fptr4);
    BOOST_CHECK(array1.getBase().getElement(3) == fptr5);
    BOOST_CHECK_THROW(array1.getBase().getElement(4), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(5), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(4), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 4), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    array1.removeElement(3);

    BOOST_CHECK(array1.getSize() == 3);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() != const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() != const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 3);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 3);

    BOOST_CHECK(&*const_cast<ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 1) == fptr3.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 1) == fptr3.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 2) == fptr4.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 2) == fptr4.get());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsBegin() + 3) == const_cast<ArrayType&>(array1).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsBegin() + 3) == const_cast<const ArrayType&>(array1).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(1) == fptr3.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(1) == fptr3.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(2) == fptr4.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(2) == fptr4.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(3), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(3), IndexError);

    BOOST_CHECK(array1.getBase().getElement(0) == fptr2);
    BOOST_CHECK(array1.getBase().getElement(1) == fptr3);
    BOOST_CHECK(array1.getBase().getElement(2) == fptr4);
    BOOST_CHECK_THROW(array1.getBase().getElement(3), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(4), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(5), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(3), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 3), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    array1.removeElement(1);

    BOOST_CHECK(array1.getSize() == 2);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() != const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() != const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 2);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 2);

    BOOST_CHECK(&*const_cast<ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array1).getElementsBegin() + 1) == fptr4.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array1).getElementsBegin() + 1) == fptr4.get());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsBegin() + 2) == const_cast<ArrayType&>(array1).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsBegin() + 2) == const_cast<const ArrayType&>(array1).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(1) == fptr4.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(1) == fptr4.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(2), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(2), IndexError);

    BOOST_CHECK(array1.getBase().getElement(0) == fptr2);
    BOOST_CHECK(array1.getBase().getElement(1) == fptr4);
    BOOST_CHECK_THROW(array1.getBase().getElement(2), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(3), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(4), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(5), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(2), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 2), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    ArrayType::ElementIterator it = array1.removeElement(array1.getElementsEnd() - 1);

    BOOST_CHECK(it == array1.getElementsEnd());

    BOOST_CHECK(array1.getSize() == 1);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() != const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() != const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 1);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 1);

    BOOST_CHECK(&*const_cast<ArrayType&>(array1).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array1).getElementsBegin() == fptr2.get());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsBegin() + 1) == const_cast<ArrayType&>(array1).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsBegin() + 1) == const_cast<const ArrayType&>(array1).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array1).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array1).getElement(0) == fptr2.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(1), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(1), IndexError);

    BOOST_CHECK(array1.getBase().getElement(0) == fptr2);
    BOOST_CHECK_THROW(array1.getBase().getElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 1), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    it = array1.removeElement(array1.getElementsBegin());

    BOOST_CHECK(it == array1.getElementsBegin());
    BOOST_CHECK(it == array1.getElementsEnd());

    BOOST_CHECK(array1.getSize() == 0);

    BOOST_CHECK(const_cast<ArrayType&>(array1).getElementsEnd() == const_cast<ArrayType&>(array1).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array1).getElementsEnd() == const_cast<const ArrayType&>(array1).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array1).getElementsEnd() - const_cast<ArrayType&>(array1).getElementsBegin()) == 0);
    BOOST_CHECK((const_cast<const ArrayType&>(array1).getElementsEnd() - const_cast<const ArrayType&>(array1).getElementsBegin()) == 0);

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(0), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(0), IndexError);

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array1).getElement(1), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array1).getElement(1), IndexError);

    BOOST_CHECK_THROW(array1.getBase().getElement(0), IndexError);
    BOOST_CHECK_THROW(array1.getBase().getElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(0), IndexError);
    BOOST_CHECK_THROW(array1.removeElement(1), IndexError);

    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin()), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsBegin() + 1), RangeError);
    BOOST_CHECK_THROW(array1.removeElement(array1.getElementsEnd()), RangeError);

//-----

    ArrayType array3;

    array3 = array2;

    BOOST_CHECK(array3.getSize() == 3);

    BOOST_CHECK(const_cast<ArrayType&>(array3).getElementsEnd() != const_cast<ArrayType&>(array3).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array3).getElementsEnd() != const_cast<const ArrayType&>(array3).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array3).getElementsEnd() - const_cast<ArrayType&>(array3).getElementsBegin()) == 3);
    BOOST_CHECK((const_cast<const ArrayType&>(array3).getElementsEnd() - const_cast<const ArrayType&>(array3).getElementsBegin()) == 3);

    BOOST_CHECK(&*const_cast<ArrayType&>(array3).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*const_cast<const ArrayType&>(array3).getElementsBegin() == fptr2.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array3).getElementsBegin() + 1) == fptr1.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array3).getElementsBegin() + 1) == fptr1.get());
    BOOST_CHECK(&*(const_cast<ArrayType&>(array3).getElementsBegin() + 2) == fptr4.get());
    BOOST_CHECK(&*(const_cast<const ArrayType&>(array3).getElementsBegin() + 2) == fptr4.get());

    BOOST_CHECK((const_cast<ArrayType&>(array3).getElementsBegin() + 3) == const_cast<ArrayType&>(array3).getElementsEnd());
    BOOST_CHECK((const_cast<const ArrayType&>(array3).getElementsBegin() + 3) == const_cast<const ArrayType&>(array3).getElementsEnd());

    BOOST_CHECK(&const_cast<ArrayType&>(array3).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array3).getElement(0) == fptr2.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array3).getElement(1) == fptr1.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array3).getElement(1) == fptr1.get());
    BOOST_CHECK(&const_cast<ArrayType&>(array3).getElement(2) == fptr4.get());
    BOOST_CHECK(&const_cast<const ArrayType&>(array3).getElement(2) == fptr4.get());

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array3).getElement(3), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array3).getElement(3), IndexError);

    BOOST_CHECK(array3.getBase().getElement(0) == fptr2);
    BOOST_CHECK(array3.getBase().getElement(1) == fptr1);
    BOOST_CHECK(array3.getBase().getElement(2) == fptr4);
    BOOST_CHECK_THROW(array3.getBase().getElement(3), IndexError);

//-----

    array2.clear();

    BOOST_CHECK(array2.getSize() == 0);

    BOOST_CHECK(const_cast<ArrayType&>(array2).getElementsEnd() == const_cast<ArrayType&>(array2).getElementsBegin());
    BOOST_CHECK(const_cast<const ArrayType&>(array2).getElementsEnd() == const_cast<const ArrayType&>(array2).getElementsBegin());

    BOOST_CHECK((const_cast<ArrayType&>(array2).getElementsEnd() - const_cast<ArrayType&>(array2).getElementsBegin()) == 0);
    BOOST_CHECK((const_cast<const ArrayType&>(array2).getElementsEnd() - const_cast<const ArrayType&>(array2).getElementsBegin()) == 0);

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array2).getElement(0), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array2).getElement(0), IndexError);

    BOOST_CHECK_THROW(const_cast<ArrayType&>(array2).getElement(1), IndexError);
    BOOST_CHECK_THROW(const_cast<const ArrayType&>(array2).getElement(1), IndexError);

    BOOST_CHECK_THROW(array2.getBase().getElement(0), IndexError);
    BOOST_CHECK_THROW(array2.getBase().getElement(1), IndexError);

    BOOST_CHECK_THROW(array2.removeElement(0), IndexError);
    BOOST_CHECK_THROW(array2.removeElement(1), IndexError);

    BOOST_CHECK_THROW(array2.removeElement(array2.getElementsBegin()), RangeError);
    BOOST_CHECK_THROW(array2.removeElement(array2.getElementsBegin() + 1), RangeError);
    BOOST_CHECK_THROW(array2.removeElement(array2.getElementsEnd()), RangeError);

//-----

    BOOST_CHECK(array2.getSize() == 0);

    array2.addElement(fptr2);
    array2.addElement(fptr2);
    array2.addElement(fptr2);
    array2.addElement(fptr2);

    BOOST_CHECK(array2.getSize() == 4);

    BOOST_CHECK(const_cast<const ArrayType&>(array2).getElementsEnd() - 
                const_cast<const ArrayType&>(array2).getElementsBegin() == 4);
    BOOST_CHECK(const_cast<ArrayType&>(array2).getElementsEnd() - 
                const_cast<ArrayType&>(array2).getElementsBegin() == 4);

    it = array2.removeElement(array2.getElementsBegin());

    BOOST_CHECK(it == array2.getElementsBegin());

    it = array2.removeElement(array2.getElementsBegin() + 1);

    BOOST_CHECK(it == array2.getElementsBegin() + 1);

    it = array2.removeElement(--array2.getElementsEnd());

    BOOST_CHECK(it == array2.getElementsEnd());

    it = array2.removeElement(array2.getElementsBegin());

    BOOST_CHECK(it == array2.getElementsEnd());
}

