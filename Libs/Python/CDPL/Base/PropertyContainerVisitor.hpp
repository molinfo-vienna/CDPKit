/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyContainerVisitor.hpp 
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


#ifndef CDPL_PYTHON_BASE_PROPERTYCONTAINERVISITOR_HPP
#define CDPL_PYTHON_BASE_PROPERTYCONTAINERVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define PROPERTYCONTAINER_IMPL(Wrapper)
/*	
#define PROPERTYCONTAINER_IMPL(Wrapper)			                                                    \
	void setProperty(const CDPL::Base::LookupKey& key, const CDPL::Base::Variant& value) {          \
		if (boost::python::override f = this->get_override("setProperty")) {                        \
			f(boost::ref(key), boost::ref(value));                                                  \
			return;                                                                                 \
		}                                                                                           \
                                                                                                    \
		CDPL::Base::PropertyContainer::setProperty(key, value);                                     \
	}                                                                                               \
                                                                                                    \
	void setPropertyDef(const CDPL::Base::LookupKey& key, const CDPL::Base::Variant& value) {       \
		CDPL::Base::PropertyContainer::setProperty(key, value);                                     \
	}                                                                                               \
                                                                                                    \
	const CDPL::Base::Variant& getProperty(const CDPL::Base::LookupKey& key, bool throw_) const {   \
		if (boost::python::override f = this->get_override("getProperty"))                          \
			return f(boost::ref(key), throw_);                                                      \
                                                                                                    \
		return CDPL::Base::PropertyContainer::getProperty(key, throw_);                             \
	}                                                                                               \
                                                                                                    \
	const CDPL::Base::Variant& getPropertyDef(const CDPL::Base::LookupKey& key, bool throw_) const {\
		return CDPL::Base::PropertyContainer::getProperty(key, throw_);                             \
	}                                                                                               \
                                                                                                    \
	bool isPropertySet(const CDPL::Base::LookupKey& key) const {                                    \
		if (boost::python::override f = this->get_override("isPropertySet"))                        \
			return f(boost::ref(key));                                                              \
                                                                                                    \
		return CDPL::Base::PropertyContainer::isPropertySet(key);                                   \
	}                                                                                               \
                                                                                                    \
	bool isPropertySetDef(const CDPL::Base::LookupKey& key) const {                                 \
		return CDPL::Base::PropertyContainer::isPropertySet(key);                                   \
	}                                                                                               \
                                                                                                    \
	bool removeProperty(const CDPL::Base::LookupKey& key) {                                         \
		if (boost::python::override f = this->get_override("removeProperty"))                       \
			return f(boost::ref(key));                                                              \
                                                                                                    \
		return CDPL::Base::PropertyContainer::removeProperty(key);                                  \
	}                                                                                               \
                                                                                                    \
	bool removePropertyDef(const CDPL::Base::LookupKey& key) {                                      \
		return CDPL::Base::PropertyContainer::removeProperty(key);                                  \
	}                                                                                               \
                                                                                                    \
	void clearProperties() {                                                                        \
		if (boost::python::override f = this->get_override("clearProperties")) {                    \
			f();                                                                                    \
			return;                                                                                 \
		}                                                                                           \
                                                                                                    \
		CDPL::Base::PropertyContainer::clearProperties();                                           \
	}                                                                                               \
                                                                                                    \
	void clearPropertiesDef() {                                                                     \
		CDPL::Base::PropertyContainer::clearProperties();                                           \
	}                                                                                               \
                                                                                                    \
	void addProperties(const CDPL::Base::PropertyContainer& cntnr) {                                \
		if (boost::python::override f = this->get_override("addProperties")) {                      \
			f(boost::ref(cntnr));                                                                   \
			return;                                                                                 \
		}                                                                                           \
                                                                                                    \
		CDPL::Base::PropertyContainer::addProperties(cntnr);                                        \
	}                                                                                               \
	                                                                                                \
	static void addPropertiesDef(CDPL::Base::PropertyContainer& self, CDPL::Base::PropertyContainer& cntnr) { \
		if (dynamic_cast<Wrapper*>(boost::addressof(self)))                                         \
			self.PropertyContainer::addProperties(cntnr);                                           \
		else                                                                                        \
			self.addProperties(cntnr);                                                              \
	}	                                                                                            \
                                                                                                    \
	void copyProperties(const CDPL::Base::PropertyContainer& cntnr) {                              	\
		if (boost::python::override f = this->get_override("copyProperties")) {                     \
			f(boost::ref(cntnr));                                                                   \
			return;                                                                                 \
		}                                                                                           \
                                                                                                    \
		CDPL::Base::PropertyContainer::copyProperties(cntnr);                                       \
	}                                                                                               \
	                                                                                                \
	static void copyPropertiesDef(CDPL::Base::PropertyContainer& self, CDPL::Base::PropertyContainer& cntnr) { \
		if (dynamic_cast<Wrapper*>(boost::addressof(self)))                                         \
			self.PropertyContainer::copyProperties(cntnr);                                          \
		else                                                                                        \
			self.copyProperties(cntnr);                                                             \
	}                                                                                               \
                                                                                                    \
	void swap(CDPL::Base::PropertyContainer& cntnr) {                                               \
		if (boost::python::override f = this->get_override("swap")) {                               \
			f(boost::ref(cntnr));                                                                   \
			return;                                                                                 \
		}                                                                                           \
                                                                                                    \
		CDPL::Base::PropertyContainer::swap(cntnr);                                                 \
	}
*/

