/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AssignFunctionGeneratorVisitor.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_MATH_ASSIGNFUNCTIONGENERATORVISITOR_HPP
#define CDPL_PYTHON_MATH_ASSIGNFUNCTIONGENERATORVISITOR_HPP

#include <boost/python.hpp>
#include <boost/mpl/bool.hpp>

#include "SupportedValueTypes.hpp"


namespace CDPLPythonMath
{

    template <typename ObjectType, template <typename T> class ExpressionType, typename ValueTypeList, typename Empty> 
    struct AssignFunctionGeneratorHelper
    {

		template <typename ClassType>
		static void apply(ClassType& cl, const char* var_name) {
			using namespace boost;

			typedef typename mpl::front<ValueTypeList>::type ValueType;
			typedef typename mpl::pop_front<ValueTypeList>::type NewValueTypeList;
			typedef typename mpl::empty<NewValueTypeList>::type IsEmpty;

			cl.def("assign", &assign<ValueType>, (python::arg("self"), python::arg(var_name)),
				   python::return_self<>());

			AssignFunctionGeneratorHelper<ObjectType, ExpressionType, NewValueTypeList, IsEmpty>::apply(cl, var_name);
		}

		template <typename ValueType>
		static void assign(ObjectType& obj, const typename ExpressionType<ValueType>::SharedPointer& expr_ptr) {
			obj = *expr_ptr;
		}
    };

    template <typename ObjectType, template <typename T> class ExpressionType, typename ValueTypeList> 
    struct AssignFunctionGeneratorHelper<ObjectType, ExpressionType, ValueTypeList, boost::mpl::true_>
    {

		template <typename ClassType>
		static void apply(ClassType& cl, const char* var_name) {}
    };

    template <typename ObjectType, template <typename T> class ExpressionType, 
			  typename ValueTypeList = SupportedValueTypes> 
    struct AssignFunctionGeneratorVisitor : 
		public boost::python::def_visitor<AssignFunctionGeneratorVisitor<ObjectType, ExpressionType, ValueTypeList> >
    {
	
		friend class boost::python::def_visitor_access;

		AssignFunctionGeneratorVisitor(const char* var_name): variableName(var_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			typedef typename boost::mpl::empty<ValueTypeList>::type IsEmpty;

			AssignFunctionGeneratorHelper<ObjectType, ExpressionType, ValueTypeList, IsEmpty>::apply(cl, variableName);
		}

		const char* variableName;
    };
}

#endif // CDPL_PYTHON_MATH_ASSIGNFUNCTIONGENERATORVISITOR_HPP
