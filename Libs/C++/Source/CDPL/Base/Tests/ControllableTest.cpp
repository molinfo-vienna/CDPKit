/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControllableTest.cpp 
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

#include "CDPL/Base/Controllable.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/ValueKey.hpp"
#include "CDPL/Base/Variant.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "TestChangeListener.hpp"


namespace
{

	class TestControllable : public CDPL::Base::Controllable {}; 
}


BOOST_AUTO_TEST_CASE(ControllableTest)
{
	using namespace CDPL;
	using namespace Base;

	TestControllable ctrl1;
	
	ControlParameterList::SharedPointer cpl_ptr(new ControlParameterList());

	ValueKey key1 = ValueKey::create("key1");
	ValueKey key2 = ValueKey::create("key2");
	ValueKey key3 = ValueKey::create("key3");

	TestChangeListener cl1;
	TestChangeListener cl2;

	std::size_t param_changed_cl1_id = ctrl1.registerParameterChangedCallback(boost::bind(&TestChangeListener::parameterChanged, 
																						  boost::ref(cl1), _1, _2));
	std::size_t param_removed_cl1_id = ctrl1.registerParameterRemovedCallback(boost::bind(&TestChangeListener::parameterRemoved, 
																						  boost::ref(cl1), _1));
	std::size_t parent_changed_cl1_id = ctrl1.registerParentChangedCallback(boost::bind(&TestChangeListener::parentChanged, 
																						boost::ref(cl1)));
	cpl_ptr->registerParameterChangedCallback(boost::bind(&TestChangeListener::parameterChanged, 
														  boost::ref(cl2), _1, _2));
	cpl_ptr->registerParameterRemovedCallback(boost::bind(&TestChangeListener::parameterRemoved, 
														  boost::ref(cl2), _1));
	cpl_ptr->registerParentChangedCallback(boost::bind(&TestChangeListener::parentChanged, 
													   boost::ref(cl2)));
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	BOOST_CHECK(ctrl1.getNumParameters() == 0);

	BOOST_CHECK(ctrl1.getParametersBegin() == ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	ctrl1.setParameter(key1, std::string("param1"));

	BOOST_CHECK(ctrl1.getNumParameters() == 1);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());
	BOOST_CHECK(ctrl1.getParametersBegin()->first == key1);
	BOOST_CHECK(ctrl1.getParametersBegin()->second.getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(!ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key2, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key2, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key2, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key2, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key2, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "default");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key1);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param1");

//-----

	cl1.reset();

	ctrl1.setParameter(key2, std::string("param2"));

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key2);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param2");

//-----

	cl1.reset();

	ctrl1.setParameter(key1, std::string("param11"));

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param11");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key1);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param11");

//-----

	cl1.reset();

	BOOST_CHECK(ctrl1.removeParameter(key1));

	BOOST_CHECK(ctrl1.getNumParameters() == 1);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParametersBegin()->first == key2);
	BOOST_CHECK(ctrl1.getParametersBegin()->second.getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key1);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	ctrl1.setParameter(key2, Variant());

	BOOST_CHECK(ctrl1.getNumParameters() == 0);

	BOOST_CHECK(ctrl1.getParametersBegin() == ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(!ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key2, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key2, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key2, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key2, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key2, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "default");

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key2);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	ctrl1.setParameter(key2, std::string("param21"));

	BOOST_CHECK(ctrl1.getNumParameters() == 1);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParametersBegin()->first == key2);
	BOOST_CHECK(ctrl1.getParametersBegin()->second.getData<std::string>() == "param21");

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param21");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param21");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param21");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param21");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param21");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param21");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param21");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param21");

	BOOST_CHECK(cl1.numParamChangedCalls == 1);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key2);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param21");

//-----

	cl1.reset();

	ctrl1.clearParameters();

	BOOST_CHECK(ctrl1.getNumParameters() == 0);

	BOOST_CHECK(ctrl1.getParametersBegin() == ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

	BOOST_CHECK(!ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key2, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key2, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key2, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key2, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key2, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "default");

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 1);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == key2);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	ctrl1.setParent(cpl_ptr.get());
	
	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 1);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

