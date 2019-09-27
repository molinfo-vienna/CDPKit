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

#ifndef CDPL_CONFGEN_UTILITYFUNCTIONS_HPP
#define CDPL_CONFGEN_UTILITYFUNCTIONS_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Bond;
		class MolecularGraph;
		class Molecule;
	}

	namespace ForceField
	{

		class MMFF94InteractionData;
		class MMFF94InteractionParameterizer;
	}

	namespace ConfGen 
	{

		/**
		 * \addtogroup CDPL_CONFGEN_FUNCTIONS
		 * @{
		 */

		CDPL_CONFGEN_API bool isFragmentLinkBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph); 

		CDPL_CONFGEN_API std::size_t buildFragmentLinkBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& mask, bool reset = true);

		CDPL_CONFGEN_API unsigned int perceiveFragmentType(const Chem::MolecularGraph& molgraph); 

		CDPL_CONFGEN_API void prepareForConformerGeneration(Chem::Molecule& mol); 

		CDPL_CONFGEN_API void parameterizeMMFF94Interactions(const Chem::MolecularGraph& molgraph, ForceField::MMFF94InteractionParameterizer& parameterizer,
															 ForceField::MMFF94InteractionData& param_data, unsigned int ff_type); 
		
		/**
		 * @}
		 */
	}
}

#endif // CDPL_CONFGEN_UTILITYFUNCTIONS_HPP
 
