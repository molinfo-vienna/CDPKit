/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SimilarityFunctions.hpp 
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
 * \brief Provides functions for the calculation of various similarity measures.
 */

#ifndef CDPL_CHEM_SIMILARITYFUNCTIONS_HPP
#define CDPL_CHEM_SIMILARITYFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		/**
		 * \addtogroup CDPL_CHEM_SIMILARITY_FUNCTIONS
		 * @{
		 */

		/**
		 * \brief Calculates the <em>Tanimoto Similarity Coefficient</em> [\ref CITB] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Tanimoto Similarity Coefficient</em> \f$ T_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    T_{ab} = \frac{N_{ab}}{N_a + N_b - N_{ab}} 
		 * \f] 
		 *
		 * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
		 * bits that are set in the first bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset.
		 * 
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \return The calculated similarity coefficient.
		 */
		CDPL_CHEM_API double calcTanimotoSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * \brief Calculates the <em>Hamming Distance</em> [\ref WHAM, \ref CITB] between the bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Hamming Distance</em> \f$ D_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    D_{ab} = N_a + N_b
		 * \f] 
		 *
		 * where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset
		 * and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
		 * 
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \return The calculated distance.
		 */
		CDPL_CHEM_API std::size_t calcHammingDistance(const Util::BitSet& bs1, const Util::BitSet& bs2);
	
		/**
		 * \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Euclidean Distance</em> \f$ D_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    D_{ab} = \sqrt{N_a + N_b}
		 * \f] 
		 *
		 * where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset
		 * and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
		 * 
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \return The calculated distance.
		 */
		CDPL_CHEM_API double calcEuclideanDistance(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SIMILARITYFUNCTIONS_HPP
 
