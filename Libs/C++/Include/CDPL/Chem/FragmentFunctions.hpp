/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Fragment instances.
 */

#ifndef CDPL_CHEM_FRAGMENTFUNCTIONS_HPP
#define CDPL_CHEM_FRAGMENTFUNCTIONS_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class Fragment;

		/**
		 * \brief Removes all explicit hydrogen atoms from the fragment \a frag.
		 * \param frag The fragment for which to remove all explicit hydrogen atoms.
		 * \return \c false if \a frag was not altered, \c true otherwise.
		 */
		CDPL_CHEM_API bool makeHydrogenDeplete(Fragment& frag);

		/**
		 * \brief Removes all explicit ordinary hydrogen atoms from the fragment \a frag.
		 * \param frag The fragment for which to remove all explicit ordinary hydrogen atoms.
		 * \param flags Specifies the set of atom properties to check (see namespace Chem::AtomPropertyFlag).
		 * \return \c false if \a frag was not altered, \c true otherwise.
		 * \see Chem::isOrdinaryHydrogen
		 */
		CDPL_CHEM_API bool makeOrdinaryHydrogenDeplete(Fragment& frag, unsigned int flags);

		CDPL_CHEM_API void removeAtomsIf(Fragment& frag, const AtomPredicate& pred);

		CDPL_CHEM_API void removeAtomsIfNot(Fragment& frag, const AtomPredicate& pred);
	}
}

#endif // CDPL_CHEM_FRAGMENTFUNCTIONS_HPP
 
