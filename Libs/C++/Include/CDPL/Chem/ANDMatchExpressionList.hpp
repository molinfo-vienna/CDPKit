/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ANDMatchExpressionList.hpp 
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
 * \brief Definition of the class CDPL::Chem::ANDMatchExpressionList.
 */

#ifndef CDPL_CHEM_ANDMATCHEXPRESSIONLIST_HPP
#define CDPL_CHEM_ANDMATCHEXPRESSIONLIST_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/MatchExpressionList.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief ANDMatchExpressionList.
		 * \tparam ObjType1 The type of the primary query/target objects for which the expression list gets evaluated.
		 * \tparam ObjType2 The type of secondary query/target objects which provide auxiliary information for
		 *                  expression list evaluation.
		 */
		template <typename ObjType1, typename ObjType2 = void>
		class ANDMatchExpressionList : public MatchExpressionList<ObjType1, ObjType2>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %ANDMatchExpressionList instances.
			 */
			typedef boost::shared_ptr<ANDMatchExpressionList> SharedPointer;

			/**
			 * Performs an evaluation of the conjunctive expression list for the given query and target objects.
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression list.
			 * \return \c true if all expression list elements evaluate to \c true, and \c false otherwise.
			 * \note If the list is empty, the expression list evaluates to \c true.
			 */
			bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, const ObjType2& target_obj2,
							const Base::Any& aux_data) const;

			/**
			 * Performs an evaluation of the conjunctive expression list for the given query and target objects under consideration of the
			 * provided candidate atom/bond mapping.
			 *
			 * \param query_obj1 The primary query object.
			 * \param query_obj2 The secondary query object.
			 * \param target_obj1 The primary target object.
			 * \param target_obj2 The secondary target object.
			 * \param mapping The current query to target atom/bond mapping candidate to evaluate.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression list.
			 * \return \c true if all expression list elements evaluate to \c true, and \c false otherwise.
			 * \note If the list is empty, the expression list evaluates to \c true.
			 */
			bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, const ObjType1& target_obj1, const ObjType2& target_obj2,
							const AtomBondMapping& mapping, const Base::Any& aux_data) const;

		private:
			const char* getClassName() const {
				return "ANDMatchExpressionList";
			}
		};

		/**
		 * \brief ANDMatchExpressionList.
		 * \tparam ObjType The type of the query/target objects for which the expression list gets evaluated.
		 */
		template <typename ObjType>
		class ANDMatchExpressionList<ObjType, void> : public MatchExpressionList<ObjType, void>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %ANDMatchExpressionList instances.
			 */
			typedef boost::shared_ptr<ANDMatchExpressionList> SharedPointer;

			/**
			 * Performs an evaluation of the conjunctive expression list for the given query and target objects.
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression list.
			 * \return \c true if all expression list elements evaluate to \c true, and \c false otherwise.
			 * \note If the list is empty, the expression list evaluates to \c true.
			 */
			bool operator()(const ObjType& query_obj, const ObjType& target_obj, const Base::Any& aux_data) const;

			/**
			 * Performs an evaluation of the conjunctive expression list for the given query and target objects under consideration of the
			 * provided candidate atom/bond mapping.
			 *
			 * \param query_obj The query object.
			 * \param target_obj The target object.
			 * \param mapping The current query to target atom/bond mapping candidate to evaluate.
			 * \param aux_data Provides auxiliary information for the evaluation of the expression list.
			 * \return \c true if all expression list elements evaluate to \c true, and \c false otherwise.
			 * \note If the list is empty, the expression list evaluates to \c true.
			 */
			bool operator()(const ObjType& query_obj, const ObjType& target_obj, const AtomBondMapping& mapping,
							const Base::Any& aux_data) const;

		private:
			const char* getClassName() const {
				return "ANDMatchExpressionList";
			}
		};
	}
}


// Implementation

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::ANDMatchExpressionList<ObjType1, ObjType2>::operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
																			   const ObjType1& target_obj1, const ObjType2& target_obj2, 
																			   const Base::Any& data) const
{
	typename MatchExpressionList<ObjType1, ObjType2>::ConstElementIterator exprs_end = this->getElementsEnd();

	for (typename MatchExpressionList<ObjType1, ObjType2>::ConstElementIterator it = this->getElementsBegin(); it != exprs_end; ++it)
		if (!(*it)(query_obj1, query_obj2, target_obj1, target_obj2, data))
			return false;

	return true;
}

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::ANDMatchExpressionList<ObjType1, ObjType2>::operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
																			  const ObjType1& target_obj1, const ObjType2& target_obj2, 
																			  const AtomBondMapping& mapping, const Base::Any& data) const
{
	typename MatchExpressionList<ObjType1, ObjType2>::ConstElementIterator exprs_end = this->getElementsEnd();

	for (typename MatchExpressionList<ObjType1, ObjType2>::ConstElementIterator it = this->getElementsBegin(); it != exprs_end; ++it)
		if (!(*it)(query_obj1, query_obj2, target_obj1, target_obj2, mapping, data))
			return false;

	return true;
}


template <typename ObjType>
bool CDPL::Chem::ANDMatchExpressionList<ObjType, void>::operator()(const ObjType& query_obj, const ObjType& target_obj, 
																		  const Base::Any& data) const
{
	typename MatchExpressionList<ObjType, void>::ConstElementIterator exprs_end = this->getElementsEnd();

	for (typename MatchExpressionList<ObjType, void>::ConstElementIterator it = this->getElementsBegin(); it != exprs_end; ++it)
		if (!(*it)(query_obj, target_obj, data))
			return false;

	return true;
}

template <typename ObjType>
bool CDPL::Chem::ANDMatchExpressionList<ObjType, void>::operator()(const ObjType& query_obj, const ObjType& target_obj, 
																		  const AtomBondMapping& mapping, const Base::Any& data) const
{
	typename MatchExpressionList<ObjType, void>::ConstElementIterator exprs_end = this->getElementsEnd();

	for (typename MatchExpressionList<ObjType, void>::ConstElementIterator it = this->getElementsBegin(); it != exprs_end; ++it)
		if (!(*it)(query_obj, target_obj, mapping, data))
			return false;

	return true;
}

#endif // CDPL_CHEM_ANDMATCHEXPRESSIONLIST_HPP
