/* 
 * ColorTableTest.cpp 
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

#include "CDPL/Vis/ColorTable.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(ColorTableTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace Base;

	ColorTable ct;

//-----

	BOOST_CHECK(ct.getSize() == 0);

	BOOST_CHECK(const_cast<const ColorTable&>(ct).getEntriesBegin() == const_cast<const ColorTable&>(ct).getEntriesEnd());
	BOOST_CHECK(const_cast<ColorTable&>(ct).getEntriesBegin() == const_cast<ColorTable&>(ct).getEntriesEnd());

	BOOST_CHECK_THROW(ct.getValue(1), ItemNotFound);
	BOOST_CHECK_THROW(ct.getValue(3), ItemNotFound);

	BOOST_CHECK(ct.containsEntry(1) == false);
	BOOST_CHECK(ct.containsEntry(3) == false);

//-----

	ct.setEntry(0, Color::RED);

	BOOST_CHECK(ct.getSize() == 1);

	BOOST_CHECK(ct.getValue(0) == Color::RED);

	BOOST_CHECK(const_cast<const ColorTable&>(ct).getEntriesBegin() != const_cast<const ColorTable&>(ct).getEntriesEnd());
	BOOST_CHECK(const_cast<ColorTable&>(ct).getEntriesBegin() != const_cast<ColorTable&>(ct).getEntriesEnd());

	BOOST_CHECK_THROW(ct.getValue(1), ItemNotFound);
	BOOST_CHECK_THROW(ct.getValue(3), ItemNotFound);

	BOOST_CHECK(ct.containsEntry(1) == false);
	BOOST_CHECK(ct.containsEntry(3) == false);

//-----

	ct.setEntry(2, Color::GREEN);

	BOOST_CHECK(ct.getSize() == 2);

	BOOST_CHECK(const_cast<const ColorTable&>(ct).getEntriesBegin() != const_cast<const ColorTable&>(ct).getEntriesEnd());
	BOOST_CHECK(const_cast<ColorTable&>(ct).getEntriesBegin() != const_cast<ColorTable&>(ct).getEntriesEnd());

	BOOST_CHECK(ct.getValue(0) == Color::RED);
	BOOST_CHECK(ct.getValue(2) == Color::GREEN);

	BOOST_CHECK_THROW(ct.getValue(1), ItemNotFound);
	BOOST_CHECK_THROW(ct.getValue(3), ItemNotFound);

	BOOST_CHECK(ct.containsEntry(1) == false);
	BOOST_CHECK(ct.containsEntry(3) == false);

	BOOST_CHECK(ct.getValue(0, Color::TRANSPARENT) == Color::RED);
	BOOST_CHECK(ct.getValue(2, Color::BLACK) == Color::GREEN);

	BOOST_CHECK(ct.getValue(1, Color::BLUE) == Color::BLUE);
	BOOST_CHECK(ct.getValue(1001, Color::MAGENTA) == Color::MAGENTA);

	BOOST_CHECK(ct[0] == Color::RED);
	BOOST_CHECK(ct[2] == Color::GREEN);

	BOOST_CHECK_THROW(ct[1], ItemNotFound);

	BOOST_CHECK(ct.getSize() == 2);

//-----

	ct.setEntry(1, Color::BLUE);
	
	BOOST_CHECK(ct.getSize() == 3);

	BOOST_CHECK(ct[0] == Color::RED);
	BOOST_CHECK(ct[1] == Color::BLUE);
	BOOST_CHECK(ct[2] == Color::GREEN);

	BOOST_CHECK(ct.getValue(0) == Color::RED);
	BOOST_CHECK(ct.getValue(1) == Color::BLUE);
	BOOST_CHECK(ct.getValue(2) == Color::GREEN);

	BOOST_CHECK(ct.containsEntry(0));
	BOOST_CHECK(ct.containsEntry(1));
	BOOST_CHECK(ct.containsEntry(2));

	BOOST_CHECK(!ct.containsEntry(1001));
	BOOST_CHECK(!ct.containsEntry(3));

	BOOST_CHECK_THROW(ct[3], ItemNotFound);

	BOOST_CHECK_THROW(ct.getValue(3), ItemNotFound);

	std::size_t i = 0;

	for (ColorTable::ConstEntryIterator it = const_cast<const ColorTable&>(ct).getEntriesBegin(), 
			 end = const_cast<const ColorTable&>(ct).getEntriesEnd();
		 it != end; ++it, i++) {

		switch (it->first) {

			case 0:
				BOOST_CHECK(it->second == Color::RED);
				break;

			case 1:
				BOOST_CHECK(it->second == Color::BLUE);
				break;
		
			case 2:
				BOOST_CHECK(it->second == Color::GREEN);
				break;
		
			default:
				BOOST_CHECK(false);
		}
	}

	BOOST_CHECK(i == 3);

	i = 0;

	for (ColorTable::EntryIterator it = const_cast<ColorTable&>(ct).getEntriesBegin(), 
			 end = const_cast<ColorTable&>(ct).getEntriesEnd();
		 it != end; ++it, i++) {

		switch (it->first) {

			case 0:
				BOOST_CHECK(it->second == Color::RED);
				break;

			case 1:
				BOOST_CHECK(it->second == Color::BLUE);
				break;
		
			case 2:
				BOOST_CHECK(it->second == Color::GREEN);
				break;
		
			default:
				BOOST_CHECK(false);
		}
	}

	BOOST_CHECK(i == 3);

//-----

	BOOST_CHECK(ct.removeEntry(0));
	BOOST_CHECK(!ct.removeEntry(0));

	BOOST_CHECK(ct.getSize() == 2);

	BOOST_CHECK_THROW(ct[0], ItemNotFound);
	BOOST_CHECK(ct[1] == Color::BLUE);
	BOOST_CHECK(ct[2] == Color::GREEN);

	BOOST_CHECK_THROW(ct.getValue(0), ItemNotFound);
	BOOST_CHECK(ct.getValue(1) == Color::BLUE);
	BOOST_CHECK(ct.getValue(2) == Color::GREEN);

	BOOST_CHECK(!ct.containsEntry(0));
	BOOST_CHECK(ct.containsEntry(1));
	BOOST_CHECK(ct.containsEntry(2));

	BOOST_CHECK(!ct.containsEntry(1001));
	BOOST_CHECK(!ct.containsEntry(3));

	BOOST_CHECK_THROW(ct[3], ItemNotFound);

	BOOST_CHECK_THROW(ct.getValue(3), ItemNotFound);

//-----
											  
	std::size_t removed_key = ct.getEntriesBegin()->first;

	ct.removeEntry(ct.getEntriesBegin());

	BOOST_CHECK(ct.getSize() == 1);

	BOOST_CHECK_THROW(ct[0], ItemNotFound);
	BOOST_CHECK_THROW(ct[removed_key], ItemNotFound);
	BOOST_CHECK(ct[ct.getEntriesBegin()->first] == ct.getEntriesBegin()->second);

	BOOST_CHECK_THROW(ct.getValue(0), ItemNotFound);
	BOOST_CHECK_THROW(ct.getValue(removed_key), ItemNotFound);
	BOOST_CHECK(ct.getValue(ct.getEntriesBegin()->first) == ct.getEntriesBegin()->second);

	BOOST_CHECK(!ct.containsEntry(0));
	BOOST_CHECK(!ct.containsEntry(removed_key));
	BOOST_CHECK(ct.containsEntry(ct.getEntriesBegin()->first));

//-----

	ct.clear();

	BOOST_CHECK(ct.getSize() == 0);

	BOOST_CHECK(const_cast<const ColorTable&>(ct).getEntriesBegin() == const_cast<const ColorTable&>(ct).getEntriesEnd());
	BOOST_CHECK(const_cast<ColorTable&>(ct).getEntriesBegin() == const_cast<ColorTable&>(ct).getEntriesEnd());

	BOOST_CHECK_THROW(ct[0], ItemNotFound);
	BOOST_CHECK_THROW(ct[1], ItemNotFound);
	BOOST_CHECK_THROW(ct[2], ItemNotFound);

	BOOST_CHECK_THROW(ct.getValue(0), ItemNotFound);
	BOOST_CHECK_THROW(ct.getValue(1), ItemNotFound);
	BOOST_CHECK_THROW(ct.getValue(2), ItemNotFound);

	BOOST_CHECK(!ct.containsEntry(0));
	BOOST_CHECK(!ct.containsEntry(1));
	BOOST_CHECK(!ct.containsEntry(2));
}

