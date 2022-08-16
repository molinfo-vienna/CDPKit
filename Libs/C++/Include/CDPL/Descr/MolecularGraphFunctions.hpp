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
 * \brief Declaration of functions that operate on Descr::MolecularGraph instances.
 */

#ifndef CDPL_DESCR_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_DESCR_MOLECULARGRAPHFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Descr/APIPrefix.hpp" 


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}
	
	namespace Descr 
	{

		/**
		 * \addtogroup CDPL_DESCR_MOLECULAR_GRAPH_FUNCTIONS
		 * @{
		 */

		CDPL_DESCR_API std::size_t calcTopologicalRadius(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API std::size_t calcTopologicalDiameter(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API double calcRingComplexity(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API double calcMolecularComplexity(const Chem::MolecularGraph& molgraph);
		
		CDPL_DESCR_API double calcKierShape1(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API double calcKierShape2(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API double calcKierShape3(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API std::size_t calcWienerIndex(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API double calcRandicIndex(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API std::size_t calcZagrebIndex1(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API std::size_t calcZagrebIndex2(const Chem::MolecularGraph& molgraph);

		CDPL_DESCR_API std::size_t calcTotalWalkCount(const Chem::MolecularGraph& molgraph);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_DESCR_MOLECULARGRAPHFUNCTIONS_HPP
 
