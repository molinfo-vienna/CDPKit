/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomConfigurationMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomConfigurationMatchExpression.
 */

#ifndef CDPL_CHEM_ATOMCONFIGURATIONMATCHEXPRESSION_HPP
#define CDPL_CHEM_ATOMCONFIGURATIONMATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;
		class MolecularGraph;

		/**
		 * \brief AtomConfigurationMatchExpression.
		 */
		class CDPL_CHEM_API AtomConfigurationMatchExpression : public MatchExpression<Atom, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %AtomConfigurationMatchExpression instances.
			 */
			typedef boost::shared_ptr<AtomConfigurationMatchExpression> SharedPointer;

			/**
			 * \brief Constructs an \c %AtomConfigurationMatchExpression instance for the specified matching mode and stereo configuration constraints.
			 * \param query_stereo_descr The descriptor object specifying the query atom's stereo configuration reference atoms and associated configuration constraints
			 *                           on matching target atoms.
			 * \param query_atom The atom for which this \c %AtomConfigurationMatchExpression instance gets constructed.
			 * \param not_match Specifies whether the stereo configuration of a target atom actually has to match (\c true) or \e not match (\c false)
			 *                  the query configuration constraints.
			 * \param allow_part_maps Specifies whether or not a target atom that has an incomplete query to target neighbor atom/bond mapping
			 *                        shall be considered to match the query configuration constraints. This is important for maximum common substructure
			 *                        searches where the provided query to target atom mapping may not be complete.
			 */
			AtomConfigurationMatchExpression(const StereoDescriptor& query_stereo_descr, const Atom& query_atom, bool not_match, bool allow_part_maps);

			/**
			 * \brief Checks whether the stereo configuration of \a target_atom satisfies (or does not satisfy) the configuration constraints specified in the
			 *        constructor.
			 *
			 * The specified configuration constraint flags are interpreted in a 'logical OR' manner. That is, the stereo configuration of the checked target atom
			 * only has to match (or not match) one of the specified query configurations to satisfy the overall configuration constraints.
			 * Note that only the flags defined in namespace Chem::AtomConfiguration are supported - any other flags will be ignored.
			 *
			 * \param query_atom The query atom.
			 * \param query_molgraph The molecular graph containing the query atom (ignored).
			 * \param target_atom The checked target atom.
			 * \param target_molgraph The molecular graph containing the target atom (ignored).
			 * \param mapping The current query to target atom/bond mapping candidate.
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return If the matching mode is 'not match' (see constructor), the method returns \c false if the stereo configuration of the
			 *         target atom matches one of the specified query configurations, and \c true if not. 
			 *         Otherwise, the method will return \c true if the target configuration does match one of the specified configurations, and \c false
			 *         if all allowed configurations remain unmatched.
			 * \note If no valid query stereo descriptor was specified or \a query_atom is not identical to the query atom specified in the constrctor,
			 *       the method will return \c true - irrespective of matching mode and actual target atom configuration!
			 */
			bool operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, const Atom& target_atom,
							const MolecularGraph& target_molgraph, const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			/**
			 * \brief Returns \c true to indicate that the expression requires a query to target atom/bond mapping candidate for its evaluation.
			 * \return \c true.
			 */
			bool requiresAtomBondMapping() const;

		private:
			StereoDescriptor queryStereoDescr;
			const Atom*      queryAtom;
			bool             queryDescrValid;
			unsigned int     configFlags;
			bool             notMatch;
			bool             allowPartMaps;
		};
	}
}

#endif // CDPL_CHEM_ATOMCONFIGURATIONMATCHEXPRESSION_HPP