//-----

	cl1.reset();

	ctrl1.setParameter(key2, std::string("param2"));
	ctrl1.setParameter(key1, std::string("param1"));
	
	BOOST_CHECK(cl1.numParamChangedCalls == 2);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == key1);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.getData<std::string>() == "param1");

	cpl_ptr->setParameter(key3, std::string("param3"));

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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == cpl_ptr.get());

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(cpl_ptr->getSize() == 1);

	BOOST_CHECK(cpl_ptr->getParametersBegin() != cpl_ptr->getParametersEnd());
	BOOST_CHECK(cpl_ptr->getParametersBegin()->first == key3);
	BOOST_CHECK(cpl_ptr->getParametersBegin()->second.getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

//-----

	cl1.reset();
	cl2.reset();

	cpl_ptr->setParameter(key1, std::string("param11"));
	
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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == cpl_ptr.get());

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(cpl_ptr->getSize() == 2);

	BOOST_CHECK(cpl_ptr->getParametersBegin() != cpl_ptr->getParametersEnd());

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

	BOOST_CHECK(cpl_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();

	BOOST_CHECK(cpl_ptr->removeParameter(key3));
	BOOST_CHECK(!cpl_ptr->removeParameter(key3));

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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == cpl_ptr.get());

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl_ptr->getSize() == 1);

	BOOST_CHECK(cpl_ptr->getParametersBegin() != cpl_ptr->getParametersEnd());

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(!cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(!cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl_ptr->getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "default");

	BOOST_CHECK(cpl_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();

	cpl_ptr->setParameter(key1, Variant());
	
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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == cpl_ptr.get());

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl_ptr->getSize() == 0);

	BOOST_CHECK(cpl_ptr->getParametersBegin() == cpl_ptr->getParametersEnd());

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(!cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(!cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl_ptr->getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "default");

	BOOST_CHECK(!cpl_ptr->isParameterSet(key1, true));
	BOOST_CHECK(!cpl_ptr->isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl_ptr->getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	cl1.reset();
	cl2.reset();

	ctrl1.setParent(0);

	cpl_ptr->setParameter(key3, std::string("param3"));
	
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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl_ptr->getSize() == 1);

	BOOST_CHECK(cpl_ptr->getParametersBegin() != cpl_ptr->getParametersEnd());
	BOOST_CHECK(cpl_ptr->getParametersBegin()->first == key3);
	BOOST_CHECK(cpl_ptr->getParametersBegin()->second.getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

//-----

	cl1.reset();
	cl2.reset();

	cpl_ptr->setParameter(key1, std::string("param11"));
	
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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).isEmpty());


	BOOST_CHECK(cpl_ptr->getSize() == 2);

	BOOST_CHECK(cpl_ptr->getParametersBegin() != cpl_ptr->getParametersEnd());

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

	BOOST_CHECK(cpl_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();
	
	ctrl1.setParent(cpl_ptr.get());

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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == cpl_ptr.get());

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(cpl_ptr->getSize() == 2);

	BOOST_CHECK(cpl_ptr->getParametersBegin() != cpl_ptr->getParametersEnd());

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK(cpl_ptr->getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "param3");

	BOOST_CHECK(cpl_ptr->isParameterSet(key1, true));
	BOOST_CHECK(cpl_ptr->isParameterSet(key1, false));

	BOOST_CHECK(cpl_ptr->getParameter(key1, true, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, true, false).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, true).getData<std::string>() == "param11");
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, false).getData<std::string>() == "param11");

	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameter<std::string>(key1, false) == "param11");

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "param11");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "param11");

