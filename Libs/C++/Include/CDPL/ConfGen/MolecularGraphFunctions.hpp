/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_CONFGEN_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_CONFGEN_MOLECULARGRAPHFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

	namespace ForceField
	{

		class MMFF94InteractionData;
		class MMFF94InteractionParameterizer;
	}

	namespace ConfGen 
	{

		/**
		 * \addtogroup CDPL_CONFGEN_MOLECULAR_GRAPH_FUNCTIONS
		 * @{
		 */

		CDPL_CONFGEN_API std::size_t buildFragmentLinkBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, bool reset = true);

		CDPL_CONFGEN_API std::size_t buildRotatableBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, 
															bool het_h_rotors, bool reset = true);

		CDPL_CONFGEN_API std::size_t buildRotatableBondMask(const Chem::MolecularGraph& molgraph, const Util::BitSet& excl_bond_mask,
															Util::BitSet& bond_mask, bool het_h_rotors, bool reset = true);

		CDPL_CONFGEN_API std::size_t getRotatableBondCount(const Chem::MolecularGraph& molgraph, bool het_h_rotors);

		CDPL_CONFGEN_API unsigned int perceiveFragmentType(const Chem::MolecularGraph& molgraph); 

		CDPL_CONFGEN_API unsigned int parameterizeMMFF94Interactions(const Chem::MolecularGraph& molgraph, 
																	 ForceField::MMFF94InteractionParameterizer& parameterizer,
																	 ForceField::MMFF94InteractionData& param_data, unsigned int ff_type,
																	 bool strict, double estat_de_const, double estat_dist_expo); 

		CDPL_CONFGEN_API void setConformers(Chem::MolecularGraph& molgraph, const ConformerDataArray& conf_array);
		
		/**
		 * @}
		 */
	}
}

#endif // CDPL_CONFGEN_MOLECULARGRAPHFUNCTIONS_HPP
 
