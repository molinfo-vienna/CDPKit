/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.hpp 
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
 * \brief Declaration of miscellaneous utility functions.
 */

#ifndef CDPL_CHEM_UTILITYFUNCTIONS_HPP
#define CDPL_CHEM_UTILITYFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class Molecule;

		/**
		 * \addtogroup CDPL_CHEM_UTILITY_FUNCTIONS
		 * @{
		 */

		/**
		 * \brief Folds the bitset \a bs the specified number of times.
		 *
		 * Folding a bitset means that the lower and upper half of the bitset are combined
		 * by a logical OR operation to produce a new bitset which is half of the original
		 * size. This process is repeated the specified number of times. See also [\ref DTPFP].
		 *
		 * \param bs The bitset to fold.
		 * \param num_times The number of times the bitset has to be folded.
		 */
		CDPL_CHEM_API void foldBitSet(Util::BitSet& bs, std::size_t num_times);

		CDPL_CHEM_API Molecule::SharedPointer parseSMARTS(const std::string& smarts, bool init_qry = true);

		CDPL_CHEM_API bool parseSMARTS(const std::string& smarts, Molecule& mol, bool init_qry = true);

		CDPL_CHEM_API Molecule::SharedPointer parseSMILES(const std::string& smiles);

		CDPL_CHEM_API bool parseSMILES(const std::string& smiles, Molecule& mol);

		CDPL_CHEM_API void extendBoundingBox(Math::Vector3D& min, Math::Vector3D& max, const Math::Vector3D& coords, bool reset = false);

		CDPL_CHEM_API bool insideBoundingBox(const Math::Vector3D& min, const Math::Vector3D& max, const Math::Vector3D& coords);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_UTILITYFUNCTIONS_HPP
 
