/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyMatchExpression.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::PropertyMatchExpression.
 */

#ifndef CDPL_CHEM_PROPERTYMATCHEXPRESSION_HPP
#define CDPL_CHEM_PROPERTYMATCHEXPRESSION_HPP

#include <boost/function.hpp>

#include "CDPL/Chem/MatchExpression.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief PropertyMatchExpression.
		 * \tparam ValueType The type of the checked property values.
		 * \tparam MatchFunc The type of a binary functor class that implements the logic of testing the target property
		 *                   values against the query property values. The overloaded function call operator is
		 *                   required to take the target property value as its first argument and the query value as the
		 *                   second argument (both provided as \c const reference to \c ValueType). The returned result
		 *                   must be implicitly convertible to type \c bool (\c true indicates a match, \c false a mismatch).
		 * \tparam ObjType1 The type of the primary query/target objects for which the expression gets evaluated.
		 * \tparam ObjType2 The type of secondary query/target objects which provide auxiliary information for
		 *                  expression evaluation.
		 */
		template <typename ValueType, typename MatchFunc, typename ObjType1, typename ObjType2 = void>
		class PropertyMatchExpression : public MatchExpression<ObjType1, ObjType2>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %PropertyMatchExpression instances.
			 */
			typedef boost::shared_ptr<PropertyMatchExpression> SharedPointer;

			/**
			 * \brief Type of the generic functor class used to store user-defined property accessor functions.
			 *
			 * \c %PropertyFunction allows to wrap any function pointer or function object compatible with a return type of \c ValueType and 
			 * two arguments of type <tt>const ObjType1&</tt> and <tt>const ObjType2&</tt>. For details refer to the <em>Boost.Function</em>
			 * documentation [\ref BFUN]. 
			 */
			typedef boost::function2<ValueType, const ObjType1&, const ObjType2&> PropertyFunction;
	
			/**
			 * \brief Constructs a \c %PropertyMatchExpression instance that performs query/target object equivalence tests based on the 
			 *        property values returned by \a property_func.
			 * \param property_func A PropertyMatchExpression::PropertyFunction2 instance that wraps the specified property value accessor function.
			 */
			PropertyMatchExpression(const PropertyFunction& property_func): 
				value(), matchFunc(), propertyFunc(property_func), fixed(false) {}

			/**
			 * \brief Constructs a \c %PropertyMatchExpression instance that performs query/target object equivalence tests based on the 
			 *        target object property values returned by \a property_func and the specified query value.
			 * \param value The query property value.
			 * \param property_func A PropertyMatchExpression::PropertyFunction2 instance that wraps the specified target property value accessor function.
			 */
			PropertyMatchExpression(const ValueType& value, const PropertyFunction& property_func):
				value(value), matchFunc(), propertyFunc(property_func), fixed(true) {}
	
			/**
			 * \brief Checks whether the value of the target object propery matches the query property value.
			 *
			 * The actual equivalence test between the query and target property values is performed by an
			 * instance of the function object type that was provided as template argument for \a MatchFunc. 
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression (ignored).	
			 * \return \c true if the target property value matches the query property value under the conditions defined by \a MatchFunc,
			 *         and \c false otherwise.
			 */
			bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, 
							const ObjType2& target_obj2, const Base::Any& aux_data) const;

		private:
			ValueType         value;
			MatchFunc         matchFunc;
			PropertyFunction  propertyFunc;
			bool              fixed;
		};

		/**
		 * \brief PropertyMatchExpression.
		 * \tparam ValueType The type of the checked property values.
		 * \tparam MatchFunc The type of a binary functor class that implements the logic of testing the target property
		 *                   values against the query property values. The overloaded function call operator is
		 *                   required to take the target property value as its first argument and the query value as the
		 *                   second argument (both provided as \c const reference to \c ValueType). The returned result
		 *                   must be implicitly convertible to type \c bool (\c true indicates a match, \c false a mismatch).
		 * \tparam ObjType The type of the query/target objects for which the expression gets evaluated.
		 */
		template <typename ValueType, typename MatchFunc, typename ObjType>
		class PropertyMatchExpression<ValueType, MatchFunc, ObjType, void> : public MatchExpression<ObjType, void>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %PropertyMatchExpression instances.
			 */
			typedef boost::shared_ptr<PropertyMatchExpression> SharedPointer;
	
			/**
			 * \brief Type of the generic functor class used to store user-defined property accessor functions.
			 *
			 * \c %PropertyFunction allows to wrap any function pointer or function object compatible with a return type of \c ValueType and 
			 * an argument of type <tt>const ObjType&</tt>. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<ValueType, const ObjType&> PropertyFunction;
		
			/**
			 * \brief Constructs a \c %PropertyMatchExpression instance that performs query/target object equivalence tests based on the 
			 *        property values returned by \a property_func.
			 * \param property_func A PropertyMatchExpression::PropertyFunction instance that wraps the specified property value accessor function.
			 */
			PropertyMatchExpression(const PropertyFunction& property_func): 
				value(), matchFunc(), propertyFunc(property_func), fixed(false) {}

			/**
			 * \brief Constructs a \c %PropertyMatchExpression instance that performs query/target object equivalence tests based on the 
			 *        target object property values returned by \a property_func and the specified query value.
			 * \param value The query property value.
			 * \param property_func A PropertyMatchExpression::PropertyFunction instance that wraps the specified target property value accessor function.
			 */
			PropertyMatchExpression(const ValueType& value, const PropertyFunction& property_func):
				value(value), matchFunc(), propertyFunc(property_func), fixed(true) {}

			/**
			 * \brief Checks whether the value of the target object propery matches the query property value.
			 *
			 * The actual equivalence test between the query and target property values is performed by an
			 * instance of the function object type that was provided as template argument for \a MatchFunc. 
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression (ignored).	
			 * \return \c true if the target property value matches the query property value under the conditions defined by \a MatchFunc,
			 *         and \c false otherwise.
			 */
			bool operator()(const ObjType& query_obj, const ObjType& target_obj, const Base::Any& aux_data) const;

		private:
			ValueType         value;
			MatchFunc         matchFunc;
			PropertyFunction  propertyFunc;
			bool              fixed;
		};
	}
}


// Implementation

template <typename ValueType, typename MatchFunc, typename ObjType1, typename ObjType2>
bool CDPL::Chem::PropertyMatchExpression<ValueType, MatchFunc, ObjType1, ObjType2>::operator()(const ObjType1& query_obj1, const ObjType2& query_obj2,
																									  const ObjType1& target_obj1, const ObjType2& target_obj2,
																									  const Base::Any&) const
{
	if (fixed)
		return matchFunc(propertyFunc(target_obj1, target_obj2), value);

	return matchFunc(propertyFunc(target_obj1, target_obj2), propertyFunc(query_obj1, query_obj2));
}


template <typename ValueType, typename MatchFunc, typename ObjType>
bool CDPL::Chem::PropertyMatchExpression<ValueType, MatchFunc, ObjType, void>::operator()(const ObjType& query_obj, const ObjType& target_obj,
																								 const Base::Any&) const
{
	if (fixed)
		return matchFunc(propertyFunc(target_obj), value);

	return matchFunc(propertyFunc(target_obj), propertyFunc(query_obj));
}

#endif // CDPL_CHEM_PROPERTYMATCHEXPRESSION_HPP
