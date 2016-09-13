/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterListTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>
#include <boost/bind.hpp>

#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/Variant.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "TestChangeListener.hpp"


BOOST_AUTO_TEST_CASE(ControlParameterListTest)
{
	using namespace CDPL;
	using namespace Base;

	ControlParameterList cpl1;
	
	ControlParameterList::SharedPointer cpl2_ptr(new ControlParameterList());

	LookupKey key1 = LookupKey::create("key1");
	LookupKey key2 = LookupKey::create("key2");
	LookupKey key3 = LookupKey::create("key3");

	TestChangeListener cl1;
	TestChangeListener cl2;

	std::size_t param_changed_cl1_id = cpl1.registerParameterChangedCallback(boost::bind(&TestChangeListener::parameterChanged, 
																						 boost::ref(cl1), _1, _2));
	std::size_t param_removed_cl1_id = cpl1.registerParameterRemovedCallback(boost::bind(&TestChangeListener::parameterRemoved, 
																						 boost::ref(cl1), _1));
	std::size_t parent_changed_cl1_id = cpl1.registerParentChangedCallback(boost::bind(&TestChangeListener::parentChanged, 
																					   boost::ref(cl1)));

	cpl2_ptr->registerParameterChangedCallback(boost::bind(&TestChangeListener::parameterChanged, 
														   boost::ref(cl2), _1, _2));
	cpl2_ptr->registerParameterRemovedCallback(boost::bind(&TestChangeListener::parameterRemoved, 
														   boost::ref(cl2), _1));
	cpl2_ptr->registerParentChangedCallback(boost::bind(&TestChangeListener::parentChanged, 
														boost::ref(cl2)));

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	BOOST_CHECK(cpl1.getNumParameters() == 0);

	BOOST_CHECK(cpl1.getParametersBegin() == cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(!cpl1.isParameterSet(key1, true));
	BOOST_CHECK(!cpl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	cpl1.setParameter(key1, std::string("param1"));

	BOOST_CHECK(cpl1.getNumParameters() == 1);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());
	BOOST_CHECK(cpl1.getParametersBegin()->first == key1);
	BOOST_CHECK(cpl1.getParametersBegin()->second.getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(!cpl1.isParameterSet(key2, true));
	BOOST_CHECK(!cpl1.isParameterSet(key2, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key2, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key2, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key2, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key2, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key2, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key2, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "default");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key1);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param1");

//-----

	cl1.reset();

	cpl1.setParameter(key2, std::string("param2"));

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key2);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param2");

//-----

	cl1.reset();

	cpl1.setParameter(key1, std::string("param11"));

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param11");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key1);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param11");

//-----

	cl1.reset();

	BOOST_CHECK(cpl1.removeParameter(key1));

	BOOST_CHECK(cpl1.getNumParameters() == 1);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParametersBegin()->first == key2);
	BOOST_CHECK(cpl1.getParametersBegin()->second.getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(!cpl1.isParameterSet(key1, true));
	BOOST_CHECK(!cpl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key1);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	cpl1.setParameter(key2, Variant());

	BOOST_CHECK(cpl1.getNumParameters() == 0);

	BOOST_CHECK(cpl1.getParametersBegin() == cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(!cpl1.isParameterSet(key1, true));
	BOOST_CHECK(!cpl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(!cpl1.isParameterSet(key2, true));
	BOOST_CHECK(!cpl1.isParameterSet(key2, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key2, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key2, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key2, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key2, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key2, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key2, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "default");

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key2);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	cpl1.setParameter(key2, std::string("param21"));

	BOOST_CHECK(cpl1.getNumParameters() == 1);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParametersBegin()->first == key2);
	BOOST_CHECK(cpl1.getParametersBegin()->second.getData<std::string>() == "param21");

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(!cpl1.isParameterSet(key1, true));
	BOOST_CHECK(!cpl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param21");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param21");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param21");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param21");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param21");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param21");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param21");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param21");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key2);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param21");

