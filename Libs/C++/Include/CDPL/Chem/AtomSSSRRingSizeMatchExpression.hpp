/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomSSSRRingSizeMatchExpression.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomSSSRRingSizeMatchExpression.
 */

#ifndef CDPL_CHEM_ATOMSSSRRINGSIZEMATCHEXPRESSION_HPP
#define CDPL_CHEM_ATOMSSSRRINGSIZEMATCHEXPRESSION_HPP

#include <memory>

#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief AtomSSSRRingSizeMatchExpression.
		 * \tparam MatchFunc The type of a binary functor class that implements the logic of testing the size of rings containing
		 *                   the target atom against the query ring size. The overloaded function call operator is
		 *                   required to take the target ring size as its first argument and the query ring size as the
		 *                   second argument (both provided as values of type <tt>std::size_t</tt> w). The returned result
		 *                   must be implicitly convertible to type \c bool (\c true indicates a match, \c false a mismatch).
		 */
		template <typename MatchFunc>
		class AtomSSSRRingSizeMatchExpression : public MatchExpression<Atom, MolecularGraph>
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %AtomSSSRRingSizeMatchExpression instances.
			 */
			typedef std::shared_ptr<AtomSSSRRingSizeMatchExpression> SharedPointer;

			/**
			 * \brief Constructs an \c %AtomSSSRRingSizeMatchExpression instance for the specified query ring size.
			 * \param ring_size The query ring size that has to be matched (according to the result returned by the
			 *                  specified matching functor) by rings containing the checked target atoms. 
			 */
			AtomSSSRRingSizeMatchExpression(std::size_t ring_size): ringSize(ring_size) {} 
	
			/**
			 * \brief Checks whether a ring in the SSSR of \a target_molgraph that contains \a target_atom matches the query
			 *        ring size specified in the constructor.
			 *
			 * The actual equivalence test between the specified query ring size and a found target ring size is performed by an
			 * instance of the function object type that was provided as template argument for \a MatchFunc. 
			 *
			 * \param query_atom The query atom (ignored).
			 * \param query_molgraph The molecular graph containing the query atom (ignored).
			 * \param target_atom The checked target atom.
			 * \param target_molgraph The molecular graph containing the target atom.
			 * \param aux_data Auxiliary information for expression evaluation (ignored).
			 * \return \c true if a ring in the SSSR of \a target_molgraph containing the specified target atom matches
			 *         the query ring size (see constructor) under the conditions defined by \a MatchFunc, and \c false otherwise.
			 * \note The SSSR of \a target_molgraph is retrieved by a call to Chem::getSSSR().
			 */
			bool operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, const Atom& target_atom, 
							const MolecularGraph& target_molgraph, const Base::Any& aux_data) const;

		private:
			std::size_t ringSize;
			MatchFunc   matchFunc;
		};
	}
}


// Implementation

template <typename MatchFunc>
bool CDPL::Chem::AtomSSSRRingSizeMatchExpression<MatchFunc>::operator()(const Atom&, const MolecularGraph&, 
																		const Atom& target_atom, const MolecularGraph& target_molgraph, 
																		const Base::Any&) const
{
	const FragmentList& sssr = *getSSSR(target_molgraph);

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;

		if (!ring.containsAtom(target_atom))
			continue;

		if (matchFunc(ring.getNumAtoms(), ringSize))
			return true;
	}

	return false;
}

#endif // CDPL_CHEM_ATOMSSSRRINGSIZEMATCHEXPRESSION_HPP
