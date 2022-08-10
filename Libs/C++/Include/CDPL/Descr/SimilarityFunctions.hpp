/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SimilarityFunctions.hpp 
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
 * \brief Provides functions for the calculation of various similarity measures.
 */

#ifndef CDPL_DESCR_SIMILARITYFUNCTIONS_HPP
#define CDPL_DESCR_SIMILARITYFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Descr 
	{

		/**
		 * \addtogroup CDPL_DESCR_SIMILARITY_FUNCTIONS
		 * @{
		 */

		/**
		 * \brief Calculates the <em>Tanimoto Similarity Measure</em> [\ref CITB] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Tanimoto Similarity Measure</em> \f$ S_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    S_{ab} = \frac{N_{ab}}{N_a + N_b - N_{ab}} 
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
		 * \return The calculated similarity measure.
		 */
		CDPL_DESCR_API double calcTanimotoSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * \brief Calculates the <em>Cosine Similarity Measure</em> [\ref WCOS] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Cosine Similarity Measure</em> \f$ S_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    S_{ab} = \frac{N_{ab}}{\sqrt{N_a * N_b}} 
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
		 * \return The calculated similarity measure.
		 */
		CDPL_DESCR_API double calcCosineSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * \brief Calculates the <em>Euclidean Similarity Measure</em> [\ref GSIM] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Euclidean Similarity Measure</em> \f$ S_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    S_{ab} = \sqrt{\frac{N_{ab} + N_{!ab}}{N_a + N_b + N_{ab} + N_{!ab}}}
		 * \f] 
		 *
		 * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
		 * bits that are set only in the first bitset, \f$ N_b \f$ is the number of bits that are set only in the second bitset and
		 * \f$ N_{!ab} \f$ is the number of bits that are not set in both bitsets.
		 * 
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \return The calculated similarity measure.
		 */
		CDPL_DESCR_API double calcEuclideanSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * \brief Calculates the <em>Manhattan Similarity Measure</em> [\ref GSIM] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Manhattan Similarity Measure</em> \f$ S_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    S_{ab} = \frac{N_a + N_b}{N_a + N_b + N_{ab} + N_{!ab}}
		 * \f] 
		 *
		 * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
		 * bits that are set only in the first bitset, \f$ N_b \f$ is the number of bits that are set only in the second bitset and
		 * \f$ N_{!ab} \f$ is the number of bits that are not set in both bitsets.
		 * 
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \return The calculated similarity measure.
		 */
		CDPL_DESCR_API double calcManhattanSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * \brief Calculates the <em>Dice Similarity Measure</em> [\ref GSIM] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Dice Similarity Measure</em> \f$ S_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    S_{ab} = \frac{2 * N_{ab}}{N_a + N_b + 2 * N_{ab}} 
		 * \f] 
		 *
		 * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
		 * bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset.
		 * 
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \return The calculated similarity measure.
		 */
		CDPL_DESCR_API double calcDiceSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * \brief Calculates the <em>Tversky Similarity Measure</em> [\ref GSIM] for the given bitsets \a bs1 and \a bs2.
		 *
		 * The <em>Tversky Similarity Measure</em> \f$ S_{ab} \f$ is calculated by:
		 *
		 * \f[ 
		 *    S_{ab} = \frac{N_{ab}}{a * N_a + b * N_b + N_{ab}} 
		 * \f] 
		 *
		 * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
		 * bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset.
		 * \f$ a \f$ and \f$ b \f$ are bitset contribution weighting factors. 
		 *
		 * The <em>Tversky Measure</em> is asymmetric. Setting the parameters \f$ a = b = 1.0 \f$ is identical to using the <em>Tanimoto</em> measure.
		 *
		 * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
		 * to be zero.
		 *
		 * \param bs1 The first bitset.
		 * \param bs2 The second bitset.
		 * \param a Weights the contribution of the first bitset.
		 * \param b Weights the contribution of the second bitset.
		 * \return The calculated similarity measure.
		 */
		CDPL_DESCR_API double calcTverskySimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2, double a, double b);

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
		CDPL_DESCR_API std::size_t calcHammingDistance(const Util::BitSet& bs1, const Util::BitSet& bs2);
	
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
		CDPL_DESCR_API double calcEuclideanDistance(const Util::BitSet& bs1, const Util::BitSet& bs2);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_DESCR_SIMILARITYFUNCTIONS_HPP
