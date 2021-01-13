/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatchExpressionList.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::MatchExpressionList.
 */

#ifndef CDPL_CHEM_MATCHEXPRESSIONLIST_HPP
#define CDPL_CHEM_MATCHEXPRESSIONLIST_HPP

#include <algorithm>

#ifndef BOOST_BIND_GLOBAL_PLACEHOLDERS
# define BOOST_BIND_GLOBAL_PLACEHOLDERS
#endif

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Util/IndirectArray.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_MATCH_EXPRESSION_BUILDING_BLOCKS
		 * @{
		 */

		/**
		 * \brief A container for the storage and evaluation of logical match expression lists.
		 *
		 * \c %MatchExpressionList allows for a concatenation of multiple Chem::MatchExpression instances that
		 * get evaluated in turn according to some logic. The actual logic of expression list evaluation
		 * has to be implemented by subclasses by overriding the virtual function call operator methods of the 
		 * Chem::MatchExpression interface.
		 *
		 * \tparam ObjType1 The type of the primary query/target objects for which the expression list gets evaluated.
		 * \tparam ObjType2 The type of secondary query/target objects which provide auxiliary information for
		 *                  expression list evaluation.
		 */
		template <typename ObjType1, typename ObjType2 = void>
		class MatchExpressionList : 
			public MatchExpression<ObjType1, ObjType2>, public Util::IndirectArray<MatchExpression<ObjType1, ObjType2> >
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %MatchExpressionList instances.
			 */
			typedef boost::shared_ptr<MatchExpressionList> SharedPointer;

			/**
			 * \brief Tells whether the expression list requires a reevaluation after a query to target object mapping
			 *        candidate has been found.
			 * \return \c true if one of the stored expressions requires a reevaluation after a mapping candidate has been found,
			 *         and \c false otherwise.
			 */
			bool requiresAtomBondMapping() const;

		private:
			const char* getClassName() const {
				return "MatchExpressionList";
			}
		};

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename ObjType1, typename ObjType2>
bool CDPL::Chem::MatchExpressionList<ObjType1, ObjType2>::requiresAtomBondMapping() const
{
	return (std::find_if(this->getElementsBegin(), this->getElementsEnd(),
						 boost::bind(&MatchExpression<ObjType1, ObjType2>::requiresAtomBondMapping, _1)) != this->getElementsEnd());
}

#endif // CDPL_CHEM_MATCHEXPRESSIONLIST_HPP
