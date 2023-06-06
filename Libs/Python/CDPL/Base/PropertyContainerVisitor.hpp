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


namespace CDPLPythonBase
{

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

		static const CDPL::Base::Any& getItem(CDPL::Base::PropertyContainer& cntnr, const CDPL::Base::LookupKey& key) {
			return cntnr.getProperty(key, true);
		}

		bool noLen;
	};
}

#endif // CDPL_PYTHON_BASE_PROPERTYCONTAINERVISITOR_HPP
