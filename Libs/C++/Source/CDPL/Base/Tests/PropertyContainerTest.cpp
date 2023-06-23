/* 
 * PropertyContainerTest.cpp 
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


#include <string>
#include <algorithm>
#include <functional>
#include <memory>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Base/PropertyContainer.hpp"
#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/Any.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	class TestPropertyContainer : public CDPL::Base::PropertyContainer 
	{

	public:
		typedef std::shared_ptr<TestPropertyContainer> SharedPointer;

		~TestPropertyContainer() {}

		using PropertyContainer::clearProperties;
		using PropertyContainer::addProperties;

		using PropertyContainer::operator=;
	};
}


BOOST_AUTO_TEST_CASE(PropertyContainerTest)
{
	using namespace CDPL;
	using namespace Base;
	using namespace std::placeholders;

	TestPropertyContainer prop_cntnr1;

	LookupKey key1 = LookupKey::create("key1");

//-----
	
	BOOST_CHECK(prop_cntnr1.getNumProperties() == 0);

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr1.getProperty(key1, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key1, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key1), ItemNotFound);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key1, std::string("default")) == "default");

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 0);

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr1.getProperty(key1, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key1, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key1), ItemNotFound);

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() == prop_cntnr1.getPropertiesEnd());

//-----

 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 0);

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr1.getProperty(key1, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key1, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key1), ItemNotFound);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key1, std::string("default")) == "default");

	prop_cntnr1.setProperty(key1, std::string("value1"));

	BOOST_CHECK(!prop_cntnr1.getProperty(key1, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key1, false).isEmpty());
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key1, std::string("default")) == "value1");

	BOOST_CHECK(prop_cntnr1.getProperty<std::string>(key1) == "value1");

	BOOST_CHECK(prop_cntnr1.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 1);

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin()->first == key1);
	BOOST_CHECK(!prop_cntnr1.getPropertiesBegin()->second.isEmpty());

//-----

	LookupKey key2 = LookupKey::create("key2");
	LookupKey key3 = LookupKey::create("key3");
	
	BOOST_CHECK(prop_cntnr1.getNumProperties() == 1);

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key2));

	BOOST_CHECK(prop_cntnr1.getProperty(key2, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key2, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key2), ItemNotFound);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key2, std::string("default2")) == "default2");

	prop_cntnr1.setProperty(key2, int(2));

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 2);

	BOOST_CHECK(!prop_cntnr1.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr1.getProperty<int>(key2) == 2);

	BOOST_CHECK(prop_cntnr1.isPropertySet(key2));

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key3));

	BOOST_CHECK(prop_cntnr1.getProperty(key3, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key3, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key3), ItemNotFound);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "default3");

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 2);

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	PropertyContainer::ConstPropertyIterator it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
															   std::bind(std::equal_to<LookupKey>(), 
																		 std::bind(&PropertyContainer::PropertyEntry::first, _1), 
																		 key1));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && !it->second.isEmpty());

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key2));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && !it->second.isEmpty());

//-----

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 2);

	BOOST_CHECK(!prop_cntnr1.isPropertySet(key3));

	BOOST_CHECK(prop_cntnr1.getProperty(key3, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key3, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key3), ItemNotFound);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "default3");

	prop_cntnr1.setProperty(key3, std::string("value3"));

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 3);

	BOOST_CHECK(!prop_cntnr1.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr1.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr1.getProperty<std::string>(key3) == "value3");

	BOOST_CHECK(prop_cntnr1.isPropertySet(key3));

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key1));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && !it->second.isEmpty());

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key2));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && !it->second.isEmpty());

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key3));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && !it->second.isEmpty());

//-----

 	LookupKey key4 = LookupKey::create("key4");
	
 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 3);
	BOOST_CHECK(!prop_cntnr1.isPropertySet(key4));

	BOOST_CHECK(prop_cntnr1.getProperty(key4, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr1.getProperty(key4, true), ItemNotFound);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<std::string>(key4), ItemNotFound);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "default4");

 	BOOST_CHECK(!prop_cntnr1.isPropertySet(key4));

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 3);

 	prop_cntnr1.setProperty(key4, std::string("value4"));

 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 4);

 	BOOST_CHECK(prop_cntnr1.isPropertySet(key4));

	BOOST_CHECK(!prop_cntnr1.getProperty(key4, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key4, false).isEmpty());

	BOOST_CHECK(prop_cntnr1.getProperty<std::string>(key4) == "value4");
	BOOST_CHECK(prop_cntnr1.getProperty(key4, false).getData<std::string>() == "value4");
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "value4");

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<float>(key4), BadCast);
	BOOST_CHECK_THROW(prop_cntnr1.getPropertyOrDefault<float>(key4, -1.0f), BadCast);

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key4));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && it->second.getData<std::string>() == "value4");

//-----

 	LookupKey key5 = LookupKey::create("key5");
	LookupKey key6 = LookupKey::create("key6");
 	LookupKey key7 = LookupKey::create("key7");

 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 4);

 	BOOST_CHECK(!prop_cntnr1.isPropertySet(key5));
 	BOOST_CHECK(!prop_cntnr1.isPropertySet(key6));
 	BOOST_CHECK(!prop_cntnr1.isPropertySet(key7));

 	prop_cntnr1.setProperty(key5, float(5.0f));
 	prop_cntnr1.setProperty(key6, std::string("value6"));
 	prop_cntnr1.setProperty(key7, char('7'));

 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 7);

 	BOOST_CHECK(prop_cntnr1.isPropertySet(key5));
 	BOOST_CHECK(prop_cntnr1.isPropertySet(key6));
 	BOOST_CHECK(prop_cntnr1.isPropertySet(key7));

	BOOST_CHECK(!prop_cntnr1.getProperty(key5, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key5, false).isEmpty());

	BOOST_CHECK(prop_cntnr1.getProperty<float>(key5) == 5.0f);
	BOOST_CHECK(prop_cntnr1.getProperty(key5, false).getData<float>() == 5.0f);
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<float>(key5, -5) == 5.0f);

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<int>(key5), BadCast);
	BOOST_CHECK_THROW(prop_cntnr1.getPropertyOrDefault<char>(key5, 'C'), BadCast);

	BOOST_CHECK(!prop_cntnr1.getProperty(key6, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key6, false).isEmpty());

	BOOST_CHECK(prop_cntnr1.getProperty<std::string>(key6) == "value6");
	BOOST_CHECK(prop_cntnr1.getProperty(key6, true).getData<std::string>() == "value6");
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<std::string>(key6, std::string("default6")) == "value6");

	BOOST_CHECK_THROW(prop_cntnr1.getProperty<int>(key6), BadCast);
	BOOST_CHECK_THROW(prop_cntnr1.getPropertyOrDefault<float>(key6, 0.0f), BadCast);

	BOOST_CHECK(!prop_cntnr1.getProperty(key7, true).isEmpty());
	BOOST_CHECK(!prop_cntnr1.getProperty(key7, false).isEmpty());

	BOOST_CHECK(prop_cntnr1.getProperty<char>(key7) == '7');
	BOOST_CHECK(prop_cntnr1.getProperty(key7, false).getData<char>() == '7');
	BOOST_CHECK(prop_cntnr1.getPropertyOrDefault<char>(key7, 'C') == '7');

	BOOST_CHECK(prop_cntnr1.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key7));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && it->second.getData<char>() == '7');

	it = std::find_if(prop_cntnr1.getPropertiesBegin(), prop_cntnr1.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key1));

	BOOST_CHECK(it != prop_cntnr1.getPropertiesEnd() && it->second.getData<std::string>() == "value1");

//-----

 	TestPropertyContainer prop_cntnr2(prop_cntnr1);

	BOOST_CHECK(prop_cntnr1.getNumProperties() == 7);
 	BOOST_CHECK(prop_cntnr2.getNumProperties() == 7);

	BOOST_CHECK(prop_cntnr2.isPropertySet(key1));
	BOOST_CHECK(prop_cntnr2.isPropertySet(key2));
	BOOST_CHECK(prop_cntnr2.isPropertySet(key3));
	BOOST_CHECK(prop_cntnr2.isPropertySet(key4));
	BOOST_CHECK(prop_cntnr2.isPropertySet(key5));
 	BOOST_CHECK(prop_cntnr2.isPropertySet(key6));
 	BOOST_CHECK(prop_cntnr2.isPropertySet(key7));

	BOOST_CHECK(!prop_cntnr2.getProperty(key1, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key1, false).isEmpty());
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<std::string>(key1, std::string("default")) == "value1");

	BOOST_CHECK(prop_cntnr2.getProperty<std::string>(key1) == "value1");

	BOOST_CHECK(!prop_cntnr2.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr2.getProperty<int>(key2) == 2);

	BOOST_CHECK(!prop_cntnr2.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr2.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr2.getProperty<std::string>(key3) == "value3");

	BOOST_CHECK(prop_cntnr2.isPropertySet(key3));

	BOOST_CHECK(!prop_cntnr2.getProperty(key4, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key4, false).isEmpty());

	BOOST_CHECK(prop_cntnr2.getProperty<std::string>(key4) == "value4");
	BOOST_CHECK(prop_cntnr2.getProperty(key4, false).getData<std::string>() == "value4");
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "value4");

	BOOST_CHECK_THROW(prop_cntnr2.getProperty<float>(key4), BadCast);
	BOOST_CHECK_THROW(prop_cntnr2.getPropertyOrDefault<float>(key4, -1.0f), BadCast);

	BOOST_CHECK(!prop_cntnr2.getProperty(key5, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key5, false).isEmpty());

	BOOST_CHECK(prop_cntnr2.getProperty<float>(key5) == 5.0f);
	BOOST_CHECK(prop_cntnr2.getProperty(key5, false).getData<float>() == 5.0f);
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<float>(key5, -5) == 5.0f);

	BOOST_CHECK_THROW(prop_cntnr2.getProperty<int>(key5), BadCast);
	BOOST_CHECK_THROW(prop_cntnr2.getPropertyOrDefault<char>(key5, 'C'), BadCast);

	BOOST_CHECK(!prop_cntnr2.getProperty(key6, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key6, false).isEmpty());

	BOOST_CHECK(prop_cntnr2.getProperty<std::string>(key6) == "value6");
	BOOST_CHECK(prop_cntnr2.getProperty(key6, true).getData<std::string>() == "value6");
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<std::string>(key6, std::string("default6")) == "value6");

	BOOST_CHECK_THROW(prop_cntnr2.getProperty<int>(key6), BadCast);
	BOOST_CHECK_THROW(prop_cntnr2.getPropertyOrDefault<float>(key6, 0.0f), BadCast);

	BOOST_CHECK(!prop_cntnr2.getProperty(key7, true).isEmpty());
	BOOST_CHECK(!prop_cntnr2.getProperty(key7, false).isEmpty());

	BOOST_CHECK(prop_cntnr2.getProperty<char>(key7) == '7');
	BOOST_CHECK(prop_cntnr2.getProperty(key7, false).getData<char>() == '7');
	BOOST_CHECK(prop_cntnr2.getPropertyOrDefault<char>(key7, 'C') == '7');

	BOOST_CHECK(prop_cntnr2.getPropertiesBegin() != prop_cntnr2.getPropertiesEnd());

	it = std::find_if(prop_cntnr2.getPropertiesBegin(), prop_cntnr2.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key7));

	BOOST_CHECK(it != prop_cntnr2.getPropertiesEnd() && it->second.getData<char>() == '7');

	it = std::find_if(prop_cntnr2.getPropertiesBegin(), prop_cntnr2.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key1));

	BOOST_CHECK(it != prop_cntnr2.getPropertiesEnd() && it->second.getData<std::string>() == "value1");

//-----

 	TestPropertyContainer prop_cntnr3;

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 0);
	BOOST_CHECK(prop_cntnr3.getPropertiesBegin() == prop_cntnr3.getPropertiesEnd());

	prop_cntnr3.setProperty(key1, int(100));

	BOOST_CHECK(!prop_cntnr3.getProperty(key1, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key1, 50) == 100);

	BOOST_CHECK(prop_cntnr3.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 1);

	BOOST_CHECK(prop_cntnr3.getPropertiesBegin() != prop_cntnr1.getPropertiesEnd());

	BOOST_CHECK(prop_cntnr3.getPropertiesBegin()->first == key1);
	BOOST_CHECK(!prop_cntnr3.getPropertiesBegin()->second.isEmpty());

 	BOOST_CHECK(&(prop_cntnr3 = prop_cntnr1) == &prop_cntnr3);

 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 7);
	BOOST_CHECK(prop_cntnr3.getNumProperties() == 7);

	BOOST_CHECK(prop_cntnr3.isPropertySet(key1));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key2));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key3));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key4));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key5));
 	BOOST_CHECK(prop_cntnr3.isPropertySet(key6));
 	BOOST_CHECK(prop_cntnr3.isPropertySet(key7));

	BOOST_CHECK(!prop_cntnr3.getProperty(key1, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key1, std::string("default")) == "value1");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key1) == "value1");

	BOOST_CHECK(!prop_cntnr3.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr3.getProperty<int>(key2) == 2);

	BOOST_CHECK(!prop_cntnr3.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key3) == "value3");

	BOOST_CHECK(!prop_cntnr3.getProperty(key4, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key4, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key4) == "value4");
	BOOST_CHECK(prop_cntnr3.getProperty(key4, false).getData<std::string>() == "value4");
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "value4");

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<float>(key4), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<float>(key4, -1.0f), BadCast);

	BOOST_CHECK(!prop_cntnr3.getProperty(key5, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key5, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<float>(key5) == 5.0f);
	BOOST_CHECK(prop_cntnr3.getProperty(key5, false).getData<float>() == 5.0f);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<float>(key5, -5) == 5.0f);

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<int>(key5), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<char>(key5, 'C'), BadCast);

	BOOST_CHECK(!prop_cntnr3.getProperty(key6, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key6, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key6) == "value6");
	BOOST_CHECK(prop_cntnr3.getProperty(key6, true).getData<std::string>() == "value6");
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key6, std::string("default6")) == "value6");

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<int>(key6), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<float>(key6, 0.0f), BadCast);

	BOOST_CHECK(!prop_cntnr3.getProperty(key7, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key7, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<char>(key7) == '7');
	BOOST_CHECK(prop_cntnr3.getProperty(key7, false).getData<char>() == '7');
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<char>(key7, 'C') == '7');

	BOOST_CHECK(prop_cntnr3.getPropertiesBegin() != prop_cntnr3.getPropertiesEnd());

	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key7));

	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<char>() == '7');

	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key1));

	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<std::string>() == "value1");

//-----

 	prop_cntnr3.clearProperties();

 	BOOST_CHECK(prop_cntnr3.getNumProperties() == 0);

	BOOST_CHECK(prop_cntnr3.getPropertiesBegin() == prop_cntnr3.getPropertiesEnd());
	
 	BOOST_CHECK(!prop_cntnr3.isPropertySet(key1));

 	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key1, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<std::string>(key1), ItemNotFound);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key2));

	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key2, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<int>(key2), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key2, -1) == -1);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key3));

	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key3, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key3, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<std::string>(key3), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "default3");

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key4));

	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key4, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key4, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<std::string>(key4), ItemNotFound);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key5));

	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key5, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key5, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<float>(key5), ItemNotFound);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key6));

	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key6, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key6, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<std::string>(key6), ItemNotFound);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key7));

	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key7, true), ItemNotFound);
	BOOST_CHECK(prop_cntnr3.getProperty(key7, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty<char>(key7), ItemNotFound);

//-----

	BOOST_CHECK(&(prop_cntnr3 = prop_cntnr1) == &prop_cntnr3);

 	BOOST_CHECK(prop_cntnr1.getNumProperties() == 7);
	BOOST_CHECK(prop_cntnr3.getNumProperties() == 7);

	BOOST_CHECK(prop_cntnr3.isPropertySet(key1));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key2));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key3));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key4));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key5));
 	BOOST_CHECK(prop_cntnr3.isPropertySet(key6));
 	BOOST_CHECK(prop_cntnr3.isPropertySet(key7));

	BOOST_CHECK(!prop_cntnr3.getProperty(key1, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key1, std::string("default")) == "value1");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key1) == "value1");

	BOOST_CHECK(!prop_cntnr3.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr3.getProperty<int>(key2) == 2);

	BOOST_CHECK(!prop_cntnr3.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key3) == "value3");

	BOOST_CHECK(!prop_cntnr3.getProperty(key4, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key4, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key4) == "value4");
	BOOST_CHECK(prop_cntnr3.getProperty(key4, false).getData<std::string>() == "value4");
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "value4");

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<float>(key4), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<float>(key4, -1.0f), BadCast);

	BOOST_CHECK(!prop_cntnr3.getProperty(key5, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key5, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<float>(key5) == 5.0f);
	BOOST_CHECK(prop_cntnr3.getProperty(key5, false).getData<float>() == 5.0f);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<float>(key5, -5) == 5.0f);

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<int>(key5), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<char>(key5, 'C'), BadCast);

	BOOST_CHECK(!prop_cntnr3.getProperty(key6, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key6, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key6) == "value6");
	BOOST_CHECK(prop_cntnr3.getProperty(key6, true).getData<std::string>() == "value6");
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key6, std::string("default6")) == "value6");

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<int>(key6), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<float>(key6, 0.0f), BadCast);

	BOOST_CHECK(!prop_cntnr3.getProperty(key7, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key7, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<char>(key7) == '7');
	BOOST_CHECK(prop_cntnr3.getProperty(key7, false).getData<char>() == '7');
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<char>(key7, 'C') == '7');

	BOOST_CHECK(prop_cntnr3.getPropertiesBegin() != prop_cntnr3.getPropertiesEnd());

	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key7));

	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<char>() == '7');

	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key1));
	
	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<std::string>() == "value1");

//-----

	prop_cntnr3.removeProperty(key7);
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key7));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 6);

	prop_cntnr3.removeProperty(key4);
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key4));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 5);

	prop_cntnr3.removeProperty(key4);
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key4));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 5);

	prop_cntnr3.removeProperty(key5);
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key5));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 4);

	prop_cntnr3.removeProperty(key6);
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key6));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 3);

	BOOST_CHECK(prop_cntnr3.isPropertySet(key1));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key2));
	BOOST_CHECK(prop_cntnr3.isPropertySet(key3));

	BOOST_CHECK(!prop_cntnr3.getProperty(key1, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key1, std::string("default")) == "value1");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key1) == "value1");

	BOOST_CHECK(!prop_cntnr3.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr3.getProperty<int>(key2) == 2);

	BOOST_CHECK(!prop_cntnr3.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key3) == "value3");

//-----

 	prop_cntnr3.setProperty(key1, std::string("key1_prop_val"));
	prop_cntnr3.setProperty(key2, std::string("key2_prop_val"));
	prop_cntnr3.setProperty(key3, std::string("key3_prop_val"));

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 3);

	BOOST_CHECK(prop_cntnr3.isPropertySet(key1));

	BOOST_CHECK(!prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key1, true).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key1) == "key1_prop_val");

	BOOST_CHECK(prop_cntnr3.isPropertySet(key2));

	BOOST_CHECK(!prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key2, true).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key2) == "key2_prop_val");

	BOOST_CHECK(prop_cntnr3.isPropertySet(key3));

	BOOST_CHECK(!prop_cntnr3.getProperty(key3, false).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key3, true).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key3) == "key3_prop_val");


	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key1));

	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<std::string>() == "key1_prop_val");

	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key2));

	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<std::string>() == "key2_prop_val");

	it = std::find_if(prop_cntnr3.getPropertiesBegin(), prop_cntnr3.getPropertiesEnd(),
					  std::bind(std::equal_to<LookupKey>(), 
								std::bind(&PropertyContainer::PropertyEntry::first, _1), 
								key3));

	BOOST_CHECK(it != prop_cntnr3.getPropertiesEnd() && it->second.getData<std::string>() == "key3_prop_val");
		
//-----

	prop_cntnr2.removeProperty(key1);
	BOOST_CHECK(!prop_cntnr2.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr2.getNumProperties() == 6);

	prop_cntnr2.removeProperty(key5);
	BOOST_CHECK(!prop_cntnr2.isPropertySet(key5));

	BOOST_CHECK(prop_cntnr2.getNumProperties() == 5);

	prop_cntnr2.removeProperty(key6);
	BOOST_CHECK(!prop_cntnr2.isPropertySet(key6));

	BOOST_CHECK(prop_cntnr2.getNumProperties() == 4);

//-----
   
	prop_cntnr3.addProperties(prop_cntnr2);

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 5);

	BOOST_CHECK(prop_cntnr3.isPropertySet(key1));

	BOOST_CHECK(!prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key1, true).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key1) == "key1_prop_val");

	BOOST_CHECK(!prop_cntnr3.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr3.getProperty<int>(key2) == 2);

	BOOST_CHECK(!prop_cntnr3.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key3) == "value3");

	BOOST_CHECK(!prop_cntnr3.getProperty(key4, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key4, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key4) == "value4");
	BOOST_CHECK(prop_cntnr3.getProperty(key4, false).getData<std::string>() == "value4");
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "value4");

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<float>(key4), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<float>(key4, -1.0f), BadCast);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key5));
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key6));

	BOOST_CHECK(prop_cntnr3.getProperty(key5, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getProperty(key6, false).isEmpty());

	BOOST_CHECK(!prop_cntnr3.getProperty(key7, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key7, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<char>(key7) == '7');
	BOOST_CHECK(prop_cntnr3.getProperty(key7, false).getData<char>() == '7');
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<char>(key7, 'C') == '7');

//-----
   
 	prop_cntnr3.clearProperties();

 	BOOST_CHECK(prop_cntnr3.getNumProperties() == 0);

	BOOST_CHECK(prop_cntnr3.getPropertiesBegin() == prop_cntnr3.getPropertiesEnd());

	prop_cntnr3.addProperties(prop_cntnr2);

	BOOST_CHECK(prop_cntnr3.getNumProperties() == 4);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key1));

	BOOST_CHECK(prop_cntnr3.getProperty(key1, false).isEmpty());
	BOOST_CHECK_THROW(prop_cntnr3.getProperty(key1, true), ItemNotFound);

	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key1, std::string("default1")) == "default1");

	BOOST_CHECK(!prop_cntnr3.getProperty(key2, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key2, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<int>(key2, -1) == 2);

	BOOST_CHECK(prop_cntnr3.getProperty<int>(key2) == 2);

	BOOST_CHECK(!prop_cntnr3.getProperty(key3, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key3, false).isEmpty());

	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<int>(key3, -1), BadCast);
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key3, std::string("default3")) == "value3");

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key3) == "value3");

	BOOST_CHECK(!prop_cntnr3.getProperty(key4, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key4, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<std::string>(key4) == "value4");
	BOOST_CHECK(prop_cntnr3.getProperty(key4, false).getData<std::string>() == "value4");
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<std::string>(key4, std::string("default4")) == "value4");

	BOOST_CHECK_THROW(prop_cntnr3.getProperty<float>(key4), BadCast);
	BOOST_CHECK_THROW(prop_cntnr3.getPropertyOrDefault<float>(key4, -1.0f), BadCast);

	BOOST_CHECK(!prop_cntnr3.isPropertySet(key5));
	BOOST_CHECK(!prop_cntnr3.isPropertySet(key6));

	BOOST_CHECK(prop_cntnr3.getProperty(key5, false).isEmpty());
	BOOST_CHECK(prop_cntnr3.getProperty(key6, false).isEmpty());

	BOOST_CHECK(!prop_cntnr3.getProperty(key7, true).isEmpty());
	BOOST_CHECK(!prop_cntnr3.getProperty(key7, false).isEmpty());

	BOOST_CHECK(prop_cntnr3.getProperty<char>(key7) == '7');
	BOOST_CHECK(prop_cntnr3.getProperty(key7, false).getData<char>() == '7');
	BOOST_CHECK(prop_cntnr3.getPropertyOrDefault<char>(key7, 'C') == '7');
	BOOST_CHECK(prop_cntnr3.getProperty(key7).getData<char>() == '7');
}

