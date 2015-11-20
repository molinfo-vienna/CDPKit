/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Molecule instances.
 */

#ifndef CDPL_CHEM_MOLECULEFUNCTIONS_HPP
#define CDPL_CHEM_MOLECULEFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class Molecule;
		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_MOLECULE_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API void replaceAtomStereoReferenceAtoms(Molecule& mol_copy, const MolecularGraph& molgraph,
														   std::size_t atom_idx_offs = 0);

		CDPL_CHEM_API void replaceBondStereoReferenceAtoms(Molecule& mol_copy, const MolecularGraph& molgraph, 
														   std::size_t atom_idx_offs = 0, std::size_t bond_start_idx = 0);

		/**
		 * \brief Removes all explicit hydrogen atoms from the molecule \a mol.
		 * \param mol The molecule for which to remove all explicit hydrogen atoms.
		 */
		CDPL_CHEM_API void makeHydrogenDeplete(Molecule& mol);

		/**
		 * \brief Removes all explicit ordinary hydrogen atoms from the molecule \a mol.
		 * \param mol The molecule for which to remove all explicit ordinary hydrogen atoms.
		 * \param flags Specifies the set of atom properties to check (see namespace Chem::AtomPropertyFlag).
		 * \see Chem::isOrdinaryHydrogen
		 */
		CDPL_CHEM_API void makeOrdinaryHydrogenDeplete(Molecule& mol, unsigned int flags);

		/**
		 * \brief Converts all implicit hydrogens of the molecule \a mol to explicit hydrogen atoms.
		 * \param mol The molecule that has to be made hydrogen complete.
		 */
		CDPL_CHEM_API void makeHydrogenComplete(Molecule& mol);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOLECULEFUNCTIONS_HPP
 
