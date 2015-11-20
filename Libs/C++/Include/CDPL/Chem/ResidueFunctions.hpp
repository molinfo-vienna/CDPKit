/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueFunctions.hpp 
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
 * \brief Declaration of functions for the lookup of meta-data associated with residues in biopolymers. 
 */

#ifndef CDPL_CHEM_RESIDUEFUNCTIONS_HPP
#define CDPL_CHEM_RESIDUEFUNCTIONS_HPP

#include <string>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_RESIDUE_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API const std::string& getResidueName(const std::string& code);

		CDPL_CHEM_API bool isStandardResidue(const std::string& code);

		CDPL_CHEM_API unsigned int getResidueType(const std::string& code);

		CDPL_CHEM_API const MolecularGraph* getResidueStructure(const std::string& code);
		
		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_RESIDUEFUNCTIONS_HPP
