/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StringDataBlockTest.cpp 
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

#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(StringDataBlockTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	StringDataBlock db1;

	BOOST_CHECK(db1.getSize() == 0);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(1), IndexError);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(1), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK_THROW(db1.removeElement(0), IndexError);
	BOOST_CHECK_THROW(db1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsBegin()), RangeError);

//-----

	StringDataBlockEntry entry1("header", "data");

	BOOST_CHECK(entry1.getHeader() == "header");
	BOOST_CHECK(entry1.getData() == "data");

	entry1.setHeader("header1");

	BOOST_CHECK(entry1.getHeader() == "header1");
	BOOST_CHECK(entry1.getData() == "data");

	entry1.setData("data1");

	BOOST_CHECK(entry1.getHeader() == "header1");
	BOOST_CHECK(entry1.getData() == "data1");

	StringDataBlockEntry entry2;

	BOOST_CHECK(entry2.getHeader() == "");
	BOOST_CHECK(entry2.getData() == "");

	entry2.setData("data2");

	BOOST_CHECK(entry2.getHeader() == "");
	BOOST_CHECK(entry2.getData() == "data2");

	entry2.setHeader("header2");

	BOOST_CHECK(entry2.getHeader() == "header2");
	BOOST_CHECK(entry2.getData() == "data2");

	BOOST_CHECK(!(entry1 == entry2));
	BOOST_CHECK(!(entry1 == StringDataBlockEntry()));
	BOOST_CHECK(!(entry1 == StringDataBlockEntry("header1", "")));
	BOOST_CHECK(!(entry1 == StringDataBlockEntry("", "data1")));
	BOOST_CHECK(!(entry1 == StringDataBlockEntry("header", "data")));
	BOOST_CHECK(entry1 == StringDataBlockEntry("header1", "data1"));

//-----

	db1.addElement(entry1);

	BOOST_CHECK(db1.getSize() == 1);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry1);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(2), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry1);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(1), IndexError);
	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(2), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK_THROW(db1.removeElement(1), IndexError);
	BOOST_CHECK_THROW(db1.removeElement(2), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsBegin() + 1), RangeError);

//-----

	db1.addElement(entry2);

	BOOST_CHECK(db1.getSize() == 2);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry1);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(1) == entry2);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(2), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry1);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(1) == entry2);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(2), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 2 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 2 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));

	BOOST_CHECK_THROW(db1.removeElement(2), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsEnd()), RangeError);

//-----

	db1.addElement(StringDataBlockEntry());

	StringDataBlockEntry& entry3 = db1.getLastElement();

	BOOST_CHECK(entry1.getHeader() == "header1");
	BOOST_CHECK(entry1.getData() == "data1");

	BOOST_CHECK(entry2.getHeader() == "header2");
	BOOST_CHECK(entry2.getData() == "data2");

	BOOST_CHECK(entry3.getHeader() == "");
	BOOST_CHECK(entry3.getData() == "");

	BOOST_CHECK(db1.getSize() == 3);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry1);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(1) == entry2);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(2) == entry3);

	BOOST_CHECK(&const_cast<const StringDataBlock&>(db1).getElement(0) != &entry1);
	BOOST_CHECK(&const_cast<const StringDataBlock&>(db1).getElement(1) != &entry2);
	BOOST_CHECK(&const_cast<const StringDataBlock&>(db1).getElement(2) == &entry3);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(3), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry1);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(1) == entry2);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(2) == entry3);

	BOOST_CHECK(&const_cast<StringDataBlock&>(db1).getElement(0) != &entry1);
	BOOST_CHECK(&const_cast<StringDataBlock&>(db1).getElement(1) != &entry2);
	BOOST_CHECK(&const_cast<StringDataBlock&>(db1).getElement(2) == &entry3);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(3), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 3 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 3 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 2) == &db1.getElement(2));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 2) == &db1.getElement(2));

	BOOST_CHECK_THROW(db1.removeElement(3), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsEnd()), RangeError);

