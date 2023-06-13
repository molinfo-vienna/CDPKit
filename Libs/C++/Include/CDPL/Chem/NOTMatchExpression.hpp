/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * NOTMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::NOTMatchExpression.
 */

#ifndef CDPL_CHEM_NOTMATCHEXPRESSION_HPP
#define CDPL_CHEM_NOTMATCHEXPRESSION_HPP

#include <memory>

#include "CDPL/Chem/MatchExpression.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief NOTMatchExpression.
		 * \tparam ObjType1 The type of the primary query/target objects for which the expression gets evaluated.
		 * \tparam ObjType2 The type of secondary query/target objects which provide auxiliary information for
		 *                  expression evaluation.
		 */
		template <typename ObjType1, typename ObjType2 = void>
		class NOTMatchExpression : public MatchExpression<ObjType1, ObjType2>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %NOTMatchExpression instances.
			 */
			typedef std::shared_ptr<NOTMatchExpression> SharedPointer;
		
			/**
			 * \brief Constructs a \c %NOTMatchExpressionBase object that wraps the match expression instance specified by \a expr_ptr.
			 * \param expr_ptr A pointer to the wrapped Chem::MatchExpression instance.
			 */
			NOTMatchExpression(const typename MatchExpression<ObjType1, ObjType2>::SharedPointer& expr_ptr): 
				expression(expr_ptr) {}

			/**
			 * Performs an evaluation of the wrapped match expression for the given query and target objects and returns the inverted result.
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the wrapped expression.
			 * \return \c true if the wrapped match expression evaluates to \c false, and vice versa.
			 */
			bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, const ObjType2& target_obj2, 
							const Base::Any& aux_data) const;

			/**
			 * Performs an evaluation of the wrapped match expression for the given query and target objects under consideration of the
			 * provided candidate atom/bond mapping and returns the inverted result.
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param mapping The current query to target atom/bond mapping candidate to evaluate.
			 * \param aux_data Provides auxiliary information for the evaluation of the wrapped expression.
			 * \return \c true if the wrapped match expression evaluates to \c false, and vice versa.
			 */
			bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, const ObjType2& target_obj2, 
							const AtomBondMapping& mapping, const Base::Any& aux_data) const;
		
			/**
			 * \brief Tells whether the wrapped match expression requires a reevaluation after a query to target atom/bond mapping
			 *        candidate has been found.
			 * \return \c true if the expression needs to be evaluated again after a query/target mapping candidate has been found,
			 *         and \c false otherwise.
			 */
			bool requiresAtomBondMapping() const;

		private:
			typename MatchExpression<ObjType1, ObjType2>::SharedPointer expression;
		};

		/**
		 * \brief NOTMatchExpression.
		 * \tparam ObjType The type of the query/target objects for which the expression gets evaluated.
		 */
		template <typename ObjType>
		class NOTMatchExpression<ObjType, void> : public MatchExpression<ObjType, void>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %NOTMatchExpression instances.
			 */
			typedef std::shared_ptr<NOTMatchExpression> SharedPointer;
		
			/**
			 * \brief Constructs a \c %NOTMatchExpressionBase object that wraps the match expression instance specified by \a expr_ptr.
			 * \param expr_ptr A pointer to the wrapped Chem::MatchExpression instance.
			 */
			NOTMatchExpression(const typename MatchExpression<ObjType, void>::SharedPointer& expr_ptr): 
				expression(expr_ptr) {}
		
			/**
			 * Performs an evaluation of the wrapped match expression for the given query and target objects and returns the inverted result.
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the wrapped expression.
			 * \return \c true if the wrapped match expression evaluates to \c false, and vice versa.
			 */
			bool operator()(const ObjType& query_obj, const ObjType& target_obj, const Base::Any& aux_data) const;

			/**
			 * Performs an evaluation of the wrapped match expression for the given query and target objects under consideration of the
			 * provided candidate atom/bond mapping and returns the inverted result.
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param mapping The current query to target atom/bond mapping candidate to evaluate.
			 * \param aux_data Provides auxiliary information for the evaluation of the wrapped expression.
			 * \return \c true if the wrapped match expression evaluates to \c false, and vice versa.
			 */
			bool operator()(const ObjType& query_obj, const ObjType& target_obj, const AtomBondMapping& mapping, const Base::Any& aux_data) const;
		
			/**
			 * \brief Tells whether the wrapped match expression requires a reevaluation after a query to target atom/bond mapping
			 *        candidate has been found.
			 * \return \c true if the expression needs to be evaluated again after a query/target mapping candidate has been found,
			 *         and \c false otherwise.
			 */
			bool requiresAtomBondMapping() const;

		private:
			typename MatchExpression<ObjType, void>::SharedPointer expression;
		};
	}
}


// Implementation

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::NOTMatchExpression<ObjType1, ObjType2>::operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
																		   const ObjType1& target_obj1, const ObjType2& target_obj2, 
																		   const Base::Any& data) const
{
	return !this->expression->operator()(query_obj1, query_obj2, target_obj1, target_obj2, data);
}

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::NOTMatchExpression<ObjType1, ObjType2>::operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
																		   const ObjType1& target_obj1, const ObjType2& target_obj2, 
																		   const AtomBondMapping& mapping, const Base::Any& data) const
{
	return !this->expression->operator()(query_obj1, query_obj2, target_obj1, target_obj2, mapping, data);
}

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::NOTMatchExpression<ObjType1, ObjType2>::requiresAtomBondMapping() const
{
	return this->expression->requiresAtomBondMapping();
}


template <typename ObjType>
bool CDPL::Chem::NOTMatchExpression<ObjType, void>::operator()(const ObjType& query_obj, const ObjType& target_obj, 
																	  const Base::Any& data) const
{
	return !this->expression->operator()(query_obj, target_obj, data);
}

template <typename ObjType>
bool CDPL::Chem::NOTMatchExpression<ObjType, void>::operator()(const ObjType& query_obj, const ObjType& target_obj, 
																	  const AtomBondMapping& mapping, const Base::Any& data) const
{
	return !this->expression->operator()(query_obj, target_obj, mapping, data);
}

template <typename ObjType1>
bool CDPL::Chem::NOTMatchExpression<ObjType1, void>::requiresAtomBondMapping() const
{
	return this->expression->requiresAtomBondMapping();
}

#endif // CDPL_CHEM_NOTMATCHEXPRESSION_HPP
