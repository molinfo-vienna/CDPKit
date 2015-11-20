 /* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondSubstituentDirectionMatchExpression.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::BondSubstituentDirectionMatchExpression.
 */

#ifndef CDPL_CHEM_BONDSUBSTITUENTDIRECTIONMATCHEXPRESSION_HPP
#define CDPL_CHEM_BONDSUBSTITUENTDIRECTIONMATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Bond;
		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_BOND_MATCH_EXPRESSIONS
		 * @{
		 */

		/**
		 * \brief BondSubstituentDirectionMatchExpression.
		 *
		 * <em>Daylight SMARTS</em> [\ref SMARTS] substructure search patterns specify cis/trans geometry constraints for a double bond by 
		 * indicating the relative direction of the bonds to its substituent atoms.  
		 */
		class CDPL_CHEM_API BondSubstituentDirectionMatchExpression : public MatchExpression<Bond, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %BondSubstituentDirectionMatchExpression instances.
			 */
			typedef boost::shared_ptr<BondSubstituentDirectionMatchExpression> SharedPointer;

			/**
			 * \brief Checks whether the relative directions of the substituent bonds of \a target_bond match the bond direction constraints
			 *        specified for the substituent bonds of \a query_bond.
			 *
			 * The relative directions of the substituent bonds of \a target_bond are considered to match the direction constraints of the
			 * \a query_bond substituents if each match expression that is associated with a query substituent bond (taken from the property
			 * Chem::BondProperty::MATCH_EXPRESSION) evaluates to \c true for the respective mapped target substituent bond and its direction.
			 * The relative directions of the target substituent bonds are calculated on the fly from the target bond's cis/trans geometry
			 * and get passed to the match expressions via the \a aux_data argument of the function call operator (see
			 * Chem::BondDirectionMatchExpression::operator()()). If the exact cis/trans geometry of \a target_bond was not properly defined (i.e.
			 * the geometry is neither Chem::BondGeometry::CIS nor Chem::BondGeometry::TRANS), the direction of its substituent bonds is set to
			 * Chem::BondDirection::UNSPECIFIED.
			 *
			 * \param query_bond The query bond.
			 * \param query_molgraph The molecular graph containing the query bond.
			 * \param target_bond The checked target bond.
			 * \param target_molgraph The molecular graph containing the target bond.
			 * \param mapping The current query to target atom/bond mapping candidate.
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return \c true if all match expressions that are associated with the substituent bonds of \a query_bond evaluate to \c true for the
			 *         calculated relative bond directions of the mapped \a target_bond substituents, and \c false otherwise.
			 * \note If \a query_bond is not a potential stereo bond or the supplied atom/bond mapping between the query and target bond environment
			 *       is incomplete, the expression evaluates to \c true.
			 * \see Chem::BondDirectionMatchExpression, Chem::BondDirection
			 */
			bool operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
							const Bond& target_bond, const MolecularGraph& target_molgraph,
							const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			/**
			 * \brief Returns \c true to indicate that the expression requires a query to target atom/bond mapping candidate for its evaluation.
			 * \return \c true.
			 */
			bool requiresAtomBondMapping() const;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_BONDSUBSTITUENTDIRECTIONMATCHEXPRESSION_HPP