//-----

	db1.addEntry("header4", "data4");

	BOOST_CHECK(db1.getSize() == 4);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry1);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(1) == entry2);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(2) == entry3);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(3) == StringDataBlockEntry("header4", "data4"));

	BOOST_CHECK(&const_cast<const StringDataBlock&>(db1).getElement(0) != &entry1);
	BOOST_CHECK(&const_cast<const StringDataBlock&>(db1).getElement(1) != &entry2);
	BOOST_CHECK(&const_cast<const StringDataBlock&>(db1).getElement(2) == &entry3);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(4), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry1);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(1) == entry2);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(2) == entry3);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(3) == StringDataBlockEntry("header4", "data4"));

	BOOST_CHECK(&const_cast<StringDataBlock&>(db1).getElement(0) != &entry1);
	BOOST_CHECK(&const_cast<StringDataBlock&>(db1).getElement(1) != &entry2);
	BOOST_CHECK(&const_cast<StringDataBlock&>(db1).getElement(2) == &entry3);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(4), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 4 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 4 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 2) == &db1.getElement(2));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 2) == &db1.getElement(2));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 3) == &db1.getElement(3));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 3) == &db1.getElement(3));

	BOOST_CHECK_THROW(db1.removeElement(4), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsEnd()), RangeError);

//-----

	StringDataBlock db2(db1);

	BOOST_CHECK(db2.getSize() == 4);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db2).getElement(0) == entry1);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db2).getElement(1) == entry2);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db2).getElement(2) == entry3);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db2).getElement(3) == StringDataBlockEntry("header4", "data4"));

	BOOST_CHECK(&const_cast<const StringDataBlock&>(db2).getElement(0) != &entry1);
	BOOST_CHECK(&const_cast<const StringDataBlock&>(db2).getElement(1) != &entry2);
	BOOST_CHECK(&const_cast<const StringDataBlock&>(db2).getElement(2) != &entry3);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db2).getElement(4), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db2).getElement(0) == entry1);
	BOOST_CHECK(const_cast<StringDataBlock&>(db2).getElement(1) == entry2);
	BOOST_CHECK(const_cast<StringDataBlock&>(db2).getElement(2) == entry3);
	BOOST_CHECK(const_cast<StringDataBlock&>(db2).getElement(3) == StringDataBlockEntry("header4", "data4"));

	BOOST_CHECK(&const_cast<StringDataBlock&>(db2).getElement(0) != &entry1);
	BOOST_CHECK(&const_cast<StringDataBlock&>(db2).getElement(1) != &entry2);
	BOOST_CHECK(&const_cast<StringDataBlock&>(db2).getElement(2) != &entry3);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db2).getElement(4), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db2).getElementsBegin() + 4 == const_cast<const StringDataBlock&>(db2).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db2).getElementsBegin() + 4 == const_cast<StringDataBlock&>(db2).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db2).getElementsBegin() == &db2.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db2).getElementsBegin() == &db2.getElement(0));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db2).getElementsBegin() + 1) == &db2.getElement(1));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db2).getElementsBegin() + 1) == &db2.getElement(1));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db2).getElementsBegin() + 2) == &db2.getElement(2));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db2).getElementsBegin() + 2) == &db2.getElement(2));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db2).getElementsBegin() + 3) == &db2.getElement(3));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db2).getElementsBegin() + 3) == &db2.getElement(3));

	BOOST_CHECK_THROW(db2.removeElement(4), IndexError);

	BOOST_CHECK_THROW(db2.removeElement(db2.getElementsEnd()), RangeError);