//-----

	cl1.reset();

	cpl1.clearParameters();

	BOOST_CHECK(cpl1.getNumParameters() == 0);

	BOOST_CHECK(cpl1.getParametersBegin() == cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(!cpl1.isParameterSet(key1, true));
	BOOST_CHECK(!cpl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(!cpl1.isParameterSet(key2, true));
	BOOST_CHECK(!cpl1.isParameterSet(key2, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key2, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key2, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key2, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key2, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key2, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key2, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "default");

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key2);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	cpl1.setParent(cpl2_ptr.get());
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 1);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	cpl1.setParameter(key2, std::string("param2"));
	cpl1.setParameter(key1, std::string("param1"));
	
	BOOST_CHECK(cl1.numParamChangedCalls == 2);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key1);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param1");

	cpl2_ptr->setParameter(key3, std::string("param3"));

	BOOST_CHECK(cl1.numParamChangedCalls == 3);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key3);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param3");

	BOOST_CHECK(cl2.numParamChangedCalls == 1);
	BOOST_CHECK(cl2.numParamRemovedCalls == 0);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == key3);
	BOOST_CHECK(cl2.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.changedParamValue.getData<std::string>() == "param3");

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == cpl2_ptr.get());

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 1);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() != cpl2_ptr->getParametersEnd());
	BOOST_CHECK(cpl2_ptr->getParametersBegin()->first == key3);
	BOOST_CHECK(cpl2_ptr->getParametersBegin()->second.getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

//-----

	cl1.reset();
	cl2.reset();

	cpl2_ptr->setParameter(key1, std::string("param11"));
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 1);
	BOOST_CHECK(cl2.numParamRemovedCalls == 0);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == key1);
	BOOST_CHECK(cl2.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.changedParamValue.getData<std::string>() == "param11");

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == cpl2_ptr.get());

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 2);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() != cpl2_ptr->getParametersEnd());

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();

	BOOST_CHECK(cpl2_ptr->removeParameter(key3));
	BOOST_CHECK(!cpl2_ptr->removeParameter(key3));
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key3);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 0);
	BOOST_CHECK(cl2.numParamRemovedCalls == 1);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.removedParamKey == key3);
	BOOST_CHECK(cl2.changedParamValue.isEmpty());

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == cpl2_ptr.get());

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(!cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 1);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() != cpl2_ptr->getParametersEnd());

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(!cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(!cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "default");

	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();

	cpl2_ptr->setParameter(key1, Variant());
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 0);
	BOOST_CHECK(cl2.numParamRemovedCalls == 1);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.removedParamKey == key1);
	BOOST_CHECK(cl2.changedParamValue.isEmpty());

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == cpl2_ptr.get());

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(!cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 0);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() == cpl2_ptr->getParametersEnd());

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(!cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(!cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "default");

	BOOST_CHECK(!cpl2_ptr->isParameterSet(key1, true));
	BOOST_CHECK(!cpl2_ptr->isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	cl1.reset();
	cl2.reset();

	cpl1.setParent(0);

	cpl2_ptr->setParameter(key3, std::string("param3"));
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 1);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 1);
	BOOST_CHECK(cl2.numParamRemovedCalls == 0);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == key3);
	BOOST_CHECK(cl2.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.changedParamValue.getData<std::string>() == "param3");

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(!cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 1);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() != cpl2_ptr->getParametersEnd());
	BOOST_CHECK(cpl2_ptr->getParametersBegin()->first == key3);
	BOOST_CHECK(cpl2_ptr->getParametersBegin()->second.getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

//-----

	cl1.reset();
	cl2.reset();

	cpl2_ptr->setParameter(key1, std::string("param11"));
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 1);
	BOOST_CHECK(cl2.numParamRemovedCalls == 0);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == key1);
	BOOST_CHECK(cl2.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.changedParamValue.getData<std::string>() == "param11");

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(!cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).isEmpty());


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 2);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() != cpl2_ptr->getParametersEnd());

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();
	
	cpl1.setParent(cpl2_ptr.get());

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 1);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 0);
	BOOST_CHECK(cl2.numParamRemovedCalls == 0);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.changedParamValue.isEmpty());

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == cpl2_ptr.get());

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 2);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() != cpl2_ptr->getParametersEnd());

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl2_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();
	
	cpl2_ptr->clearParameters();

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key3);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cl2.numParamChangedCalls == 0);
	BOOST_CHECK(cl2.numParamRemovedCalls == 2);
	BOOST_CHECK(cl2.numParentChangedCalls == 0);
	BOOST_CHECK(cl2.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl2.changedParamValue.isEmpty());

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == cpl2_ptr.get());

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(!cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl2_ptr->getNumParameters() == 0);

	BOOST_CHECK(cpl2_ptr->getParametersBegin() == cpl2_ptr->getParametersEnd());

	BOOST_CHECK(cpl2_ptr->getParent() == 0);

	BOOST_CHECK(!cpl2_ptr->isParameterSet(key3, true));
	BOOST_CHECK(!cpl2_ptr->isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl2_ptr->getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "default");

	BOOST_CHECK(!cpl2_ptr->isParameterSet(key1, true));
	BOOST_CHECK(!cpl2_ptr->isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl2_ptr->getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl2_ptr->getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl2_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	cl1.reset();
	cl2.reset();
	
	cpl2_ptr = ControlParameterList::SharedPointer();

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 1);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cpl1.getNumParameters() == 2);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key1, true));
	BOOST_CHECK(cpl1.isParameterSet(key1, false));

	BOOST_CHECK(cpl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!cpl1.isParameterSet(key3, true));
	BOOST_CHECK(!cpl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key3, false, false).isEmpty());

