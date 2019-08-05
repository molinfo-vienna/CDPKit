/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StreamDataReaderTest.cpp 
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


#include <string>
#include <sstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Util/StreamDataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"


class TestStringReader : public CDPL::Util::StreamDataReader<std::string, TestStringReader>
{

public:
	typedef std::string DataType;

	TestStringReader(std::istream& is): CDPL::Util::StreamDataReader<std::string, TestStringReader>(is) {}

private:
	friend class CDPL::Util::StreamDataReader<std::string, TestStringReader>;

	bool readData(std::istream& is, std::string& str, bool) {
		if (moreData(is))
			return bool(is >> str);

		return false;
	}

	bool skipData(std::istream& is) {
		if (!moreData(is))
			return false;

		std::string sink;

		return bool(is >> sink);
	}

	bool moreData(std::istream& is) {
		return bool(std::istream::sentry(is, false));
	}
};

struct TestProgressCallback
{

	TestProgressCallback(): calls(0) {}

	void operator()(const CDPL::Base::DataIOBase&, double) {
		calls++;
	}

	std::size_t calls;
};


BOOST_AUTO_TEST_CASE(StreamDataReaderTest)
{
	using namespace CDPL;
	using namespace Util;

	std::string record;
	std::istringstream is1("Record#1 Record#2 \nRecord#3 Record#4   ");

	TestStringReader reader1(is1);
	TestProgressCallback callback;

	reader1.registerIOCallback(boost::ref(callback));

	BOOST_CHECK(reader1.getNumRecords() == 4);
	
	BOOST_CHECK(callback.calls == 5);

	BOOST_CHECK(reader1.read(record));
	BOOST_CHECK(record == "Record#1");

	BOOST_CHECK(callback.calls == 6);

	BOOST_CHECK(reader1.read(record));
	BOOST_CHECK(record == "Record#2");

	BOOST_CHECK(callback.calls == 7);

	BOOST_CHECK(reader1.getRecordIndex() == 2);

	BOOST_CHECK(reader1.skip());

	BOOST_CHECK(callback.calls == 8);

	BOOST_CHECK(reader1.getRecordIndex() == 3);

	BOOST_CHECK(reader1.hasMoreData());

	BOOST_CHECK(reader1.read(record));
	BOOST_CHECK(record == "Record#4");

	BOOST_CHECK(callback.calls == 9);

	BOOST_CHECK(reader1.getRecordIndex() == 4);

	BOOST_CHECK(!reader1.hasMoreData());
	BOOST_CHECK(!reader1.read(record));
	BOOST_CHECK(!reader1.skip());

	BOOST_CHECK(reader1.getRecordIndex() == 4);

	reader1.setRecordIndex(2);

	BOOST_CHECK(reader1.getRecordIndex() == 2);

	BOOST_CHECK(reader1.read(record));
	BOOST_CHECK(record == "Record#3");

	BOOST_CHECK(reader1.getRecordIndex() == 3);

	BOOST_CHECK(reader1.read(1, record));

	BOOST_CHECK(record == "Record#2");

	BOOST_CHECK(reader1.getRecordIndex() == 2);

	BOOST_CHECK(reader1.read(record));
	BOOST_CHECK(record == "Record#3");

	BOOST_CHECK(reader1.getRecordIndex() == 3);

	BOOST_CHECK_THROW(reader1.read(5, record), Base::IndexError);

	BOOST_CHECK(reader1.getRecordIndex() == 3);

	BOOST_CHECK(reader1.hasMoreData());

	BOOST_CHECK(reader1.read(record));
	BOOST_CHECK(record == "Record#4");

	BOOST_CHECK(!reader1.hasMoreData());
	BOOST_CHECK(!reader1.read(record));
	BOOST_CHECK(!reader1);

// -------------

	std::istringstream is2("\n  Record#1");

	TestStringReader reader2(is2);

	BOOST_CHECK(reader2.read(record));
	BOOST_CHECK(record == "Record#1");

	BOOST_CHECK(!reader2.hasMoreData());
	BOOST_CHECK(!reader2.read(record));
	BOOST_CHECK(!reader2);

	BOOST_CHECK(reader2.getRecordIndex() == 1);
	
	BOOST_CHECK(reader2.read(0, record));
	BOOST_CHECK(record == "Record#1");

	BOOST_CHECK(reader2.getRecordIndex() == 1);

	BOOST_CHECK(reader2.getNumRecords() == 1);

// -------------

	std::istringstream is3("");

	TestStringReader reader3(is3);

	BOOST_CHECK(reader3.getRecordIndex() == 0);

	BOOST_CHECK(!reader3.skip());
	BOOST_CHECK(!reader3.read(record));
	BOOST_CHECK(!reader3.hasMoreData());
	BOOST_CHECK(!reader3);

	BOOST_CHECK(reader3.getNumRecords() == 0);
}

