/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterContainerExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <algorithm>

#include <boost/python.hpp>
#include <boost/bind.hpp>

#include "CDPL/Base/ControlParameterContainer.hpp"

#include "CallableObjectAdapter.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	const CDPL::Base::Variant& getParameterOrDef(CDPL::Base::ControlParameterContainer& cntnr, 
												 const CDPL::Base::LookupKey& key, 
												 const CDPL::Base::Variant& def_val, bool local = false)
	{
		const CDPL::Base::Variant& val = cntnr.getParameter(key, false, local);

		if (val.isEmpty())
			return def_val;

		return val;
	}

	const CDPL::Base::Variant& getItem(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Base::LookupKey& key)
	{
		return cntnr.getParameter(key, true);
	}

	boost::python::list getParameterKeys(CDPL::Base::ControlParameterContainer& cntnr)
	{
		using namespace boost;
		using namespace CDPL;

		python::list keys;

		std::for_each(cntnr.getParametersBegin(), cntnr.getParametersEnd(),
					  boost::bind(&python::list::append<Base::LookupKey>, boost::ref(keys),
								  boost::bind(&Base::ControlParameterContainer::ParameterEntry::first, _1)));
		return keys;
	}

	boost::python::list getParameterValues(CDPL::Base::ControlParameterContainer& cntnr)
	{
		using namespace boost;
		using namespace CDPL;

		python::list values;

		std::for_each(cntnr.getParametersBegin(), cntnr.getParametersEnd(),
					  boost::bind(&python::list::append<Base::Variant>, boost::ref(values),
								  boost::bind(&Base::ControlParameterContainer::ParameterEntry::second, _1)));
		return values;
	}

	boost::python::list getParameters(CDPL::Base::ControlParameterContainer& cntnr)
	{
		using namespace boost;
		using namespace CDPL;

		python::list params;

		Base::ControlParameterContainer::ConstParameterIterator params_end = cntnr.getParametersEnd();

		for (Base::ControlParameterContainer::ConstParameterIterator it = cntnr.getParametersBegin(); it!= params_end; ++it)  
			params.append(python::make_tuple(it->first, it->second));

		return params;
	}

	std::size_t registerParameterChangedCallback(CDPL::Base::ControlParameterContainer& cntnr, const boost::python::object& callable)
	{
		return cntnr.registerParameterChangedCallback(CDPLPythonBase::BinaryFunctionAdapter<void, CDPL::Base::LookupKey, 
													CDPL::Base::Variant, true>(callable));
	}

	std::size_t registerParameterRemovedCallback(CDPL::Base::ControlParameterContainer& cntnr, const boost::python::object& callable)
	{
		return cntnr.registerParameterRemovedCallback(CDPLPythonBase::UnaryFunctionAdapter<void, CDPL::Base::LookupKey> 
													(callable));
	}
	
	std::size_t registerParentChangedCallback(CDPL::Base::ControlParameterContainer& cntnr, const boost::python::object& callable)
	{
		return cntnr.registerParentChangedCallback(CDPLPythonBase::NoArgFunctionAdapter<void>(callable));
	}

	void addParameters(CDPL::Base::ControlParameterContainer& cntnr, CDPL::Base::ControlParameterContainer& other)
	{
		cntnr.addParameters(other);
	}

	void copyParameters(CDPL::Base::ControlParameterContainer& cntnr, CDPL::Base::ControlParameterContainer& other)
	{
		cntnr.copyParameters(other);
	}

	struct ControlParameterContainerWrapper : CDPL::Base::ControlParameterContainer, boost::python::wrapper<CDPL::Base::ControlParameterContainer>
	{
	};
}


void CDPLPythonBase::exportControlParameterContainer()
{
	using namespace boost;
	using namespace CDPL;

	void (Base::ControlParameterContainer::*setParameterFunc)(const Base::LookupKey&, const Base::Variant&) = 
		&Base::ControlParameterContainer::setParameter;

	typedef const Base::Variant& (Base::ControlParameterContainer::*GetParameterFuncType)(const Base::LookupKey&, bool, bool) const;

	python::class_<ControlParameterContainerWrapper, boost::noncopyable>("ControlParameterContainer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("setParameter", setParameterFunc, (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("removeParameter", &Base::ControlParameterContainer::removeParameter, (python::arg("self"), python::arg("key")))
		.def("getParameter", GetParameterFuncType(&Base::ControlParameterContainer::getParameter), 
			 ((python::arg("self"), python::arg("key"), python::arg("throw_") = false, python::arg("local") = false)),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getParameterOrDefault", &getParameterOrDef, 
			 ((python::arg("self"), python::arg("key"), python::arg("def_value"), python::arg("local") = false)),
			 python::return_value_policy<python::copy_const_reference>()) 
		.def("isParameterSet", &Base::ControlParameterContainer::isParameterSet,
			 ((python::arg("self"), python::arg("key"), python::arg("local") = false)))
		.def("clearParameters", &Base::ControlParameterContainer::clearParameters, python::arg("self"))
		.def("addParameters", &addParameters, (python::arg("self"), python::arg("cntnr")))
		.def("copyParameters", &copyParameters, (python::arg("self"), python::arg("cntnr")))
		.def("getNumParameters", &Base::ControlParameterContainer::getNumParameters, python::arg("self"))
		.def("registerParameterChangedCallback", &registerParameterChangedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParameterChangedCallback", &Base::ControlParameterContainer::unregisterParameterChangedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("registerParameterRemovedCallback", &registerParameterRemovedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParameterRemovedCallback", &Base::ControlParameterContainer::unregisterParameterRemovedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("registerParentChangedCallback", &registerParentChangedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParentChangedCallback", &Base::ControlParameterContainer::unregisterParentChangedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("getParent", &Base::ControlParameterContainer::getParent, python::arg("self"), python::return_internal_reference<1>())
		.def("setParent", &Base::ControlParameterContainer::setParent, (python::arg("self"), python::arg("cntnr")), 
			 python::with_custodian_and_ward<1, 2>())
		.def("getParameterKeys", &getParameterKeys, python::arg("self"))
		.def("getParameterValues", &getParameterValues, python::arg("self"))
		.def("getParameters", &getParameters, python::arg("self"))
		.def(ObjectIdentityCheckVisitor<Base::ControlParameterContainer>())
		.add_property("parent", python::make_function(&Base::ControlParameterContainer::getParent, python::return_internal_reference<1>()),
					  python::make_function(&Base::ControlParameterContainer::setParent, python::with_custodian_and_ward<1, 2>()))
		.add_property("parameterKeys", &getParameterKeys)
		.add_property("parameterValues", &getParameterValues)
		.add_property("parameters", &getParameters)
		.add_property("numParameters", &Base::ControlParameterContainer::getNumParameters)
		.def("__getitem__", &getItem, python::return_value_policy<python::copy_const_reference>(), (python::arg("self"), python::arg("key")))
		.def("__setitem__", setParameterFunc, (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("__delitem__", &Base::ControlParameterContainer::removeParameter, python::arg("self"))
		.def("__contains__", &Base::ControlParameterContainer::isParameterSet, (python::arg("self"), python::arg("key")))
		.def("__len__", &Base::ControlParameterContainer::getNumParameters, python::arg("self"));
}
