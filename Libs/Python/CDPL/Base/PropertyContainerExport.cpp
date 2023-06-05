/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyContainerExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Base/PropertyContainer.hpp"

#include "PropertyContainerVisitor.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	const CDPL::Base::Variant& getPropertyOrDef(CDPL::Base::PropertyContainer& cntnr, 
												const CDPL::Base::LookupKey& key, 
												const CDPL::Base::Variant& def_val)
	{
		const CDPL::Base::Variant& val = cntnr.getProperty(key, false);

		if (val.isEmpty())
			return def_val;

		return val;
	}

	boost::python::list getPropertyKeys(CDPL::Base::PropertyContainer& cntnr)
	{
		using namespace boost;
		using namespace CDPL;

		python::list keys;

		std::for_each(cntnr.getPropertiesBegin(), cntnr.getPropertiesEnd(),
					  boost::bind(&python::list::append<Base::LookupKey>, boost::ref(keys),
								  boost::bind(&Base::PropertyContainer::PropertyEntry::first, _1)));

		return keys;
	}

	boost::python::list getPropertyValues(CDPL::Base::PropertyContainer& cntnr)
	{
		using namespace boost;
		using namespace CDPL;

		python::list values;

		std::for_each(cntnr.getPropertiesBegin(), cntnr.getPropertiesEnd(),
					  boost::bind(&python::list::append<Base::Variant>, boost::ref(values),
								  boost::bind(&Base::PropertyContainer::PropertyEntry::second, _1)));

		return values;
	}

	boost::python::list getProperties(CDPL::Base::PropertyContainer& cntnr)
	{
		using namespace boost;
		using namespace CDPL;

		python::list props;

		Base::PropertyContainer::ConstPropertyIterator props_end = cntnr.getPropertiesEnd();

		for (Base::PropertyContainer::ConstPropertyIterator it = cntnr.getPropertiesBegin(); it!= props_end; ++it)  
			props.append(python::make_tuple(it->first, it->second));

		return props;
	}

	void addProperties(CDPL::Base::PropertyContainer& cntnr, CDPL::Base::PropertyContainer& other)
	{
		cntnr.addProperties(other);
	}

	void copyProperties(CDPL::Base::PropertyContainer& cntnr, CDPL::Base::PropertyContainer& other)
	{
		cntnr.copyProperties(other);
	}

	struct PropertyContainerWrapper : CDPL::Base::PropertyContainer, boost::python::wrapper<CDPL::Base::PropertyContainer>
	{
	};
}


void CDPLPythonBase::exportPropertyContainer()
{
	using namespace boost;
	using namespace CDPL;

	const Base::Variant& (Base::PropertyContainer::*getPropertyFunc)(const Base::LookupKey&, bool) const
		= &Base::PropertyContainer::getProperty;
			
	python::class_<PropertyContainerWrapper, boost::noncopyable>("PropertyContainer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(ObjectIdentityCheckVisitor<Base::PropertyContainer>())
		.def("getNumProperties", &Base::PropertyContainer::getNumProperties, python::arg("self"))
		.def("getPropertyOrDefault", &getPropertyOrDef, 
			 ((python::arg("self"), python::arg("key"), python::arg("def_value"))),
			 python::return_value_policy<python::copy_const_reference>()) 
		.def("getPropertyKeys", &getPropertyKeys, python::arg("self"))
		.def("getPropertyValues", &getPropertyValues, python::arg("self"))
		.def("getProperties", &getProperties, python::arg("self"))
		.def("setProperty", &Base::PropertyContainer::setProperty,
			 (python::arg("self"), python::arg("key"), python::arg("value")))
		.def("removeProperty", &Base::PropertyContainer::removeProperty,
			 (python::arg("self"), python::arg("key")))
		.def("getProperty", getPropertyFunc,
			 (python::arg("self"), python::arg("key"), python::arg("throw_") = false),
			 python::return_value_policy<python::copy_const_reference>())
		.def("isPropertySet", &Base::PropertyContainer::isPropertySet,
			 (python::arg("self"), python::arg("key")))
		.def("clearProperties", &Base::PropertyContainer::clearProperties,
			 python::arg("self"))
		.def("addProperties", &addProperties,
			 (python::arg("self"), python::arg("cntnr")))
		.def("copyProperties", &copyProperties,
			 (python::arg("self"), python::arg("cntnr")))
		.def("swap", &Base::PropertyContainer::swap,
			 (python::arg("self"), python::arg("cntnr")))
		.def(PropertyContainerSpecialFunctionsVisitor())
		.add_property("propertyKeys", &getPropertyKeys)
		.add_property("propertyValues", &getPropertyValues)
		.add_property("properties", &getProperties)
		.add_property("numProperties", &Base::PropertyContainer::getNumProperties);
}

