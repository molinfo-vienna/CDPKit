/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::MatchExpression.
 */

#ifndef CDPL_CHEM_MATCHEXPRESSION_HPP
#define CDPL_CHEM_MATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>


namespace CDPL 
{

	namespace Base
	{

		class Variant;
	}

	namespace Chem
	{

		class AtomBondMapping;

		/**
		 * \brief A generic boolean expression interface for the implementation of query/target object equivalence tests
		 *        in molecular graph matching algorithms.
		 *
		 * The \c %MatchExpression interface abstracts the task of checking a set of constraints on the attributes of target
		 * objects when performing query object equivalence tests in molecular graph matching procedures.
		 * Subclasses of \c %MatchExpression must override one (or all, if required) of the provided function call operators
		 * to implement the logic of the constraint checks. The first form of the two operators gets called in the pre-mapping stage
		 * of the graph matching algorithm where all feasible query/target object pairings are determined. In this pre-mapping
		 * stage all sorts of query constraints can be checked that are invariant with respect to the final mapping between
		 * any of the other query and target objects. 
		 * The second type of operator is invoked immediately after a complete graph mapping solution has been found and can
		 * be used to re-evaluate the validity of a given query/target object pairing in the context of the provided matching
		 * result. As soon as a pairing is found to be invalid, the current mapping solution is rejected and the algorithm proceeds
		 * to find the next possible query to target graph mapping (if any).
		 * For efficiency reasons, subclasses of \c %MatchExpression which implement the post-mapping function call operator must
		 * explicitly enable its invocation by additionally overriding the MatchExpression::requiresAtomBondMapping() method. Its
		 * implementation simply has to return \c true (the default implementation returns \c false) to request the invocation of
		 * the operator. 
		 *
		 * \tparam ObjType1 The type of the primary query/target objects for which the expression gets evaluated.
		 * \tparam ObjType2 The type of secondary query/target objects which provide auxiliary information for
		 *                  expression evaluation.
		 */
		template <typename ObjType1, typename ObjType2 = void>
		class MatchExpression
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %MatchExpression instances.
			 */
			typedef boost::shared_ptr<MatchExpression> SharedPointer;

			/**
			 * \brief Virtual Destructor.
			 */
			virtual ~MatchExpression() {}

			/**
			 * Performs an evaluation of the expression for the given query and target objects.
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression.
			 * \return The result of the expression evaluation for the specified query and target objects.
			 * \note The default implementation returns \c true.
			 */
			virtual bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, const ObjType2& target_obj2, 
									const Base::Variant& aux_data) const;

			/**
			 * Performs an evaluation of the expression for the given query and target objects under consideration of the provided candidate atom/bond mapping.
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param mapping The current query to target atom/bond mapping candidate to evaluate.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression.
			 * \return The result of the expression evaluation for the specified query and target objects.
			 * \note The default implementation returns the result of <tt>operator()(query_obj1, query_obj2, target_obj1, target_obj2, aux_data)</tt>.
			 */
			virtual bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, const ObjType2& target_obj2, 
									const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			/**
			 * \brief Tells whether the expression must be reevaluated after a query to target atom/bond mapping candidate has been found.
			 * \return \c true if the expression needs to be evaluated again after a query to target atom/bond mapping candidate has been found,
			 *         and \c false otherwise.
			 * \note The default implementation returns \c false.
			 */
			virtual bool requiresAtomBondMapping() const;
		};

		/**
		 * \brief A generic boolean expression interface for the implementation of query/target object equivalence tests
		 *        in molecular graph matching algorithms.
		 *
		 * The \c %MatchExpression interface abstracts the task of checking a set of constraints on the attributes of target
		 * objects when performing query object equivalence tests in molecular graph matching procedures.
		 * Subclasses of \c %MatchExpression must override one (or all, if required) of the provided function call operators
		 * to implement the logic of the constraint checks. The first form of the two operators gets called in the pre-mapping stage
		 * of the graph matching algorithm where all feasible query/target object pairings are determined. In this pre-mapping
		 * stage all sorts of query constraints can be checked that are invariant with respect to the final mapping between
		 * any of the other query and target objects. 
		 * The second type of operator is invoked immediately after a complete graph mapping solution has been found and can
		 * be used to re-evaluate the validity of a given query/target object pairing in the context of the provided matching
		 * result. As soon as a pairing is found to be invalid, the current mapping solution is rejected and the algorithm proceeds
		 * to find the next possible query to target graph mapping (if any).
		 * For efficiency reasons, subclasses of \c %MatchExpression which implement the post-mapping function call operator must
		 * explicitly enable its invocation by additionally overriding the MatchExpression::requiresAtomBondMapping() method. Its
		 * implementation simply has to return \c true (the default implementation returns \c false) to request the invocation of
		 * the operator. 
		 *
		 * \tparam ObjType The type of the query/target objects for which the expression gets evaluated.
		 */
		template <typename ObjType>
		class MatchExpression<ObjType, void>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %MatchExpression instances.
			 */
			typedef boost::shared_ptr<MatchExpression> SharedPointer;

			/**
			 * \brief Virtual Destructor.
			 */
			virtual ~MatchExpression() {}

			/**
			 * Performs an evaluation of the expression for the given query and target objects.
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression.
			 * \return The result of the expression evaluation for the specified query and target objects.
			 * \note The default implementation returns \c true.
			 */
			virtual bool operator()(const ObjType& query_obj, const ObjType& target_obj, const Base::Variant& aux_data) const;

			/**
			 * Performs an evaluation of the expression for the given query and target objects under consideration of the provided candidate atom/bond mapping.
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param mapping The current query to target atom/bond mapping candidate to evaluate.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression.
			 * \return The result of the expression evaluation for the specified query and target objects.
			 * \note The default implementation returns the result of <tt>operator()(query_obj, target_obj, aux_data)</tt>.
			 */
			virtual bool operator()(const ObjType& query_obj, const ObjType& target_obj, const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			/**
			 * \brief Tells whether the expression must be reevaluated after a query to target atom/bond mapping candidate has been found.
			 * \return \c true if the expression needs to be evaluated again after a query to target atom/bond mapping candidate has been found,
			 *         and \c false otherwise.
			 * \note The default implementation returns \c false.
			 */
			virtual bool requiresAtomBondMapping() const;
		};
	}
}


// Implementation

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::MatchExpression<ObjType1, ObjType2>::operator()(const ObjType1&, const ObjType2&, 
																		const ObjType1&, const ObjType2&, 
																		const Base::Variant&) const
{
	return true;
}

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::MatchExpression<ObjType1, ObjType2>::operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
																		const ObjType1& target_obj1, const ObjType2& target_obj2, 
																		const AtomBondMapping&, const Base::Variant& data) const
{
	return operator()(query_obj1, query_obj2, target_obj1, target_obj2, data);
}

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::MatchExpression<ObjType1, ObjType2>::requiresAtomBondMapping() const
{
	return false;
}


template <typename ObjType>
bool CDPL::Chem::MatchExpression<ObjType, void>::operator()(const ObjType&, const ObjType&, 
																   const Base::Variant&) const
{
	return true;
}

template <typename ObjType>
bool CDPL::Chem::MatchExpression<ObjType, void>::operator()(const ObjType& query_obj, const ObjType& target_obj, 
																   const AtomBondMapping&, const Base::Variant& data) const
{
	return operator()(query_obj, target_obj, data);
}

template <typename ObjType1>
bool CDPL::Chem::MatchExpression<ObjType1, void>::requiresAtomBondMapping() const
{
	return false;
}

#endif // CDPL_CHEM_MATCHEXPRESSION_HPP