//-----

	ControlParameterList cpl3;

	cpl3 = cpl1;

	BOOST_CHECK(cpl3.getNumParameters() == 2);

	BOOST_CHECK(cpl3.getParametersBegin() != cpl3.getParametersEnd());

	BOOST_CHECK(cpl3.getParent() == 0);

	BOOST_CHECK(cpl3.isParameterSet(key1, true));
	BOOST_CHECK(cpl3.isParameterSet(key1, false));

	BOOST_CHECK(cpl3.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl3.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl3.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl3.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl3.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl3.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl3.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl3.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl3.isParameterSet(key2, true));
	BOOST_CHECK(cpl3.isParameterSet(key2, false));

	BOOST_CHECK(cpl3.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl3.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl3.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl3.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl3.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl3.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl3.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl3.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

//-----

	ControlParameterList cpl4(cpl3);

	BOOST_CHECK(cpl4.getNumParameters() == 2);

	BOOST_CHECK(cpl4.getParametersBegin() != cpl4.getParametersEnd());

	BOOST_CHECK(cpl4.getParent() == 0);

	BOOST_CHECK(cpl4.isParameterSet(key1, true));
	BOOST_CHECK(cpl4.isParameterSet(key1, false));

	BOOST_CHECK(cpl4.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl4.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(cpl4.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(cpl4.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(cpl4.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(cpl4.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(cpl4.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(cpl4.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(cpl4.isParameterSet(key2, true));
	BOOST_CHECK(cpl4.isParameterSet(key2, false));

	BOOST_CHECK(cpl4.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl4.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl4.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl4.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl4.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl4.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl4.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl4.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

//-----

	cl1.reset();

	cpl1.unregisterParameterChangedCallback(param_changed_cl1_id);
	cpl1.unregisterParameterRemovedCallback(param_removed_cl1_id);
	cpl1.unregisterParentChangedCallback(parent_changed_cl1_id);

	cpl1.setParameter(key1, Variant());

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(cpl1.getNumParameters() == 1);

	BOOST_CHECK(cpl1.getParametersBegin() != cpl1.getParametersEnd());
	BOOST_CHECK(cpl1.getParametersBegin()->first == key2);
	BOOST_CHECK(cpl1.getParametersBegin()->second.getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParent() == 0);

	BOOST_CHECK(cpl1.isParameterSet(key2, true));
	BOOST_CHECK(cpl1.isParameterSet(key2, false));

	BOOST_CHECK(cpl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(cpl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(cpl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(cpl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(!cpl1.isParameterSet(key1, true));
	BOOST_CHECK(!cpl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");
}
