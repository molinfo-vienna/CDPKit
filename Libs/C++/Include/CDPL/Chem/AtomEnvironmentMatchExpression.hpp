/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomEnvironmentMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomEnvironmentMatchExpression.
 */

#ifndef CDPL_CHEM_ATOMENVIRONMENTMATCHEXPRESSION_HPP
#define CDPL_CHEM_ATOMENVIRONMENTMATCHEXPRESSION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief AtomEnvironmentMatchExpression.
		 */
		class CDPL_CHEM_API AtomEnvironmentMatchExpression : public MatchExpression<Atom, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %AtomEnvironmentMatchExpression instances.
			 */
			typedef boost::shared_ptr<AtomEnvironmentMatchExpression> SharedPointer;

			/**
			 * \brief Constructs an \c %AtomEnvironmentMatchExpression instance for the specified atom environment pattern and matching mode.
			 * \param env_pattern A substructure search pattern that describes the required (or not desired) structural environment of matching target atoms. 
			 *                    Note: The substructure pattern has to be formulated in a way that the first atom of the pattern molecule matches the
			 *                    target atoms.
			 * \param not_match Specifies whether the environment of a target atom actually has to match (\c true) or \e not match (\c false)
			 *                  the given query environment pattern.
			 */
			AtomEnvironmentMatchExpression(const MolecularGraph::SharedPointer& env_pattern, bool not_match); 

			/**
			 * \brief Checks whether the structural environment of \a target_atom matches (or does not match) the query environment pattern specified
			 *        in the constructor.
			 * \param query_atom The query atom (ignored).
			 * \param query_molgraph The molecular graph containing the query atom (ignored).
			 * \param target_atom The checked target atom.
			 * \param target_molgraph The molecular graph containing the target atom.
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return If the matching mode is 'not match' (see constructor), the method returns \c false if the structural environment of the
			 *         target atom matches the query environment pattern, and \c true if the pattern is not matched. 
			 *         Otherwise, \c true is returned if the atom environments match, and \c false if they do not.
			 * \note If an invalid query environment pattern has been specified (\e null pointer or the atom count is zero), the method will always return
			 *       \c true - irrespective of matching mode and target atom environment.
			 */
			bool operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, const Atom& target_atom,
							const MolecularGraph& target_molgraph, const Base::Variant& aux_data) const;

		private:
			MolecularGraph::SharedPointer envPattern;
			mutable SubstructureSearch    substructSearch;
			mutable boost::mutex          mutex;
			bool                          notMatch;
		};
	}
}

#endif // CDPL_CHEM_ATOMENVIRONMENTMATCHEXPRESSION_HPP
