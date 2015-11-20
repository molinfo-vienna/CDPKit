/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControllableExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Base/Controllable.hpp"

#include "CallableObjectAdapter.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	const CDPL::Base::Variant& getParameterOrDef(CDPL::Base::Controllable& controllable, 
												 const CDPL::Base::ValueKey& key, 
												 const CDPL::Base::Variant& def_val, bool local = false)
	{
		const CDPL::Base::Variant& val = controllable.getParameter(key, false, local);

		if (val.isEmpty())
			return def_val;

		return val;
	}

	std::size_t registerParameterChangedCallback(CDPL::Base::Controllable& controllable, const boost::python::object& callable)
	{
		return controllable.registerParameterChangedCallback(CDPLPythonBase::BinaryFunctionAdapter<void, 
															 CDPL::Base::ValueKey, 
															 CDPL::Base::Variant, true>(callable));
	}

	std::size_t registerParameterRemovedCallback(CDPL::Base::Controllable& controllable, const boost::python::object& callable)
	{
		return controllable.registerParameterRemovedCallback(CDPLPythonBase::UnaryFunctionAdapter<void, 
															 CDPL::Base::ValueKey> 
															 (callable));
	}
	
	std::size_t registerParentChangedCallback(CDPL::Base::Controllable& controllable, const boost::python::object& callable)
	{
		return controllable.registerParentChangedCallback(CDPLPythonBase::NoArgFunctionAdapter<void>(callable));
	}

	void setControllableParent(CDPL::Base::Controllable& controllable, CDPL::Base::Controllable& parent)
	{
		controllable.setParent(parent);
	}

	const CDPL::Base::Variant& getItem(CDPL::Base::Controllable& controllable, const CDPL::Base::ValueKey& key) 
	{
		return controllable.getParameter(key, true);
	}

	struct ControllableWrapper : CDPL::Base::Controllable, boost::python::wrapper<CDPL::Base::Controllable> {};
}


void CDPLPythonBase::exportControllable()
{
	using namespace boost;
	using namespace CDPL;

	void (Base::Controllable::*setParameterFunc)(const Base::ValueKey&, const Base::Variant&) = 
		&Base::Controllable::setParameter;
	
	void (Base::Controllable::*setParentFunc)(const Base::ControlParameterList*) = &Base::Controllable::setParent;

	const Base::ControlParameterList& (Base::Controllable::*getParametersFunc)() const = &Base::Controllable::getParameters;

	typedef const Base::Variant& (Base::Controllable::*GetParameterFuncType)(const Base::ValueKey&, bool, bool) const;

	python::class_<ControllableWrapper, boost::noncopyable>("Controllable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("setParameters", &Base::Controllable::setParameters, (python::arg("self"), python::arg("cpl")))
		.def("setParameter", setParameterFunc, (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("removeParameter", &Base::Controllable::removeParameter, (python::arg("self"), python::arg("key")))
		.def("getParameter", GetParameterFuncType(&Base::Controllable::getParameter), 
			 ((python::arg("self"), python::arg("key"), python::arg("throw_") = false, 
			   python::arg("local") = false)), python::return_value_policy<python::copy_const_reference>())
		.def("getParameterOrDefault", &getParameterOrDef, 
			 ((python::arg("self"), python::arg("key"), python::arg("def_value"), 
			   python::arg("local") = false)), python::return_value_policy<python::copy_const_reference>()) 
		.def("isParameterSet", &Base::Controllable::isParameterSet, 
			 ((python::arg("self"), python::arg("key"), python::arg("local") = false)))
		.def("clearParameters", &Base::Controllable::clearParameters, python::arg("self"))
		.def("getParent", &Base::Controllable::getParent, python::arg("self"), python::return_internal_reference<1>())
		.def("setParent", setParentFunc, (python::arg("self"), python::arg("cpl")), python::with_custodian_and_ward<1, 2>())
		.def("setParent", &setControllableParent, (python::arg("self"), python::arg("controllable")), python::with_custodian_and_ward<1, 2>())
		.def("registerParameterChangedCallback", &registerParameterChangedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParameterChangedCallback", &Base::Controllable::unregisterParameterChangedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("registerParameterRemovedCallback", &registerParameterRemovedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParameterRemovedCallback", &Base::Controllable::unregisterParameterRemovedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("registerParentChangedCallback", &registerParentChangedCallback, (python::arg("self"), python::arg("func")))
		.def("unregisterParentChangedCallback", &Base::Controllable::unregisterParentChangedCallback, 
			 (python::arg("self"), python::arg("id")))
		.def("getNumParameters", &Base::Controllable::getNumParameters, python::arg("self"))
		.def("getParameters", getParametersFunc, python::arg("self"), python::return_internal_reference<1>())
		.def(ObjectIdentityCheckVisitor<Base::Controllable>())
		.def("__getitem__", &getItem, python::return_value_policy<python::copy_const_reference>(), 
			 (python::arg("self"), python::arg("key")))
		.def("__setitem__", setParameterFunc, (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("__delitem__", &Base::Controllable::removeParameter, (python::arg("self"), python::arg("key")))		
		.def("__contains__", &Base::Controllable::isParameterSet, (python::arg("self"), python::arg("key")))
		.add_property("parent", 
					  python::make_function(&Base::Controllable::getParent, python::return_internal_reference<1>()),
					  python::make_function(setParentFunc, python::with_custodian_and_ward<1, 2>()))
		.add_property("parameters", python::make_function(getParametersFunc, python::return_internal_reference<1>()))
		.add_property("numParameters", &Base::Controllable::getNumParameters);
}

