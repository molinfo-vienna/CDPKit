/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondDirectionMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondDirectionMatchExpression.
 */

#ifndef CDPL_CHEM_BONDDIRECTIONMATCHEXPRESSION_HPP
#define CDPL_CHEM_BONDDIRECTIONMATCHEXPRESSION_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Bond;
		class MolecularGraph;

		/**
		 * \brief BondDirectionMatchExpression.
		 */
		class CDPL_CHEM_API BondDirectionMatchExpression : public MatchExpression<Bond, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BondDirectionMatchExpression instances.
			 */
			typedef std::shared_ptr<BondDirectionMatchExpression> SharedPointer;

			/**
			 * \brief Constructs an \c %BondDirectionMatchExpression instance for the specified matching mode and bond direction constraints.
			 * \param dir_flags A bitwise OR combination of the flags defined in namespace Chem::BondDirection that specifies constraints on
			 *                  the direction of matching target bonds.
			 * \param not_match Specifies whether the direction of a target bond actually has to match (\c true) or \e not match (\c false)
			 *                  the query direction constraints.
			 */
			BondDirectionMatchExpression(unsigned int dir_flags, bool not_match);

			/**
			 * \brief Checks whether the direction given by \a target_bond_dir matches (or does not match) the direction constraints specified
			 *        in the constructor.
			 *
			 * The specified query direction constraint flags are interpreted in a 'logical OR' manner. That is, the target bond
			 * direction specified by \a target_bond_dir only has to match (or not match) one of the specified query directions
			 * to satisfy the overall direction constraints.
			 * Note that only the flags defined in namespace Chem::BondDirection are supported - any other flags will be ignored.
			 *
			 * \param query_bond The query bond (ignored).
			 * \param query_molgraph The molecular graph containing the query bond (ignored).
			 * \param target_bond The target bond (ignored).
			 * \param target_molgraph The molecular graph containing the target bond (ignored).
			 * \param mapping The current query to target atom/bond mapping candidate (ignored).
			 * \param target_bond_dir Specifies the direction of the target bond by one of the flags defined in namespace Chem::BondDirection. 
			 * \return If the matching mode is 'not match' (see constructor), the method returns \c false if the direction of the
			 *         target bond (given by \a target_bond_dir) matches one of the directions specified in the constructor, and \c true if not. 
			 *         If the matching mode is 'match', the expression evaluates to \c true if the target bond matches one of the query directions,
			 *         and \c false otherwise.
			 * \note If no valid query direction flags were specified or \a target_bond_dir does not hold a value, the method will return \c true -
			 *       irrespective of matching mode and actual target bond direction!
			 */
			bool operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
							const Bond& target_bond, const MolecularGraph& target_molgraph,
							const AtomBondMapping& mapping, const Base::Any& target_bond_dir) const;

		private:
			unsigned int dirFlags;
			bool         notMatch;
		};
	}
}

#endif // CDPL_CHEM_BONDDIRECTIONMATCHEXPRESSION_HPP
