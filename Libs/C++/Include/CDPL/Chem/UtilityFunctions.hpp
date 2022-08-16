/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.hpp 
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
 * \brief Declaration of miscellaneous utility functions.
 */

#ifndef CDPL_CHEM_UTILITYFUNCTIONS_HPP
#define CDPL_CHEM_UTILITYFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		/**
		 * \addtogroup CDPL_CHEM_UTILITY_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API Molecule::SharedPointer parseSMARTS(const std::string& smarts, bool init_qry = true);

		CDPL_CHEM_API bool parseSMARTS(const std::string& smarts, Molecule& mol, bool init_qry = true);

		CDPL_CHEM_API Molecule::SharedPointer parseSMILES(const std::string& smiles);

		CDPL_CHEM_API bool parseSMILES(const std::string& smiles, Molecule& mol);

		CDPL_CHEM_API void extendBoundingBox(Math::Vector3D& min, Math::Vector3D& max, const Math::Vector3D& coords, bool reset = false);

		CDPL_CHEM_API bool insideBoundingBox(const Math::Vector3D& min, const Math::Vector3D& max, const Math::Vector3D& coords);

		CDPL_CHEM_API bool isAromatic(const Fragment& ring, const MolecularGraph& molgraph, const Util::BitSet& arom_bond_mask);

		CDPL_CHEM_API bool isNotAromatic(const Fragment& ring, const MolecularGraph& molgraph);

		CDPL_CHEM_API bool containsFragmentWithBond(const FragmentList& frag_list, const Bond& bond);

		CDPL_CHEM_API bool containsFragmentWithMinSize(const FragmentList& frag_list, std::size_t min_size);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_UTILITYFUNCTIONS_HPP
 
