/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterListExport.cpp 
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

#include "CDPL/Base/ControlParameterList.hpp"

#include "CallableObjectAdapter.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	const CDPL::Base::Variant& getParameterOrDef(const CDPL::Base::ControlParameterList& cpl, 
												 const CDPL::Base::ValueKey& key, 
												 const CDPL::Base::Variant& def_val, bool local = false)
	{
		const CDPL::Base::Variant& val = cpl.getParameter(key, false, local);

		if (val.isEmpty())
			return def_val;

		return val;
	}

	const CDPL::Base::Variant& getItem(const CDPL::Base::ControlParameterList& cpl, const CDPL::Base::ValueKey& key)
	{
		return cpl.getParameter(key, true);
	}

	boost::python::list getParameterKeys(const CDPL::Base::ControlParameterList& cpl)
	{
		using namespace boost;
		using namespace CDPL;

		python::list keys;

		std::for_each(cpl.getParametersBegin(), cpl.getParametersEnd(),
					  boost::bind(&python::list::append<Base::ValueKey>, boost::ref(keys),
								  boost::bind(&Base::ControlParameterList::ParameterEntry::first, _1)));
		return keys;
	}

	boost::python::list getParameterValues(const CDPL::Base::ControlParameterList& cpl)
	{
		using namespace boost;
		using namespace CDPL;

		python::list values;

		std::for_each(cpl.getParametersBegin(), cpl.getParametersEnd(),
					  boost::bind(&python::list::append<Base::Variant>, boost::ref(values),
								  boost::bind(&Base::ControlParameterList::ParameterEntry::second, _1)));
		return values;
	}

	boost::python::list getParameters(const CDPL::Base::ControlParameterList& cpl)
	{
		using namespace boost;
		using namespace CDPL;

		python::list params;

		Base::ControlParameterList::ConstParameterIterator params_end = cpl.getParametersEnd();

		for (Base::ControlParameterList::ConstParameterIterator it = cpl.getParametersBegin(); it!= params_end; ++it)  
			params.append(python::make_tuple(it->first, it->second));

		return params;
	}

	std::size_t registerParameterChangedCallback(CDPL::Base::ControlParameterList& cpl, const boost::python::object& callable)
	{
		return cpl.registerParameterChangedCallback(CDPLPythonBase::BinaryFunctionAdapter<void, CDPL::Base::ValueKey, 
													CDPL::Base::Variant, true>(callable));
	}

	std::size_t registerParameterRemovedCallback(CDPL::Base::ControlParameterList& cpl, const boost::python::object& callable)
	{
		return cpl.registerParameterRemovedCallback(CDPLPythonBase::UnaryFunctionAdapter<void, CDPL::Base::ValueKey> 
													(callable));
	}
	
	std::size_t registerParentChangedCallback(CDPL::Base::ControlParameterList& cpl, const boost::python::object& callable)
	{
		return cpl.registerParentChangedCallback(CDPLPythonBase::NoArgFunctionAdapter<void>(callable));
	}
}


void CDPLPythonBase::exportControlParameterList()
{
	using namespace boost;
	using namespace CDPL;

	void (Base::ControlParameterList::*setParameterFunc)(const Base::ValueKey&, const Base::Variant&) = 
		&Base::ControlParameterList::setParameter;

	typedef const Base::Variant& (Base::ControlParameterList::*GetParameterFuncType)(const Base::ValueKey&, bool, bool) const;

	python::class_<Base::ControlParameterList, Base::ControlParameterList::SharedPointer>("ControlParameterList")
		.def(python::init<const Base::ControlParameterList&>((python::arg("self"), python::arg("cpl"))))
		.def("setParameter", setParameterFunc, (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("removeParameter", &Base::ControlParameterList::removeParameter, (python::arg("self"), python::arg("key")))
		.def("getParameter", GetParameterFuncType(&Base::ControlParameterList::getParameter), 
			 ((python::arg("self"), python::arg("key"), python::arg("throw_") = false, python::arg("local") = false)),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getParameterOrDefault", &getParameterOrDef, 
			 ((python::arg("self"), python::arg("key"), python::arg("def_value"), python::arg("local") = false)),
			 python::return_value_policy<python::copy_const_reference>()) 
		.def("isParameterSet", &Base::ControlParameterList::isParameterSet,
			 ((python::arg("self"), python::arg("key"), python::arg("local") = false)))
		.def("clear", &Base::ControlParameterList::clear, python::arg("self"))
		.def("assign", &Base::ControlParameterList::operator=, (python::arg("self"), python::arg("cpl")), python::return_self<>())
		.def("getSize", &Base::ControlParameterList::getSize, python::arg("self"))
		.def("registerParameterChangedCallback", &registerParameterChangedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParameterChangedCallback", &Base::ControlParameterList::unregisterParameterChangedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("registerParameterRemovedCallback", &registerParameterRemovedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParameterRemovedCallback", &Base::ControlParameterList::unregisterParameterRemovedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("registerParentChangedCallback", &registerParentChangedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParentChangedCallback", &Base::ControlParameterList::unregisterParentChangedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("getParent", &Base::ControlParameterList::getParent, python::arg("self"), python::return_internal_reference<1>())
		.def("setParent", &Base::ControlParameterList::setParent, (python::arg("self"), python::arg("cpl")), 
			 python::with_custodian_and_ward<1, 2>())
		.def("getParameterKeys", &getParameterKeys, python::arg("self"))
		.def("getParameterValues", &getParameterValues, python::arg("self"))
		.def("getParameters", &getParameters, python::arg("self"))
		.def(ObjectIdentityCheckVisitor<Base::ControlParameterList>())
		.add_property("parent", 
					  python::make_function(&Base::ControlParameterList::getParent, python::return_internal_reference<1>()),
					  python::make_function(&Base::ControlParameterList::setParent, python::with_custodian_and_ward<1, 2>()))
		.add_property("parameterKeys", &getParameterKeys)
		.add_property("parameterValues", &getParameterValues)
		.add_property("parameters", &getParameters)
		.add_property("size", &Base::ControlParameterList::getSize)
		.def("__getitem__", &getItem, python::return_value_policy<python::copy_const_reference>(), (python::arg("self"), python::arg("key")))
		.def("__setitem__", setParameterFunc, (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("__delitem__", &Base::ControlParameterList::removeParameter, python::arg("self"))
		.def("__contains__", &Base::ControlParameterList::isParameterSet, (python::arg("self"), python::arg("key")))
		.def("__len__", &Base::ControlParameterList::getSize, python::arg("self"));
}
