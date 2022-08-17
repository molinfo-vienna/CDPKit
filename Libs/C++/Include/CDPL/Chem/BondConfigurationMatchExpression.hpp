/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondConfigurationMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondConfigurationMatchExpression.
 */

#ifndef CDPL_CHEM_BONDCONFIGURATIONMATCHEXPRESSION_HPP
#define CDPL_CHEM_BONDCONFIGURATIONMATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Bond;
		class MolecularGraph;

		/**
		 * \brief BondConfigurationMatchExpression.
		 */
		class CDPL_CHEM_API BondConfigurationMatchExpression : public MatchExpression<Bond, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %BondConfigurationMatchExpression instances.
			 */
			typedef boost::shared_ptr<BondConfigurationMatchExpression> SharedPointer;

			/**
			 * \brief Constructs an \c %BondConfigurationMatchExpression instance for the specified matching mode, cis/trans bond configuration constraints.
			 * \param query_stereo_descr The descriptor object specifying the query bond's cis/trans configuration reference atoms and associated configuration constraints
			 *                           on matching target bonds.
			 * \param query_bond The bond for which this \c %BondConfigurationMatchExpression instance gets constructed.
			 * \param not_match Specifies whether the configuration of a target bond actually has to match (\c true) or \e not match (\c false)
			 *                  the query configuration constraints.
			 * \param allow_part_maps Specifies whether or not a target bond that has an incomplete query to target neighbor atom/bond mapping
			 *                        shall be considered to match the query configuration constraints. This is important for maximum common substructure
			 *                        searches where the provided query to target mapping may not be complete.
			 */
			BondConfigurationMatchExpression(const StereoDescriptor& query_stereo_descr, const Bond& query_bond, bool not_match, bool allow_part_maps);

			/**
			 * \brief Checks whether the cis/trans configuration of \a target_bond satisfies (or does not satisfy) the configuration constraints specified in the
			 *        constructor.
			 *
			 * The specified configuration constraint flags are interpreted in a 'logical OR' manner. That is, the cis/trans configuration of the checked target bond
			 * only has to match (or not match) one of the specified query configurations to satisfy the overall configuration constraints.
			 * Note that only the flags defined in namespace Chem::BondConfiguration are supported - any other flags will be ignored.
			 *
			 * \param query_bond The query bond.
			 * \param query_molgraph The molecular graph containing the query bond (ignored).
			 * \param target_bond The checked target bond.
			 * \param target_molgraph The molecular graph containing the target bond (ignored).
			 * \param mapping The current query to target atom/bond mapping candidate.
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return If the matching mode is 'not match' (see constructor), the method returns \c false if the configuration of the
			 *         target bond matches one of the specified query configurations, and \c true if not. 
			 *         Otherwise, the method will return \c true if the target bond configuration does match one of the specified query configurations,
			 *         and \c false if all allowed configurations remain unmatched.
			 * \note If no valid query stereo descriptor was specified or \a query_bond is not identical to the query bond specified in the constrctor,
			 *       the method will return \c true - irrespective of matching mode and actual target bond configuration!
			 */
			bool operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
							const Bond& target_bond, const MolecularGraph& target_molgraph, 
							const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			/**
			 * \brief Returns \c true to indicate that the expression requires a query to target atom/bond mapping candidate for its evaluation.
			 * \return \c true.
			 */
			bool requiresAtomBondMapping() const;

		private:
			StereoDescriptor queryStereoDescr;
			const Bond*      queryBond;
			bool             queryDescrValid;
			unsigned int     configFlags;
			bool             notMatch;
			bool             allowPartMaps;
		};
	}
}

#endif // CDPL_CHEM_BONDCONFIGURATIONMATCHEXPRESSION_HPP