//-----

	cl1.reset();
	cl2.reset();
	
	cpl_ptr->clear();

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

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == cpl_ptr.get());

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "default");


	BOOST_CHECK(cpl_ptr->getSize() == 0);

	BOOST_CHECK(cpl_ptr->getParametersBegin() == cpl_ptr->getParametersEnd());

	BOOST_CHECK(cpl_ptr->getParent() == 0);

	BOOST_CHECK(!cpl_ptr->isParameterSet(key3, true));
	BOOST_CHECK(!cpl_ptr->isParameterSet(key3, false));

	BOOST_CHECK_THROW(cpl_ptr->getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(cpl_ptr->getParameter(key3, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key3, false), ItemNotFound);

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key3, "default", false) == "default");

	BOOST_CHECK(!cpl_ptr->isParameterSet(key1, true));
	BOOST_CHECK(!cpl_ptr->isParameterSet(key1, false));

	BOOST_CHECK_THROW(cpl_ptr->getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(cpl_ptr->getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(cpl_ptr->getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(cpl_ptr->getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	cl1.reset();
	cl2.reset();
	
	cpl_ptr = ControlParameterList::SharedPointer();

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 1);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(ctrl1.getNumParameters() == 2);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK(ctrl1.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");


	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).isEmpty());

//-----

	TestControllable ctrl3;

	ctrl3 = ctrl1;

	BOOST_CHECK(ctrl3.getNumParameters() == 2);

	BOOST_CHECK(ctrl3.getParametersBegin() != ctrl3.getParametersEnd());

	BOOST_CHECK(ctrl3.getParent() == 0);

	BOOST_CHECK(ctrl3.isParameterSet(key1, true));
	BOOST_CHECK(ctrl3.isParameterSet(key1, false));

	BOOST_CHECK(ctrl3.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl3.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl3.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl3.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl3.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl3.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl3.isParameterSet(key2, true));
	BOOST_CHECK(ctrl3.isParameterSet(key2, false));

	BOOST_CHECK(ctrl3.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl3.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl3.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl3.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl3.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl3.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

//-----

	TestControllable ctrl4(ctrl3);

	BOOST_CHECK(ctrl4.getNumParameters() == 2);

	BOOST_CHECK(ctrl4.getParametersBegin() != ctrl4.getParametersEnd());

	BOOST_CHECK(ctrl4.getParent() == 0);

	BOOST_CHECK(ctrl4.isParameterSet(key1, true));
	BOOST_CHECK(ctrl4.isParameterSet(key1, false));

	BOOST_CHECK(ctrl4.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl4.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl4.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl4.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl4.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl4.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl4.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl4.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl4.isParameterSet(key2, true));
	BOOST_CHECK(ctrl4.isParameterSet(key2, false));

	BOOST_CHECK(ctrl4.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl4.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl4.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl4.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl4.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl4.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl4.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl4.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

//-----

	TestControllable ctrl5;

	ctrl5.setParameters(ctrl4.getParameters());

	BOOST_CHECK(ctrl5.getNumParameters() == 2);

	BOOST_CHECK(ctrl5.getParametersBegin() != ctrl5.getParametersEnd());

	BOOST_CHECK(ctrl5.getParent() == 0);

	BOOST_CHECK(ctrl5.isParameterSet(key1, true));
	BOOST_CHECK(ctrl5.isParameterSet(key1, false));

	BOOST_CHECK(ctrl5.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl5.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl5.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl5.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl5.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl5.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl5.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl5.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl5.isParameterSet(key2, true));
	BOOST_CHECK(ctrl5.isParameterSet(key2, false));

	BOOST_CHECK(ctrl5.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl5.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl5.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl5.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl5.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl5.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl5.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl5.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

//-----

	cl1.reset();

	ctrl1.unregisterParameterChangedCallback(param_changed_cl1_id);
	ctrl1.unregisterParameterRemovedCallback(param_removed_cl1_id);
	ctrl1.unregisterParentChangedCallback(parent_changed_cl1_id);

	ctrl1.setParameter(key1, Variant());

	BOOST_CHECK(cl1.numParamChangedCalls == 0);
	BOOST_CHECK(cl1.numParamRemovedCalls == 0);
	BOOST_CHECK(cl1.numParentChangedCalls == 0);
	BOOST_CHECK(cl1.changedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.removedParamKey == RESET_KEY);
	BOOST_CHECK(cl1.changedParamValue.isEmpty());

	BOOST_CHECK(ctrl1.getNumParameters() == 1);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());
	BOOST_CHECK(ctrl1.getParametersBegin()->first == key2);
	BOOST_CHECK(ctrl1.getParametersBegin()->second.getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParent() == 0);

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(!ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, false), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).isEmpty());

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, false), ItemNotFound);

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "default");