namespace CDPLPythonBase
{

	template <typename Wrapper>
	class PropertyContainerVirtualFunctionsVisitor : 
		public boost::python::def_visitor<PropertyContainerVirtualFunctionsVisitor<Wrapper> >
	{

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
/*
			using namespace boost;
			using namespace CDPL;

			const Base::Variant& (Base::PropertyContainer::*getPropertyFunc)(const Base::LookupKey&, bool) const
				= &Base::PropertyContainer::getProperty;

			cl	
				.def("setProperty", &Base::PropertyContainer::setProperty, &Wrapper::setPropertyDef,
					 (python::arg("self"), python::arg("key"), python::arg("value")))
				.def("removeProperty", &Base::PropertyContainer::removeProperty, &Wrapper::removePropertyDef,
					 (python::arg("self"), python::arg("key")))
				.def("getProperty", getPropertyFunc, &Wrapper::getPropertyDef,
					 (python::arg("self"), python::arg("key"), python::arg("throw_") = false),
					 python::return_value_policy<python::copy_const_reference>())
				.def("isPropertySet", &Base::PropertyContainer::isPropertySet, &Wrapper::isPropertySetDef,
					 (python::arg("self"), python::arg("key")))
				.def("clearProperties", &Base::PropertyContainer::clearProperties, &Wrapper::clearPropertiesDef,
					 python::arg("self"))
				.def("addProperties", &Wrapper::addPropertiesDef,
					 (python::arg("self"), python::arg("cntnr")))
				.def("copyProperties", &Wrapper::copyPropertiesDef,
					 (python::arg("self"), python::arg("cntnr")))
				.def("swap", &Wrapper::swap,
					 (python::arg("self"), python::arg("cntnr")));
*/
		}
	};

	class PropertyContainerSpecialFunctionsVisitor : 
		public boost::python::def_visitor<PropertyContainerSpecialFunctionsVisitor>
	{

		friend class boost::python::def_visitor_access;

	public:
		PropertyContainerSpecialFunctionsVisitor(bool no_len = false): noLen(no_len) {}
		
	private:
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl	
				.def("__getitem__", &getItem, (python::arg("self"), python::arg("key")), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("__contains__", &Base::PropertyContainer::isPropertySet, (python::arg("self"), python::arg("key")))
				.def("__setitem__", &Base::PropertyContainer::setProperty, (python::arg("self"), python::arg("key"), python::arg("value")))
				.def("__delitem__", &Base::PropertyContainer::removeProperty, (python::arg("self"), python::arg("key")));

			if (!noLen)
				cl.def("__len__", &Base::PropertyContainer::getNumProperties, python::arg("self"));
		}

		static const CDPL::Base::Variant& getItem(CDPL::Base::PropertyContainer& cntnr, const CDPL::Base::LookupKey& key) {
			return cntnr.getProperty(key, true);
		}

		bool noLen;
	};
}

#endif // CDPL_PYTHON_BASE_PROPERTYCONTAINERVISITOR_HPP