//-----

	db2.clear();

	BOOST_CHECK(db2.getSize() == 0);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db2).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db2).getElement(1), IndexError);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db2).getElement(0), IndexError);
	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db2).getElement(1), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db2).getElementsBegin() == const_cast<const StringDataBlock&>(db2).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db2).getElementsBegin() == const_cast<StringDataBlock&>(db2).getElementsEnd());

	BOOST_CHECK_THROW(db2.removeElement(0), IndexError);
	BOOST_CHECK_THROW(db2.removeElement(1), IndexError);

	BOOST_CHECK_THROW(db2.removeElement(db2.getElementsBegin()), RangeError);

//-----

	db1.removeElement(0);

	BOOST_CHECK(db1.getSize() == 3);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry2);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(1) == StringDataBlockEntry("", ""));
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(2) == StringDataBlockEntry("header4", "data4"));

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(4), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry2);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(1) == StringDataBlockEntry("", ""));
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(2) == StringDataBlockEntry("header4", "data4"));

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(3), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 3 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 3 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 2) == &db1.getElement(2));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 2) == &db1.getElement(2));

	BOOST_CHECK_THROW(db1.removeElement(3), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsEnd()), RangeError);

//-----

	StringDataBlock::ElementIterator it = db1.removeElement(--db1.getElementsEnd());

	BOOST_CHECK(it == db1.getElementsEnd());

	BOOST_CHECK(db1.getSize() == 2);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry2);
	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(1) == StringDataBlockEntry("", ""));

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(2), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry2);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(1) == StringDataBlockEntry("", ""));

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(2), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 2 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 2 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK(&*(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));
	BOOST_CHECK(&*(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1) == &db1.getElement(1));

	BOOST_CHECK_THROW(db1.removeElement(2), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsBegin() + 2), RangeError);

//-----

	db1.removeElement(1);

	BOOST_CHECK(db1.getSize() == 1);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElement(0) == entry2);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(1), IndexError);

	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElement(0) == entry2);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(1), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() + 1 == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() + 1 == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK(&*const_cast<const StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));
	BOOST_CHECK(&*const_cast<StringDataBlock&>(db1).getElementsBegin() == &db1.getElement(0));

	BOOST_CHECK_THROW(db1.removeElement(1), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsBegin() + 1), RangeError);

//-----

	it = db1.removeElement(db1.getElementsBegin());

	BOOST_CHECK(it == db1.getElementsBegin());
	BOOST_CHECK(it == db1.getElementsEnd());

	BOOST_CHECK(db1.getSize() == 0);

	BOOST_CHECK_THROW(const_cast<const StringDataBlock&>(db1).getElement(0), IndexError);

	BOOST_CHECK_THROW(const_cast<StringDataBlock&>(db1).getElement(0), IndexError);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsBegin() == const_cast<const StringDataBlock&>(db1).getElementsEnd());
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsBegin() == const_cast<StringDataBlock&>(db1).getElementsEnd());

	BOOST_CHECK_THROW(db1.removeElement(0), IndexError);

	BOOST_CHECK_THROW(db1.removeElement(db1.getElementsBegin()), RangeError);

//-----

	BOOST_CHECK(db1.getSize() == 0);

	db1.addElement();
	db1.addElement();
	db1.addElement();
	db1.addElement();

	BOOST_CHECK(db1.getSize() == 4);

	BOOST_CHECK(const_cast<const StringDataBlock&>(db1).getElementsEnd() - 
				const_cast<const StringDataBlock&>(db1).getElementsBegin() == 4);
	BOOST_CHECK(const_cast<StringDataBlock&>(db1).getElementsEnd() - 
				const_cast<StringDataBlock&>(db1).getElementsBegin() == 4);

	it = db1.removeElement(db1.getElementsBegin());

	BOOST_CHECK(it == db1.getElementsBegin());

	it = db1.removeElement(db1.getElementsBegin() + 1);

	BOOST_CHECK(it == db1.getElementsBegin() + 1);

	it = db1.removeElement(--db1.getElementsEnd());

	BOOST_CHECK(it == db1.getElementsEnd());

	it = db1.removeElement(db1.getElementsBegin());

	BOOST_CHECK(it == db1.getElementsEnd());
}

