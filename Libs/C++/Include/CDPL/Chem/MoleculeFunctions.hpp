/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Molecule instances.
 */

#ifndef CDPL_CHEM_MOLECULEFUNCTIONS_HPP
#define CDPL_CHEM_MOLECULEFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class Molecule;
		class MolecularGraph;

		/**
		 * \brief Removes all explicit hydrogen atoms from the molecule \a mol.
		 * \param mol The molecule for which to remove all explicit hydrogen atoms.
		 * \param corr_impl_h_count \c true if the implicit hydrogen count property of the hydrogen completed atoms shall be set to zero,
		 *                          \c false if the property shall be left unchanged.
		 * \return \c false if \a mol was not altered, \c true otherwise.
		 */
		CDPL_CHEM_API bool makeHydrogenDeplete(Molecule& mol, bool corr_impl_h_count = true);

		/**
		 * \brief Removes all explicit ordinary hydrogen atoms from the molecule \a mol.
		 * \param mol The molecule for which to remove all explicit ordinary hydrogen atoms.
		 * \param flags Specifies the set of atom properties to check (see namespace Chem::AtomPropertyFlag).
		 * \param corr_impl_h_count \c true if the implicit hydrogen count property of the hydrogen completed atoms shall be set to zero,
		 *                          \c false if the property shall be left unchanged.
		 * \return \c false if \a mol was not altered, \c true otherwise.
		 * \see Chem::isOrdinaryHydrogen
		 */
		CDPL_CHEM_API bool makeOrdinaryHydrogenDeplete(Molecule& mol, unsigned int flags, bool corr_impl_h_count = true);

		/**
		 * \brief Converts all implicit hydrogens of the molecule \a mol to explicit hydrogen atoms.
		 * \param mol The molecule that has to be made hydrogen complete.
		 * \param corr_impl_h_count \c true if the implicit hydrogen count property of the hydrogen completed atoms shall be set to zero,
		 *                          \c false if the property shall be left unchanged.
		 * \return \c false if \a mol was not altered, \c true otherwise.
		 */
		CDPL_CHEM_API bool makeHydrogenComplete(Molecule& mol, bool corr_impl_h_count = true);

		CDPL_CHEM_API void removeAtomsIf(Molecule& mol, const AtomPredicate& pred);

		CDPL_CHEM_API void removeAtomsIfNot(Molecule& mol, const AtomPredicate& pred);
	}
}

#endif // CDPL_CHEM_MOLECULEFUNCTIONS_HPP
 
