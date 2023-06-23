/* 
 * DataIOManagerTest.cpp 
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

#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const char* testFileExtensions1[] = { "ext1" };
	const char* testFileExtensions2[] = { "ext2" };

	CDPL::Base::DataFormat testFormat1("TEST_FORMAT1", "Test format1", "application/test1", 
									   testFileExtensions1, testFileExtensions1 + 1, true);
	CDPL::Base::DataFormat testFormat2("TEST_FORMAT2", "Test format2", "application/test2", 
									   testFileExtensions2, testFileExtensions2 + 1, true);

	class TestInputHandler : public CDPL::Base::DataInputHandler<int>
	{

	public:
		TestInputHandler(const CDPL::Base::DataFormat& format): format(format) {}

		const CDPL::Base::DataFormat& getDataFormat() const {
			return format;
		}

		virtual CDPL::Base::DataReader<int>::SharedPointer createReader(std::istream&) const {
			return CDPL::Base::DataReader<int>::SharedPointer();
		}

		virtual CDPL::Base::DataReader<int>::SharedPointer createReader(const std::string&, std::ios_base::openmode) const {
			return CDPL::Base::DataReader<int>::SharedPointer();
		}

	private:
		const CDPL::Base::DataFormat& format;
	};

	class TestOutputHandler : public CDPL::Base::DataOutputHandler<int>
	{

	public:
		TestOutputHandler(const CDPL::Base::DataFormat& format): format(format) {}

		const CDPL::Base::DataFormat& getDataFormat() const {
			return format;
		}

		virtual CDPL::Base::DataWriter<int>::SharedPointer createWriter(std::iostream&) const {
			return CDPL::Base::DataWriter<int>::SharedPointer();
		}

		virtual CDPL::Base::DataWriter<int>::SharedPointer createWriter(const std::string&, std::ios_base::openmode) const {
			return CDPL::Base::DataWriter<int>::SharedPointer();
		}

	private:
		const CDPL::Base::DataFormat& format;
	};
}


BOOST_AUTO_TEST_CASE(DataIOManagerTest)
{
	using namespace CDPL;
	using namespace Base;

	TestInputHandler::SharedPointer test_input_handler1(new TestInputHandler(testFormat1));
	TestInputHandler::SharedPointer test_input_handler2(new TestInputHandler(testFormat2));

	TestOutputHandler::SharedPointer test_output_handler1(new TestOutputHandler(testFormat1));
	TestOutputHandler::SharedPointer test_output_handler2(new TestOutputHandler(testFormat2));

//-----

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 0);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() == DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	DataIOManager<int>::registerInputHandler(test_input_handler1);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 1);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(1), IndexError);

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat1) == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat2) == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_fOrmat1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("TEST_format2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test f rmat1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_format3") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("ExT1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("eXT2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension(" xt2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("e t2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/TeST1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("APPLICATION/test2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/test1 ") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("abplication/test1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("") == DataInputHandler<int>::SharedPointer());

//-----

	DataIOManager<int>::registerInputHandler(test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler2); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat1) == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat2) == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_fOrmat1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("TEST_format2") == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test f rmat1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_format3") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("ExT1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("eXT2") == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension(" xt2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("e t2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/TeST1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("APPLICATION/test2") == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/test1 ") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("abplication/test1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("") == DataInputHandler<int>::SharedPointer());

//-----

	DataIOManager<int>::registerOutputHandler(test_output_handler2);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 1);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler2); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() != DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getOutputHandlersBegin() == test_output_handler2); 

	BOOST_CHECK(DataIOManager<int>::getOutputHandler(0) == test_output_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(1), IndexError);

//----- 

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat2) == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat1) == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_fOrmat2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("TEST_format1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test f rmat1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_format3") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("ExT2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("eXT1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension(" xt2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("e t2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/TeST2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("APPLICATION/test1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/test1 ") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("abplication/test1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("") == DataOutputHandler<int>::SharedPointer());

//-----

	DataIOManager<int>::registerOutputHandler(test_output_handler1);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler2); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 2);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() != DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getOutputHandlersBegin() == test_output_handler2); 
	BOOST_CHECK(*(DataIOManager<int>::getOutputHandlersBegin() + 1) == test_output_handler1); 

	BOOST_CHECK(DataIOManager<int>::getOutputHandler(0) == test_output_handler2); 
	BOOST_CHECK(DataIOManager<int>::getOutputHandler(1) == test_output_handler1); 
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(2), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat2) == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat1) == test_output_handler1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_fOrmat2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("TEST_format1") == test_output_handler1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test f rmat1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_format3") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("ExT2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("eXT1") == test_output_handler1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension(" xt2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("e t2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/TeST2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("APPLICATION/test1") == test_output_handler1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/test1 ") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("abplication/test1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("") == DataOutputHandler<int>::SharedPointer());

//-----

	BOOST_CHECK(DataIOManager<int>::unregisterOutputHandler(testFormat1));

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 1);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler2); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() != DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getOutputHandlersBegin() == test_output_handler2); 

	BOOST_CHECK(DataIOManager<int>::getOutputHandler(0) == test_output_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(1), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat2) == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat1) == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_fOrmat2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("TEST_format1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test f rmat1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_format3") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("ExT2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("eXT1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension(" xt2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("e t2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/TeST2") == test_output_handler2);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("APPLICATION/test1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/test1 ") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("abplication/test1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("") == DataOutputHandler<int>::SharedPointer());

//-----

	BOOST_CHECK_THROW(DataIOManager<int>::unregisterInputHandler(2), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterOutputHandler(1), IndexError);

//-----

	DataIOManager<int>::unregisterOutputHandler(0);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler2); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(1), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat2) == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat1) == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_fOrmat2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("TEST_format1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test f rmat1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_format3") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("ExT2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("eXT1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension(" xt2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("e t2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/TeST2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("APPLICATION/test1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/test1 ") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("abplication/test1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat1) == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat2) == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_fOrmat1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("TEST_format2") == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test f rmat1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_format3") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("ExT1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("eXT2") == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension(" xt2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("e t2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/TeST1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("APPLICATION/test2") == test_input_handler2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/test1 ") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("abplication/test1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("") == DataInputHandler<int>::SharedPointer());

//-----

	DataIOManager<int>::unregisterInputHandler(1);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 1);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler1); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler1); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(1), IndexError);

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat1) == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat2) == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_fOrmat1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("TEST_format2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test f rmat1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_format3") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("ext1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("ExT1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("eXT2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension(" xt2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("e t2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/test1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/TeST1") == test_input_handler1);
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("APPLICATION/test2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/test1 ") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("abplication/test1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("") == DataInputHandler<int>::SharedPointer());

//-----

	BOOST_CHECK(DataIOManager<int>::unregisterInputHandler(testFormat1));

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 0);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() == DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat2) == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFormat(testFormat1) == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_fOrmat2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("TEST_format1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test f rmat1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("test_format3") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByName("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("ExT2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("eXT1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension(" xt2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("e t2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByFileExtension("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/TeST2") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("APPLICATION/test1") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("application/test1 ") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("abplication/test1") == DataOutputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlerByMimeType("") == DataOutputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat1) == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFormat(testFormat2) == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_fOrmat1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("TEST_format2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test f rmat1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("test_format3") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByName("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("ExT1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("eXT2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension(" xt2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("e t2") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByFileExtension("") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/TeST1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("APPLICATION/test2") == DataInputHandler<int>::SharedPointer());

	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("application/test1 ") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("abplication/test1") == DataInputHandler<int>::SharedPointer());
	BOOST_CHECK(DataIOManager<int>::getInputHandlerByMimeType("") == DataInputHandler<int>::SharedPointer());

//-----

	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterInputHandler(0), IndexError);

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterOutputHandler(0), IndexError);


//-----

	DataIOManager<int>::registerInputHandler(test_input_handler2);
	DataIOManager<int>::registerInputHandler(test_input_handler1);

	DataIOManager<int>::registerOutputHandler(test_output_handler1);
	DataIOManager<int>::registerOutputHandler(test_output_handler2);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler2); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler1); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler2); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler1); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 2);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() != DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getOutputHandlersBegin() == test_output_handler1); 
	BOOST_CHECK(*(DataIOManager<int>::getOutputHandlersBegin() + 1) == test_output_handler2); 

	BOOST_CHECK(DataIOManager<int>::getOutputHandler(0) == test_output_handler1); 
	BOOST_CHECK(DataIOManager<int>::getOutputHandler(1) == test_output_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(2), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::unregisterOutputHandler(test_output_handler1));

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 1);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler2); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler1); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler2); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler1); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 1);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() != DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getOutputHandlersBegin() == test_output_handler2); 

	BOOST_CHECK(DataIOManager<int>::getOutputHandler(0) == test_output_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(1), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::unregisterOutputHandler(test_output_handler1) == false);

	BOOST_CHECK_THROW(DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersEnd()), RangeError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersBegin() + 1), RangeError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersBegin() + 2), RangeError);

	DataIOManager<int>::OutputHandlerIterator oh_it =
		DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersBegin());

	BOOST_CHECK(oh_it == DataIOManager<int>::getOutputHandlersBegin());
	BOOST_CHECK(oh_it == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 2);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler2); 
	BOOST_CHECK(*(DataIOManager<int>::getInputHandlersBegin() + 1) == test_input_handler1); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler2); 
	BOOST_CHECK(DataIOManager<int>::getInputHandler(1) == test_input_handler1); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(2), IndexError);

	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(1), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::unregisterInputHandler(test_input_handler1));

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 1);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() != DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(*DataIOManager<int>::getInputHandlersBegin() == test_input_handler2); 

	BOOST_CHECK(DataIOManager<int>::getInputHandler(0) == test_input_handler2); 
	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(1), IndexError);

	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	BOOST_CHECK(DataIOManager<int>::unregisterInputHandler(test_input_handler1) == false);

	BOOST_CHECK_THROW(DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersEnd()), RangeError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersBegin() + 1), RangeError);
	BOOST_CHECK_THROW(DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersBegin() + 2), RangeError);

	DataIOManager<int>::InputHandlerIterator ih_it = 
		DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersBegin());

	BOOST_CHECK(ih_it == DataIOManager<int>::getInputHandlersBegin());

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 0);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 0);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersBegin() == DataIOManager<int>::getInputHandlersEnd());
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersBegin() == DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK_THROW(DataIOManager<int>::getInputHandler(0), IndexError);
	BOOST_CHECK_THROW(DataIOManager<int>::getOutputHandler(0), IndexError);

//-----

	DataIOManager<int>::registerInputHandler(test_input_handler2);
	DataIOManager<int>::registerInputHandler(test_input_handler1);
	DataIOManager<int>::registerInputHandler(test_input_handler2);
	DataIOManager<int>::registerInputHandler(test_input_handler1);

	DataIOManager<int>::registerOutputHandler(test_output_handler1);
	DataIOManager<int>::registerOutputHandler(test_output_handler1);
	DataIOManager<int>::registerOutputHandler(test_output_handler2);
	DataIOManager<int>::registerOutputHandler(test_output_handler2);

	BOOST_CHECK(DataIOManager<int>::getNumInputHandlers() == 4);
	BOOST_CHECK(DataIOManager<int>::getNumOutputHandlers() == 4);

	BOOST_CHECK(DataIOManager<int>::getInputHandlersEnd() - DataIOManager<int>::getInputHandlersBegin() == 4);
	BOOST_CHECK(DataIOManager<int>::getOutputHandlersEnd() - DataIOManager<int>::getOutputHandlersBegin() == 4);


	ih_it = DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersBegin());

	BOOST_CHECK(ih_it == DataIOManager<int>::getInputHandlersBegin());

	ih_it = DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersBegin() + 1);

	BOOST_CHECK(ih_it == DataIOManager<int>::getInputHandlersBegin() + 1);

	ih_it = DataIOManager<int>::unregisterInputHandler(--DataIOManager<int>::getInputHandlersEnd());

	BOOST_CHECK(ih_it == DataIOManager<int>::getInputHandlersEnd());

	ih_it = DataIOManager<int>::unregisterInputHandler(DataIOManager<int>::getInputHandlersBegin());

	BOOST_CHECK(ih_it == DataIOManager<int>::getInputHandlersEnd());


	oh_it = DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersBegin());

	BOOST_CHECK(oh_it == DataIOManager<int>::getOutputHandlersBegin());

	oh_it = DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersBegin() + 1);

	BOOST_CHECK(oh_it == DataIOManager<int>::getOutputHandlersBegin() + 1);

	oh_it = DataIOManager<int>::unregisterOutputHandler(--DataIOManager<int>::getOutputHandlersEnd());

	BOOST_CHECK(oh_it == DataIOManager<int>::getOutputHandlersEnd());

	oh_it = DataIOManager<int>::unregisterOutputHandler(DataIOManager<int>::getOutputHandlersBegin());

	BOOST_CHECK(oh_it == DataIOManager<int>::getOutputHandlersEnd());
}