//-----

	ctrl1.setParent(ctrl3);

	BOOST_CHECK(ctrl1.getParent() == &ctrl3.getParameters());

	ctrl3.setParameter(key3, std::string("param3"));

	BOOST_CHECK(ctrl1.getNumParameters() == 1);

	BOOST_CHECK(ctrl1.getParametersBegin() != ctrl1.getParametersEnd());
	BOOST_CHECK(ctrl1.getParametersBegin()->first == key2);
	BOOST_CHECK(ctrl1.getParametersBegin()->second.getData<std::string>() == "param2");

	BOOST_CHECK(!ctrl1.isParameterSet(key1, true));
	BOOST_CHECK(ctrl1.isParameterSet(key1, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key1, true, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl1.getParameter(key1, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key1, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl1.isParameterSet(key2, true));
	BOOST_CHECK(ctrl1.isParameterSet(key2, false));

	BOOST_CHECK(ctrl1.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl1.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl1.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(!ctrl1.isParameterSet(key3, true));
	BOOST_CHECK(ctrl1.isParameterSet(key3, false));

	BOOST_CHECK_THROW(ctrl1.getParameter(key3, true, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl1.getParameter(key3, false, true).isEmpty());
	BOOST_CHECK(ctrl1.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK_THROW(ctrl1.getParameter<std::string>(key3, true), ItemNotFound);
	BOOST_CHECK(ctrl1.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", true) == "default");
	BOOST_CHECK(ctrl1.getParameterOrDefault<std::string>(key3, "default", false) == "param3");


	BOOST_CHECK(ctrl3.getNumParameters() == 3);

	BOOST_CHECK(ctrl3.getParametersBegin() != ctrl3.getParametersEnd());

	BOOST_CHECK(ctrl3.getParent() == 0);

	BOOST_CHECK(ctrl3.isParameterSet(key1, true));
	BOOST_CHECK(ctrl3.isParameterSet(key1, false));

	BOOST_CHECK(ctrl3.getParameter(key1, true, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl3.getParameter(key1, true, false).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl3.getParameter(key1, false, true).getData<std::string>() == "param1");
	BOOST_CHECK(ctrl3.getParameter(key1, false, false).getData<std::string>() == "param1");

	BOOST_CHECK(ctrl3.getParameter<std::string>(key1, true) == "param1");
	BOOST_CHECK(ctrl3.getParameter<std::string>(key1, false) == "param1");

	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key1, "default", true) == "param1");
	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key1, "default", false) == "param1");

	BOOST_CHECK(ctrl3.isParameterSet(key2, true));
	BOOST_CHECK(ctrl3.isParameterSet(key2, false));

	BOOST_CHECK(ctrl3.getParameter(key2, true, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl3.getParameter(key2, true, false).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl3.getParameter(key2, false, true).getData<std::string>() == "param2");
	BOOST_CHECK(ctrl3.getParameter(key2, false, false).getData<std::string>() == "param2");

	BOOST_CHECK(ctrl3.getParameter<std::string>(key2, true) == "param2");
	BOOST_CHECK(ctrl3.getParameter<std::string>(key2, false) == "param2");

	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key2, "default", true) == "param2");
	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key2, "default", false) == "param2");

	BOOST_CHECK(ctrl3.isParameterSet(key3, true));
	BOOST_CHECK(ctrl3.isParameterSet(key3, false));

	BOOST_CHECK(ctrl3.getParameter(key3, true, true).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl3.getParameter(key3, true, false).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl3.getParameter(key3, false, true).getData<std::string>() == "param3");
	BOOST_CHECK(ctrl3.getParameter(key3, false, false).getData<std::string>() == "param3");

	BOOST_CHECK(ctrl3.getParameter<std::string>(key3, true) == "param3");
	BOOST_CHECK(ctrl3.getParameter<std::string>(key3, false) == "param3");

	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key3, "default", true) == "param3");
	BOOST_CHECK(ctrl3.getParameterOrDefault<std::string>(key3, "default", false) == "param3");
}
